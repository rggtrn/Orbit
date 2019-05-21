#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

  ofSetVerticalSync(true);
  ofEnableSmoothing();
  ofEnableAntiAliasing();
  ofSetWindowTitle("Orbit");

  ofSetFrameRate(30);
  ofBackground(0);
  
  // let's see what's going on inside
  ofSetLogLevel("ofxGLEditor", OF_LOG_VERBOSE);
	
  // setup the global editor font before you do anything!
  ofxEditor::loadFont("fonts/PrintChar21.ttf", 24);
  
  // set a custom Repl banner & prompt (do this before setup())
  ofxRepl::setReplBanner("Orbit Repl");
  ofxRepl::setReplPrompt("prompt> ");
  
  // setup editor with event listener
  editor.setup(this);
  
  // make some room for the bottom editor info text
  editor.resize(ofGetWidth(), ofGetHeight()-ofxEditor::getCharHeight());

  orbitSyntax.setLang("Orbit");
  orbitSyntax.addFileExt("orbit"); // associate .lua with Lua
  orbitSyntax.setSingleLineComment("//");
  orbitSyntax.setMultiLineComment("/*", "*/");
  orbitSyntax.setStringLiteral("[[", "]]");
  orbitSyntax.setWord("function", ofxEditorSyntax::KEYWORD);
  orbitSyntax.setWord("end", ofxEditorSyntax::KEYWORD);
  orbitSyntax.setWord("print", ofxEditorSyntax::FUNCTION);
  editor.getSettings().addSyntax(&orbitSyntax);

  colorScheme.setNumberColor(ofColor(255, 150, 255));
  colorScheme.setStringColor(ofColor(1, 255, 255));
  colorScheme.setCommentColor(ofColor(72, 255, 94));
  colorScheme.setKeywordColor(ofColor::fuchsia);
  colorScheme.setTypenameColor(ofColor::red);
  colorScheme.setFunctionColor(ofColor::green);
  colorScheme.setTextColor(ofColor(255)); // main text color

  editor.setColorScheme(&colorScheme);
  // editor.openFile("test.orbit");
  // setup GLSL syntax via xml file
  syntax.loadFile("glslSyntax.xml"); // lang: GLSL, file exts: frag & vert
  editor.getSettings().addSyntax(&syntax);
  editor.getSettings().printSyntaxes();

  
  // open & load a file into the current editor (1)
  editor.openFile("hello.orbit", 1);
  //ofLogNotice() << "number of lines: " << editor.getNumLines(1);
  editor.openFile("intl.orbit", 2);
  //ofLogNotice() << "number of lines: " << editor.getNumLines(2);
  
  // change multi editor settings, see ofxEditorSettings.h for details
  //editor.getSettings().setCursorColor(ofColor::blue); // current pos curso
