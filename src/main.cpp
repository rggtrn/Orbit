#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofAppGlutWindow window;

    window.setGlutDisplayString("rgba double depth alpha samples>=8");

//    window.setGlutDisplayString("rgba double samples>=4");
    //glutInitDisplayString( "rgba double samples>=4 ");
    ofSetupOpenGL(1024,768,OF_WINDOW);

    ofRunApp(new ofApp());
     
}
