
# PiranhaVivo / Orbit

PV / Orbit es un proyecto que sirve para mezclar videos en vivo. PV se controla por medio del protocolo OSC y persigue la ligereza y la eficiencia como premisas. De entre los desarrollos que insipiran a PV / Orbit están [CineVivo](https://github.com/essteban/CineVivo) y Fluxus. Para ejecutarlo es necesario utilizar un programa o dispositivo externo que pueda enviar mensajes OSC. Actualmente no es posible enviar mensajes de control desde el mismo PV / Orbit (trabajo futuro) sin embargo es posible de una forma amigable a través de PiranhaLib (SuperCollider). 

## PV / Orbit en acción

[RGGTRN - moombahcode++geom](https://vimeo.com/289901460)

## Instalación

Para instalar el códec Hap: https://github.com/Vidvox/hap-qt-codec/releases/

PV / Orbit corre en Linux y Mac y requiere tener una versión compilada de OpenFrameworks.

Addons necesarios para compilar PV / Orbit: ofxCenteredTrueTypeFont, ofxOsc, ofxPostGlitch ofxSyphon (sólamente en mac) y una rama específica de la extensión ofxHapPlayer:

`$ git clone https://github.com/astellato/ofxSyphon`

`$ git clone https://github.com/bangnoise/ofxHapPlayer`

`$ cd addons/ofxHapPlayer`

`$ git checkout libavformat-OF-0.9`

Una vez realizado esto, es posible compilar con Xcode o make, dependiendo de la arquitectura. Para compilar en Linux es necesario eliminar la línea ofxSyphon del archivo addons.make.

## Uso

PV utiliza el códec Hap, con lo cual es posible utilizar de forma eficiente videos con y sin opacidad.

### Videos en Hap

La conversión de videos es posible con ffmpeg. En macOS es posible instalar FFmpeg con soporte para hap con [brew](https://brew.sh/index_es):

`brew install ffmpeg --with-snappy`

* Para convertir videos en Hap

`ffmpeg -i yourSourceFile.mov -c:v hap outputName.mov`

* Para convertir videos en Hap Aplha

`ffmpeg -i yourSourceFile.mov -c:v hap -format hap_alpha outputName.mov`

* Para instrucciones más detalladas en inglés: https://gist.github.com/dlublin/e4585b872dd136ae88b2aa51a6a89aac

### Control OSC

Es posible controlar los parámetros de PV / Orbit con [PiranhaLib](https://github.com/rggtrn/PiranhaLib).

PirS.start // Para iniciar localmente
PirS.start("direcciónIP", puerto) // Inicio en una red local. Dirección IP es la dirección de la máquina que corre PV / Orbit y el puerto es 5612. Este parámetro se puede modificar desde PV / Orbit

/load, pista, video | PirV.load(pista, "video") // donde pista es un parámetro que va de 0-10 y video un archivo existente en la carpeta bin/data/videos.
/speed, pista, velocidad | PirV.speed(pista, velocidad) // donde la velocidad normal es 1, -1 es reversa y 0 es detenido. Velocidad acepta flotantes.
/pos, pista, posX, posY, posZ | PirV.pos(pista, posX, posY, posZ) // Posición del objeto
/rot, pista, posX, posY, posZ | PirV.rot(pista, rotX, rotY, rotZ) // Rotación del objeto
