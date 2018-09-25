
# Orbit

Text / Sound / Video | OpenFrameworks + SuperCollider

![holaMundo](img/holaMundo.gif)

### Orbit en acción 

[RGGTRN - moombahcode++geom](https://vimeo.com/289901460)

## Instalación

Orbit requiere una versión compilada de OF y los siguientes addons: [ofxCenteredTrueTypeFont](https://github.com/armadillu/ofxCenteredTrueTypeFont), [ofxPostGlitch](https://github.com/maxillacult/ofxPostGlitch), [ofxSyphon](https://github.com/astellato/ofxSyphon) (sólamente en mac) y una rama específica de la extensión [ofxHapPlayer](https://github.com/bangnoise/ofxHapPlayer):

Para instalar el códec Hap: https://github.com/Vidvox/hap-qt-codec/releases/

`$ git clone https://github.com/bangnoise/ofxHapPlayer`

`$ cd addons/ofxHapPlayer`

`$ git checkout libavformat-OF-0.9`

Para compilar en Linux es necesario eliminar la línea ofxSyphon del archivo addons.make.

### Control OSC

Es posible controlar los parámetros de Orbit con [PiranhaLib](https://github.com/rggtrn/PiranhaLib).

PirS.start("127.0.0.1", 5612) // Para iniciar en modo local

PirV // acciones de video ej: PirV.load

### Videos en Hap

La conversión de videos es posible con ffmpeg. En macOS es posible instalar FFmpeg con soporte para hap con [brew](https://brew.sh/index_es):

`brew install ffmpeg --with-snappy`

* Para convertir videos en Hap

`ffmpeg -i yourSourceFile.mov -c:v hap outputName.mov`

* Para convertir videos en Hap Aplha

`ffmpeg -i yourSourceFile.mov -c:v hap -format hap_alpha outputName.mov`

* Para instrucciones más detalladas en inglés: https://gist.github.com/dlublin/e4585b872dd136ae88b2aa51a6a89aac
