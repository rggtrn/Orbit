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
    ofSetupOpenGL(1024,768,OF_WINDOW);

    ofRunApp(new ofApp());
     
}
