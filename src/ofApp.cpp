#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetVerticalSync(true);
    ofBackground(0, 0, 0);
    
    ofSetFrameRate(60);

    audio_io.setup();


    interact_speed.setup("speed", "/gpio/1");
    interact_volume.setup("volume", "/gpio/2");

    setup_gui();

    
    cam_get_param_b.addListener(this, &ofApp::cam_get_param);
    cam_set_param_b.addListener(this, &ofApp::cam_set_param);
    //cam_set_distance.addListener(this, &ofApp::cam_set_distance_change);

    osc_receiver.setup(INTERACT_PORT); //pour input de senseur
    
    sync.setup((ofParameterGroup&)preset_panel.getParameter(),SYNC_INPORT,"localhost",SYNC_OUTPORT);
    
    feedback_plane.rotateDeg(180, 1, 0, 0); //flipper la texture de feedback car inverse
   
}

//

void ofApp::setup_gui()
{

    // camera
    camera_preset_gui.setup("camera");
    camera_preset_gui.add(cam_set_ortho.set("cam_set_ortho", 1));
    //camera_preset_gui.add(cam_set_distance.set("cam_set_distance", 0, 0, 1000));
    camera_preset_gui.add(cam_view_position.set("position",
                                                glm::vec3(0),
                                                glm::vec3(-1000),
                                                glm::vec3(1000)));
    camera_preset_gui.add(cam_view_orientation_quat_string.set("orientation"," "));
    //camera_preset_gui.add(cam_view_orientation_quat.set("orientation",
//                                                        glm::vec4(0),
//                                                        glm::vec4(-1),
//                                                        glm::vec4(1));
    //camera_preset_gui.add(cam_view_position.set("position"));
    
    
    camera_settings_gui.setup("camera");
    camera_settings_gui.add(fps_label.setup("FPS"," "));
    camera_settings_gui.add(cam_set_reset.set("cam_set_reset", 1));
    camera_settings_gui.add(set_fullscreen.set("fullscreen", 0));
    camera_settings_gui.add(cam_get_param_b.set("cam_get_param",0));
    camera_settings_gui.add(cam_set_param_b.set("cam_set_param",0));
    
    // graphe
    graphe_input.setup();
    graphe_input.gui.setName("input");
    graphe_player.setup();
    graphe_player.gui.setName("player");
    graphe_output.setup();
    graphe_output.gui.setName("output");
    
    graphe_gui.setup();
    graphe_gui.setName("graphe");
    graphe_gui.add(&graphe_input.gui);
    graphe_gui.add(&graphe_player.gui);
    graphe_gui.add(&graphe_output.gui);
    graphe_gui.minimizeAll();
    
    // feedback
    feedback_gui.setup();
    feedback_gui.setName("feedback");
    feedback_gui.add(feedback_enable.set("enable",0));
    feedback_gui.add(feedback_ammount.set("ammount", 0, 0, 1));
    feedback_gui.add(feedback_pos_x.set("x", 1, 0, 2 ));
    feedback_gui.add(feedback_pos_y.set("y", 1, 0, 2 ));
    feedback_gui.add(feedback_scale.set("scale", 1, 0 ,2));
    
    // interact
    
    
    interact_gui.setup();
    interact_gui.setName("interact");
    interact_gui.add(&interact_speed.gui);
    interact_gui.add(&interact_volume.gui);
    interact_gui.minimizeAll();

    
    // preset load and save pannel
    preset_gui.setup();
    preset_gui.setName("presets");
    preset_gui.add(preset_index.set("index",0,0,10));
    preset_gui.add(preset_load_b.set("load",0));
    preset_gui.add(preset_save_b.set("save",0));
    preset_gui.minimizeAll();
    
    
    
    // compose the preset pannel
    
    preset_panel.setup("oscillo_0", "oscillo.xml", 10, 10);
    
    //preset_panel.setName("oscillo");
    
    
    preset_panel.add(&camera_preset_gui);
    preset_panel.add(&audio_io.gui);
    preset_panel.add(&graphe_gui);
    preset_panel.add(&feedback_gui);
    preset_panel.add(&interact_gui);

    preset_panel.minimizeAll();
    audio_io.gui.minimizeAll();
    audio_io.gui_device.minimizeAll();


    preset_panel.loadFromFile("oscillo.xml");
    
    
    
    //setup panel
    setup_panel.setup("settings", "settings.xml", 220, 10);
    setup_panel.add(&camera_settings_gui);
    setup_panel.add(&preset_gui);
    
    setup_panel.add(&audio_io.gui_device);
    setup_panel.minimizeAll();
    setup_panel.loadFromFile("settings.xml");
    preset_save_b.addListener(this, &ofApp::preset_save);
    preset_load_b.addListener(this, &ofApp::preset_load);
}

