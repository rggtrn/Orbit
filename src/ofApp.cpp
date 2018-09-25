
#include "ofApp.h"

void ofApp::setup(){
    
    // iniciales
    
    ofSetCircleResolution(50);
    ofBackground(0, 0, 0);
    ofSetVerticalSync(true);
    ofSetWindowTitle("Orbit");
    
    winSizeW = 1024;
    winSizeH = 1024;
    
    ofSetWindowShape(winSizeW, winSizeH); /// La resolución de la pantalla final
    ofSetFrameRate(30);
    ofHideCursor();
    tempo = 1;
    
    // domemmaster
    
    domemaster.setup();
    domemaster.setCameraPosition(0,0,20);
    domeON = 0;
    
    // camara
    
    camera.setDistance(1500);
    autoOrbit = 0;
    orbitX = 0;
    orbitY = 0;
    distanceLockON = 1;
    
    // texto
    
    //font2.load("fonts/CloisterBlack.ttf", 28, true, true, true);
    //font.load("fonts/CloisterBlack.ttf", 20, true, true, true);
    
    font2.load("fonts/DejaVuSansMono.ttf", 20, true, true, true);
    font.load("fonts/DejaVuSansMono.ttf", 20, true, true, true);
    textON = 0;
    texto = "";
    nombre = "";
    fixText = 1;
    textRotX = 0;
    textRotY = 0;
    textRotZ = 0;
    namesON = 0;
    
    // Syphon
    
#if (defined(__APPLE__) && defined(__MACH__))
    client.setup();
    syphonON = 0;
#endif
    
    // glitch
    
    plane.set(ofGetWidth(), ofGetHeight());
    //ofDisableArbTex();
    //fbo.allocate(plane.getWidth()/2, plane.getHeight()/2, GL_RGBA);
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    myGlitch.setup(&fbo);
    ofxglitch = 0;
    fbox = 0;
    fboy = 0;
    fboz = 0;
    fboscaleX = 1;
    fboscaleY = 1;
    fboSpeed=1;
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
    
    /// información
    
    timeElapsedON=0;
    
    
    // OSC
    
    XML.load ("xml/OSCConf.xml");
    portOut = XML.getValue("PORT:NAME:OUT",5613);
    sender.setup("127.0.0.1",portOut);
    portIn = XML.getValue("PORT:NAME:IN",5612);
    reciever.setup(portIn);
    
    // transformaciones
    
    for(int i = 0; i < LIM; i++){
        vX[i] = 0;
        vY[i] = 0;
        vZ[i] = 0;
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
    
    /// retro alimentación
    
    retroON = 0;
    position = 0;
    screenImage.allocate(960*2, 560*2, GL_RGBA);
    retroX = 40;
    retroY = 40;
    feedback = 0;
    retroVel = 4;
    canonGenerator = 0;
    feedbackON = 0; /// activarla de vez en cuando chin
    
    /// Luces
    
    ofSetSmoothLighting(true);
    pointLight.setDiffuseColor( ofFloatColor(1.f, 1.f, 1.f) );
    pointLight.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    lightON = 0;
    
}

void ofApp::update(){
    
    /// luces
    
    pointLight.setPosition((ofGetWidth()*.5)+ cos(ofGetElapsedTimef()*.5)*(ofGetWidth()*.3), ofGetHeight()/2, 200);
    
    // retroalmientación
    
    position = 500 + 250 * sin(ofGetElapsedTimef() * 4);
    screenImage.loadScreenData(0,0,ofGetWidth(), ofGetHeight());
    
    //// OSC
    
    while (reciever.hasWaitingMessages()){
        
        ofxOscMessage m;
        reciever.getNextMessage(&m);
        
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
            vRotX[n] = 0;
            vRotY[n] = 0;
            vRotZ[n] = 0;
            //vScaleX[n] = (ofGetWidth()*1.0)/vW[m.getArgAsInt(0)];
            //vScaleY[n] = (ofGetHeight()*1.0)/vH[m.getArgAsInt(0)];
        }
        
        if (m.getAddress() == "/free"  &&  m.getNumArgs() == 1){
            videoLC[m.getArgAsInt(0)].close();
            vX[m.getArgAsInt(0)] = 0;
            vY[m.getArgAsInt(0)] = 0;
            vSpeed[m.getArgAsInt(0)] = 1;
            vOpacity[m.getArgAsInt(0)] = 255;
            models3D[m.getArgAsInt(0)].clear();
            vW[m.getArgAsInt(0)] = videoLC[m.getArgAsInt(0)].getWidth();
            vH[m.getArgAsInt(0)] = videoLC[m.getArgAsInt(0)].getHeight();
        }
        
        if (m.getAddress() == "/speed" && m.getNumArgs() == 2){
            int n = m.getArgAsInt(0);
            videoLC[n].setSpeed(m.getArgAsFloat(1)*tempo);
        }
        
        if (m.getAddress() == "/lightON" && m.getNumArgs() == 1){
            lightON = m.getArgAsInt(0);
        }
        
        if (m.getAddress() == "/tempo" && m.getNumArgs() == 1){
            tempo = m.getArgAsInt(0);
        }
        
        if (m.getAddress() == "/opacity" && m.getNumArgs() == 2){
            vOpacity[m.getArgAsInt(0)] = m.getArgAsInt(1);
        }
        
        if (m.getAddress() == "/pos" && m.getNumArgs() == 4){ /// posZ
            vX[m.getArgAsInt(0)] = m.getArgAsInt(1);
            vY[m.getArgAsInt(0)] = m.getArgAsInt(2);
            vZ[m.getArgAsInt(0)] = m.getArgAsInt(3);
            
            if(canonGenerator == 1){
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
            retroX = m.getArgAsFloat(0);
            retroY = m.getArgAsFloat(1);
        }
        
        if (m.getAddress() == "/feedbackX" && m.getNumArgs() == 1){
            retroX = m.getArgAsFloat(0);
        }
        
        if (m.getAddress() == "/feedbackY" && m.getNumArgs() == 1){
            retroY = m.getArgAsFloat(0);
        }
        
        if (m.getAddress() == "/rot" && m.getNumArgs() == 4){
            vRotX[m.getArgAsInt(0)] = m.getArgAsFloat(1);
            vRotY[m.getArgAsInt(0)] = m.getArgAsFloat(2);
            vRotZ[m.getArgAsInt(0)] = m.getArgAsFloat(3);
        }
        
        if (m.getAddress() == "/textRot" && m.getNumArgs() == 3){
            textRotX = m.getArgAsFloat(0);
            textRotY = m.getArgAsFloat(1);
            textRotZ = m.getArgAsFloat(2);
        }
        
        if (m.getAddress() == "/message"  &&  m.getNumArgs() == 2){
            texto = m.getArgAsString(0);
            nombre = m.getArgAsString(1);
        }
        
        if (m.getAddress() == "/message"  &&  m.getNumArgs() == 1){
            texto = m.getArgAsString(0);
        }
        
        if (m.getAddress() == "/domeON"  &&  m.getNumArgs() == 1){
            domeON = m.getArgAsInt(0);
        }
        
        if (m.getAddress() == "/namesON"  &&  m.getNumArgs() == 1){
            namesON = m.getArgAsInt(0);
        }
        
        if (m.getAddress() == "/timeElapsedON"  &&  m.getNumArgs() == 1){
            timeElapsedON = m.getArgAsInt(0);
        }
        
        if (m.getAddress() == "/textON" && m.getNumArgs() == 2){
            textON = m.getArgAsInt(0);
            fixText = m.getArgAsInt(1);
        }
        
        if (m.getAddress() == "/distanceLockON" && m.getNumArgs() == 1){
            textON = m.getArgAsInt(0);
            fixText = m.getArgAsInt(1);
        }
        
        if (m.getAddress() == "/autoOrbit" && m.getNumArgs() == 3){
            autoOrbit = m.getArgAsInt(0);
            orbitX = m.getArgAsInt(1);
            orbitY = m.getArgAsInt(2);
        }
        
        if (m.getAddress() == "/canonGeneratorON" && m.getNumArgs() == 1){
            canonGenerator = m.getArgAsInt(0);
        }
        
        if (m.getAddress() == "/feedbackON" && m.getNumArgs() == 1){
            feedbackON = m.getArgAsInt(0);
        }
        
#if (defined(__APPLE__) && defined(__MACH__))
        if (m.getAddress() == "/syphonON" && m.getNumArgs() == 1){
            syphonON = m.getArgAsInt(0);
        }
#endif
        
        if (m.getAddress() == "/glitchColor" && m.getNumArgs() == 2){
            
            if(m.getArgAsInt(1) == 0 && m.getArgAsInt(0) == 0){
                highcontrast = false;
                blueraise = false;
                redraise = false;
                greenraise = false;
                blueinvert = false;
                redinvert = false;
                greeninvert = false;
            }
            
            if(m.getArgAsInt(1) == 1){
                highcontrast = m.getArgAsBool(0);
            }
            
            if(m.getArgAsInt(1) == 2){
                blueraise = m.getArgAsBool(0);
            }
            
            if(m.getArgAsInt(1) == 3){
                redraise = m.getArgAsBool(0);
            }
            
            if(m.getArgAsInt(1) == 4){
                greenraise = m.getArgAsBool(0);
            }
            
            if(m.getArgAsInt(1) == 5){
                blueinvert = m.getArgAsBool(0);
            }
            
            if(m.getArgAsInt(1) == 6){
                redinvert = m.getArgAsBool(0);
            }
            
            if(m.getArgAsInt(1) == 1){
                greeninvert = m.getArgAsBool(0);
            }
        }
        
        if (m.getAddress() == "/glitch" && m.getNumArgs() == 2){
            
            if(m.getArgAsInt(1) == 0 && m.getArgAsInt(0) == 0){
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
            
            if(m.getArgAsInt(1) == 1){
                convergence = m.getArgAsBool(0);
            }
            
            if(m.getArgAsInt(1) == 2){
                glow = m.getArgAsBool(0);
            }
            
            if(m.getArgAsInt(1) == 3){
                shaker = m.getArgAsBool(0);
            }
            
            if(m.getArgAsInt(1) == 4){
                cutslider = m.getArgAsBool(0);
            }
            
            if(m.getArgAsInt(1) == 5){
                twist = m.getArgAsBool(0);
            }
            
            if(m.getArgAsInt(1) == 6){
                outline = m.getArgAsBool(0);
            }
            
            if(m.getArgAsInt(1) == 7){
                noise = m.getArgAsBool(0);
            }
            
            if(m.getArgAsInt(1) == 8){
                slitscan = m.getArgAsBool(0);
            }
            
            if(m.getArgAsInt(1) == 9){
                swell = m.getArgAsBool(0);
            }
            
            if(m.getArgAsInt(1) == 10){
                invert = m.getArgAsBool(0);
            }
            
        }
        
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
    
    drawScene();
    
    //fbo.draw(0, 0);
    
}

void ofApp::draw(){
    
    // Glitch
    
    ofBackground(0, 0, 0);
    ofEnableAlphaBlending();
    ofSetRectMode(OF_RECTMODE_CORNER);
    
    ofClear(0);
    myGlitch.generateFx();
    
    if(domeON == 0){
        fbo.draw(0, 0);
    }
    
    if(domeON == 1){
    for (int i=0; i<domemaster.renderCount; i++){
        domemaster.begin(i);
        drawFbo();
        //fbo.draw(0, 0);
        domemaster.end(i);
    }
    domemaster.draw();
    }
    
    
}


//--------------------------------------------------------------

void ofApp::drawFbo(){
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofScale(0.125, 0.125);
    ofTranslate(0, 0, -10);
    ofRotateX(180);
    
    //fbo.getTexture().bind();
    //plane.draw();
    //fbo.getTexture().unbind();
    fbo.draw(0, 0);
    
}

//--------------------------------------------------------------

void ofApp::drawScene(){
    
    
    fbo.begin();
    
    ofClear(0);
    //glEnable(GL_DEPTH_TEST);
    
    
    if(timeElapsedON==1){
        ofDrawBitmapString("timeElapsed: " + ofToString(ofGetElapsedTimef()), 30, 30);
    }
    
    if(feedbackON == 1){
        screenImage.draw(0+retroX, 0+retroY, ofGetWidth()-80, ofGetHeight()-80);
    }
    
    // luces
    
    if(lightON == 1){
        ofEnableLighting();
        pointLight.enable();
    }
    
    // syphon
    
#if (defined(__APPLE__) && defined(__MACH__))
    
    if(syphonON == 1){
        client.draw(0, 0);
    };
    
#endif
    
    for(int i = 0; i < LIM; i++){
        
        ofPushMatrix();
        ///texto fuera de cámara
        
        if(textON == 1 && fixText == 1){
            
            ofSetRectMode(OF_RECTMODE_CENTER);
            ofTranslate(0, 0, 200);
            ofScale(1, 1);
            ofRotateX(textRotX);
            ofRotateY(textRotY);
            ofRotateZ(textRotZ);
            
            text = wrapString(texto, 200);
            ofRectangle rect = font.getStringBoundingBox(text, 0, 0);
            
            if(namesON == 1){
                float distancia;
                float distancia2;
                distancia = ofMap(rect.height, 25, 1000, 55, 625);
                distancia2 = ofMap(rect.width, 25, 1000, 55, 525);
                font2.drawStringCentered(nombre, distancia2 * (-1), distancia);
            }
            
            if(distanceLockON == 1){
                float distancia;
                distancia = ofMap(rect.height, 0, 1000, 100, -400);
                ofTranslate(0, 0, distancia);
            }
            
            font.drawStringCentered(text, (ofGetWidth()*0.5), ofGetHeight()*0.5);
        };
        
        camera.begin();
        ofSetRectMode(OF_RECTMODE_CENTER);
        
        /// texto en cámara
        
        if(textON == 1 && fixText == 0){
            
            //ofDisableArbTex();
            
            ofSetRectMode(OF_RECTMODE_CENTER);
            ofTranslate(0, 0, 200);
            ofScale(1, 1);
            ofRotateX(textRotX);
            ofRotateY(textRotY);
            ofRotateZ(textRotZ);
            
            text = wrapString(texto, 200);
            ofRectangle rect = font.getStringBoundingBox(text, 0, 0);
            font.drawString(text, 0-(rect.width*0.5), 0+(rect.height*0.5));
            
            if(namesON == 1){
                float distancia;
                float distancia2;
                distancia = ofMap(rect.height, 25, 1000, 55, 625);
                distancia2 = ofMap(rect.width, 25, 1000, 55, 525);
                font2.drawStringCentered(nombre, distancia2 * (-1), distancia);
            }
            
            if(autoOrbit == 1){
                camera.orbit(ofGetElapsedTimef()*orbitX, ofGetElapsedTimef()*orbitY, 500, ofVec3f(rect.x, rect.y, 250));
            }
            
            if(distanceLockON == 1){
                float distancia;
                distancia = ofMap(rect.height, 26, 1234, 500, 1234 * 1.25);
                camera.setDistance(distancia);
            }
            
            if(distanceLockON == 0){
                camera.setDistance(100);
            }
            
        };
        
        ofRotateX(vRotX[i]);
        ofRotateY(vRotY[i]);
        ofRotateZ(vRotZ[i]);
        ofSetColor(255,vOpacity[i]);
        ofScale(vScaleX[i],vScaleY[i]);
        ofTranslate((vX[i]),vY[i], vZ[i]-200);
        videoLC[i].draw(0, 0);
        
        camera.end();
        
        if(canonGenerator == 1){
            videoLC[i].setLoopState(OF_LOOP_NONE);
        }
        
        ofPopMatrix();
        
    }
    
    if(feedbackON == 1){
        screenImage.loadScreenData(0,0, ofGetWidth(), ofGetHeight());
    }
    
    fbo.end();
    
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
