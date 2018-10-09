
#include "ofApp.h"

void ofApp::setup(){
    
    // iniciales
    
    ofSetCircleResolution(50);
    ofBackground(0, 0, 0);
    //ofSetVerticalSync(true);
    ofSetWindowTitle("Orbit");
    
    winSizeW = 1200;
    winSizeH = 740;
    lcneON = 1;
    
    ofSetWindowShape(winSizeW, winSizeH); /// La resolución de la pantalla final
    ofSetFrameRate(30);
    ofHideCursor();
    tempo = 1;
    onScreen = 1;
    depth = 0;
    ofSetLineWidth(4);
    
    // domemmaster
    
    domeDistance=20;
    domemaster.setup();
    domemaster.setCameraPosition(0,0,domeDistance);
    domeON = 0;
    
    // camara
    
    camera.setDistance(1500);
    autoOrbit = 0;
    orbitX = 0;
    orbitY = 0;
    distanceLockON = 1;

    
    // shader blur
    
#ifdef TARGET_OPENGLES
    shaderBlurX.load("shadersES2/shaderBlurX");
    shaderBlurY.load("shadersES2/shaderBlurY");
#else
    if(ofIsGLProgrammableRenderer()){
        shaderBlurX.load("shadersGL3/shaderBlurX");
        shaderBlurY.load("shadersGL3/shaderBlurY");
    }else{
        shaderBlurX.load("shadersGL2/shaderBlurX");
        shaderBlurY.load("shadersGL2/shaderBlurY");
    }
#endif
    
    fboBlurOnePass.allocate(ofGetWidth(), ofGetHeight());
    fboBlurTwoPass.allocate(ofGetWidth(), ofGetHeight());
    
    blur = 0;
    blurON = 0;
    
    // Syphon
    
#if (defined(__APPLE__) && defined(__MACH__))
    client.setup();
    syphonON = 0;
#endif
    
    // 3d
    
    model3D.loadModel("3d/terrain.obj");
    model3D.setPosition(0, 0, 0);
    modelON = 0;
    multiModelON = 0;
    
    ofDisableArbTex();
    asteroid.enableMipmap();
    //ofDisableArbTex();
    ofLoadImage(asteroid,"img/stone.jpg");
    asteroid.generateMipmap();
    asteroid.setTextureWrap(GL_REPEAT, GL_REPEAT);
    asteroid.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    
    ofEnableArbTex();
    
    // texto
    
    //font2.load("fonts/CloisterBlack.ttf", 80, true, true, true);
    //font.load("fonts/CloisterBlack.ttf", 80, true, true, true);
    titleFont.load("fonts/DejaVuSansMono.ttf", 20);
    font2.load("fonts/DejaVuSansMono.ttf", 40, true, true, true);
    font.load("fonts/DejaVuSansMono.ttf", 40, true, true, true);
    
    textON = 0;
    texto = "";
    nombre = "";
    fixText = 1;
    textRotX = 0;
    textRotY = 0;
    textRotZ = 0;
    namesON = 0;
    multiMsg = 0;
    
    // glitch
    
    plane.set(ofGetWidth(), ofGetHeight());
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
    
    // información
    
    timeElapsedON=0;
    
    // objetos
    
    icoIntON = 0;
    icoOutON = 0;
    stars = 0;
    planeMatrix.set(3000, 3000);   ///dimensions for width and height in pixels
    planeMatrix.setPosition(0, 0, 0); /// position in x y z
    planeMatrix.setResolution(32, 32);
    
    // OSC
    
    XML.load ("xml/OSCConf.xml");
    portOut = XML.getValue("PORT:NAME:OUT",5613);
    sender.setup("127.0.0.1",portOut);
    portIn = XML.getValue("PORT:NAME:IN",5612);
    reciever.setup(portIn);
    
    for(int i = 0; i < LIM; i++){
        
        // videos
        
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
        
        // multMsg
        
        fontOrb[i].load("fonts/DejaVuSansMono.ttf", 40, true, true, true);
        rectOrb[i];
        textOrb[i] = "";
        textOrbPrima[i] = "";
        noiseX[i] = 0;
        noiseY[i] = 0;
        msgRotX[i] = 0;
        msgRotY[i] = 0;
        msgRotZ[i] = 0;
        
        // multiModel
        
        multiModelX[i] = 0;
        multiModelY[i] = 0;
        multiModelZ[i] = 0;
        multiModelRotX[i] = 0;
        multiModelRotY[i] = 0;
        multiModelRotZ[i] = 0;
        
    }
    
    // retro alimentación
    
    retroON = 1;
    position = 0;
    screenImage.allocate(960*2, 560*2, GL_RGBA);
    retroX = 40;
    retroY = 40;
    feedback = 0;
    retroVel = 4;
    canonGenerator = 0;
    feedbackON = 0; /// activarla de vez en cuando chin
    
    // luces
    
    lightON = 1;
    
    colorLight1 = ofColor(255, 113, 206);
    colorLight2 = ofColor( 1, 205, 254 );
    colorLight3 = ofColor(185, 103, 255);
    
    ofSetSmoothLighting(true);
    
    pointLight.setDiffuseColor( colorLight1 );
    pointLight.setSpecularColor( colorLight1 );
    
    pointLight2.setDiffuseColor( colorLight2 );
    pointLight2.setSpecularColor( colorLight2 );
    
    pointLight3.setDiffuseColor( colorLight3 );
    pointLight3.setSpecularColor( colorLight3 );
    
    // shininess is a value between 0 - 128, 128 being the most shiny //
    material.setShininess( 120 );
    // the light highlight of the material //
    material.setSpecularColor(ofColor(255, 255, 255, 255));
    material.setDiffuseColor(ofColor(255, 255, 255, 255));
    
}