//  editor.getSettings().setAlpha(0.1); // main text, cursor, & highlight alpha
  
	// other settings
  editor.setLineWrapping(true);
  editor.setLineNumbers(true);
  editor.setAutoFocus(false);
  
  // move the cursor to a specific line
  //editor.setCurrentLine(5);
  //ofLogNotice() << "current line: " << editor.getCurrentLine();
  orbitON = 0;
  camera.setDistance(200); 

  pointLight.setDiffuseColor( ofColor(255.f, 255.f, 255.f));

  // specular color, the highlight/shininess color //
  pointLight.setSpecularColor( ofColor(255.f, 255.f, 255.f));
  
  // shininess is a value between 0 - 128, 128 being the most shiny //
  material.setShininess( 128 );

  // colorHue = ofRandom(0, 250);

  //lightColor.setBrightness( 180.f );
  // lightColor.setSaturation( 150.f );

  //materialColor = ofColor(255, 255, 255, 255); 
  
  //materialColor.setBrightness(255.f);
  //materialColor.setSaturation(255);
  pointLight.setPosition(camera.getPosition());
  material.setSpecularColor(materialColor);
  
  for(int i = 0; i < LIM; i++){
    vOpacity[i] = 255;
    multiModelX[i] = 0;
    multiModelY[i] = 0;
    multiModelZ[i] = 0;
    multiModelRotX[i] = 0;
    multiModelRotY[i] = 0;
    multiModelRotZ[i] = 0;
    multiModelScale[i] = 1;
    texturas[i].enableMipmap();
    texturas[i].setTextureWrap(GL_REPEAT, GL_REPEAT);
    texturas[i].setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
  }

  // multilight

  lightON = 1;
    
  for(int i = 0; i < LIM2; i++){
    clR[i] = 255;
    clG[i] = 255;
    clB[i] = 255;
    colorLight2[i] = ofColor(clR[i], clG[i], clB[i]);
    lightSpeedX[i] = 1;
    lightSpeedY[i] = 1;
    lightSpeedZ[i] = 1;
    lightAmpX[i] = 200; 
    lightAmpY[i] = 200; 
    lightAmpZ[i] = 200; 
  }
  
  ofSetSmoothLighting(true);
  
  pointLight.enable();

  //fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
  fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB32F_ARB); 
  //fbo.getTextureReference().setTextureMinMagFilter(GL_NEAREST,GL_NEAREST);
  myGlitch.setup(&fbo);
  convergence = false;
  glow = false;
  shaker = false;
  cutslider = false;
  twist = false;
  outline = false;
  noise = false;
  slitscan = false;
  swell = false;
  invert = false;
  highcontrast = false;
  blueraise = false;
  redraise = false;
  greenraise = false;
  blueinvert = false;
  redinvert = false;
  greeninvert = false;
  glitchON = 0;
  
  retro = 0;
  position = 0;
  screenImage.allocate(960*2, 560*2, GL_RGBA);
  retroX = 0;
  retroY = 0;

  /*    shader.load("Shaders/shaderExample");
	shaderFbo.allocate(ofGetWidth(), ofGetHeight());
	shaderFbo.begin();
	ofClear(0, 0, 0, 0);
	shaderFbo.end();
	shaderON = 1; */

  shaderON = 0; 
  #ifdef TARGET_OPENGLES
  shader.load("shaders_gles/noise.vert","shaders_gles/noise.frag");
  #else
  if(ofIsGLProgrammableRenderer()){
  shader.load("shaders_gl3/noise.vert", "shaders_gl3/noise.frag");
  }else{
    shader.load("shaders/noise.vert", "shaders/noise.frag");
    }
    #endif

  shaderName = "noise";
}

//--------------------------------------------------------------
void ofApp::update() { 

  pointLight.setPosition(camera.getPosition());

  for(int i = 0; i < LIM2; i++){
    pointLight2[i].setPosition(sin(ofGetElapsedTimef()*lightSpeedX[i]) * lightAmpX[i], sin(ofGetElapsedTimef()*lightSpeedY[i]) * lightAmpY[i], sin(ofGetElapsedTimef()*lightSpeedZ[i]) * lightAmpZ[i]);
  }
  
  for(int i = 0; i < LIM2; i++){
    
    pointLight2[i].setDiffuseColor( colorLight2[i] );
    pointLight2[i].setSpecularColor( colorLight2[i] );

  }

  if(retro == 1){
  position = 500 + 250 * sin(ofGetElapsedTimef() * 28);
  screenImage.loadScreenData(0,0,ofGetWidth(), ofGetHeight());
  }

  if(glitchON == 1){
    drawScene();
  }

  /*
  if(shaderON == 1 && glitchON == 1){
  shaderFbo.begin();
  ofClear(0, 0, 0, 0);
  shader.begin();  
  shader.setUniformTexture("tex0", fbo.getTextureReference(), 0);
  shader.setUniform1f("time", ofGetElapsedTimef());
  shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
  fbo.draw(0, 0);
  shader.end();
  shaderFbo.end();
  }
  */
}

