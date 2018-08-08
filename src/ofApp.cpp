#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
   
    ofBackground(0, 0, 0); 
    ofSetVerticalSync(true);
    ofSetWindowTitle("PiranhaVivo");
    ofSetWindowShape(1280, 800);
    ofSetFrameRate(30);
    
#if (defined(__APPLE__) && defined(__MACH__))
    client.setup();
    syphonON = false;
#endif
    player.setPixelFormat(OF_PIXELS_RGBA);
    player.setLoopState(OF_LOOP_NORMAL);

    XML.load ("xml/OSCConf.xml");
    portOut = XML.getValue("PORT:NAME:OUT",5613);
    sender.setup("127.0.0.1",portOut);
    //OSC in
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
    }
    ofSetVerticalSync(true);
    ofBackground(255,255,255);
    position = 0;
    screenImage.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    retroX = 40;
    retroY = 40;
    feedback = 0;

}

void ofApp::update(){
    
    player.update();
    
    position = 500 + 250 * sin(ofGetElapsedTimef()*4);
    screenImage.loadScreenData(0,0,ofGetWidth(), ofGetHeight());
    
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

	//	if (m.getAddress() == "invert" && m.getNumArgs() == 1){
	//  videoLC[m.getArgAsInt(0)].invert();
	//}
        
        /// Para lograr hacer espejeo de las cosas

	#if (defined(__APPLE__) && defined(__MACH__))
	if (m.getAddress() == "/syphon" && m.getArgAsInt(1) == 1){
                    syphonON = true;
	}
	if (m.getAddress() == "/syphon" && m.getArgAsInt(1) == 0){
                    syphonON = false;
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
    
    //ofSetColor(255,255,255); Hace falta agregar  un if
    
    screenImage.draw(0+retroX, 0+retroY, ofGetWidth()-80, ofGetHeight()-80);

#if (defined(__APPLE__) && defined(__MACH__))
    client.draw(0, 0);
#endif
    
    for(int i = 0; i < LIM; i++){
	ofPushMatrix();
        ofSetColor(255,vOpacity[i]);
        ofScale(vScaleX[i],vScaleY[i]);
        ofTranslate(vX[i],vY[i]);
        videoLC[i].draw(0, 0);
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
