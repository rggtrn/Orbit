#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    //ofAppGlutWindow window;
    
    //ofAppGlutWindow window;
   // window.setGlutDisplayString("rgba double depth alpha samples>=4");
    //ofSetupOpenGL(&window, 1440, 900, OF_WINDOW);

    //window.setGlutDisplayString("rgba alpha double stencil samples>=4");

//    window.setGlutDisplayString("rgba double samples>=4");
    //glutInitDisplayString( "rgba double samples>=4 ");
    //ofSetupOpenGL(1300,700,OF_WINDOW);
    //ofRunApp(new ofApp());
    ofGLFWWindowSettings settings;
    settings.decorated = false;
    //settings.setSize(1280, 720);

#if (defined(__APPLE__) && defined(__MACH__))

    settings.width = 1280;
    settings.height = 720;

#endif

    settings.windowMode =  OF_WINDOW;
    settings.windowMode =  OF_FULLSCREEN;
    ofCreateWindow(settings);
    
    //ofSetupOpenGL(1280,720,OF_WINDOW);
    ofRunApp(new ofApp());
    
}