//--------------------------------------------------------------
void ofApp::draw() {

  ofSetColor(255, 255, 255);
  ofDisableAlphaBlending();
  ofSetRectMode(OF_RECTMODE_CORNER);
          
  if(glitchON == 1 && colorBackground ==1){
    ofBackgroundGradient(colorLight2[1], colorLight2[2],  OF_GRADIENT_LINEAR);
  }
    
  myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE, convergence);
  myGlitch.setFx(OFXPOSTGLITCH_GLOW, glow);
  myGlitch.setFx(OFXPOSTGLITCH_SHAKER, shaker);
  myGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER, cutslider);
  myGlitch.setFx(OFXPOSTGLITCH_TWIST, twist);
  myGlitch.setFx(OFXPOSTGLITCH_OUTLINE, outline);
  myGlitch.setFx(OFXPOSTGLITCH_NOISE, noise);
  myGlitch.setFx(OFXPOSTGLITCH_SLITSCAN, slitscan);
  myGlitch.setFx(OFXPOSTGLITCH_SWELL, swell);
  myGlitch.setFx(OFXPOSTGLITCH_INVERT, invert);
  myGlitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, highcontrast);
  myGlitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE, blueraise);
  myGlitch.setFx(OFXPOSTGLITCH_CR_REDRAISE, redraise);
  myGlitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE, greenraise);
  myGlitch.setFx(OFXPOSTGLITCH_CR_BLUEINVERT, blueinvert);
  myGlitch.setFx(OFXPOSTGLITCH_CR_REDINVERT, redinvert);
  myGlitch.setFx(OFXPOSTGLITCH_CR_GREENINVERT, greeninvert);
  
  myGlitch.generateFx();

  /*
  if(glitchON == 1 && shaderON == 1){
    shaderFbo.draw(0, 0); 
  }
  */
  
  if(glitchON == 1){
    fbo.draw(0, 0);
  }

  if(glitchON == 0){
  drawScene(); 
  }
  
}

