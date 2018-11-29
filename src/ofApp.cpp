/*

 fbo sin alpha, cam distance, inout esferas, tamaños estrellas lookat
 
 Visualizador de actividad alrrededor de la pantalla.
 asignación de vectores dependiendo de la posición de los objetos. Asignar la posición de los objetos a nodos.
 
 */

#include "ofApp.h"

void ofApp::setup(){
    
    // iniciales
    
    ofSetCircleResolution(50);
    ofBackground(0, 0, 0);
    //ofSetVerticalSync(true);
    ofSetWindowTitle("Orbit");
    
    winSizeW = 1360;
    winSizeH = 750;
    lcneON = 1;
    lago = 1;
    
    ofSetWindowShape(winSizeW, winSizeH); /// La resolución de la pantalla final
    ofSetFrameRate(30);
    ofHideCursor();
    tempo = 1;
    intOnScreen = 1;
    outOnScreen = 0;
    depth = 0;
    //ofSetLineWidth(4);
    videoTex = 0;
    colorBackground = 0;
    
    // domemmaster
    
    domeDistance=5;
    domemaster.setup();
    domemaster.setCameraPosition(0, 0, domeDistance);
    domeON = 0;
    
    // camara
    
    camdistance = 250;
    camera.setDistance(camdistance);
    autoOrbit = 0;
    orbitX = 0;
    orbitY = 0;
    distanceLockON = 1;
    centro = ofVec3f(0, 0, 0);
    posOrbit = ofVec3f(0, 0, 0);
    
    // Shaders
    
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
    
    fboBlurOnePass.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA, 8);
    fboBlurTwoPass.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA, 8);
    blur = 0;
    blurON = 0;
    glitchBlurX.load("Shaders/glitchBlurX");
    glitchBlurY.load("Shaders/glitchBlurY");
    fboGlitchBlurOnePass.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    fboGlitchBlurTwoPass.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    glitchBlur = 0;
    glitchBlurON = 0;
    clearGB = 0;
    
    // 3d
    
    model3D.loadModel("3d/nave.obj");
    model3D.setPosition(0, 0, 0);
    modelON = 0;
    multiModelON = 0;
    ofDisableArbTex();
    modelScale = 4;
    textureON = 0;
    ofEnableArbTex();
    centroSph.setRadius(20);
    reticulaSph.setRadius(400);
    centroSphON = 0;
    reticulaSphON = 0;
    
    ofDisableArbTex();
    asteroid.enableMipmap();
    //ofDisableArbTex();
    ofLoadImage(asteroid,"img/stone.jpg");
    asteroid.generateMipmap();
    asteroid.setTextureWrap(GL_REPEAT, GL_REPEAT);
    asteroid.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    ofEnableArbTex();
    
    // mecho
    
    //image.loadImage("img/algorave16.png");
    //image.resize(100, 100);
    //mesh.setMode(OF_PRIMITIVE_POINTS);
    glPointSize(1);
    ofSetLineWidth(1);
    intensityThreshold = 100;
    timeScale = 1;
    int numVerts = mesh.getNumVertices();
    meshVecX = 0;
    meshVecY = 0;
    meshVecZ = 0;
    meshPosX = 0;
    meshPosY = 0;
    meshPosZ = 0;
    meshRotX = 0;
    meshRotY = 0;
    meshRotZ = 0;
    meshscale = 1;
     
    /*
    
    // We need to calculate our center point for the mesh
    // ofMesh has a method called getCentroid() that will
    // find the average location over all of our vertices
    meshCentroid = mesh.getCentroid();
    
    // Now that we know our centroid, we need to know the polar coordinates (distance and angle)
    // of each vertex relative to that center point.
    // We've found the distance between points before, but what about the angle?
    // This is where atan2 comes in.  atan2(y, x) takes an x and y value and returns the angle relative
    //     to the origin (0,0).  If we want the angle between two points (x1, y1) and (x2, y2) then we
    //     just need to use atan2(y2-y1, x2-x1).
    for (int i=0; i<numVerts; ++i) {
        ofVec3f vert = mesh.getVertex(i);
        float distance = vert.distance(meshCentroid);
        float angle = atan2(vert.y-meshCentroid.y, vert.x-meshCentroid.x);
        distances.push_back(distance);
        angles.push_back(angle);
    }
    
    // These variables will allow us to toggle orbiting on and off
    orbiting = false;
    startOrbitTime = 0.0;
    meshCopy = mesh;
    
     */
    // texto
    
    //titleFont.load("fonts/CloisterBlack.ttf", 20);
    //font2.load("fonts/CloisterBlack.ttf", 40, true, true, true);
    //font.load("fonts/CloisterBlack.ttf", 40, true, true, true);
    titleFont.load("fonts/DejaVuSansMono.ttf", 20);
    font2.load("fonts/DejaVuSansMono.ttf", 40, true, true, true);
    font.load("fonts/DejaVuSansMono.ttf", 40, true, true, true);
    fontOut.load("fonts/DejaVuSansMono.ttf", 40, true, true, true);

    textON = 1;
    textOut = "";
    text = "";
    nombre = "";
    fixText = 1;
    textRotX = 0;
    textRotY = 0;
    textRotZ = 0;
    namesON = 0;
    multiMsg = 0;
    cero = "";
    uno = "";
    dos = "";
    tres = "";
    mechON=0;
    
    // glitch
    
     fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB );
    //fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F_ARB); // esto era un resquicio. El alpha hace aliasing pero permite que haya blur ;( Antes estaba rgba16. 32 es demasiado para mi computadora antes era una combinación loca pero ahora no pongo sin alphas parece que funciona todo
    //fbo.getTextureReference().setTextureMinMagFilter(GL_NEAREST,GL_NEAREST);
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
    glitchON = 0;
    
    // información
    
    timeElapsedON=0;
    
    // objetos
    
    icoIntON = 0;
    icoOutON = 0;
    stars = 0;
    numstars = 100;
    sizestars = 1;
    dispstarsX = 1000;
    dispstarsY = 1000;
    dispstarsZ = 1000;
    
    // OSC
    
    XML.load ("xml/OSCConf.xml");
    portOut = XML.getValue("PORT:NAME:OUT",5613);
    sender.setup("127.0.0.1",portOut);
    portIn = XML.getValue("PORT:NAME:IN",5612);
    reciever.setup(portIn);
    
    // client side
    clientDestination = "127.0.0.1";
    //clientDestination    = "192.168.0.115"; // if you send to another instance enter IP here
    clientSender.setup(clientDestination, 5612);
    
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
        multiModelScale[i] = 1;
        texturas[i].enableMipmap();
        texturas[i].setTextureWrap(GL_REPEAT, GL_REPEAT);
        texturas[i].setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    }
    
    // retro alimentación
    
    retroON = 1;
    position = 0;
    screenImage.allocate(960*2, 560*2, GL_RGBA16F_ARB, 8);
    retroX = 40;
    retroY = 40;
    feedback = 0;
    retroVel = 4;
    canonGenerator = 0;
    feedbackON = 0; /// activarla de vez en cuando chin
    
    // luces
    
    lightON = 1;
    
    for(int i = 0; i < LIM2; i++){
        clR[i] = 255;
        clG[i] = 255;
        clB[i] = 255;
    }

    colorLight1 = ofColor(clR[0], clG[0], clB[0]);
    colorLight2 = ofColor(clR[1], clG[1], clB[1]);
    colorLight3 = ofColor(clR[2], clG[2], clB[2]);
    
    //colorLight1 = ofColor(255, 113, 206);
    //colorLight2 = ofColor( 1, 205, 254 );
    //colorLight3 = ofColor(185, 103, 255);
    
    ofSetSmoothLighting(true);
    
    // shininess is a value between 0 - 128, 128 being the most shiny //
    material.setShininess( 20 );
    // the light highlight of the material //
    //material.setSpecularColor(ofColor(255, 255, 255, 255));
    material.setSpecularColor(ofColor(255, 255, 255, 255));
    
    radius        = 180.f;
    center.set(ofGetWidth()*.5, ofGetHeight()*.5, 0);

}

