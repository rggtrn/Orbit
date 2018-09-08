#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    
    ofGLFWWindowSettings settings;
    //settings.width = 600;
    //settings.height = 600;
    settings.setPosition(ofVec2f(300,0));
    settings.resizable = true;
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
    
    //settings.width = 300;
    //settings.height = 300;
    settings.setPosition(ofVec2f(0,0));
    settings.resizable = true;
    
    // uncomment next line to share main's OpenGL resources with gui
    settings.shareContextWith = mainWindow;
    shared_ptr<ofAppBaseWindow> guiWindow = ofCreateWindow(settings);
    guiWindow->setVerticalSync(false); /// esto estaba false
    
    shared_ptr<ofApp> mainApp(new ofApp);
    mainApp->setupGlitch();
    ofAddListener(guiWindow->events().draw,mainApp.get(),&ofApp::drawGlitch);
    
    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();
    
    
//    #if (defined(__APPLE__) && defined(__MACH__))

    /*
    ofSetupOpenGL(1024,768,OF_WINDOW); // GL context esto es lo unico que estaba activado antes.
    ofAppGlutWindow window;

    window.setGlutDisplayString("rgba double samples>=4");
    */
//    #endif

//    #if (defined(__LINUX__) && defined(__MACH__))

//    ofGLFWWindowSettings settings;
   
//    settings.windowMode = OF_WINDOW;
//    settings.setSize(1024, 768);

//    settings.decorated = false;

//    ofCreateWindow(settings);
    
//    #endif
    
    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    
    /*
    ofRunApp(new ofApp());
     */
}