//--------------------------------------------------------------
void ofApp::drawScene() {

  if(glitchON == 1){
  fbo.begin();
  ofClear(0);
  }

  if(shaderON == 1){
    ofEnableLighting(); 
    //ofSetColor(245, 58, 135);
    //ofFill();
    shader.begin();
    shader.setUniform1f("timeValX", ofGetElapsedTimef() * 0.1 );
    shader.setUniform1f("timeValY", -ofGetElapsedTimef() * 0.18 );
    
    //we also pass in the mouse position 
    //we have to transform the coords to what the shader is expecting which is 0,0 in the center and y axis flipped. 
    shader.setUniform2f("mouse", mouseX - ofGetWidth()/2, ofGetHeight()/2-mouseY );
  }
   
  editor.getSettings().setAlpha(1); // main text, cursor, & highlight alpha
  camera.lookAt(centro);

  ofSetRectMode(OF_RECTMODE_CENTER);

  //  if(boxON == 1){
  //  ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
  
  ofDisableDepthTest();
  ofEnableArbTex(); 
    
  if(retro == 1){
    screenImage.draw(retroX+ofGetWidth()/2, retroY+ofGetHeight()/2, ofGetWidth()-160, ofGetHeight()-160);
  }

  ofEnableDepthTest(); 
    
  camera.begin();

  ofDisableLighting(); 
  //pointLight.disable(); 
  //if(videoON == 1){
  for(int i = 0; i < LIM; i++){      
     //ofEnableAlphaBlending();
    ofPushMatrix(); 
    ofRotateX(vRotX[i]);
    ofRotateY(vRotY[i]);
    ofRotateZ(vRotZ[i]);
    ofSetColor(255,vOpacity[i]);
    ofScale(vScaleX[i] * 0.25,vScaleY[i] * 0.25, vScaleZ[i] * 0.25);
    ofTranslate((vX[i]),vY[i], vZ[i]);
    videoLC[i].draw(0, 0);
    ofPopMatrix();
   }

  ofEnableLighting();
  // pointLight.enable();
  //pointLight.draw();
  //pointLight2.draw();
  //pointLight3.draw();
  
  for(int i = 0; i < LIM2; i++){
    if(drawLight[i] == 1){
      pointLight2[i].draw(); 
    }
  }
  
  //for(int i = 0; i < LIM2; i++){
  //   pointLight2[i].draw();
   //  pointLight2[i].enable();
  // }

   material.begin();
  
   if(orbitON == 1){
     camera.orbit(ofGetElapsedTimef()*orbitX, ofGetElapsedTimef()*orbitY, camera.getDistance(), ofVec3f(0, 0, 0));
  }
   
   if(boxON == 1){
     box.draw();
   } 

   if(planeON == 1){
     plane.draw();
   }

   if(cylinderON== 1){
     cylinder.draw();
   }
   
  if(icoON== 1){
    icoSphere.draw();
  }
  
  if(sphereON== 1){
    sphere.draw();
  }

  if(coneON== 1){
    cone.draw();
  }

  // multimodelos
    
    for(int i = 0; i < LIM; i++){
        
      ofTexture *texture[i] = {0};
      ofShader *shader[i] = {0};
      
      if(videoTex == 1){
	// aqui van los videos como texturas
        //texture[i] = tempPlayer[i].getTexture();
	//shader[i] = tempPlayer[i].getShader();
      }
      
      ofPushMatrix();
      
      ofRotateX(multiModelRotX[i]);
      ofRotateY(multiModelRotY[i]);
      ofRotateZ( multiModelRotZ[i]);
      ofScale(multiModelScale[i] * 0.25,multiModelScale[i] * 0.25, multiModelScale[i] * 0.25);
      ofTranslate(0, 0, 0);
      multiModel[i].setPosition(multiModelX[i] * 1, multiModelY[i] * 1, multiModelZ[i]);
        
      if(textureON == 1){
	texturas[i].bind();
      }
        
      if(videoTex == 1){
	if (shader[i]){
	  shader[i]->begin();
	}
	texture[i]->bind();
      }
        
      multiModel[i].drawFaces();
        
      if(textureON == 1){
	texturas[i].unbind();
      }
        
      if(videoTex == 1){
	texture[i] -> unbind();
	if (shader[i]){
	  shader[i]->end();
	}
      }  
      ofPopMatrix();
    }

    material.end(); 
    camera.end();
  //}
  
  ofSetRectMode(OF_RECTMODE_CORNER);
  
  //ofTranslate(0, 0);
  ofDisableDepthTest();
  ofDisableLighting();

if(shaderON == 1){
   shader.end();
  }
  
  editor.draw();
  
  if(retro == 1){
    screenImage.loadScreenData(0,0, ofGetWidth(), ofGetHeight());
  }

  if(glitchON == 1){
    fbo.end(); 
  }
   
  // draw current editor info using the same font as the editor
  if(!editor.isHidden() && editor.getCurrentEditor() > 0) {
    
    int bottom = ofGetHeight()-ofxEditor::getCharHeight();
    int right = ofGetWidth()-ofxEditor::getCharWidth()*7; // should be enough room
    ofSetColor(ofColor::gray);
    
    // draw the current editor num
    editor.drawString("Editor: "+ofToString(editor.getCurrentEditor()),
		      0, bottom);
    
    // draw the current line & line pos
    editor.drawString(ofToString(editor.getCurrentLine()+1)+","+
		      ofToString(editor.getCurrentLinePos()),
		      right, bottom);
  }
  
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	
	// note: when using CTRL as the modifier key, CTRL + key might be an ascii
	// control char so check for both the char 'f' and 6, the ascii value for
	// CTRL + f, see also: http://ascii-table.com/control-chars.php
	bool modifier = ofGetKeyPressed(ofxEditor::getSuperAsModifier() ? OF_KEY_SUPER : OF_KEY_CONTROL);
	if(modifier) {
		switch(key) {
			case 'f': case 6:
				ofToggleFullscreen();
				return;
			case 'l': case 12:
				editor.setLineWrapping(!editor.getLineWrapping());
				return;
			case 'n': case 14:
				editor.setLineNumbers(!editor.getLineNumbers());
				return;
			case 'k': case 26:
				editor.setAutoFocus(!editor.getAutoFocus());
				return;
		}
	}
	
	// see ofxGLEditor.h for key commands
	editor.keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
	// make some room for the bottom editor info text
	editor.resize(w, h-ofxEditor::getCharHeight());
}

//--------------------------------------------------------------
void ofApp::openFileEvent(int &whichEditor) {
	// received an editor open via CTRL/Super + o
	
	ofLogNotice() << "received open event for editor " << whichEditor
		<< " with filename " << editor.getEditorFilename(whichEditor);
}

