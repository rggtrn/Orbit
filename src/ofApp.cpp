#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetCircleResolution(50);
    ofBackground(0, 0, 0); 
    ofSetVerticalSync(true);
    ofSetWindowTitle("PiranhaVivo");
    ofSetWindowShape(1280, 800);
    ofSetFrameRate(30);

    //font.load("fonts/DejaVuSansMono.ttf", 12, true, true, true);
    //fontSize = 14;
    font2.load("fonts/DejaVuSansMono.ttf", 20, true, true, true);
    font.load("fonts/DejaVuSansMono.ttf", 12, true, true, true);
    font.setLineHeight(17);
    //fontname.load("fonts/Batang.ttf", 14, true, true, true);
    textON = 0;
    texto = "PiranhaVivo";
    nombre = "PiranhaVivo";
    
#if (defined(__APPLE__) && defined(__MACH__))
    client.setup();
    syphonON = 0;
#endif
    player.setPixelFormat(OF_PIXELS_RGBA);
    player.setLoopState(OF_LOOP_NORMAL);
    
    XML.load ("xml/OSCConf.xml");
    portOut = XML.getValue("PORT:NAME:OUT",5613);
    sender.setup("127.0.0.1",portOut);
    portIn = XML.getValue("PORT:NAME:IN",5612);
    reciever.setup(portIn);
        
    for(int i = 0; i < LIM; i++){
        vX[i] = 0;
        vY[i] = 0;
        vW[i] = 0;
        vH[i] = 0;
        vSpeed[i] = 1;
        vOpacity[i] = 255;
        vScaleX[i] = 1;
        vScaleY[i] = 1;
        vRotX[i] = 0;
        vRotY[i] = 0;
        vRotZ[i] = 0;
	path[i];
    }
    
    ofSetVerticalSync(true);
    ofBackground(255,255,255);
    position = 0;
    screenImage.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    retroX = 40;
    retroY = 40;
    feedback = 0;
    canonGenerator = 0;

    //model.loadModel("3d/cubo.obj");
    //model.setPosition(ofGetWidth()*.5, ofGetHeight() * 0.75, 0);

    ofSetSmoothLighting(true);
    pointLight.setDiffuseColor( ofFloatColor(1.f, 1.f, 1.f) );
    pointLight.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    
    //pointLight2.setDiffuseColor( ofFloatColor( 238.f/255.f, 57.f/255.f, 135.f/255.f ));
    //pointLight2.setSpecularColor(ofFloatColor(.8f, .8f, .9f));
    
    //pointLight3.setDiffuseColor( ofFloatColor(19.f/255.f,94.f/255.f,77.f/255.f) );
    //pointLight3.setSpecularColor( ofFloatColor(18.f/255.f,150.f/255.f,135.f/255.f) );
    
}

