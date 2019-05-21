#pragma once

#include "ofMain.h"
#include "ofxGLEditor.h"
#include "ofxHapPlayer.h"
#include "ofxAssimpModelLoader.h"
#include "ofxPostGlitch.h"
#include "ofxOsc.h"

#define LIM 10
#define LIM2 3

class ofApp : public ofBaseApp, public ofxGLEditorListener {

public:
  void setup();
  void update(); 
  void draw();
  void drawScene();
  
  void keyPressed(int key);
  void windowResized(int w, int h);
  
  /// ofxGLEditor events
  void saveFileEvent(int &whichEditor);
  void openFileEvent(int &whichEditor);
  void executeScriptEvent(int &whichEditor);
  void evalReplEvent(const string &text);
  
  ofxGLEditor editor;

  int orbitON;
  
  std::vector<string> texto;
  ofEasyCam camera;
  std::vector<string> lineas;
  float orbitX;
  float orbitY;

  ofxEditorSyntax orbitSyntax;
  ofxEditorColorScheme colorScheme;

  // Primitivos
  
  ofSpherePrimitive sphere;
  ofIcoSpherePrimitive icoSphere;
  ofPlanePrimitive plane;
  ofCylinderPrimitive cylinder;
  ofConePrimitive cone;
  ofBoxPrimitive box;

  ofColor colorLight2[LIM2];

  int clR[LIM2];
  int clG[LIM2];
  int clB[LIM2];
  
  ofLight pointLight2[LIM2];

  float lightSpeedX[LIM2];
  float lightSpeedY[LIM2];
  float lightSpeedZ[LIM2];
  float lightAmpX[LIM2];
  float lightAmpY[LIM2];
  float lightAmpZ[LIM2];

  int drawLight[LIM2];

  int lightON; 

  int sphereON;
  int icoON;
  int planeON;
  int cylinderON;
  int coneON;
  int boxON;

  ofxHapPlayer videoLC[LIM];

  int vRotX[LIM];
  int vRotY[LIM];
  int vRotZ[LIM];

  float vScaleX[LIM];
  float vScaleY[LIM];
  float vScaleZ[LIM];

  float vX[LIM];
  float vY[LIM];
  float vZ[LIM];

  int vOpacity[LIM];
  
  float vSpeed[LIM];

  int videoON;

  string textToExe;

  int numLines = 0;
  ofVec3f centro;
  float camdistance;

  ofxAssimpModelLoader multiModel[LIM];
  //ofTexture asteroid;
  ofTexture texturas[LIM];
  int multiModelON;
  int multiModelX[LIM];
  int multiModelY[LIM];
  int multiModelZ[LIM];
  int multiModelRotX[LIM];
  int multiModelRotY[LIM];
  int multiModelRotZ[LIM];
  float multiModelScale[LIM];
  
  int textureON;
  int materialON;
  int videoTex; 

  // luces

  ofLight pointLight;
  ofColor lightColor;
  float colorHue;
  ofColor materialColor;
  ofMaterial material;

  ofxPostGlitch myGlitch;

  ofFbo fbo;
  int glitchON; 

  bool convergence;
  bool glow;
  bool shaker;
  bool cutslider;
  bool twist;
  bool outline;
  bool noise;
  bool slitscan;
  bool swell;
  bool invert;

  bool highcontrast;
  bool blueraise;
  bool redraise;
  bool greenraise;
  bool blueinvert;
  bool redinvert;
  bool greeninvert;

  int retro;
  float position;
  ofTexture screenImage;
  float retroX;
  float retroY;
  int colorBackground; 
  int fboON;

  ofShader shader;
  ofxEditorSyntax syntax;
  int shaderON;
  ofFbo shaderFbo;
  string shaderName;

  ofxOscReceiver reciever;
  ofxOscSender sender;

};