//--------------------------------------------------------------
void ofApp::saveFileEvent(int &whichEditor) {
	// received an editor save via CTRL/Super + s or CTRL/Super + d
  // editor.saveFile("shaders/noise.vert");
  shader.load("shaders/noise");
  
  ofLogNotice() << "received save event for editor " << whichEditor
		<< " with filename " << editor.getEditorFilename(whichEditor);
}

//--------------------------------------------------------------
void ofApp::executeScriptEvent(int &whichEditor) {

  // received on editor CTRL/Super + e
      
  string txt = editor.getText(whichEditor);

  lineas = ofSplitString(txt, "\n");
      
  texto = ofSplitString(lineas[editor.getCurrentLine()], " ");
  
  ofLogNotice() << "Orbit: " << lineas[editor.getCurrentLine()];
  
  if(texto[1] == "video" && texto[2] == "draw" && texto.size() == 4){ 
    videoLC[ofToInt(texto[0])].close();
    string temp = "videos/" + texto[3];
    videoLC[ofToInt(texto[0])].setPixelFormat(OF_PIXELS_RGBA);
    videoLC[ofToInt(texto[0])].setLoopState(OF_LOOP_NORMAL);
    videoLC[ofToInt(texto[0])].load(temp);
    if(texto[0] != "close"){
      videoLC[ofToInt(texto[0])].play();
    }
    vScaleX[ofToInt(texto[0])] = 1.0;
    vScaleY[ofToInt(texto[0])] = 1.0;
    vRotX[ofToInt(texto[0])] = 0;
    vRotY[ofToInt(texto[0])] = 0;
    vRotZ[ofToInt(texto[0])] = 0;
    vOpacity[ofToInt(texto[0])] = 255;
    videoON = 1;
    
  }
  
  if(texto[1] == "video" && texto[2] == "close"){
    videoLC[ofToInt(texto[0])].stop();
    videoLC[ofToInt(texto[0])].close();
    vX[ofToInt(texto[0])] = 0;
    vY[ofToInt(texto[0])] = 0;
    vSpeed[ofToInt(texto[0])] = 1;
    vOpacity[ofToInt(texto[0])] = 255;
    vX[ofToInt(texto[0])] = 0;
    vY[ofToInt(texto[0])] = 0;
    vZ[ofToInt(texto[0])] = 0;
    vRotX[ofToInt(texto[0])] = 0;
    vRotZ[ofToInt(texto[0])] = 0;
    vRotX[ofToInt(texto[0])] = 0;
    videoON = 0;
  }
  //      }
  
  if (texto[1] == "video" && texto[2] == "setSpeed"){
    videoLC[ofToInt(texto[0])].setSpeed(ofToFloat(texto[3]));
  }

  if (texto[1] == "video" && texto[2] == "setOpacity"){
    vOpacity[ofToInt(texto[0])] = ofToInt(texto[3]);
  }
        
  if (texto[1] == "video" && texto[2] == "setPosition"){
    vX[ofToInt(texto[0])] = ofToInt(texto[3]);
    vY[ofToInt(texto[0])] = ofToInt(texto[4]);
    vZ[ofToInt(texto[0])] = ofToInt(texto[5]);
  }
        
  if (texto[1] == "video" && texto[2] == "scale" ){
    vScaleX[ofToInt(texto[0])] = ofToFloat(texto[3]);
    vScaleY[ofToInt(texto[0])] = ofToFloat(texto[4]);
  }

  if (texto[1] == "video" && texto[2] == "rotate"){
    vRotX[ofToInt(texto[0])] = ofToFloat(texto[3]);
    vRotY[ofToInt(texto[0])] = ofToFloat(texto[4]);
    vRotZ[ofToInt(texto[0])] = ofToFloat(texto[5]);
  }
          
  if(texto[1] == "draw" && texto.size() == 2){
    if(texto[0] == "box"){ 
      boxON = 1; 
    } 
    if(texto[0] == "plane"){ 
      planeON = 1; 
    }
    if(texto[0] == "cylinder"){ 
      cylinderON = 1; 
    }	
    if(texto[0] == "sphere"){ 
      sphereON = 1; 
    }
    if(texto[0] == "ico"){ 
      icoON = 1; 
    }
    if(texto[0] == "cone"){ 
      icoON = 1; 
    }  
  }

  if(texto[1] == "clear" && texto.size() == 2){
    if(texto[0] == "box"){ 
      boxON = 0; 
    } 
    if(texto[0] == "plane"){ 
      planeON = 0; 
    }
    if(texto[0] == "cylinder"){ 
      cylinderON = 0; 
    }	
    if(texto[0] == "sphere"){ 
      sphereON = 0; 
    }
    if(texto[0] == "ico"){ 
      icoON = 0; 
    }
    if(texto[0] == "cone"){ 
      icoON = 0; 
    }  
  } 

  if(texto[0] == "cam" && texto.size() == 4){
    if(texto[1] == "orbit" && ofToInt(texto[2]) == 0 & ofToInt(texto[3]) == 0){
      orbitON = 0;	
    }
    else{
      orbitON = 1;
    }
    orbitX = ofToFloat(texto[2]);
    orbitY = ofToFloat(texto[3]);
  }
  
  if (texto[0] == "cam" && texto[1] == "setPosition"){
    camera.setPosition(ofVec3f(ofToInt(texto[2]), ofToInt(texto[3]), ofToInt(texto[4])));
  }
        
  if (texto[0] == "cam" && texto[1] == "lookAt" && texto.size() == 5){
    centro = ofVec3f(ofToInt(texto[2]), ofToInt(texto[3]), ofToInt(texto[4]));
  }
          
  if (texto[0] == "cam" && texto[1] == "setDistance" ){
    camdistance = ofToFloat(texto[2]);
    camera.setDistance(camdistance);
  }

  // modelos
   
  if (texto[1] == "model" && texto[2] == "load" && texto.size() == 4){
    string temp = "3d/" + texto[3];
    multiModel[ofToInt(texto[0])].loadModel(temp);
    //multiModelON = ofToFloat(textAnalisis[2]);
  }
  
  if (texto[1] == "model" && texto[2] == "clear"){
    multiModel[ofToInt(texto[0])].clear();
  }
  
  if (texto[1] == "model" && texto[2] == "setPosition"){
    multiModelX[ofToInt(texto[0])] = ofToInt(texto[3]);
    multiModelY[ofToInt(texto[0])] = ofToInt(texto[4]);
    multiModelZ[ofToInt(texto[0])] = ofToInt(texto[5]);
  }
  
  if (texto[1] == "model" && texto[2] == "rotate"){
    multiModelRotX[ofToInt(texto[0])] = ofToInt(texto[3]);
    multiModelRotY[ofToInt(texto[0])] = ofToInt(texto[4]);
    multiModelRotZ[ofToInt(texto[0])] = ofToInt(texto[5]);
  }
  
  if (texto[1] == "model" && texto[2] == "scale"){
    multiModelScale[ofToInt(texto[0])] = ofToFloat(texto[3]);
  }
    
  // if you have some scripting language (e.g. ofxLua)
  // ofLogNotice() << "currentline " << currentLine;

  if(texto[0] == "mainLight" && texto[1] == "color"){
    pointLight.setDiffuseColor( ofColor(ofToFloat(texto[2]), ofToFloat(texto[3]), ofToFloat(texto[4])));
  // specular color, the highlight/shininess color //
  pointLight.setSpecularColor( ofColor(ofToFloat(texto[2]), ofToFloat(texto[3]), ofToFloat(texto[4])));
  }

  if(texto[0] == "mainLight" && texto[1] == "disable"){
    pointLight.disable(); 
  }

  if(texto[0] == "mainLight" && texto[1] == "enable"){
    pointLight.enable(); 
  }

  if(texto[0] == "material" && texto[1] == "setShininess"){
    material.setShininess( ofToInt(texto[2]) );
  }
    
  if(texto[1] == "light" && texto[2] == "enable"){
    pointLight2[ofToInt(texto[0])].enable(); 
  }

  if(texto[1] == "light" && texto[2] == "disable"){
    pointLight2[ofToInt(texto[0])].disable(); 
  }

  if(texto[1] == "light" && texto[2] == "draw"){
    drawLight[ofToInt(texto[0])] = 1; 
  }

   if(texto[1] == "light" && texto[2] == "clear"){
    drawLight[ofToInt(texto[0])] = 0; 
  }

  if(texto[1] == "light" && texto[2] == "color"){
    colorLight2[ofToInt(texto[0])] = ofColor(ofToInt(texto[3]), ofToInt(texto[4]), ofToInt(texto[5]));
  }

  if(texto[1] == "light" && texto[2] == "oscSpeed"){
    lightSpeedX[ofToInt(texto[0])] = ofToFloat(texto[3]);
    lightSpeedY[ofToInt(texto[0])] = ofToFloat(texto[4]);
    lightSpeedZ[ofToInt(texto[0])] = ofToFloat(texto[5]);  
  }

   if(texto[1] == "light" && texto[2] == "oscAmp"){
    lightAmpX[ofToInt(texto[0])] = ofToFloat(texto[3]);
    lightAmpY[ofToInt(texto[0])] = ofToFloat(texto[4]);
    lightAmpZ[ofToInt(texto[0])] = ofToFloat(texto[5]);  
  }

   if(texto[0] == "feedback" && texto[1] == "enable"){
     retro = 1; 
   }

   if(texto[0] == "feedback" && texto[1] == "disable"){
     retro = 0; 
   }

   if(texto[0] == "feedback" && texto[1] == "setPosition"){
     retroX = ofToFloat(texto[2]);
     retroY = ofToFloat(texto[3]);
   }

   if (texto[0] == "glitch"){
     if(texto[2] == "false" && texto[1] == "all"){
       convergence = false;
       glow = false;
       shaker = false;
       cutslider = false;
       twist = false;
       outline = false;
       noise = false;
       slitscan = false;
       swell = false;
       invert = false;
     }
            
     if(texto[1] == "convergence"){
       convergence = ofToBool(texto[2]);
       glitchON = ofToBool(texto[2]);
     }
            
     if(texto[1] == "glow"){
       glow = ofToBool(texto[2]);
       glitchON = ofToBool(texto[2]);
     }
            
     if(texto[1] == "shaker"){
       shaker = ofToBool(texto[2]);
       glitchON = ofToBool(texto[2]);
     }
     
     if(texto[1] == "cutslider"){
       cutslider = ofToBool(texto[2]);
       glitchON = ofToBool(texto[2]);
     }
     
     if(texto[1] == "twist"){
       twist = ofToBool(texto[2]);
       glitchON = ofToBool(texto[2]);
     }
            
     if(texto[1] == "outline"){
       outline = ofToBool(texto[2]);
       glitchON = ofToBool(texto[2]);
     }
     
     if(texto[1] == "noise"){
       noise = ofToBool(texto[2]);
       glitchON = ofToBool(texto[2]);
     }
     
     if(texto[1] == "slitscan"){
       slitscan = ofToBool(texto[2]);
       glitchON = ofToBool(texto[2]);
     }
     
     if(texto[1] == "swell"){
       swell = ofToBool(texto[2]);
       glitchON = ofToBool(texto[2]);
     }
     
     if(texto[1] == "invert"){
       invert = ofToBool(texto[2]);
       glitchON = ofToBool(texto[2]);
     }
   }
   
   if (texto[0] == "colorRemap"){
     if(texto[2] == "false" && texto[1] == "all"){
       highcontrast = false;
       blueraise = false;
       redraise = false;
       greenraise = false;
       blueinvert = false;
       redinvert = false;
       greeninvert = false;
     }
     
     if(texto[1] == "highContrast"){
       highcontrast = ofToBool(texto[2]);
       glitchON = ofToBool(texto[2]);
     }
     
     if(texto[1] == "blueRaise"){
       blueraise = ofToBool(texto[2]);
       glitchON = ofToBool(texto[2]);
     }
     
     if(texto[1] == "redRaise"){
       redraise = ofToBool(texto[2]);
       glitchON = ofToBool(texto[2]);
     }
     
     if(texto[1] == "greenRaise"){
       greenraise = ofToBool(texto[2]);
       glitchON = ofToBool(texto[2]);
     }
     if(texto[1] == "blueInvert"){
       blueinvert = ofToBool(texto[2]);
       glitchON = ofToBool(texto[2]);
     }
     if(texto[1] == "redInvert"){
       redinvert = ofToBool(texto[2]);
       glitchON = ofToBool(texto[2]);
     } 
     if(texto[1] == "greenInvert"){
       greeninvert = ofToBool(texto[2]);
       glitchON = ofToBool(texto[2]);
     }
   }

   if(texto[0] == "shader" && texto[1] == "enable"){
     shaderON = 1; 
   }

   if(texto[0] == "shader" && texto[1] == "disable"){
     shaderON = 0; 
   }

   if(texto[0] == "term"){
     string comando;
     comando = texto[1]; 
     string result = ofSystem(comando);
     ofLogNotice() << "term: " << result;
   }

   if(texto[0] == "oscSender"){
     sender.setup(texto[1], ofToInt(texto[2]));
    ofxOscMessage m;
    m.setAddress(texto[3]);
    m.addIntArg(ofToFloat(texto[4]));

    if(texto.size() == 6){
      m.addIntArg(ofToFloat(texto[5]));     
    }
    
    if(texto.size() == 7){
      m.addIntArg(ofToFloat(texto[5]));
      m.addIntArg(ofToFloat(texto[6]));
    }
 
    sender.sendMessage(m, false);

   }
}