void ofApp::update(){
    
    /// luces
    
    //pointLight.setPosition(ofGetWidth()/2, ofGetHeight()/2, 500);
    
    pointLight.setPosition((ofGetWidth()*.5)+ cos(ofGetElapsedTimef()*.5)*(ofGetWidth()*.3), ofGetHeight()/2, 500);
    pointLight2.setPosition((ofGetWidth()*.5)+ cos(ofGetElapsedTimef()*.15)*(ofGetWidth()*.3),
                            ofGetHeight()*.5 + sin(ofGetElapsedTimef()*.7)*(ofGetHeight()), 300);
    
    pointLight3.setPosition(
                            cos(ofGetElapsedTimef()*1.5) * ofGetWidth()*.5,
                            sin(ofGetElapsedTimef()*1.5f) * ofGetWidth()*.5,
                            cos(ofGetElapsedTimef()*.2) * ofGetWidth()
                            );
    ;
    
    // retroalmientación
    
    position = 500 + 250 * sin(ofGetElapsedTimef() * 8);
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
            //model3DOn[n] = false;
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
        
        if (m.getAddress() == "/modelON" && m.getNumArgs() == 1){
            modelON = m.getArgAsInt(0);
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
        
        if (m.getAddress() == "/multiModel" && m.getNumArgs() == 3){
            string temp = "3d/" + m.getArgAsString(2) + ".obj";
            multiModel[m.getArgAsInt(1)].loadModel(temp);
            multiModelON = m.getArgAsInt(0);
        }
        
        if (m.getAddress() == "/multiModelFree" && m.getNumArgs() == 1){
            multiModelON = m.getArgAsInt(0);
            multiModel[m.getArgAsInt(0)].clear();
        }
        
        if (m.getAddress() == "/modelFree" && m.getNumArgs() == 1){
            model3D.clear();
            modelON = m.getArgAsInt(0);
        }
        
        if (m.getAddress() == "/multiModelPos" && m.getNumArgs() == 4){
            multiModelX[m.getArgAsInt(0)] = m.getArgAsInt(1);
            multiModelY[m.getArgAsInt(0)] = m.getArgAsInt(2);
            multiModelZ[m.getArgAsInt(0)] = m.getArgAsInt(3);
        }
        
        if (m.getAddress() == "/multiModelRot" && m.getNumArgs() == 4){
            multiModelRotX[m.getArgAsInt(0)] = m.getArgAsInt(1);
            multiModelRotY[m.getArgAsInt(0)] = m.getArgAsInt(2);
            multiModelRotZ[m.getArgAsInt(0)] = m.getArgAsInt(3);
        }
        
        if (m.getAddress() == "/blur" && m.getNumArgs() == 2){
            blurON = m.getArgAsInt(0);
            blur = m.getArgAsFloat(1);
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
        
        if (m.getAddress() == "/multiMsg"  &&  m.getNumArgs() == 7){
            int n = m.getArgAsInt(0);
            multiMsg = 1;
            noiseX[m.getArgAsInt(0)] = m.getArgAsFloat(1);
            noiseY[m.getArgAsInt(0)] = m.getArgAsFloat(2);
            msgRotX[m.getArgAsInt(0)] = m.getArgAsFloat(3);
            msgRotY[m.getArgAsInt(0)] = m.getArgAsFloat(4);
            msgRotZ[m.getArgAsInt(0)] = m.getArgAsFloat(5);
            textOrb[m.getArgAsInt(0)] = m.getArgAsString(6);
        }
        
        if (m.getAddress() == "/domeON"  &&  m.getNumArgs() == 1){
            domeON = m.getArgAsInt(0);
            lightON = 0;
        }
        
        if (m.getAddress() == "/onScreen"  &&  m.getNumArgs() == 1){
            onScreen = m.getArgAsInt(0);
        }
        
        if (m.getAddress() == "/icosON"  &&  m.getNumArgs() == 1){
            icoOutON = m.getArgAsInt(0);
            icoIntON = m.getArgAsInt(0);
        }
        
        if (m.getAddress() == "/stars"  &&  m.getNumArgs() == 1){
            stars = m.getArgAsInt(0);
        }
        
        if (m.getAddress() == "/domeDistance"  &&  m.getNumArgs() == 1){
            domeDistance = m.getArgAsInt(0);
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
            depth = m.getArgAsInt(0);
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
    ofDisableAlphaBlending();
    ofSetRectMode(OF_RECTMODE_CORNER);
    
    myGlitch.generateFx();
    
    if(domeON == 0){
        if(blurON == 1){
            drawBlur();
        }
        if(blurON == 0){
            fbo.draw(0, 0);
        }
    }
    
    if(domeON == 1){
        for (int i=0; i<domemaster.renderCount; i++){
            domemaster.begin(i);
            drawFbo();
            domemaster.end(i);
        }
        domemaster.draw();
    }
    
}

//--------------------------------------------------------------

void ofApp::drawBlur(){
    
    ofEnableAlphaBlending();
    
    //float blur = ofMap(mouseX, 0, ofGetWidth(), 0, 10, true);
    
    fboBlurOnePass.begin();
    shaderBlurX.begin();
    
    ofClear(0);
    shaderBlurX.setUniform1f("blurAmnt", blur);
    fbo.draw(0, 0);
    shaderBlurX.end();
    fboBlurOnePass.end();
    
    fboBlurTwoPass.begin();
    shaderBlurY.begin();
    ofClear(0);
    shaderBlurY.setUniform1f("blurAmnt", blur);
    fboBlurOnePass.draw(0, 0);
    shaderBlurY.end();
    fboBlurTwoPass.end();

    fboBlurTwoPass.draw(0, 0);
    
}

//--------------------------------------------------------------

void ofApp::drawFbo(){
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofScale(0.125/2, 0.125/2);
    ofTranslate(0, 0, 0);
    ofRotateX(180);
    
    //fbo.getTexture().bind();
    //plane.draw();
    //fbo.getTexture().unbind();
    
    if(blurON == 1){
        drawBlur();
    }
    
    if(blurON == 0){
        fbo.draw(0, 0);
    }
    
}

//--------------------------------------------------------------

void ofApp::drawScene(){
    
    fbo.begin();
    ofClear(0);
    ofEnableArbTex();
    
    if(depth == 0){
    ofEnableDepthTest();
    }
    
    if(depth == 1){
        ofDisableDepthTest();
    }
    
    ofEnableSmoothing();
    ofEnableAntiAliasing();
    
    if(timeElapsedON==1){
        ofDrawBitmapString("timeElapsed: " + ofToString(ofGetElapsedTimef()), 30, 30);
    }
    
    if(feedbackON == 1){
        screenImage.draw(0+retroX, 0+retroY, ofGetWidth()-80, ofGetHeight()-80);
    }
    
    // syphon
    
#if (defined(__APPLE__) && defined(__MACH__))
    
    if(syphonON == 1){
        client.draw(0, 0);
    };
    
#endif
    
    //for(int i = 0; i < LIM; i++){
    
    //    ofPushMatrix();
    // texto fuera de cámara
    
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
    ofRectangle rect;
    
    // videos
    
    for(int i = 0; i < LIM; i++){
        ofPushMatrix();
        ofRotateX(vRotX[i]);
        ofRotateY(vRotY[i]);
        ofRotateZ(vRotZ[i]);
        ofSetColor(255,vOpacity[i]);
        ofScale(vScaleX[i],vScaleY[i]);
        ofTranslate((vX[i]),vY[i], vZ[i]-200);
        videoLC[i].draw(0, 0);
        ofPopMatrix();
    }
    
    /// luces
    
    if(lightON == 1){
        ofEnableLighting();
        //pointLight.draw();
        //pointLight2.draw();
        //pointLight3.draw();
        pointLight.enable();
        pointLight2.enable();
        pointLight3.enable();
        material.begin();
    }
    
    if(lightON == 0){
        ofDisableLighting();
    }
    
    ofPushMatrix();
    
    text = wrapString(texto, 500);
    rect = font.getStringBoundingBox(text, 0, 0);
    ofSetLineWidth(2);

    if(modelON == 1){
        float distancia;
        distancia = ofMap(rect.height, 26, 1234, 20, 50);
        ofPushMatrix();
        ofRotateX(0);
        ofRotateY(0);
        ofRotateZ(180);
        ofScale(16, 16, 16);
        ofTranslate(0, 0, 0);
        //planeMatrix.setPosition(0, 0, 0); /// position in x y z
        //planeMatrix.drawWireframe();
        model3D.setPosition(0, distancia, 0);
        asteroid.bind();
        model3D.drawFaces();
        asteroid.unbind();
        ofPopMatrix();
    }
    
    if(multiModelON == 1){
        for(int i = 0; i < LIM; i++){
        float distancia;
        distancia = ofMap(rect.height, 26, 1234, 20, 50);
        ofPushMatrix();
        ofRotateX(ofGetElapsedTimef() * multiModelRotX[i]);
        ofRotateY(ofGetElapsedTimef() * multiModelRotY[i]);
        ofRotateZ(ofGetElapsedTimef() * multiModelRotZ[i]);
        ofScale(2, 2, 2);
        ofTranslate(0, 0, 0);
        //planeMatrix.setPosition(0, 0, 0); /// position in x y z
        //planeMatrix.drawWireframe();
        multiModel[i].setPosition(multiModelX[i], multiModelY[i], multiModelZ[i]);
        asteroid.bind();
        multiModel[i].drawFaces();
        asteroid.unbind();
        ofPopMatrix();
        }
    }
    
    // ICOS
    
    if(icoIntON == 1){
        ofPopMatrix();
        ofRotateZ(0);
        icoSphere.setRadius(rect.width*1);
        icoSphere.setPosition(rect.x, rect.y+50, 0);
        icoSphere.setResolution(0);
        icoSphere.drawWireframe();
        ofPushMatrix();
    }
    
    /*
    if(icoOutON == 1){
        ofPopMatrix();
        ofRotateZ(0);
        icoSphere.setRadius(rect.width*1);
        icoSphere.setPosition(rect.x, rect.y+50, 0);
        icoSphere.setResolution(1);
        icoSphere.drawWireframe();
        ofPushMatrix();
    }
     */
    
    // estrellas puntos
    
    if(stars == 1){
        
        for (int i = 0;i < 500;i++){
            
            ofPushMatrix();
            ofRotateZ(ofGetElapsedTimef()+10);

            ofTranslate((ofNoise(i/2.4)-0.5)*5000,
                        (ofNoise(i/5.6)-0.5)*5000,
                        (ofNoise(i/8.2)-0.5)*5000);
            
            ofCircle(0, 0, (ofNoise(i/3.4)-0.1)*2);
            ofPopMatrix();
        }
        
    }

    if(textON == 1 && fixText == 0){
        
        //pointLight.draw();
        //pointLight2.draw();
        //pointLight3.draw();
        
        /*
         if(onScreen == 1){
         text = wrapString(clientTyping, 200);
         rect = font.getStringBoundingBox(text, 0, 0);
         titleFont.drawStringAsShapes(text, 0-(rect.width*0.75), 0+(rect.height*0.5));
         }
         
         //if(onScreen == 0){
         text = wrapString(texto, 200);
         rect = font.getStringBoundingBox(text, 0, 0);
         //ofNoFill();
         font.drawStringAsShapes(text, 0-(rect.width*0.5), 0+(rect.height*0.5));
         //}
         */
        
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofTranslate(0, 0, 0);
        ofScale(0.5, 0.5);
        ofRotateX(textRotX);
        ofRotateY(textRotY);
        ofRotateZ(textRotZ);
        
        //text = wrapString(texto, 500);
        //rect = font.getStringBoundingBox(text, 0, 0);
        //ofNoFill();
        font.drawString(text, 0-(rect.width*0.5), 0+(rect.height*0.5));
        //font.drawStringCentered(text, 0-(rect.width*0.5), 0+(rect.height*0.5));

	//font.drawStringExtruded(text, 0-(rect.width*0.5), 0+(rect.height*0.5));

        
        ///
        if(namesON == 1){
            ofRotateZ(0);
            float distancia;
            float distancia2;
            distancia = ofMap(rect.height, 25, 1000, 55, 625);
            distancia2 = ofMap(rect.width, 25, 1000, 55, 525);
            font2.drawString(nombre, distancia2 * (-1), distancia);
        }
        
        if(autoOrbit == 1){
            camera.orbit(ofGetElapsedTimef()*orbitX, ofGetElapsedTimef()*orbitY, 500, ofVec3f(rect.x, rect.y, 250));
        }
        
        if(distanceLockON == 1){
            float distancia;
            distancia = ofMap(rect.height, 26, 1234, 350, 700);
            camera.setDistance(distancia);
        }
        
        if(distanceLockON == 0){
            camera.setDistance(100);
        }
        
    };
    
    if(multiMsg == 1){
        
        for(int i = 0; i < LIM; i++){
            // aquí había push matrix
            ofPushMatrix();
            ofTranslate(0, 0, 0);
            ofScale(1, 1);
            ofRotateX(msgRotX[i]);
            ofRotateY(msgRotY[i]);
            ofRotateZ(msgRotZ[i]);
            textOrbPrima[i] = wrapString(textOrb[i], 500);
            rectOrb[i] = fontOrb[i].getStringBoundingBox(textOrbPrima[i], 0, 0);
            //ofNoFill();
            fontOrb[i].drawStringAsShapes(textOrbPrima[i], noiseX[i] + (rect.width*0.5),  noiseY[i] + (rect.height*0.5));
            ofPopMatrix();
        }
        
    }
    
    ofPopMatrix();
   
    if(lightON == 1){
        
        material.end();
        
    }

    
    camera.end();
    
    if(feedbackON == 1){
        screenImage.loadScreenData(0,0, ofGetWidth(), ofGetHeight());
    }
    
    fbo.end();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    // if we didn't hit return, add the key to our string
    if(key != OF_KEY_RETURN){
        // some trickery: ignore the backspace key
        if(key != OF_KEY_BACKSPACE){
            clientTyping += key;
        }
        else{
            if(clientTyping.size() > 0){
                clientTyping.erase(clientTyping.end() - 1);
            }
        }
    }
    // hit Return, time to send the osc message if it's not empty
    else{
        
        // aquí iría el old. a ver si funciona.
        clientTyping = "";
    }
    
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
    
    if(autoOrbit== 1 && orbitX != 0){
        autoOrbit = 0;
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    if(autoOrbit== 0 && orbitX != 0){
        autoOrbit = 1;
        
    }
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
