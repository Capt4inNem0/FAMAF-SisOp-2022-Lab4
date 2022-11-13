#include "big_brother.h"
#include "fat_volume.h"
#include "fat_table.h"
#include "fat_util.h"
#include <stdio.h>
#include <string.h>

int bb_is_log_file_dentry(fat_dir_entry dir_entry) {
    return strncmp(LOG_FILE_BASENAME, (char *)(dir_entry->base_name), 3) == 0 &&
           strncmp(LOG_FILE_EXTENSION, (char *)(dir_entry->extension), 3) == 0;
}

int bb_is_log_filepath(const char *filepath) {
    return strncmp(BB_LOG_FILE, filepath, 8) == 0;
}

int bb_is_log_dirpath(const char *filepath) {
    return strncmp(BB_DIRNAME, filepath, 15) == 0;
}

/* Searches for a cluster that could correspond to the bb directory and returns
 * its index. If the cluster is not found, returns 0.
 */
u32 search_bb_orphan_dir_cluster() {
    u32 bb_dir_start_cluster = 0;
    fat_volume vol = get_fat_volume();
    bool found_orphan = false;
    u32 aux_clauster = 0;

    for(u32 i = 3; i < 1000 && !found_orphan; i++){
        aux_clauster = fat_table_get_next_cluster(vol->table, i);
        
        if(fat_table_cluster_is_bad_sector(aux_clauster)){
            fat_file orphan_dir = fat_file_init_orphan_dir(BB_DIRNAME, vol->table, i);
            GList * children = fat_file_read_children(orphan_dir);

            fat_file file =  g_list_nth_data(children, 0);    
            //Condición: "Su primera entrada de directorio es un archivo con nombre fs.log"
            found_orphan = bb_is_log_file_dentry(file->dentry); 
            if (found_orphan) bb_dir_start_cluster = i;

            g_list_free_full(children,(GDestroyNotify) fat_file_destroy);
            
            fat_file_destroy(orphan_dir);
        }
    }
    return bb_dir_start_cluster;
}

/* Creates the /bb directory as an orphan and adds it to the file tree as 
 * child of root dir.
 */
static void bb_init_log_dir(u32 start_cluster) {
    fat_volume vol = get_fat_volume();
    fat_tree_node root_node = NULL;

    // Create a new file from scratch, instead of using a direntry like normally done.
    fat_file loaded_bb_dir = fat_file_init_orphan_dir(BB_DIRNAME, vol->table, start_cluster);

    // Add directory to file tree. It's entries will be like any other dir.
    root_node = fat_tree_node_search(vol->file_tree, "/");
    vol->file_tree = fat_tree_insert(vol->file_tree, root_node, loaded_bb_dir);
}

void bb_create_orphan_dir(){
    fat_volume vol = get_fat_volume();

    // Marcar el cluster como reservado
    u32 reserved_cluster = fat_table_get_next_free_cluster(vol->table);
    fat_table_set_next_cluster(vol->table, reserved_cluster, FAT_CLUSTER_BAD_SECTOR);

    // Inicializar el directorio huérfano
    bb_init_log_dir(reserved_cluster);
}


void bb_read_log(u32 start_cluster){
    fat_volume vol = get_fat_volume();

    bb_init_log_dir(start_cluster);
    // Buscar nodo y la fat_file del directorio huérfano 
    fat_tree_node orphan_dir_node = fat_tree_node_search(vol->file_tree, BB_DIRNAME);
    fat_file orphan_dir_file = fat_tree_get_file(orphan_dir_node);

    // Leer fs.log del disco e insertarlo en el árbol de directorios
    GList * children = fat_file_read_children(orphan_dir_file);
    fat_file log_file =  g_list_nth_data(children, 0);

    fat_tree_insert(vol->file_tree, orphan_dir_node, log_file);
}