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
