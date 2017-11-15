#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetVerticalSync(true);
    
  //  cam.setDistance(buffer_history*0.01);
    ofBackground(0, 0, 0);
    
    ofSetFrameRate(60);
    
    
    // gui setup
    camera_gui.setup("camera");
    camera_gui.add(fps_label.setup("FPS"," "));
    camera_gui.add(cam_set_ortho.set("cam_set_ortho", 1));
    camera_gui.add(cam_set_reset.set("cam_set_reset", 1));
    camera_gui.add(cam_set_distance.set("cam_set_distance", 1, -1, 2));
    camera_gui.add(set_fullscreen.set("fullscreen", 0));

    audio_io.setup();
    graphe.setup();
    
    gui.setup();
    gui.setName("oscillo");
    gui.add(&camera_gui);
    gui.add(&audio_io.gui);
    gui.add(&graphe.gui);

    
    gui.loadFromFile("settings.xml");
    sync.setup((ofParameterGroup&)gui.getParameter(),SYNC_INPORT,"localhost",SYNC_OUTPORT);
    
}



//--------------------------------------------------------------
void ofApp::update(){
    
    
    graphe.update(audio_io.buffer_size, audio_io.output_buffer_1, audio_io.output_buffer_2);
    sync.update();
    if(gui_draw)
        {
            fps_label= ofToString(ofGetFrameRate());
        };
    
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
    
    graphe.draw();

    cam.end();
    
    ofDisableDepthTest();
    
    if (gui_draw){gui.draw();}
    if (screen_workaround_to_update)
    {
        windowResized(ofGetWidth(), ofGetHeight());
        screen_workaround_to_update = 0;
    }
}
//--------------------------------------------------------------





//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == 'g' ){gui_draw=!gui_draw;}
    
    if (key == 'f'){set_fullscreen=!set_fullscreen;}
    

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
    graphe.set_size(w,h);
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


