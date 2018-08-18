#pragma once

#include "ofMain.h"
#if (defined(__APPLE__) && defined(__MACH__))
#include "ofxSyphon.h"
#endif
#include "ofxHapPlayer.h"
#include "ofxOsc.h"
#include "ofxXmlSettings.h"
#include "ofxAssimpModelLoader.h"
#include "ofxCenteredTrueTypeFont.h"

#define LIM 10

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofxHapPlayer videoLC[LIM]; // para volver al estado anterior
    //mirrors videoLC[LIM2]; // para volver al estado anterior
    float position;
    ofTexture screenImage;
    bool feedback;

    float correccion = 0;
    
    //ofDrawCircle circulos;
    
    ofxHapPlayer player;
    void load(std::string movie);
#if (defined(__APPLE__) && defined(__MACH__))
    ofxSyphonClient client;
    bool syphonON;
#endif
    ofxXmlSettings XML;
    ofxOscReceiver reciever;
    ofxOscSender sender;
    
    int retroX;
    int retroY;
    
    int portIn;
    int portOut;
    
    float vSpeed [LIM];
    int vOpacity[LIM];
    int vX[LIM];
    int vY[LIM];
    float vScaleX[LIM];
    float vScaleY[LIM];
    int vW [LIM];
    int vH [LIM];
    float vRotX [LIM];
    float vRotY [LIM];
    float vRotZ [LIM];
    
    ofLight light;
    ofxCenteredTrueTypeFont font; // standard font
    ofxCenteredTrueTypeFont font2; // standard font

    string texto; 
    string nombre;
    string text;
    float fontScale;
    
    ofxAssimpModelLoader models3D[LIM];
    bool model3DOn[LIM];
    int textON;
    int fontSize;
    
    ofLight pointLight;
    ofLight pointLight2;
    ofLight pointLight3;
    
    void drawWithModel();
    void drawWithMesh();
    
    string wrapString(string text, int width) {
        
        string typeWrapped = "";
        string tempString = "";
        vector <string> words = ofSplitString(text, " ");
        
        for(int i=0; i<words.size(); i++) {
            
            string wrd = words[i];
            cout << wrd << endl;
            
            tempString += wrd + " ";
            int stringwidth = font.stringWidth(tempString);
            if(stringwidth >= width) {
                tempString = "";
                typeWrapped += "\n";
            }
            
            typeWrapped += wrd + " ";
        }
        
        return typeWrapped;
        
    }

};