//--------------------------------------------------------------
void ofApp::update()
{
    
    graphe_input.update(audio_io.buffer_size, audio_io.input_buffer_1, audio_io.input_buffer_2);
    graphe_player.update(audio_io.buffer_size, audio_io.player_buffer_1_wo, audio_io.player_buffer_2_wo);
    graphe_output.update(audio_io.buffer_size, audio_io.output_buffer_1, audio_io.output_buffer_2);

    // pas clair play quoi faire pour que ce soit clean...
    
    while(osc_receiver.hasWaitingMessages())
    {
        ofxOscMessage m;
        osc_receiver.getNextMessage(m);
        //cout<<m.getAddress()<<endl;
        interact_speed.parse_osc(m);
        interact_volume.parse_osc(m);
        // mettre ici les deux parse osc de classe
    }
    
    if (interact_speed.interact_enable)
    {
        interact_speed.update();
        audio_io.player_set_speed(interact_speed.get_value());
    } else {
        audio_io.player_set_speed(audio_io.player_speed);
    }
    
    if (interact_volume.interact_enable)
    {
        interact_volume.update();
        audio_io.set_output_vol(interact_volume.get_value());
        // devrait etre changé pour get value
    } else {
        audio_io.set_output_vol(audio_io.output_volume.get());
        //audio_io.player_set_speed(audio_io.player_speed);
    }
   
    sync.update();
    
    if(gui_draw){fps_label= ofToString(ofGetFrameRate());}
    
    ofEnableAlphaBlending();
    
}

//--------------------------------------------------------------
void ofApp::draw()
{
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
    
    interact_speed.draw();
    interact_volume.draw();
    ofEnableBlendMode( OF_BLENDMODE_ADD );
    
    if(feedback_enable)
    {
        screen_texture.loadScreenData(0,0,app_size_w,app_size_h);
    }

    ofDisableDepthTest();
    
   ofEnableBlendMode(OF_BLENDMODE_DISABLED);
    
    if (gui_draw)
    {
        preset_panel.draw();
        setup_panel.draw();
    }
    if (screen_workaround_to_update)
    {
        windowResized(ofGetWidth(), ofGetHeight());
        screen_workaround_to_update = 0;
    }
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if( key == 'g' ){gui_draw=!gui_draw;}
    
    if (key == 'f'){set_fullscreen=!set_fullscreen;}
    
    if (key >=48  && key <= 57)
    {
        audio_io.player_file_index = key-48;
    }

}
//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    
}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{

}
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
     if( button == 2 ){gui_draw=!gui_draw;}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{


}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
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
void ofApp::gotMessage(ofMessage msg)
{

}
//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
    
}
//--------------------------------------------------------------
void ofApp::exit(){
    audio_io.exit();
}
//--------------------------------------------------------------


void ofApp::preset_save(bool &b)
{
    cam_get_param(b);
    std::string str = "oscillo_";
    str += ofToString(preset_index);
    preset_panel.setName(str);
    preset_panel.saveToFile("oscillo.xml");
    preset_save_b =0;
}


//--------------------------------------------------------------

void ofApp::preset_load(bool &b)
{
    std::string str = "oscillo_";
    str += ofToString(preset_index);
    preset_panel.setName(str);
    preset_panel.loadFromFile("oscillo.xml");
    preset_load_b =0;
    cam_set_param(b);
}


//--------------------------------------------------------------

void ofApp::cam_get_param(bool &b)
{
    cam_view_position=cam.getPosition();
    glm::quat cam_view_orientation_quat=cam.getOrientationQuat();
    //workaround pour sauvegarder un quat en string dans un ofParameter
    cam_view_orientation_quat_string =ofToString(cam_view_orientation_quat);
    cam_get_param_b = 0;
}
//--------------------------------------------------------------

void ofApp::cam_set_param(bool &b)
{
    // workaround pour restaurer un quat a partir d une string
    glm::quat temp_orientation;
    vector <string> orientation_quat_vec = ofSplitString(cam_view_orientation_quat_string, " ");
    // comprendre pourquoi l'index est offset de 1 ici...?
    temp_orientation[0]=ofToFloat(orientation_quat_vec[1]);
    temp_orientation[1]=ofToFloat(orientation_quat_vec[2]);
    temp_orientation[2]=ofToFloat(orientation_quat_vec[3]);
    temp_orientation[3]=ofToFloat(orientation_quat_vec[0]);
    cout<<ofToString(temp_orientation)<<endl;
    cam.setOrientation(temp_orientation);
    cam.setPosition(cam_view_position);
    cam_set_param_b = 0;
}

