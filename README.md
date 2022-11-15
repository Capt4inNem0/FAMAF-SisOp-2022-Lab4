# Lab04-SisOp-2022: BigBrother FS
## Grupo N° 15
#### Integrantes:
- Esteban Druetta
- Sharry Facundo
- Collo Gaston
- Ivan Bainotti

# Indice
1. [Compilar el código](#id1)
2. [Respuestas](#id2)


## Compilar el código ##
---

### Installing necessary libraries: 

```sh
sudo apt-get install check make test libglib2.0-dev libfuse-dev 
```

### GIT USEFUL COMMANDS
#### ignoren los <> y reemplacen por lo correspondiente, por si tenian el problema del acces token

```sh
git clone https://<your_user_name>:<app_password>@bitbucket.org/sistop-famaf/so22lab4g15.git
```
## Crear Ejecutable fat-fuse / Compilar

```sh
cd path/to/where/fat-fuse.c_and_makefile_are/

make
```

## Montar

```sh
mkdir mnt

./fat-fuse ../imagenes/resources/bb_fs.img mnt
```
## Desmontar

```sh
umount mnt
```
 
## Respuestas <span id="id2"/>
---

### **1. Cuando se ejecuta el main con la opción -d, ¿qué se está mostrando en la pantalla?** ###

Cuando se ejecuta fat-fuse con la opcion -d se muestran en el log la informacion de DEBUG, que incluye llamadas a funciones, prints, comunicacion con la interfaz, o en nuestra implementación, donde se llame a DEBUG(). 
   
### **2. ¿Hay alguna manera de saber el nombre del archivo guardado en el cluster 157?** ###

Para encontrar el nombre, deberiamos iterar en el arbol de directorios obteniendo los clusters de cada archivo y fijarnos si el cluster 157 se encuentra entre estos.
   
### **3. ¿Dónde se guardan las entradas de directorio?¿Cuántos archivos puede tener adentro un directorio en FAT32?** ###

Las entradas se guardan en un espacio de memoria llamado cluster, en FAT32 tiene entradas de 32 Bytes y cada directorio puede tener hasta 65536 entradas, en nuestra implementacion de FAT-FUSE tenemos un maximo de 16 entradas (Sin contar el punto extra 7). 
   
### **4. Cuando se ejecuta el comando como ls -l, el sistema operativo, ¿llama a algún programa de usuario? ¿A alguna llamada al sistema? ¿Cómo se conecta esto con FUSE? ¿Qué funciones de su código se ejecutan finalmente** ###   

Al ejecutar ls -l se ejecutan estos pasos: Dependiendo del fs en que este montado se ejecuta una funcion definida en un modulo dentro del kernel (En nuestro caso FUSE y sus operaciones) * Se llama a la Syscall Opendir * Se leen los atributos con la operacion del FS correspondiente (Getattr) * Se leen las entradas de los directorios (Readdir) * Se llama a la Syscall Releasedir 
   
### **5. ¿Por qué tienen que escribir las entradas de directorio manualmente pero no tienen que guardar la tabla FAT cada vez que la modifican?** ###

Nosotros trabajamos sobre una abstraccion donde no es necesario actualizar la tabla FAT cada vez que se modifique, pero existe a mas bajo nivel un procedimiento encargado de esta sincronizacion 

### **6. Para los sistemas de archivos FAT32, la tabla FAT, ¿siempre tiene el mismo tamaño? En caso de que sí, ¿qué tamaño tiene?** ###
Si, tiene un tamaño fijo de 512MB.