void ofApp::update(){
    
    pointLight.setPosition((ofGetWidth()*.5)+ cos(ofGetElapsedTimef()*.5)*(ofGetWidth()*.3), ofGetHeight()/2, 500);
    //pointLight2.setPosition((ofGetWidth()*.5)+ cos(ofGetElapsedTimef()*.15)*(ofGetWidth()*.3),
    //                       ofGetHeight()*.5 + sin(ofGetElapsedTimef()*.7)*(ofGetHeight()), -300);
    
    //pointLight3.setPosition(
    //                        cos(ofGetElapsedTimef()*1.5) * ofGetWidth()*.5,
    //                        sin(ofGetElapsedTimef()*1.5f) * ofGetWidth()*.5,
    //                        cos(ofGetElapsedTimef()*.2) * ofGetWidth()
    //                        );
    
    player.update();
    
    position = 500 + 250 * sin(ofGetElapsedTimef()*4);
    screenImage.loadScreenData(0,0,ofGetWidth(), ofGetHeight());
    
    //// para las formas
    
    while (reciever.hasWaitingMessages()){
        
        ofxOscMessage m;
        reciever.getNextMessage(&m);
        
        /// mensajes que vienen del history
        
        /// mensajes OSC para dibujar
        
        if (m.getAddress() == "/load"  &&  m.getNumArgs() ==2){
            string temp = "videos/" + m.getArgAsString(1) + ".mov";
            int n = m.getArgAsInt(0);
            videoLC[n].setPixelFormat(OF_PIXELS_RGBA);
            videoLC[n].setLoopState(OF_LOOP_NORMAL);
            videoLC[n].load(temp);
            videoLC[n].play();
            model3DOn[n] = false;
	    //vW[m.getArgAsInt(0)] = videoLC[m.getArgAsInt(0)].getWidth();
            //vH[m.getArgAsInt(0)] = videoLC[m.getArgAsInt(0)].getHeight();
            vScaleX[n] = (ofGetWidth()*1.0)/960;
            vScaleY[n] = (ofGetHeight()*1.0)/560;
	    //vScaleX[n] = (ofGetWidth()*1.0)/vW[m.getArgAsInt(0)];
            //vScaleY[n] = (ofGetHeight()*1.0)/vH[m.getArgAsInt(0)];
            
        }
        
        if (m.getAddress() == "/free"  &&  m.getNumArgs() == 1){
            videoLC[m.getArgAsInt(0)].close();
            vX[m.getArgAsInt(0)] = 0;
            vY[m.getArgAsInt(0)] = 0;
            vSpeed[m.getArgAsInt(0)] = 1;
            vOpacity[m.getArgAsInt(0)] = 255;
            //videoLC[m.getArgAsInt(0)].draw(0,0);
            models3D[m.getArgAsInt(0)].clear();
            vW[m.getArgAsInt(0)] = videoLC[m.getArgAsInt(0)].getWidth();
            vH[m.getArgAsInt(0)] = videoLC[m.getArgAsInt(0)].getHeight();
        }
        
        if (m.getAddress() == "/speed" && m.getNumArgs() == 2){
            int n = m.getArgAsInt(0);
            //vSpeed[m.getArgAsInt(0)] = m.getArgAsFloat(1);
            videoLC[n].setSpeed(m.getArgAsInt(1));
        }
        
        if (m.getAddress() == "/opacity" && m.getNumArgs() == 2){
            vOpacity[m.getArgAsInt(0)] = m.getArgAsInt(1);
        }
        
        if (m.getAddress() == "/pos" && m.getNumArgs() == 3){
            vX[m.getArgAsInt(0)] = m.getArgAsInt(1);
            vY[m.getArgAsInt(0)] = m.getArgAsInt(2);

	    if(canonGenerator == 1){
	    //videoLC[m.getArgAsInt(0)].close();
	    videoLC[m.getArgAsInt(0)].play();	      
	    }
        }
        
        if (m.getAddress() == "/size" && m.getNumArgs() == 3){
	  //vScaleX[m.getArgAsInt(0)] = m.getArgAsFloat(1)/vW[m.getArgAsInt(0)];
	  //vScaleY[m.getArgAsInt(0)] = m.getArgAsFloat(2)/vH[m.getArgAsInt(0)];
	  vScaleX[m.getArgAsInt(0)] = m.getArgAsFloat(1);
	  vScaleY[m.getArgAsInt(0)] = m.getArgAsFloat(2);
        }
        
        if (m.getAddress() == "/feedback" && m.getNumArgs() == 2){
            //vScaleX[m.getArgAsInt(0)] = m.getArgAsFloat(1)/vW[m.getArgAsInt(0)];
            //vScaleY[m.getArgAsInt(0)] = m.getArgAsFloat(2)/vH[m.getArgAsInt(0)];
            retroX = m.getArgAsFloat(0);
            retroY = m.getArgAsFloat(1);
        }
        
        if (m.getAddress() == "/rot" && m.getNumArgs() == 4){
            vRotX[m.getArgAsInt(0)] = m.getArgAsFloat(1);
            vRotY[m.getArgAsInt(0)] = m.getArgAsFloat(2);
            vRotZ[m.getArgAsInt(0)] = m.getArgAsFloat(3);
        }
        
        if (m.getAddress() == "/load3d"  &&  m.getNumArgs() == 2){
            videoLC[m.getArgAsInt(0)].close();
            vX[m.getArgAsInt(0)] = 0;
            vY[m.getArgAsInt(0)] = 0;
            vScaleX[m.getArgAsInt(0)] = 1;
            vScaleY[m.getArgAsInt(0)] = 1;
            vRotX[m.getArgAsInt(0)] = 0;
            vRotY[m.getArgAsInt(0)] = 0;
            vRotZ[m.getArgAsInt(0)] = 0;
            vSpeed[m.getArgAsInt(0)] = 1;
            vOpacity[m.getArgAsInt(0)] = 255;
            string temp = "3d/" + m.getArgAsString(1);
            model3DOn[m.getArgAsInt(0)] = true;
            models3D[m.getArgAsInt(0)].loadModel(temp,false);
            models3D[m.getArgAsInt(0)].setPosition(ofGetWidth()*0.5,ofGetHeight()*0.5, -400);
            models3D[m.getArgAsInt(0)].setLoopStateForAllAnimations(OF_LOOP_NORMAL);
            models3D[m.getArgAsInt(0)].playAllAnimations();
        }
        
        if (m.getAddress() == "/message"  &&  m.getNumArgs() == 2){
            //serverTyping = "";
            //serverTyping =
            texto = m.getArgAsString(0);
            nombre = m.getArgAsString(1);
            
        }

	if (m.getAddress() == "/message"  &&  m.getNumArgs() == 1){
            //serverTyping = "";
            //serverTyping =
            texto = m.getArgAsString(0);
            //nombre = m.getArgAsString(1);
            
        }
 
	if (m.getAddress() == "/textON" && m.getNumArgs() == 1){
	  textON = m.getArgAsInt(0);
        }

	
	if (m.getAddress() == "/canonGeneratorON" && m.getNumArgs() == 1){
	  canonGenerator = m.getArgAsInt(0);
        }

        if (m.getAddress() == "/feedbackX" && m.getNumArgs() == 1){
            //vScaleX[m.getArgAsInt(0)] = m.getArgAsFloat(1)/vW[m.getArgAsInt(0)];
            //vScaleY[m.getArgAsInt(0)] = m.getArgAsFloat(2)/vH[m.getArgAsInt(0)];
            retroX = m.getArgAsFloat(0);
        }
        
        if (m.getAddress() == "/feedbackY" && m.getNumArgs() == 1){
            //vScaleX[m.getArgAsInt(0)] = m.getArgAsFloat(1)/vW[m.getArgAsInt(0)];
            //vScaleY[m.getArgAsInt(0)] = m.getArgAsFloat(2)/vH[m.getArgAsInt(0)];
            retroY = m.getArgAsFloat(0);
        }
                    
      //  }

	#if (defined(__APPLE__) && defined(__MACH__))
	if (m.getAddress() == "/syphonON" && m.getNumArgs() == 1){
	  syphonON = m.getArgAsInt(0);
	}	
#endif
	// No funciona con el Hap
	//	if (m.getAddress() == "/setFrame" && m.getNumArgs() == 2){
	//  videoLC[m.getArgAsInt(0)].setFrame(m.getArgAsInt(1));
	//}

    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0, 0, 0);
    ofEnableAlphaBlending();
    
    ofEnableLighting();
    pointLight.enable();
    //pointLight2.enable();
    //pointLight3.enable();
    
    screenImage.draw(0+retroX, 0+retroY, ofGetWidth()-80, ofGetHeight()-80);

#if (defined(__APPLE__) && defined(__MACH__))

    //if(syphonON == 1){
    client.draw(0, 0);
   // };
    
#endif
    
    for(int i = 0; i < LIM; i++){

      ofPushMatrix();
	
        if(textON == 1){
	  
	  //ofTranslate(ofGetWidth()*(0.125*fontScale), ofGetHeight()*0.125);
	  ofScale(1, 1, 1);
	  text = wrapString(texto, 200);

	  font2.drawStringCentered(nombre, ofGetWidth()*0.125, ofGetHeight()*0.125);
	  font.drawStringCentered(text, (ofGetWidth()*0.5), ofGetHeight()*0.5);
	};

	if(textON == 0){
	  font.drawStringCentered("", (ofGetWidth()*fontScale), ofGetHeight()*0.5);
	}
	
        ofRotateX(vRotX[i]);
        ofRotateY(vRotY[i]);
        ofRotateZ(vRotZ[i]);
        ofSetColor(255,vOpacity[i]);
        ofScale(vScaleX[i],vScaleY[i]);
        ofTranslate(vX[i],vY[i]);

	videoLC[i].draw(0, 0);
        
        if(model3DOn[i] == true){
            ofSetColor(255);
            ofEnableBlendMode(OF_BLENDMODE_ALPHA);
            ofEnableDepthTest();
            light.enable();
            ofEnableSeparateSpecularLight();
            models3D[i].drawFaces();
            ofDisableDepthTest();
            ofDisableBlendMode();
            ofDisableSeparateSpecularLight();
        };
        
        if(model3DOn[i] == false){
            models3D[i].clear();
        }

	if(canonGenerator == 1){

	  videoLC[i].setLoopState(OF_LOOP_NONE);
	  //ofNoFill();
	  //ofSetColor(255);
	  //path[i].hasOutline();
	  //path[i].setCircleResolution(80);
	  //path[i].circle(0, 0, 40);
	  //path[i].setStrokeWidth(10);
	  //path[i].draw();	

      }
        
        ofPopMatrix();
        
    }
    
    screenImage.loadScreenData(0,0, ofGetWidth(), ofGetHeight());
    
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
