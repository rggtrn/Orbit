# Orbit

## Introducción 

Orbit es un proyecto construido en OpenFrameworks que busca ser una extensión visual para el performance audiovisual. Orbit adscribe al paradigma del live coding: través de Orbit es posible modificar aspectos visuales desde la misma pantalla. También puede recibir mensajes OSC por medio de una red. Surge de la curiosidad por explorar audio y video simultáneamente. 

Actualmente es posible utilizar Orbit para enviar unos mensajes sencillos al motor de audio de SuperCollider. 

Orbit se inspira en los siguientes proyectos: 

[Fluxus](http://www.pawfal.org/fluxus)

[Hydra](https://github.com/ojack/hydra) 

[Estuary](https://github.com/dktr0/estuary) 

[CineVivo](https://github.com/essteban/CineVivo)

## Objetivos

Además de funcionar como una herramienta para extender la interpretación audiovisual a través de la computadora, Orbit es un pretexto para la investigación y una invitación a la exploración del software como objeto de conocimiento. 

## Instalación

Orbit ha sido probado en Linux y Mac con la versión 0.10.1 de OpenFrameworks. La cámara tiene comportamientos extraños en versiones anteriores y con el sistema operativo Linux. Hasta el momento no ha sido probado en Windows.

Para compilar Orbit es necesario descargar OpenFrameworks de [github](https://github.com/openframeworks/openFrameworks) o de la [página oficial](https://openframeworks.cc/download/) dependiendo del Sistema Operativo.

Es necesario compilar el archivo. Para el caso de Windows y Mac es necesario contruir el proyecto con Project Generator. 

### Addons

Para que la compilación de Orbit sea exitosa es necesario descargar los addons siguientes: 

Para instalar el códec Hap: https://github.com/Vidvox/hap-qt-codec/releases/

`$ git clone https://github.com/bangnoise/ofxHapPlayer`

`$ cd addons/ofxHapPlayer`

`$ git checkout libavformat-OF-0.9`

Para todos los casos, es necesario utilizar un [fork](https://github.com/bolkaaa/ofxGLEditor) de ofxGLEditor

[ofxPostGlitch](https://github.com/maxillacult/ofxPostGlitch)

### Compilación

Para linux es necesario entrar a la carpeta del proyecto y: 

`make`

`make RunRelease`

Para el caso de MacOS es necesario abrir el proyecto con XCode. 

### Indicaciones

Una vez compilado, es posible acceder a un archivo de instrucciones al teclear Ctrl + 2. 

## Videos en Hap

Es posible transcodificar videos Hap con ffmpeg. En macOS es posible instalar ffmpeg con soporte para hap con [brew](https://brew.sh/index_es):

`brew install ffmpeg --with-snappy`

* Para convertir videos en Hap

`ffmpeg -i yourSourceFile.mov -c:v hap outputName.mov`

* Para convertir videos en Hap Aplha

`ffmpeg -i yourSourceFile.mov -c:v hap -format hap_alpha outputName.mov`

* Para instrucciones más detalladas en inglés: https://gist.github.com/dlublin/e4585b872dd136ae88b2aa51a6a89aac

### Recursos Externos y Bibliografía seleccionada

[A free, shared visual playground in the browser: Olivia Jack talks Hydra](http://cdm.link/2019/02/hydra-olivia-jack/)

[Hydra](http://cdm.link/2019/02/hydra-olivia-jack/)

[Estuary: Browser-based Collaborative Projectional Live Coding of Musical Patterns. David Ogborn, Jamie Beverley, Luis N. Del Angel, Eldad Tsabary y Alex McLean](https://iclc.livecodenetwork.org/2017/cameraReady/ICLC_2017_paper_78.pdf)

[Estuary](http://intramuros.mcmaster.ca:8002/)

[Bellacode: localized textual interfaces for live coding music. Luis N. Del Angel, Marianne Teixido, Emilio Ocelotl, Ivanka Cotrina y David Ogborn](https://iclc.livecodenetwork.org/2019/papers/paper111.pdf)

[Fuck off Google, en A Nuestros Amigos. Comité Invisible](http://mexico.indymedia.org/IMG/pdf/a_nuestros_amigos_-_comite_invisible.pdf)

[En Defensa de la Imagen Pobre. Hito Steyerl](https://monoskop.org/images/7/72/Steyerl_Hito_Los_condenados_de_la_pantalla.pdf#page=18)

[Curso de OpenFrameworks (ES). Patricio González Vivo](https://github.com/patriciogonzalezvivo/cursoOF)

[El libro de los Shaders (ES). Patricio González Vivo y Jen Lowe](https://thebookofshaders.com/?lan=es)

[Curso de SuperCollider del Taller de Audio del Centro Multimedia (ES). Ernesto Romero y Ezequiel Netri](http://cmm.cenart.gob.mx/tallerdeaudio/cursos/cursocollider/textos/curso%20de%20supercollider%20principiantes.pdf)

[ofBook](https://openframeworks.cc/ofBook/chapters/foreword.html)

[OpenFrameworks](https://openframeworks.cc/)

[SuperCollider](https://supercollider.github.io/)
