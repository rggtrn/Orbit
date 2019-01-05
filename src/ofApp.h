
#pragma once

#include "ofMain.h"
#include "ofxHapPlayer.h"
#include "ofxOsc.h"
#include "ofxPostGlitch.h"
#include "ofxXmlSettings.h"
#include "ofxAssimpModelLoader.h"
#include "ofxCenteredTrueTypeFont.h"
#include "ofxDomemaster.h"

#define LIM 10
#define LIM2 3

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
    void drawScene();
    void drawFbo();
    void drawBlur();
    void textControl();
    void drawGlitchBlur();
    
    ofxHapPlayer videoLC[LIM];
    ofxDomemaster domemaster;
    // retroalimentación
    
    float position;
    ofTexture screenImage;
    bool feedback;
    
    ofxXmlSettings XML;
    ofxOscReceiver reciever;
    ofxOscSender sender;

    float retroVel;
    int retroX;
    int retroY;
    int retroON;
    int domeON;
    int domeDistance;
    int colorBackground;
    
    //ofBoxPrimitive caja;
    ofIcoSpherePrimitive icoSphere;
    ofIcoSpherePrimitive icoSphere2;
    ofIcoSpherePrimitive icoSphere3;
    
    int winSizeW;
    int winSizeH;
    
    int portIn;
    int portOut;
    
    float vSpeed [LIM];
    int vOpacity[LIM];
    int vX[LIM];
    int vY[LIM];
    int vZ[LIM];
    float vScaleX[LIM];
    float vScaleY[LIM];
    int vW [LIM];
    int vH [LIM];
    float vRotX [LIM];
    float vRotY [LIM];
    float vRotZ [LIM];
    int canonGenerator;
    ofPath path[LIM];
    
    int feedbackON;
    float glitchBlur;
    int glitchBlurON;
    float lago;
    float modelScale;

    ofShader shaderFish;
    
    ofFbo fbo;
    int clearGB;
    
    ofPlanePrimitive plane;
    ofxPostGlitch myGlitch;
    
    int icoIntON;
    int icoOutON;

    //
    string clientTyping;
    ofTrueTypeFont titleFont; // font for some info in the title line
    //
    
    ofColor colorLight1;
    ofColor colorLight2;
    ofColor colorLight3;
    
    ofShader shaderBlurX;
    ofShader shaderBlurY;
    
    ofShader glitchBlurX;
    ofShader glitchBlurY;
    
    ofFbo fboBlurOnePass;
    ofFbo fboBlurTwoPass;
    
    ofFbo fboGlitchBlurOnePass;
    ofFbo fboGlitchBlurTwoPass;
    
    float blur;
    int blurON;

    float fbox;
    float fboy;
    float fboz;
    float fboscaleX;
    float fboscaleY;
    float fboSpeed;
    float lightON;
    float namesON;
    float fixText;
    float autoOrbit;
    float orbitX;
    float orbitY;
    int distanceLockON;
    int malandroModeON;
    float timeElapsedON;
    
    ofFbo fboText;

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
    float intOnScreen;
    float outOnScreen;
    
    float textRotX;
    float textRotY;
    float textRotZ;
    int ofxglitch;
    float tempo;
    float depth;
        
    ofLight pointLight;
    ofLight pointLight2;
    ofLight pointLight3;
    ofMaterial material;
    ofColor lightColor;
    int modelON;
    ofPlanePrimitive planeMatrix;

    ofxCenteredTrueTypeFont fontOut;
    ofxCenteredTrueTypeFont font;
    ofxCenteredTrueTypeFont font2;
    
    string texto;
    string textOut;
    string nombre;
    string text;
    
    string letras3dString;
    ofTrueTypeFont ttf;

    int typeSolid;
    int typeWire; 
    
    /*
    
    ofShader shaderBlurX;
    ofShader shaderBlurY;
    
    ofFbo fboBlurOnePass;
    ofFbo fboBlurTwoPass;
    
     */
    
    ofxCenteredTrueTypeFont fontOrb [LIM];
    ofRectangle rectOrb [LIM];
    
    string textOrb[LIM];
    string textOrbPrima[LIM];
    float noiseX[LIM];
    float noiseY[LIM];
    float msgRotX[LIM];
    float msgRotY[LIM];
    float msgRotZ[LIM];
    
    string cero;
    string uno;
    string dos;
    string tres;
    string prueba;
    
    float radius;
    ofVec3f center2;
    ofVec2f center;
    
    int glitchON; 
    
    ofxOscSender clientSender; // client sender object
    string clientDestination; // IP address we're sending to
    int clientSendPort; // port we're sending to

    float lcneON;
    float multiMsg;
    float stars;
    float videoTex;
    ofTexture *textur;
    ofShader *shad;
    ofxHapPlayer tempPlayer;
    ofImage image;
    int mechON;
    ofMesh mesh;
    vector<ofVec3f> offsets;
    float meshconnect;
    float timeScale;
    
    // para la rotación
    
    ofMesh meshCopy;
    bool orbiting;
    float startOrbitTime;
    
    // letras 3d
    
    bool bResample;
    float resampleSpacing;
    float letterThickness;
    ofVboMesh letras3d;
    
    ofPath resamplePath(ofPath path, float spacing);
    ofMesh createMeshFromPath(ofPath path, float offSet);
    void colorFaces(ofMesh & mesh);
    
    int type3d;
    
    // These variables will let us store the polar coordinates of each vertex
    vector<float> distances;
    vector<float> angles;
    ofVec3f meshCentroid;
    float intensityThreshold;
    float meshVecX;
    float meshVecY;
    float meshVecZ;
    float meshPosX;
    float meshPosY;
    float meshPosZ;
    float meshRotX;
    float meshRotY;
    float meshRotZ;
    float meshscale;
    ofSpherePrimitive centroSph;
    ofSpherePrimitive reticulaSph;
    int centroSphON;
    int reticulaSphON;
    float camdistance;
    ofVec3f centro;
    ofVec3f posOrbit;

    ofTexture asteroid;
    
    int numstars;
    float sizestars;
    float dispstarsX;
    float dispstarsY;
    float dispstarsZ;
    
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
    
    ofxAssimpModelLoader multiModel[LIM];
    ofxAssimpModelLoader model3D;
    int textON;
    int fontSize;
    int textureON;
    int materialON;
    
    int clR[LIM2];
    int clG[LIM2];
    int clB[LIM2];
        
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
