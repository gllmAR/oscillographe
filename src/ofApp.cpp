#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetVerticalSync(true);
    ofBackground(0, 0, 0);
    
    ofSetFrameRate(60);
    
    interact.setup();
    
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
    
    feedback_gui.setup();
    feedback_gui.setName("feedback");
    feedback_gui.add(feedback_enable.set("enable",0));
    feedback_gui.add(feedback_ammount.set("ammount", 0, 0, 1));
    feedback_gui.add(feedback_pos_x.set("x", 1, 0, 2 ));
    feedback_gui.add(feedback_pos_y.set("y", 1, 0, 2 ));
    feedback_gui.add(feedback_scale.set("scale", 1, 0 ,2));
    
    
    
    gui.add(&audio_io.gui);
    gui.add(&graphe_gui);
    gui.add(&feedback_gui);

    gui.add(&interact.gui);
    
    
    
    gui.minimizeAll();
    audio_io.gui.minimizeAll();
    audio_io.gui_device.minimizeAll();
    graphe_gui.minimizeAll();
    
    
    
    gui.loadFromFile("settings.xml");
    cam_set_distance.addListener(this, &ofApp::cam_set_distance_change);

    sync.setup((ofParameterGroup&)gui.getParameter(),SYNC_INPORT,"localhost",SYNC_OUTPORT);
    
feedback_plane.rotateDeg(180, 1, 0, 0);
   
}


// faut passer le buffer minimu, a la classe sinon ca crash quand on va chercher plus bas sur
// faut clamp avec le minimum buffer que la carte lie
//--------------------------------------------------------------
void ofApp::update(){
    
    graphe_input.update(audio_io.buffer_size, audio_io.input_buffer_1, audio_io.input_buffer_2);
    graphe_player.update(audio_io.buffer_size, audio_io.player_buffer_1_wo, audio_io.player_buffer_2_wo);
    graphe_output.update(audio_io.buffer_size, audio_io.output_buffer_1, audio_io.output_buffer_2);

    // pas clair play quoi faire pour que ce soit clean...
    
    if (interact.interact_enable)
    {
        interact.update();
        audio_io.player_set_speed(interact.get_speed());
    } else {
        audio_io.player_set_speed(audio_io.player_speed);
    }
    sync.update();
    
    
    if(gui_draw){fps_label= ofToString(ofGetFrameRate());}
    
   ofEnableAlphaBlending();
   
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    if (set_fullscreen_old != set_fullscreen)
    {
        ofSetFullscreen(set_fullscreen);
        set_fullscreen_old = set_fullscreen;
    };
    if(feedback_enable)
    {
        ofSetColor(255, 255, 255, feedback_ammount*255);
        feedback_plane.setPosition(app_size_w/2, app_size_h/2, 0);
        screen_texture.bind();
        feedback_plane.setScale(feedback_scale);
        feedback_plane.setPosition(feedback_pos_x*app_size_w/2, feedback_pos_y*app_size_h/2, 0);
        
        feedback_plane.draw();
        screen_texture.unbind();
    }
    ofEnableDepthTest();
    if (cam_set_ortho){cam.enableOrtho();}else{cam.disableOrtho();};
    if (cam_set_reset){cam.reset(); cam_set_reset=0;};
    
    
    cam.begin();
    ofSetColor(255);
    graphe_input.draw();
    graphe_player.draw();
    graphe_output.draw();
    
    cam.end();
    
    interact.draw();
    ofEnableBlendMode( OF_BLENDMODE_ADD );
    
    if(feedback_enable)
    {
        
        screen_texture.loadScreenData(0,0,app_size_w,app_size_h);
    
    }
    

    
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
    
    if (key >=48  && key <= 57)
    {
        audio_io.player_file_index = key-48;
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
     if( button == 2 ){gui_draw=!gui_draw;}


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
    
    screen_texture.allocate(w,h,GL_RGBA);
    feedback_plane.resizeToTexture(screen_texture);

    
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