//--------------------------------------------------------------
void ofApp::evalReplEvent(const string &text) {
  ofLogNotice() << "repl: " << text;
  
  // make sure there is a response since this triggers printing the
  // next conosle prompt
  // string texto;
  
  editor.evalReplReturn(text); // print this, then prompt
  //editor.evalReplReturn(); // empty response, just prints prompt
  std::vector < std::string > texto = ofSplitString(text, " ");
  
  if(texto[0] == "video" && texto[1] == "draw" && texto.size() == 4){ 
    videoLC[ofToInt(texto[2])].close();
    string temp = "videos/" + texto[3] + ".mov";
    videoLC[ofToInt(texto[2])].setPixelFormat(OF_PIXELS_RGBA);
    videoLC[ofToInt(texto[2])].setLoopState(OF_LOOP_NORMAL);
    videoLC[ofToInt(texto[2])].load(temp);
    if(texto[0] != "close"){
      videoLC[ofToInt(texto[2])].play();
    }
    vScaleX[ofToInt(texto[2])] = 1.0;
    vScaleY[ofToInt(texto[2])] = 1.0;
    vRotX[ofToInt(texto[2])] = 0;
    vRotY[ofToInt(texto[2])] = 0;
    vRotZ[ofToInt(texto[2])] = 0;
    vOpacity[ofToInt(texto[2])] = 255;
    videoON = 1;
  }
  if(texto[0] == "video" && texto[1] == "close" && texto[1] != "draw"){
    videoLC[ofToInt(texto[2])].stop();
    videoLC[ofToInt(texto[2])].close();
    vX[ofToInt(texto[2])] = 0;
    vY[ofToInt(texto[2])] = 0;
    vSpeed[ofToInt(texto[2])] = 1;
    vOpacity[ofToInt(texto[2])] = 255;
    vX[ofToInt(texto[2])] = 0;
    vY[ofToInt(texto[2])] = 0;
    vZ[ofToInt(texto[2])] = 0;
    vRotX[ofToInt(texto[2])] = 0;
    vRotZ[ofToInt(texto[2])] = 0;
    vRotX[ofToInt(texto[2])] = 0;
    videoON = 0;
  }

  if (texto[0] == "video" && texto[1] == "setSpeed"){
    videoLC[ofToInt(texto[2])].setSpeed(ofToFloat(texto[3]));
  }
  
  if(texto[0] == "camera" && texto.size() == 4){
    if(texto[1] == "orbit" && ofToInt(texto[2]) == 0 & ofToInt(texto[3]) == 0){
      orbitON = 0;	
    }
    else{
      orbitON = 1;
    }
    orbitX = ofToFloat(texto[2]);
    orbitY = ofToFloat(texto[3]);
  }
  
}
