
#pragma once

#include "ofMain.h"
#if (defined(__APPLE__) && defined(__MACH__))
#include "ofxSyphon.h"
#endif
#include "ofxHapPlayer.h"
#include "ofxOsc.h"
#include "ofxPostGlitch.h"
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
    void setupGlitch();
    void drawGlitch(ofEventArgs & args);
    
    ofxHapPlayer videoLC[LIM]; // para volver al estado anterior
    float position;
    ofTexture screenImage;
    bool feedback;
    ofxHapPlayer player;
    
#if (defined(__APPLE__) && defined(__MACH__))
    ofxSyphonClient client;
    bool syphonON;
#endif
    ofxXmlSettings XML;
    ofxOscReceiver reciever;
    ofxOscSender sender;

    float retroVel;
    int retroX;
    int retroY;
    int retroON;
    
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
    int canonGenerator;
    ofPath path[LIM];
    //ofFbo fbo[LIM];
    //ofPlanePrimitive plane[LIM];
    //ofTexture *texturas[LIM];
    //ofShader *shaderes[LIM];

    ofShader shader;
    ofFbo fbo;
    ofPlanePrimitive plane;    
    ofxPostGlitch myGlitch;
    float fbox;
    float fboy;
    float fboz;
    float fboscaleX;
    float fboscaleY;
    float fboSpeed;
    float lightON;
    float namesON;
    float fixText;

    ofFbo fboText;
    //ofBoxPrimitive plane;    
    // fx

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
    
    //ofxPostGlitch myGlitch;
    
    float textRotX;
    float textRotY;
    float textRotZ;
    int ofxglitch;
    
    bool bDrawLenna;
    
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
    
    /// Para el postglitch
    
    ofEasyCam camera;
    
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
