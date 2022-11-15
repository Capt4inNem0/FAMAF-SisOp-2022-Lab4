# Lab04-SisOp-2022
## Grupo N° 15
#### Integrantes:
- Esteban Druetta
- Sharry Facundo
- Collo Gaston
- Ivan Bainotti

# Indice
1. [Introducción](#id1)
2. [Técnicas de Programación](#id2)
3. [Herramientas de Programación](#id3)
4. [Setup](#id4)
5. [Desarrollo](#id5)
6. [Respuestas](#id6)

# Introducción <span id="id1"/>
En este laboratorio 

# Técnicas de Programación <span id="id2"/>
 
# Herramientas de Programación <span id="id3"/>
Se utilizó C-Lion como IDE, y

# Setup <span id="id4"/>

## Requirements:

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
 
## Desarrollo <span id="id5"/>

## Respuestas <span id="id6"/>
1) Cuando se ejecuta fat-fuse con la opcion -d se muestran en el log la informacion de DEBUG, que incluye llamadas a funciones,
   prints, comunicacion con la interfaz, o en nuestra implementación, donde se llame a DEBUG().
2) Para encontrar el nombre, deberiamos iterar en el arbol de directorios obteniendo los clusters de cada archivo y fijarnos si el cluster 157 se encuentra entre estos.
3) Las entradas se guardan en un espacio de memoria llamado cluster, en FAT32 tiene entradas de 32 Bytes y cada directorio puede tener hasta 65536 entradas, en nuestra implementacion de FAT-FUSE tenemos un maximo de 16 entradas (Sin contar el punto extra 7).
4) Al ejecutar ls -l se ejecutan estos pasos:
Dependiendo del fs en que este montado se ejecuta una funcion definida en un modulo dentro del kernel (En nuestro caso FUSE y sus operaciones)
    * Se llama a la Syscall Opendir
    * Se leen los atributos con la operacion del FS correspondiente (Getattr)
    * Se leen las entradas de los directorios (Readdir)
    * Se llama a la Syscall Releasedir
6) Nosotros trabajamos sobre una abstraccion donde no es necesario actualizar la tabla FAT cada vez que se modifique, pero existe a mas bajo nivel un procedimiento encargado de esta sincronizacion
7) Si, tiene un tamaño fijo de 512MB.