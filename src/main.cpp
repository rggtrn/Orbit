#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
  //ofSetupOpenGL(1024,768,OF_WINDOW); // GL context esto es lo unico que estaba activado antes.
  ofGLFWWindowSettings settings;
  settings.windowMode = OF_WINDOW;
  settings.setSize(1024, 768);

  settings.decorated = false;

  ofCreateWindow(settings);
  
  // this kicks off the running of my app
  // can be OF_WINDOW or OF_FULLSCREEN
  // pass in width and height too:
  ofRunApp(new ofApp());

}
