#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofGLWindowSettings settings;
    settings.setGLVersion(4,0); /// < select your GL Version here
    ofCreateWindow(settings); ///< create your window here
    
    ofRunApp(new ofApp());
    
    
//    ofGLESWindowSettings settings;
//    settings.width = 1280;
//    settings.height = 720;
//    settings.setGLESVersion(2);
//    ofCreateWindow(settings);
//    
//    ofRunApp( new testApp());

    //	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context
//
//	// this kicks off the running of my app
//	// can be OF_WINDOW or OF_FULLSCREEN
//	// pass in width and height too:
//	ofRunApp(new ofApp());

}
