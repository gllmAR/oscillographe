#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"


//========================================================================
int main( ){
    ofGLFWWindowSettings settings;
    settings.setGLVersion(4,0); /// < select your GL Version here
    
    settings.width = 600;
    settings.height = 600;
    settings.setPosition(ofVec2f(300,0));
    settings.resizable = true;
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
    
    settings.width = 300;
    settings.height = 300;
    settings.setPosition(ofVec2f(0,0));
    settings.resizable = true;
    // uncomment next line to share main's OpenGL resources with gui
    //settings.shareContextWith = mainWindow;
    shared_ptr<ofAppBaseWindow> guiWindow = ofCreateWindow(settings);
    guiWindow->setVerticalSync(false);
    
    shared_ptr<ofApp> mainApp(new ofApp);
    mainApp->setup_settings_screen();
    ofAddListener(guiWindow->events().draw,mainApp.get(),&ofApp::draw_settings_screen);
    
    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();

    
    
    //ofCreateWindow(settings); ///< create your window here
    
    //ofRunApp(new ofApp());
    
    

}
