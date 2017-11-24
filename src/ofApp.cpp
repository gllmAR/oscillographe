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
    camera_gui.add(cam_set_distance.set("cam_set_distance", 0, 0, 1000));
    camera_gui.add(set_fullscreen.set("fullscreen", 0));

    audio_io.setup();
    
    graphe_input.setup();
    graphe_input.gui.setName("input");
    graphe_player.setup();
    graphe_player.gui.setName("player");
    graphe_output.setup();
    graphe_output.gui.setName("output");
    

    gui.setup();
    gui.setName("oscillo");
    
    gui.add(&camera_gui);
    
    
    graphe_gui.setup();
    graphe_gui.setName("graphe");

    
    graphe_gui.add(&graphe_input.gui);
    graphe_gui.add(&graphe_player.gui);
    graphe_gui.add(&graphe_output.gui);
    
    gui.add(&audio_io.gui);
    gui.add(&graphe_gui);

    
    
    gui.minimizeAll();
    audio_io.gui.minimizeAll();
    audio_io.gui_device.minimizeAll();
    graphe_gui.minimizeAll();
    
    
    
    gui.loadFromFile("settings.xml");
    cam_set_distance.addListener(this, &ofApp::cam_set_distance_change);

    sync.setup((ofParameterGroup&)gui.getParameter(),SYNC_INPORT,"localhost",SYNC_OUTPORT);
    

   
}


// faut passer le buffer minimu, a la classe sinon ca crash quand on va chercher plus bas sur
// faut clamp avec le minimum buffer que la carte lie
//--------------------------------------------------------------
void ofApp::update(){
    
    // mettre if enable dans la classe pour optimiser
    graphe_input.update(audio_io.buffer_size, audio_io.input_buffer_1, audio_io.input_buffer_2);
    graphe_player.update(audio_io.buffer_size, audio_io.player_buffer_1_wo, audio_io.player_buffer_2_wo);
    graphe_output.update(audio_io.buffer_size, audio_io.output_buffer_1, audio_io.output_buffer_2);

    // pas clair play quoi faire pour que ce soit clean... 
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
    

    
   ofEnableBlendMode(OF_BLENDMODE_SCREEN);

    cam.begin();
    graphe_input.draw();
    graphe_player.draw();
    graphe_output.draw();

    cam.end();
    
    
    ofDisableDepthTest();
    
   ofEnableBlendMode(OF_BLENDMODE_DISABLED);
    
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
    
    graphe_input.set_size(w,h);
    graphe_player.set_size(w,h);
    graphe_output.set_size(w,h);
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------

void ofApp::exit(){
    audio_io.exit();
}

void ofApp::cam_set_distance_change(float &f)
{
    cam.setDistance( cam_set_distance);
    cout<<cam.getDistance()<<endl;
}


