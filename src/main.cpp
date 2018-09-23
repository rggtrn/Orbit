#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
        
    ofSetupOpenGL(1024,768,OF_WINDOW);
    ofAppGlutWindow window;

    window.setGlutDisplayString("rgba double samples>=4");
    
    ofRunApp(new ofApp());
     
}
