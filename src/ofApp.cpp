#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetVerticalSync(true);

  //  cam.setDistance(buffer_history*0.01);
    ofBackground(0, 0, 0);
    
    ofSetFrameRate(60);
    
    
    // gui setup
    camera_gui.setup("camera");
    
    camera_gui.add(cam_set_ortho.set("cam_set_ortho", 1));
    camera_gui.add(cam_set_reset.set("cam_set_reset", 1));
    camera_gui.add(cam_set_distance.set("cam_set_distance", 1, -1, 2));
    camera_gui.add(set_fullscreen.set("fullscreen", 0));

    audio_in.setup();
    oscillo.setup();
    
    gui.setup();
    gui.setName("oscillo");
    gui.add(&camera_gui);
    gui.add(&audio_in.gui);
    gui.add(&oscillo.gui);
    
    gui.loadFromFile("settings.xml");

}



//--------------------------------------------------------------
void ofApp::update(){
    
    
    oscillo.update(audio_in.buffer_size, audio_in.left, audio_in.right);

    
}

//--------------------------------------------------------------
void ofApp::draw(){

    if (set_fullscreen_old != set_fullscreen)
    {
        ofSetFullscreen(set_fullscreen);
        set_fullscreen_old = set_fullscreen;
    };
    
    ofEnableDepthTest();
    if (cam_set_ortho){cam.enableOrtho();}else{cam.disableOrtho();};
    if (cam_set_reset){cam.reset(); cam_set_reset=0;};
    
 
    cam.begin();
    
    oscillo.draw();

    cam.end();
    
    ofDisableDepthTest();
    
    if (gui_draw)
    {
        gui.draw();

    }
    if (screen_workaround_to_update)
    {
        windowResized(ofGetWidth(), ofGetHeight());
        screen_workaround_to_update = 0;
    }
}
//--------------------------------------------------------------





//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == 'g' ){
        gui_draw=!gui_draw;
    }
    
    if (key == 'f'){
        set_fullscreen=!set_fullscreen;
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
    app_size_w = w;
    app_size_h = h;
    cout << "app size = " << w << " by " << h <<endl;
    oscillo.set_size(w,h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------

void ofApp::exit(){
    
    
}

void ofApp::rhizome_init()
{
    sender.setup(HOST, RHIZOME_INPORT);
    ofxOscMessage m;
    m.setAddress("/sys/subscribe");
    m.addIntArg(RHIZOME_OUTPORT);
    m.addStringArg("/");
    sender.sendMessage(m, false);
}