void ofApp::update(){
    
    /*
    if (orbiting) {
        int numVerts = mesh.getNumVertices();
        for (int i=0; i<numVerts; ++i) {
            ofVec3f vert = mesh.getVertex(i);
            float distance = distances[i];
            float angle = angles[i];
            float elapsedTime = ofGetElapsedTimef() - startOrbitTime;
            
            // Lets adjust the speed of the orbits such that things that are closer to
            // the center rotate faster than things that are more distant
            float speed = ofMap(distance, 0, 200, 0.5, 0.25, true);
            
            // To find the angular rotation of our vertex, we use the current time and
            // the starting angular rotation
            float rotatedAngle = elapsedTime * speed + angle;
            
            // Remember that our distances are calculated relative to the centroid of the mesh, so
            // we need to shift everything back to screen coordinates by adding the x and y of the centroid
            vert.x = distance * cos(rotatedAngle) + meshCentroid.x;
            vert.y = distance * sin(rotatedAngle) + meshCentroid.y;
            
            mesh.setVertex(i, vert);
        }
    }
    
    orbiting = true;             // This inverts the boolean
    //startOrbitTime = ofGetElapsedTimef();
    //mesh = meshCopy;            // This restores the mesh to its original values
    
     */
    
    if(mechON == 1){
        int numVerts = mesh.getNumVertices();
        for (int i=0; i<numVerts; ++i) {
            ofVec3f vert = mesh.getVertex(i);
            float time = ofGetElapsedTimef();
            ofVec3f timeOffsets = offsets[i];
            
            // A typical design pattern for using Perlin noise uses a couple parameters:
            // ofSignedNoise(time*timeScale+timeOffset)*displacementScale
            //     ofSignedNoise(time) gives us noise values that change smoothly over time
            //     ofSignedNoise(time*timeScale) allows us to control the smoothness of our noise (smaller timeScale, smoother values)
            //     ofSignedNoise(time+timeOffset) allows us to use the same Perlin noise function to control multiple things and have them look as if they are moving independently
            //     ofSignedNoise(time)*displacementScale allows us to change the bounds of the noise from [-1, 1] to whatever we want
            // Combine all of those parameters together, and you've got some nice control over your noise
            
            vert.x += (ofSignedNoise(time*timeScale+timeOffsets.x)) * meshVecX;
            vert.y += (ofSignedNoise(time*timeScale+timeOffsets.y)) * meshVecX;
            vert.z += (ofSignedNoise(time*timeScale+timeOffsets.z)) * meshVecZ;
            
            mesh.setVertex(i, vert);
        }
    }
    
    /// luces
    
    pointLight.setDiffuseColor( colorLight1 );
    pointLight.setSpecularColor( colorLight1 );
    pointLight2.setDiffuseColor( colorLight2 );
    pointLight2.setSpecularColor( colorLight2 );
    pointLight3.setDiffuseColor( colorLight3 );
    pointLight3.setSpecularColor( colorLight3 );
    
    //pointLight.setPosition(ofGetWidth()/2, ofGetHeight()/2, 500);
    
    pointLight.setPosition((ofGetWidth()*.5)+ cos(ofGetElapsedTimef()*.5)*(ofGetWidth()*.3), ofGetHeight()/2, 500);
    
    pointLight2.setPosition((ofGetWidth()*.5)+ cos(ofGetElapsedTimef()*.15)*(ofGetWidth()*.3),
                            ofGetHeight()*.5 + sin(ofGetElapsedTimef()*.7)*(ofGetHeight()), 300);
    
    pointLight3.setPosition(
                            cos(ofGetElapsedTimef()*1.5) * radius * 2 + center.x,
                            sin(ofGetElapsedTimef()*1.5f) * radius * 2 + center.y,
                            cos(ofGetElapsedTimef()*.2) * radius * 2 + center.z);
    
    //pointLight.setPosition(cos(ofGetElapsedTimef()*.6f) * radius * 2 + center.x,
    //                       sin(ofGetElapsedTimef()*.8f) * radius * 2 + center.y,
    //                       -cos(ofGetElapsedTimef()*.8f) * radius * 2 + center.z);
    
    ;
    
    // retroalmientación
    
    position = 500 + 250 * sin(ofGetElapsedTimef() * 8);
    screenImage.loadScreenData(0,0,ofGetWidth(), ofGetHeight());
    
    //// OSC
    
    while (reciever.hasWaitingMessages()){
        
        ofxOscMessage m;
        reciever.getNextMessage(&m);
        
        if (m.getAddress() == "/vload"  &&  m.getNumArgs() ==2){
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
        
        if (m.getAddress() == "/vfree"  &&  m.getNumArgs() == 1){
            videoLC[m.getArgAsInt(0)].close();
            vX[m.getArgAsInt(0)] = 0;
            vY[m.getArgAsInt(0)] = 0;
            vSpeed[m.getArgAsInt(0)] = 1;
            vOpacity[m.getArgAsInt(0)] = 255;
            vW[m.getArgAsInt(0)] = videoLC[m.getArgAsInt(0)].getWidth();
            vH[m.getArgAsInt(0)] = videoLC[m.getArgAsInt(0)].getHeight();
        }
        
        if (m.getAddress() == "/vspeed" && m.getNumArgs() == 2){
            int n = m.getArgAsInt(0);
            videoLC[n].setSpeed(m.getArgAsFloat(1)*tempo);
        }
        
        if (m.getAddress() == "/light" && m.getNumArgs() == 1){
            lightON = m.getArgAsInt(0);
        }
        
        if (m.getAddress() == "/cbackground" && m.getNumArgs() == 1){
            colorBackground = m.getArgAsInt(0);
        }
        
        if (m.getAddress() == "/sceneload" && m.getNumArgs() == 2){
	  string temp = "3d/" + m.getArgAsString(1) + ".obj";
	  model3D.loadModel(temp);
	  modelON = m.getArgAsInt(0);
        }

	if (m.getAddress() == "/sceneclear"){
            model3D.clear();
        }
	
        if (m.getAddress() == "/tempo" && m.getNumArgs() == 1){
            tempo = m.getArgAsInt(0);
        }
        
        if (m.getAddress() == "/meshdisplacement" && m.getNumArgs() == 3){
            meshVecX = m.getArgAsFloat(0);
            meshVecY = m.getArgAsFloat(1);
            meshVecZ = m.getArgAsFloat(2);
        }
        
        if (m.getAddress() == "/vop" && m.getNumArgs() == 2){
            vOpacity[m.getArgAsInt(0)] = m.getArgAsInt(1);
        }
        
        if (m.getAddress() == "/vpos" && m.getNumArgs() == 4){ /// posZ
            vX[m.getArgAsInt(0)] = m.getArgAsInt(1);
            vY[m.getArgAsInt(0)] = m.getArgAsInt(2);
            vZ[m.getArgAsInt(0)] = m.getArgAsInt(3);
            /*
             if(canonGenerator == 1){
             videoLC[m.getArgAsInt(0)].play();
             }             */
        }
        
        if (m.getAddress() == "/vscale" && m.getNumArgs() == 3){
            //vScaleX[m.getArgAsInt(0)] = m.getArgAsFloat(1)/vW[m.getArgAsInt(0)];
            //vScaleY[m.getArgAsInt(0)] = m.getArgAsFloat(2)/vH[m.getArgAsInt(0)];
            vScaleX[m.getArgAsInt(0)] = m.getArgAsFloat(1);
            vScaleY[m.getArgAsInt(0)] = m.getArgAsFloat(2);
        }
        
        if (m.getAddress() == "/fbxy" && m.getNumArgs() == 2){
            retroX = m.getArgAsFloat(0);
            retroY = m.getArgAsFloat(1);
        }
        
        if (m.getAddress() == "/fbx" && m.getNumArgs() == 1){
            retroX = m.getArgAsFloat(0);
        }
        
        if (m.getAddress() == "/numstars" && m.getNumArgs() == 1){
            numstars = m.getArgAsFloat(0);
        }
        
        if (m.getAddress() == "/sizestars" && m.getNumArgs() == 1){
            sizestars = m.getArgAsFloat(0);
        }
        
        if (m.getAddress() == "/dispstars" && m.getNumArgs() == 1){
            dispstarsX = m.getArgAsFloat(0);
            dispstarsY = m.getArgAsFloat(0);
            dispstarsZ = m.getArgAsFloat(0);        }
        
        if (m.getAddress() == "/dispstarsxyz" && m.getNumArgs() == 3){
            dispstarsX = m.getArgAsFloat(0);
            dispstarsY = m.getArgAsFloat(1);
            dispstarsZ = m.getArgAsFloat(2);
        }
        
        if (m.getAddress() == "/font" && m.getNumArgs() == 1){
            if(m.getArgAsString(0) == "dejavu"){
                //font.load("fonts/CloisterBlack.ttf", 40, true, true, true);
                titleFont.load("fonts/DejaVuSansMono.ttf", 20);
                font2.load("fonts/DejaVuSansMono.ttf", 40, true, true, true);
                font.load("fonts/DejaVuSansMono.ttf", 40, true, true, true);
                fontOut.load("fonts/DejaVuSansMono.ttf", 40, true, true, true);
                for(int i = 0; i < LIM; i++){
                    fontOrb[i].load("fonts/DejaVuSansMono.ttf", 40, true, true, true);
                }
            }
            if(m.getArgAsString(0) == "malandrone"){
                //font.load("fonts/CloisterBlack.ttf", 40, true, true, true);
                titleFont.load("fonts/CloisterBlack.ttf", 20);
                font2.load("fonts/CloisterBlack.ttf", 40, true, true, true);
                font.load("fonts/CloisterBlack.ttf", 40, true, true, true);
                fontOut.load("fonts/CloisterBlack.ttf", 40, true, true, true);
                for(int i = 0; i < LIM; i++){
                    fontOrb[i].load("fonts/CloisterBlack.ttf", 40, true, true, true);
                }
            }
        }
        
        if (m.getAddress() == "/texclear"){
            textureON = 0;
            videoTex = 0;
        }
        
        if (m.getAddress() == "/itex" && m.getNumArgs() == 2){
            string temp = "img/" + m.getArgAsString(1);
            ofDisableArbTex();
            texturas[m.getArgAsInt(0)].generateMipmap();
            texturas[m.getArgAsInt(0)].setTextureWrap(GL_REPEAT, GL_REPEAT);
            texturas[m.getArgAsInt(0)].setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
            ofLoadImage(texturas[m.getArgAsInt(0)], temp);
            videoTex = 0;
            textureON = 1;
        }
        
        if (m.getAddress() == "/fby" && m.getNumArgs() == 1){
            retroY = m.getArgAsFloat(0);
        }
        
        if (m.getAddress() == "/lago" && m.getNumArgs() == 1){
            lago = m.getArgAsFloat(0)+0.1;
        }

        if (m.getAddress() == "/pointsize" && m.getNumArgs() == 1){
            glPointSize(m.getArgAsFloat(0));
        }
        
        if (m.getAddress() == "/mload" && m.getNumArgs() == 2){ /// modificar sintaxis
            string temp = "3d/" + m.getArgAsString(1) + ".obj";
            multiModel[m.getArgAsInt(0)].loadModel(temp);
            // multiModelON = m.getArgAsInt(0);
        }
        
        if (m.getAddress() == "/mfree" && m.getNumArgs() == 1){
            multiModel[m.getArgAsInt(0)].clear();
        }

	/*
        if (m.getAddress() == "/scenefree" && m.getNumArgs() == 1){
            model3D.clear();
            modelON = m.getArgAsInt(0);
        }
	*/
        
        if (m.getAddress() == "/mpos" && m.getNumArgs() == 4){
            multiModelX[m.getArgAsInt(0)] = m.getArgAsInt(1);
            multiModelY[m.getArgAsInt(0)] = m.getArgAsInt(2);
            multiModelZ[m.getArgAsInt(0)] = m.getArgAsInt(3);
        }
        
        if (m.getAddress() == "/mscale" && m.getNumArgs() == 2){
            multiModelScale[m.getArgAsInt(0)] = m.getArgAsFloat(1);
            
        }

	/*
        if (m.getAddress() == "/sceneload" && m.getNumArgs() == 2){
            string temp = "3d/" + m.getArgAsString(2) + ".obj";
            if(m.getArgAsInt(1) == 0){
                model3D.clear();
            }
            if(m.getArgAsInt(1) == 1){
                model3D.loadModel(temp);
            }
        }
	*/
        
        if (m.getAddress() == "/mrot" && m.getNumArgs() == 4){
            multiModelRotX[m.getArgAsInt(0)] = m.getArgAsInt(1);
            multiModelRotY[m.getArgAsInt(0)] = m.getArgAsInt(2);
            multiModelRotZ[m.getArgAsInt(0)] = m.getArgAsInt(3);
        }
        
        if (m.getAddress() == "/blur" && m.getNumArgs() == 2){
            blurON = m.getArgAsInt(0);
            blur = m.getArgAsFloat(1);
        }
        
        if (m.getAddress() == "/gblur" && m.getNumArgs() == 2){
            glitchBlurON = m.getArgAsInt(0);
            glitchBlur = m.getArgAsFloat(1);
        }
        
        if (m.getAddress() == "/vrot" && m.getNumArgs() == 4){
            vRotX[m.getArgAsInt(0)] = m.getArgAsFloat(1);
            vRotY[m.getArgAsInt(0)] = m.getArgAsFloat(2);
            vRotZ[m.getArgAsInt(0)] = m.getArgAsFloat(3);
        }

	/* // sirve de algo? 
        if (m.getAddress() == "/textRot" && m.getNumArgs() == 3){
            textRotX = m.getArgAsFloat(0);
            textRotY = m.getArgAsFloat(1);
            textRotZ = m.getArgAsFloat(2);
	    }*/
        
        /// faltan los mensajes en el modo on screen
        
        if (m.getAddress() == "/message"  &&  m.getNumArgs() == 2){
            texto = m.getArgAsString(0);
            nombre = m.getArgAsString(1);
        }
        
        if (m.getAddress() == "/message"  &&  m.getNumArgs() == 1){
            texto = m.getArgAsString(0);
        }
        
        if (m.getAddress() == "/sphinr"  &&  m.getNumArgs() == 1){
            texto = m.getArgAsString(0);
        }
        
        if (m.getAddress() == "/clear" &&  m.getNumArgs() == 1){
            clearGB = m.getArgAsInt(0);
        }
        
        if (m.getAddress() == "/spherein" &&  m.getNumArgs() == 1){
            centroSphON = m.getArgAsInt(0);
        }
        
        if (m.getAddress() == "/sphereout" &&  m.getNumArgs() == 1){
            reticulaSphON = m.getArgAsInt(0);
        }
        
        if (m.getAddress() == "/camdistance" &&  m.getNumArgs() == 1){
            camera.setDistance(m.getArgAsFloat(0));
        }
        
        if (m.getAddress() == "/scenescale"  &&  m.getNumArgs() == 1){
            modelScale = m.getArgAsFloat(0);
        }
        
        /// hace falta poder asignarlos independientemente
        
        if (m.getAddress() == "/vtex"  &&  m.getNumArgs() == 1){
            string temp = "videos/" + m.getArgAsString(0);
            videoTex = 1;
            textureON = 0;
            tempPlayer.setPixelFormat(OF_PIXELS_RGBA);
            tempPlayer.setLoopState(OF_LOOP_NORMAL);
            tempPlayer.load(temp);
            tempPlayer.play();
        }
        
        if (m.getAddress() == "/multimsg"  &&  m.getNumArgs() == 7){
            int n = m.getArgAsInt(0);
            multiMsg = 1;
            noiseX[m.getArgAsInt(0)] = m.getArgAsFloat(1);
            noiseY[m.getArgAsInt(0)] = m.getArgAsFloat(2);
            msgRotX[m.getArgAsInt(0)] = m.getArgAsFloat(3);
            msgRotY[m.getArgAsInt(0)] = m.getArgAsFloat(4);
            msgRotZ[m.getArgAsInt(0)] = m.getArgAsFloat(5);
            textOrb[m.getArgAsInt(0)] = m.getArgAsString(6);
        }
        
        if (m.getAddress() == "/dome"  &&  m.getNumArgs() == 1){
            domeON = m.getArgAsInt(0);
            lightON = 0;
        }
        
        if (m.getAddress() == "/intOnScreen"  &&  m.getNumArgs() == 1){
            intOnScreen = m.getArgAsInt(0);
        }
        
        if (m.getAddress() == "/icos"  &&  m.getNumArgs() == 1){
            icoOutON = m.getArgAsInt(0);
            icoIntON = m.getArgAsInt(0);
        }
        
        if (m.getAddress() == "/stars"  &&  m.getNumArgs() == 1){
            stars = m.getArgAsInt(0);
        }
        
        // no funciona
        
        if (m.getAddress() == "/domeDistance"  &&  m.getNumArgs() == 1){
            domeDistance = m.getArgAsInt(0);
        }
        
        if (m.getAddress() == "/histnames"  &&  m.getNumArgs() == 1){
            namesON = m.getArgAsInt(0);
        }
        
        if (m.getAddress() == "/timeelapsed"  &&  m.getNumArgs() == 1){
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
        
        if (m.getAddress() == "/orbit" && m.getNumArgs() == 2){
            //autoOrbit = m.getArgAsInt(0);
            orbitX = m.getArgAsInt(0);
            orbitY = m.getArgAsInt(1);
        }
        
        if (m.getAddress() == "/fb" && m.getNumArgs() == 1){
            feedbackON = m.getArgAsInt(0);
            depth = m.getArgAsInt(0);
        }
        
        if (m.getAddress() == "/lightmode" && m.getNumArgs() == 1){
            if(m.getArgAsString(0) == "vaporwave"){
                colorLight1 = ofColor(255, 113, 206);
                colorLight2 = ofColor( 1, 205, 254 );
                colorLight3 = ofColor(185, 103, 255);
            }
            if(m.getArgAsString(0) == "vaporwave2"){
                colorLight1 = ofColor(255, 251, 150);
                colorLight2 = ofColor(185, 103, 255 );
                colorLight3 = ofColor(5, 255, 161);
            }
            if(m.getArgAsString(0) == "risky"){
                colorLight1 = ofColor(203, 4, 165);
                colorLight2 = ofColor(144, 85, 62 );
                colorLight3 = ofColor(38, 240, 241);
            }
            if(m.getArgAsString(0) == "risky2"){
                colorLight1 = ofColor(69, 23, 108);
                colorLight2 = ofColor(54, 207, 198);
                colorLight3 = ofColor(207, 53, 131);
            }
            if(m.getArgAsString(0) == "white"){
                colorLight1 = ofColor(255, 255, 255);
                colorLight2 = ofColor(255, 255, 255);
                colorLight3 = ofColor(255, 255, 255);
            }
            if(m.getArgAsString(0) == "rgb"){
                colorLight1 = ofColor(255, 255, 0);
                colorLight2 = ofColor(0, 255, 255);
                colorLight3 = ofColor(255, 0, 255);
            }
        }

	if (m.getAddress() == "/mesh" && m.getNumArgs() == 3){
            mesh.clear();
            mechON = 1;
            image.loadImage("img/"+ m.getArgAsString(1));
            image.update();
            image.resize(100, 100);
            intensityThreshold = m.getArgAsFloat(0);
            int w = image.getWidth();
            int h = image.getHeight();
            for (int x=0; x<w; ++x) {
                for (int y=0; y<h; ++y) {
                    ofColor c = image.getColor(x, y);
                    float intensity = c.getLightness();
                    if (intensity >= intensityThreshold) {
                        float saturation = c.getSaturation();
                        float z = ofMap(saturation, 0, 255, -100, 100);
                        ofVec3f pos(x * 4, y * 4, z);
                        mesh.addVertex(pos);
                        mesh.addColor(c);
                        offsets.push_back(ofVec3f(ofRandom(0, 100000), ofRandom(0,100000), ofRandom(0,100000)));
                    }
                }
            }
            
            float connectionDistance = 4;
            connectionDistance = m.getArgAsFloat(2);
            
            int numVerts = mesh.getNumVertices();
            for (int a=0; a<numVerts; ++a) {
                ofVec3f verta = mesh.getVertex(a);
                for (int b=a+1; b<numVerts; ++b) {
                    ofVec3f vertb = mesh.getVertex(b);
                    float distance = verta.distance(vertb);
                    if (distance <= connectionDistance) {
                        mesh.addIndex(a);
                        mesh.addIndex(b);
                    }
                }
            }
        }

	if (m.getAddress() == "/meshscale"){
	  meshscale = m.getArgAsFloat(0);
	}

	if (m.getAddress() == "/meshclear"){
	  mesh.clear();
	}

	if (m.getAddress() == "/meshpos" && m.getNumArgs() == 3){
	  meshPosX = m.getArgAsFloat(0);
	  meshPosY = m.getArgAsFloat(1);
	  meshPosZ = m.getArgAsFloat(2);
	}

	if (m.getAddress() == "/meshrot" && m.getNumArgs() == 3){
	  meshRotX = m.getArgAsFloat(0);
	  meshRotY = m.getArgAsFloat(1);
	  meshRotZ = m.getArgAsFloat(2);
	}

        if (m.getAddress() == "/meshmode" && m.getNumArgs() == 1){
            if(m.getArgAsString(0) == "points"){
            mesh.setMode(OF_PRIMITIVE_POINTS);
            }
            if(m.getArgAsString(0) == "lines"){
            mesh.setMode(OF_PRIMITIVE_LINES);
            }
            if(m.getArgAsString(0) == "triangles"){
            mesh.setMode(OF_PRIMITIVE_TRIANGLES);
            }
        }
        
        if (m.getAddress() == "/cglitch" && m.getNumArgs() == 2){
            
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
            
            glitchON = m.getArgAsInt(0);
            
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

    drawScene();
    
    //fbo.draw(0, 0);
    
}

void ofApp::draw(){
    
    // Glitch
    
    //ofBackground(0, 0, 0);
    ofSetColor(255, 255, 255);
    ofDisableAlphaBlending();
    ofSetRectMode(OF_RECTMODE_CORNER);

    camera.lookAt(centro);

    if(glitchON == 1 && colorBackground ==1){
    ofBackgroundGradient(colorLight1, colorLight3 , OF_GRADIENT_LINEAR);
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
    
    if(domeON == 0){
        if(blurON == 1){
            drawBlur();
        }
        if(glitchBlurON == 1){
            drawGlitchBlur();
        }
        if(blurON == 0 && glitchBlurON == 0){
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
// pendiente: fboTrails

void ofApp::drawBlur(){
    
    ofEnableAlphaBlending();
    
    //float blur = ofMap(mouseX, 0, ofGetWidth(), 0, 10, true);
    
    fboBlurOnePass.begin();
    shaderBlurX.begin();
    
    
    if(clearGB == 0){
        ofSetColor(255,255,255, 0);
    }
    if(clearGB == 1){
        ofClear(0);
    }
    
    shaderBlurX.setUniform1f("blurAmnt", blur);
    fbo.draw(0, 0);
    shaderBlurX.end();
    fboBlurOnePass.end();
    
    fboBlurTwoPass.begin();
    shaderBlurY.begin();

    if(clearGB == 0){
        ofSetColor(255,255,255, 0);
    }
    if(clearGB == 1){
        ofClear(0);
    }
    
    shaderBlurY.setUniform1f("blurAmnt", blur);
    fboBlurOnePass.draw(0, 0);
    shaderBlurY.end();
    fboBlurTwoPass.end();
    
    fboBlurTwoPass.draw(0, 0);
    
}
 
//--------------------------------------------------------------

void ofApp::drawGlitchBlur(){
    
    ofEnableAlphaBlending();
    fboGlitchBlurOnePass.begin();
    glitchBlurX.begin();
    
    //ofClear(0);
    if(clearGB == 0){
        ofSetColor(255, 255, 255, 0);
    }
    if(clearGB == 1){
        ofClear(0);
    }
    
    glitchBlurX.setUniform1f("blurAmnt", glitchBlur);
    
    fbo.draw(0, 0); // aqui está la parte que dibuja
    
    glitchBlurX.end();
    fboGlitchBlurOnePass.end();
    
    // segunda parte del blur
    
    fboGlitchBlurTwoPass.begin();
    glitchBlurY.begin();
    
    //ofClear(0);
    if(clearGB == 0){
        ofSetColor(255, 255, 255, 0);
    }
    if(clearGB == 1){
        ofClear(0);
    }
    
    glitchBlurY.setUniform1f("blurAmnt", glitchBlur*lago);
    fboGlitchBlurOnePass.draw(0, 0); // la segunda parte que dibuja
    glitchBlurY.end();
    fboGlitchBlurTwoPass.end();
    //ofSetColor(ofColor::white);
    fboGlitchBlurTwoPass.draw(0, 0);
    
}

//--------------------------------------------------------------

void ofApp::drawFbo(){
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofDisableAlphaBlending();
    ofScale(0.125/4, 0.125/4);
    ofTranslate(0, 0, 0);
    ofRotateX(180);
    
    //fbo.getTexture().bind();
    //plane.draw();
    //fbo.getTexture().unbind();
    
    if(blurON == 1){
        drawBlur();
    }
    if(glitchBlurON == 1){
        drawGlitchBlur();
    }
    if(blurON == 0 && glitchBlurON == 0){
        fbo.draw(0, 0);
    }
    
}

//--------------------------------------------------------------

void ofApp::drawScene(){
    
    fbo.begin();
    
    ofClear(0);
    
    ofEnableArbTex();
    ofRectangle rect;
    
    if(glitchON == 0 && colorBackground == 1){
    ofBackgroundGradient(colorLight1, colorLight3 , OF_GRADIENT_LINEAR);
    }
    
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
    
    ofEnableDepthTest();

    camera.begin();
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofEnableSmoothing();
    ofEnableAntiAliasing();
    //if(autoOrbit == 1){
       camera.orbit(ofGetElapsedTimef()*orbitX, ofGetElapsedTimef()*orbitY, camera.getDistance(), posOrbit); // hace falta investigar como funciona esto
    //}

    // videos
    
    for(int i = 0; i < LIM; i++){
        ofEnableAlphaBlending();
        ofPushMatrix();
        ofRotateX(vRotX[i]);
        ofRotateY(vRotY[i]);
        ofRotateZ(vRotZ[i]);
        ofSetColor(255,vOpacity[i]);
        ofScale(vScaleX[i],vScaleY[i], 0);
        ofTranslate((vX[i]),vY[i], vZ[i]-200);
        videoLC[i].draw(0, 0);
        ofPopMatrix();
    }
    
    if(mechON == 1){
        ofEnableLighting();
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofPushMatrix();
        ofRotateX(meshRotX);
        ofRotateY(meshRotY);
        ofRotateZ(meshRotZ);
        ofScale(meshscale, meshscale, meshscale);
        //mesh.setPosition(0, 0, 0);
        ofTranslate(-200+meshPosX, -200+meshPosY, meshPosZ);
        mesh.draw();
        ofPopMatrix();
    }

    // luces y material
    
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
    
    text = wrapString(texto, 400);
    rect = font.getStringBoundingBox(text, 0, 0);
    ofSetLineWidth(0.5);
    
    // Escenario
    
    if(modelON == 1){
        ofSetRectMode(OF_RECTMODE_CENTER);
        float distancia;
        distancia = ofMap(rect.height, 26, 1234, 20, 50);
        ofPushMatrix();
        ofRotateX(0); // 90 cuando es el almacen
        ofRotateY(0); // 180 cuando es el almacen
        //ofRotateZ(0+ofGetElapsedTimef()); // 180 cuando es el otro
        ofRotateZ(180);
        ofScale(modelScale, modelScale, modelScale);
        ofTranslate(0, 0, 0);
        //planeMatrix.setPosition(0, 0, 0); /// position in x y z
        //planeMatrix.drawWireframe();
        model3D.setPosition(0, 50, 0);
        //model3D.setPosition(-275, -200, -50);
        asteroid.bind();
        model3D.drawFaces();
        asteroid.unbind();
        ofPopMatrix();
    }
    
    // multimodelos
    
    material.begin();

    
    //if(multiModelON == 1){
    for(int i = 0; i < LIM; i++){
        
        ofTexture *texture2;
        ofShader *shader2;
        
        if(videoTex == 1){
        ofTexture *texture2 = tempPlayer.getTexture();
        ofShader *shader2 = tempPlayer.getShader();
        }
        
        float distancia;
        distancia = ofMap(rect.height, 26, 1234, 20, 50);
        
        ofPushMatrix();
        
        ofRotateX(multiModelRotX[i]);
        ofRotateY(multiModelRotY[i]);
        ofRotateZ( multiModelRotZ[i]+180);
        ofScale(multiModelScale[i] * 0.25,multiModelScale[i] * 0.25, multiModelScale[i] * 0.25); /// falta mscale
        ofTranslate(0, 0, 0);
        //planeMatrix.setPosition(0, 0, 0); /// position in x y z
        //planeMatrix.drawWireframe();
        multiModel[i].setPosition(multiModelX[i], multiModelY[i], multiModelZ[i]);
        
        if(textureON == 1){
            texturas[i].bind();
        }
        
        if(videoTex == 1){
            if (shader2){
                shader2->begin();
            }
            texture2->bind();
        }
        
        multiModel[i].drawFaces();
        
        if(textureON == 1){
            texturas[i].unbind();
        }
        
        if(videoTex == 1){
            texture2 -> unbind();
            if (shader2){
                shader2->end();
            }
        }
        
        ofPopMatrix();
    }
    //}
    
    // centro
    
    if(centroSphON == 1){
    centroSph.setPosition(0, 0, 0);
    centroSph.draw();
    }
    
    if(reticulaSphON == 1){
        reticulaSph.setPosition(0, 0, 0);
        reticulaSph.drawWireframe();
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

     if(icoOutON == 1){
     ofPopMatrix();
     ofRotateZ(0);
     icoSphere.setRadius(rect.width*1);
     icoSphere.setPosition(rect.x, rect.y+50, 0);
     icoSphere.setResolution(1);
     icoSphere.drawWireframe();
     ofPushMatrix();
     }
    
    // estrellas puntos
    
    if(stars == 1){
        for (int i = 0;i < numstars;i++){
            ofPushMatrix();
            //ofRotateZ(ofGetElapsedTimef()+10);
            ofTranslate((ofNoise(i/2.4)-0.5)*dispstarsX,
                        (ofNoise(i/5.6)-0.5)*dispstarsY,
                        (ofNoise(i/8.2)-0.5)*dispstarsZ);
            ofSphere(0, 0, (ofNoise(i/3.4)-0.1)*sizestars);
            ofPopMatrix();
        }
    }
    
    material.end();

    if(textON == 1 && fixText == 0){
        //pointLight.draw();
        //pointLight2.draw();
        //pointLight3.draw();
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofTranslate(0, 0, 0);
        ofScale(1, 1, 1);
        ofRotateX(textRotX);
        ofRotateY(textRotY);
        ofRotateZ(textRotZ);
        //text = wrapString(texto, 500);
        //rect = font.getStringBoundingBox(text, 0, 0);
        //ofNoFill();
        if(outOnScreen == 0){
            ofScale(0.25, 0.25, 0.25);
            ofTranslate(0, 0, 0);
            //clientTyping = "";
            ofRectangle rectOut;
            textOut = wrapString(texto, 400);
            rectOut = font.getStringBoundingBox(textOut, 0, 0);
            //ofSetLineWidth(2);
            float distancia4;
            distancia4 = ofMap(rect.height, 26, 1234, 500, 1234 * 1.25);
            //camera.setDistance(distancia4);
            font.drawString(textOut, 0-(rectOut.width*0.5), 0+(rectOut.height*0.5));
        }
        
        if(namesON == 1){
            ofRotateZ(0);
            float distancia;
            float distancia2;
            distancia = ofMap(rect.height, 25, 1000, 55, 625);
            distancia2 = ofMap(rect.width, 25, 1000, 55, 525);
            font2.drawString(nombre, distancia2 * (-1), distancia);
        }
        
        //if(autoOrbit == 1){

            //camera.orbit(ofGetElapsedTimef()*orbitX, ofGetElapsedTimef()*orbitY, 500, ofVec3f(rect.x, rect.y, 250));
        //}
        
        // lo siguiente ya no es necesario
        
        /*
        
        if(distanceLockON == 0){
            float distancia;
            distancia = ofMap(rect.height, 25, 1234, 500, 700);
            camera.setDistance(distancia);
        }
        
        if(distanceLockON == 0){
            camera.setDistance(100);
        }    */
        
    };
         
    if(multiMsg == 1){
        for(int i = 0; i < LIM; i++){
            // aquí había push matrix
            ofPushMatrix();
            ofTranslate(0, 0, 0);
            ofScale(0.25, 0.25, 0.25);
            ofRotateX(msgRotX[i]);
            ofRotateY(msgRotY[i]);
            ofRotateZ(msgRotZ[i]);
            textOrbPrima[i] = wrapString(textOrb[i], 500);
            rectOrb[i] = fontOrb[i].getStringBoundingBox(textOrbPrima[i], 0, 0);
            //ofNoFill();
            fontOrb[i].drawString(textOrbPrima[i], noiseX[i] + (rect.width*0.5),  noiseY[i] + (rect.height*0.5));
            ofPopMatrix();
        }
    }
    
    ofPopMatrix();
    
    if(lightON == 1){
        material.end();
    }
    
    camera.end();
    
    /*
     
     text = wrapString(clientTyping, 500);
     rect = font.getStringBoundingBox(text, 0, 0);
     font.drawString(text, 0-(rect.width*0.5), 0+(rect.height*0.5));
     
     */
        ofDisableLighting();
        ofDisableDepthTest();
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofTranslate(0, 0, 0);
        ofScale(0.5, 0.5, 0.5);
        ofRotateX(textRotX);
        ofRotateY(textRotY);
        ofRotateZ(textRotZ);
        ofPushMatrix();
        text = wrapString(clientTyping, 700);
        rect = font.getStringBoundingBox(text, 0, 0);
        ofTranslate(0, 0, -200);
        float distancia;
        distancia = ofMap(rect.height, 0, 500, 400, 200);
        ofTranslate(0, 0, distancia);
        font.drawString(text, ofGetWidth()-(rect.width*0.5), (ofGetHeight()-(rect.height*0.5)));
        ofPopMatrix();
    
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
            clearGB = 0;
            clientTyping += key;
        }
        else{
            if(clientTyping.size() > 0){
                clientTyping.erase(clientTyping.end() - 1);
            }
        }
    }
    
    else{
        
        std::vector < std::string > textAnalisis = ofSplitString(clientTyping, " ");
        textAnalisis.push_back(clientTyping);
        
        if(textAnalisis[0] == "vload"){
            string temp = "videos/" + textAnalisis[2] + ".mov";
            videoLC[ofToInt(textAnalisis[1])].setPixelFormat(OF_PIXELS_RGBA);
            videoLC[ofToInt(textAnalisis[1])].setLoopState(OF_LOOP_NORMAL);
            videoLC[ofToInt(textAnalisis[1])].load(temp);
            videoLC[ofToInt(textAnalisis[1])].play();
            vScaleX[ofToInt(textAnalisis[1])] = (ofGetWidth()*1.0)/960;
            vScaleY[ofToInt(textAnalisis[1])] = (ofGetHeight()*1.0)/560;
            vRotX[ofToInt(textAnalisis[1])] = 0;
            vRotY[ofToInt(textAnalisis[1])] = 0;
            vRotZ[ofToInt(textAnalisis[1])] = 0;
        }
        
        if (textAnalisis[0] == "vfree"){ // falta rot
            videoLC[ofToInt(textAnalisis[1])].close();
            vX[ofToInt(textAnalisis[1])] = 0;
            vY[ofToInt(textAnalisis[1])] = 0;
            vSpeed[ofToInt(textAnalisis[1])] = 1;
            vOpacity[ofToInt(textAnalisis[1])] = 255;
            vX[ofToInt(textAnalisis[1])] = 0;
            vY[ofToInt(textAnalisis[1])] = 0;
            vZ[ofToInt(textAnalisis[1])] = 0;
            vRotX[ofToInt(textAnalisis[1])] = 0;
            vRotZ[ofToInt(textAnalisis[1])] = 0;
            vRotX[ofToInt(textAnalisis[1])] = 0;
        }
        
        if (textAnalisis[0] == "vspeed"){
            videoLC[ofToInt(textAnalisis[1])].setSpeed(ofToFloat(textAnalisis[2])*tempo);
        }
        
        if (textAnalisis[0] == "light"){
            lightON = ofToInt(textAnalisis[1]);
        }
        
        if (textAnalisis[0] == "spherein"){
            centroSphON = ofToInt(textAnalisis[1]);
        }
        
        if (textAnalisis[0] == "sphereout"){
            reticulaSphON = ofToInt(textAnalisis[1]);
        }
        
        if (textAnalisis[0] == "numstars"){
            numstars = ofToInt(textAnalisis[1]);
        }
        
        if (textAnalisis[0] == "sizestars"){
            sizestars = ofToInt(textAnalisis[1]);
        }
        
        if (textAnalisis[0] == "dispstarsxyz"){
            dispstarsX = ofToInt(textAnalisis[1]);
            dispstarsY = ofToInt(textAnalisis[2]);
            dispstarsZ = ofToInt(textAnalisis[3]);
        }
        
        if (textAnalisis[0] == "dispstars"){
            dispstarsX = ofToInt(textAnalisis[1]);
            dispstarsY = ofToInt(textAnalisis[1]);
            dispstarsZ = ofToInt(textAnalisis[1]);
        }

	if (textAnalisis[0] == "cbackground"){
	  colorBackground = ofToInt(textAnalisis[1]);
	}
        
        if (textAnalisis[0] == "lightmode"){
            if(textAnalisis[1] == "vaporwave"){
                colorLight1 = ofColor(255, 113, 206);
                colorLight2 = ofColor( 1, 205, 254 );
                colorLight3 = ofColor(185, 103, 255);
            }
            if(textAnalisis[1] == "vaporwave2"){
                colorLight1 = ofColor(255, 251, 150);
                colorLight2 = ofColor(185, 103, 255 );
                colorLight3 = ofColor(5, 255, 161);
            }
            if(textAnalisis[1] == "risky"){
                colorLight1 = ofColor(203, 4, 165);
                colorLight2 = ofColor(144, 85, 62 );
                colorLight3 = ofColor(38, 240, 241);
            }
            if(textAnalisis[1] == "risky2"){
                colorLight1 = ofColor(69, 23, 108);
                colorLight2 = ofColor(54, 207, 198);
                colorLight3 = ofColor(207, 53, 131);
            }
            if(textAnalisis[1] == "white"){
                colorLight1 = ofColor(255, 255, 255);
                colorLight2 = ofColor(255, 255, 255);
                colorLight3 = ofColor(255, 255, 255);
            }
            if(textAnalisis[1] == "rgb"){
                colorLight1 = ofColor(255, 255, 0);
                colorLight2 = ofColor(0, 255, 255);
                colorLight3 = ofColor(255, 0, 255);
            }
        }
        
        if (textAnalisis[0] == "tempo"){
            tempo = ofToFloat(textAnalisis[1]);
        }
        
        if (textAnalisis[0] == "vop"){
            vOpacity[ofToInt(textAnalisis[1])] = ofToInt(textAnalisis[2]);
        }
        
        if (textAnalisis[0] == "vpos"){
            vX[ofToInt(textAnalisis[1])] = ofToInt(textAnalisis[2]);
            vY[ofToInt(textAnalisis[1])] = ofToInt(textAnalisis[3]);
            vZ[ofToInt(textAnalisis[1])] = ofToInt(textAnalisis[4]);
        }
        
        if (textAnalisis[0] == "vscale"){
            vScaleX[ofToInt(textAnalisis[1])] = ofToFloat(textAnalisis[2]);
            vScaleY[ofToInt(textAnalisis[1])] = ofToFloat(textAnalisis[3]);
        }
        
        if (textAnalisis[0] == "fbxy"){
            retroX = ofToFloat(textAnalisis[1]);
            retroY = ofToFloat(textAnalisis[2]);
        }
        
        if (textAnalisis[0] == "fbx"){
            retroX = ofToFloat(textAnalisis[1]);
        }
        
        if (textAnalisis[0] == "clear"){
            clearGB = 1;
        }
        
        if (textAnalisis[0] == "fby"){
            retroY = ofToFloat(textAnalisis[1]);
        }
        
        if (textAnalisis[0] == "mload"){
            string temp = "3d/" + textAnalisis[2] + ".obj";
            multiModel[ofToInt(textAnalisis[1])].loadModel(temp);
            multiModelON = ofToFloat(textAnalisis[1]);
        }
        
        if (textAnalisis[0] == "mfree"){
            multiModel[ofToInt(textAnalisis[1])].clear();
        }
        
        if (textAnalisis[0] == "sceneclear"){
            model3D.clear();
        }
        
        if (textAnalisis[0] == "posorbit"){
            posOrbit = ofVec3f(ofToInt(textAnalisis[1]), ofToInt(textAnalisis[2]), ofToInt(textAnalisis[3]));
        }
        
        if (textAnalisis[0] == "lookat"){
            centro = ofVec3f(ofToInt(textAnalisis[1]), ofToInt(textAnalisis[2]), ofToInt(textAnalisis[3]));
            //posOrbit = ofVec3f(ofToInt(textAnalisis[1]), ofToInt(textAnalisis[2]), ofToInt(textAnalisis[3]));
            //amera.lookAt(centro);
        }
        
        if (textAnalisis[0] == "sceneload"){ // aquí hace falta escribir parámetros espcíficos para cada escenario.
            string temp = "3d/" + textAnalisis[2] + ".obj";
            model3D.loadModel(temp);
            modelON = ofToInt(textAnalisis[1]);
        }
        
        if (textAnalisis[0] == "mpos"){
            multiModelX[ofToInt(textAnalisis[1])] = ofToInt(textAnalisis[2]);
            multiModelY[ofToInt(textAnalisis[1])] = ofToInt(textAnalisis[3]);
            multiModelZ[ofToInt(textAnalisis[1])] = ofToInt(textAnalisis[4]);
        }
        
        if (textAnalisis[0] == "mrot" ){
            multiModelRotX[ofToInt(textAnalisis[1])] = ofToInt(textAnalisis[2]);
            multiModelRotY[ofToInt(textAnalisis[1])] = ofToInt(textAnalisis[3]);
            multiModelRotZ[ofToInt(textAnalisis[1])] = ofToInt(textAnalisis[4]);
        }
        
        if (textAnalisis[0] == "mscale"){
            multiModelScale[ofToInt(textAnalisis[1])] = ofToFloat(textAnalisis[2]);
        }
        
        if (textAnalisis[0] == "blur"){
            blurON = ofToInt(textAnalisis[1]);
            blur = ofToFloat(textAnalisis[2]);
        }
        
        if (textAnalisis[0] == "gblur"){
            glitchBlurON = ofToInt(textAnalisis[1]);
            glitchBlur = ofToFloat(textAnalisis[2]);
            if(ofToInt(textAnalisis[1]) == 1){
                clearGB = 0;
            }
            if(ofToInt(textAnalisis[1]) == 0){
                clearGB = 1;
            }
        }
        
        if (textAnalisis[0] == "vrot"){
            vRotX[ofToInt(textAnalisis[1])] = ofToFloat(textAnalisis[2]);
            vRotY[ofToInt(textAnalisis[1])] = ofToFloat(textAnalisis[3]);
            vRotZ[ofToInt(textAnalisis[1])] = ofToFloat(textAnalisis[4]);
        }
        
        if (textAnalisis[0] == "txtrot"){
            textRotX = ofToFloat(textAnalisis[1]);
            textRotY = ofToFloat(textAnalisis[2]);
            textRotZ = ofToFloat(textAnalisis[3]);
        }
        
        if (textAnalisis[0] == "dome"){
            domeON = ofToInt(textAnalisis[1]);
            //lightON = 0;
        }
        
        if (textAnalisis[0] == "icos"){ // patrones de movimiento
            icoOutON = ofToInt(textAnalisis[1]);
            icoIntON = ofToInt(textAnalisis[1]);
        }
        
        if (textAnalisis[0] == "stars"){
            stars = ofToInt(textAnalisis[1]);
        }
        
        if (textAnalisis[0] == "fb" ){
            feedbackON = ofToInt(textAnalisis[1]);
            depth = ofToInt(textAnalisis[1]);
        }
        
        if (textAnalisis[0] == "meshmode" ){
            if(textAnalisis[1] == "points"){
            mesh.setMode(OF_PRIMITIVE_POINTS);
            }
            if(textAnalisis[1] == "lines"){
            mesh.setMode(OF_PRIMITIVE_LINES);
            }
            if(textAnalisis[1] == "triangles"){
            mesh.setMode(OF_PRIMITIVE_TRIANGLES);
            }
        }
        
        if (textAnalisis[0] == "pointsize"){
            glPointSize(ofToFloat(textAnalisis[1]));
        }
        
        if (textAnalisis[0] == "linewidth"){
            ofSetLineWidth(ofToFloat(textAnalisis[1]));
        }
        
        if (textAnalisis[0] == "sphinr"){
            centroSph.setRadius(ofToInt(textAnalisis[1]));
        }
        
        if (textAnalisis[0] == "sphoutr"){
            reticulaSph.setRadius(ofToInt(textAnalisis[1]));
        }
        
        if (textAnalisis[0] == "timescale"){
            timeScale = ofToFloat(textAnalisis[1]);
        }
        
        if (textAnalisis[0] == "meshdisplacement"){
            meshVecX = ofToFloat(textAnalisis[1]);
            meshVecY = ofToFloat(textAnalisis[2]);
            meshVecZ = ofToFloat(textAnalisis[3]);
        }
        
        if (textAnalisis[0] == "meshclear" ){
            mechON = 0;
            mesh.clear();
        }
        
        if (textAnalisis[0] == "meshscale" ){
            meshscale = ofToFloat(textAnalisis[1]);
        }
        
        if (textAnalisis[0] == "camdistance" ){
            camera.setDistance(ofToFloat(textAnalisis[1]));
        }
        
        if (textAnalisis[0] == "meshpos" ){
            meshPosX = ofToFloat(textAnalisis[1]);
            meshPosY = ofToFloat(textAnalisis[2]);
            meshPosZ = ofToFloat(textAnalisis[3]);
        }
        
        if (textAnalisis[0] == "font"){
            if(textAnalisis[1] == "dejavu"){
                //font.load("fonts/CloisterBlack.ttf", 40, true, true, true);
                titleFont.load("fonts/DejaVuSansMono.ttf", 20);
                font2.load("fonts/DejaVuSansMono.ttf", 40, true, true, true);
                font.load("fonts/DejaVuSansMono.ttf", 40, true, true, true);
                fontOut.load("fonts/DejaVuSansMono.ttf", 40, true, true, true);
                for(int i = 0; i < LIM; i++){
                    fontOrb[i].load("fonts/DejaVuSansMono.ttf", 40, true, true, true);
                }
            }
            if(textAnalisis[1] == "malandrone"){
                //font.load("fonts/CloisterBlack.ttf", 40, true, true, true);
                titleFont.load("fonts/CloisterBlack.ttf", 20);
                font2.load("fonts/CloisterBlack.ttf", 40, true, true, true);
                font.load("fonts/CloisterBlack.ttf", 40, true, true, true);
                fontOut.load("fonts/CloisterBlack.ttf", 40, true, true, true);
                for(int i = 0; i < LIM; i++){
                fontOrb[i].load("fonts/CloisterBlack.ttf", 40, true, true, true);
                }
            }
        }
        
        if (textAnalisis[0] == "meshrot" ){
            meshRotX = ofToFloat(textAnalisis[1]);
            meshRotY = ofToFloat(textAnalisis[2]);
            meshRotZ = ofToFloat(textAnalisis[3]);
        }
        
        if (textAnalisis[0] == "mesh" ){
            mesh.clear();
            mechON = 1;
            image.loadImage("img/"+ textAnalisis[2]);
            image.update();
            image.resize(100, 100);
            intensityThreshold = ofToFloat(textAnalisis[1]);
            int w = image.getWidth();
            int h = image.getHeight();
            for (int x=0; x<w; ++x) {
                for (int y=0; y<h; ++y) {
                    ofColor c = image.getColor(x, y);
                    float intensity = c.getLightness();
                    if (intensity >= intensityThreshold) {
                        float saturation = c.getSaturation();
                        float z = ofMap(saturation, 0, 255, -100, 100);
                        ofVec3f pos(x * 4, y * 4, z);
                        mesh.addVertex(pos);
                        mesh.addColor(c);
                        offsets.push_back(ofVec3f(ofRandom(0, 100000), ofRandom(0,100000), ofRandom(0,100000)));
                    }
                }
            }
            
            float connectionDistance = 4;
            connectionDistance = ofToInt(textAnalisis[3]);
            
            int numVerts = mesh.getNumVertices();
            for (int a=0; a<numVerts; ++a) {
                ofVec3f verta = mesh.getVertex(a);
                for (int b=a+1; b<numVerts; ++b) {
                    ofVec3f vertb = mesh.getVertex(b);
                    float distance = verta.distance(vertb);
                    if (distance <= connectionDistance) {
                        mesh.addIndex(a);
                        mesh.addIndex(b);
                    }
                }
            }
        }
        
        if (textAnalisis[0] == "texoff"){
            textureON = 0;
            videoTex = 0;
        }
        
        if (textAnalisis[0] == "itex"){
            string temp = "img/" + textAnalisis[2];
            ofDisableArbTex();
            texturas[ofToInt(textAnalisis[1])].generateMipmap();
            texturas[ofToInt(textAnalisis[1])].setTextureWrap(GL_REPEAT, GL_REPEAT);
            texturas[ofToInt(textAnalisis[1])].setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
            ofLoadImage(texturas[ofToInt(textAnalisis[1])], temp);
            videoTex = 0;
            textureON = 1;
        }
        
        if (textAnalisis[0] == "vtex"){
            string temp = "videos/" + textAnalisis[1];
            videoTex = 1;
            textureON = 0;
            tempPlayer.setPixelFormat(OF_PIXELS_RGBA);
            tempPlayer.setLoopState(OF_LOOP_NORMAL);
            tempPlayer.load(temp);
            tempPlayer.play();
        }
        
        if(textAnalisis[0] == "orbit"){
            //autoOrbit = ofToInt(textAnalisis[1]);
            orbitX = ofToFloat(textAnalisis[1]);
            orbitY = ofToInt(textAnalisis[2]);
        }
        
        /*
        if (m.getAddress() == "/multiMsg"  &&  m.getNumArgs() == 7){
            int n = m.getArgAsInt(0);
            multiMsg = 1;
            noiseX[m.getArgAsInt(0)] = m.getArgAsFloat(1);
            noiseY[m.getArgAsInt(0)] = m.getArgAsFloat(2);
            msgRotX[m.getArgAsInt(0)] = m.getArgAsFloat(3);
            msgRotY[m.getArgAsInt(0)] = m.getArgAsFloat(4);
            msgRotZ[m.getArgAsInt(0)] = m.getArgAsFloat(5);
            textOrb[m.getArgAsInt(0)] = m.getArgAsString(6);
        }*/
        
        if (textAnalisis[0] == "glitch"){
            if(ofToInt(textAnalisis[1]) == 0 && ofToInt(textAnalisis[2]) == 0){
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
            
            if(ofToInt(textAnalisis[2]) == 1){
                convergence = ofToBool(textAnalisis[1]);
            }
            
            if(ofToInt(textAnalisis[2]) == 2){
                glow = ofToBool(textAnalisis[1]);
            }
            
            if(ofToInt(textAnalisis[2]) == 3){
                shaker = ofToBool(textAnalisis[1]);
            }
            
            if(ofToInt(textAnalisis[2]) == 4){
                cutslider = ofToBool(textAnalisis[1]);
            }
            
            if(ofToInt(textAnalisis[2]) == 5){
                twist = ofToBool(textAnalisis[1]);
            }
            
            if(ofToInt(textAnalisis[2]) == 6){
                outline = ofToBool(textAnalisis[1]);
            }
            
            if(ofToInt(textAnalisis[2]) == 7){
                noise = ofToBool(textAnalisis[1]);
            }
            
            if(ofToInt(textAnalisis[2]) == 8){
                slitscan = ofToBool(textAnalisis[1]);
            }
            
            if(ofToInt(textAnalisis[2]) == 9){
                swell = ofToBool(textAnalisis[1]);
            }
            
            if(ofToInt(textAnalisis[2]) == 10){
                invert = ofToBool(textAnalisis[1]);
            }
        }
        
        if (textAnalisis[0] == "cglitch"){
            if(ofToInt(textAnalisis[1]) == 0 && ofToInt(textAnalisis[2]) == 0){
                highcontrast = false;
                blueraise = false;
                redraise = false;
                greenraise = false;
                blueinvert = false;
                redinvert = false;
                greeninvert = false;
            }
            
            if(ofToInt(textAnalisis[2]) == 1){
                highcontrast = ofToBool(textAnalisis[1]);
            }
            
            if(ofToInt(textAnalisis[2]) == 2){
                blueraise = ofToBool(textAnalisis[1]);
            }
            
            if(ofToInt(textAnalisis[2]) == 3){
                redraise = ofToBool(textAnalisis[1]);
            }
            
            if(ofToInt(textAnalisis[2]) == 4){
                greenraise = ofToBool(textAnalisis[1]);
            }
            
            if(ofToInt(textAnalisis[2]) == 5){
                blueinvert = ofToBool(textAnalisis[1]);
            }
            
            if(ofToInt(textAnalisis[2]) == 6){
                redinvert = ofToBool(textAnalisis[1]);
            }
            
            if(ofToInt(textAnalisis[2]) == 1){
                greeninvert = ofToBool(textAnalisis[1]);
            }
        }
        
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
    cout << "resized"<< endl;
    //ofSetWindowShape(winSizeW, winSizeH); /// La resolución de la pantalla final
    //winSizeW = w;
    //winSizeH = h;
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
