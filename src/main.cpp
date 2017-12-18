#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofGLFWWindowSettings settings;
    //settings.setGLVersion(4,0); /// < select your GL Version here
    //ofCreateWindow(settings); ///< create your window here
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
    shared_ptr<ofApp> mainApp(new ofApp);
    ofRunApp(mainWindow, mainApp);
//    ofRunApp(new ofApp());
    ofRunMainLoop();
    

};
