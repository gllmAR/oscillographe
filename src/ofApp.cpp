#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetVerticalSync(true);
    ofBackground(0, 0, 0);
    
    ofSetFrameRate(60);

    audio_io.setup();


    interact_speed.setup("speed", "/gpio/2");
    interact_volume.setup("volume", "/gpio/2");
    interact_preset.setup("preset","/gpio/1");
    
    cam.setup();
    feedback.setup();
    fbo_feedback.setup();
    setup_gui();

    osc_receiver.setup(INTERACT_PORT); //pour input de senseur
    sync.setup((ofParameterGroup&)preset_panel.getParameter(),SYNC_INPORT,"localhost",SYNC_OUTPORT);
    
}

//--------------------------------------------------------------

void ofApp::setup_gui()
{

    /* graphe */
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
    

    
    /* interact */

    interact_gui.setup();
    interact_gui.setName("interact");
    interact_gui.add(&interact_speed.gui);
    interact_gui.add(&interact_volume.gui);
    interact_gui.add(&interact_preset.gui);
    interact_gui.minimizeAll();

    
    /* preset load and save pannel */
    preset_gui.setup();
    preset_gui.setName("presets");
    preset_gui.add(preset_index.set("index",0,0,10));
    preset_gui.add(preset_load_b.set("load",0));
    preset_gui.add(preset_save_b.set("save",0));
    preset_gui.minimizeAll();
    
    
    
    /* compose the preset pannel */
    
    preset_panel.setup("oscillo_0", "oscillo.xml", 220, 10);
    
    preset_panel.add(&cam.camera_preset_gui);
    preset_panel.add(&audio_io.gui);
    preset_panel.add(&graphe_gui);
    preset_panel.add(&feedback.feedback_gui);
    preset_panel.add(&fbo_feedback.feedback_gui);


    preset_panel.minimizeAll();
    audio_io.gui.minimizeAll();
    audio_io.gui_device.minimizeAll();


    preset_panel.loadFromFile("oscillo.xml");
    
    
    
    /* setup panel */
    setup_panel.setup("settings", "settings.xml", 10, 10);
    setup_panel.add(fps_label.setup("FPS"," "));
    setup_panel.add(&preset_gui);
    setup_panel.add(&cam.camera_settings_gui);
    setup_panel.add(&audio_io.gui_device);
    setup_panel.add(&interact_gui);
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

    interact_preset.update();
    
    while(osc_receiver.hasWaitingMessages())
    {
        ofxOscMessage m;
        osc_receiver.getNextMessage(m);
        interact_speed.parse_osc(m);
        interact_volume.parse_osc(m);
        //interact_preset.parse_osc(m);
        interact_preset.parse_osc(m);
        

    }
    
    if (interact_preset.return_flag)
    {
        if(preset_index>=preset_index.getMax())
        {
            preset_index=0;
        }else{
            preset_index++;
        }
        interact_preset.return_flag=0;
        preset_load_b=1;
    }
    
    if (interact_speed.interact_enable)
    {
        interact_speed.update();
        audio_io.player_set_speed(interact_speed.get_value());
    } else { //pas top efficace car update toujours...
        audio_io.player_set_speed(audio_io.player_speed);
    }
    
    if (interact_volume.interact_enable)
    {
        interact_volume.update();
        audio_io.set_output_vol(interact_volume.get_value());
    } else { //pas top efficace
        audio_io.set_output_vol(audio_io.output_volume.get());
    }
    cam.update();
    sync.update();
    
    if(gui_draw){fps_label= ofToString(ofGetFrameRate());}
    
    ofEnableAlphaBlending();
    
}

//--------------------------------------------------------------
void ofApp::draw()
{


    feedback.begin();
    fbo_feedback.begin();
    ofEnableDepthTest();

    cam.cam.begin();
    ofSetColor(255);
    graphe_input.draw();
    graphe_player.draw();
    graphe_output.draw();
    
    cam.cam.end();
    

    ofEnableBlendMode( OF_BLENDMODE_ADD );
    fbo_feedback.end();
    feedback.end();

    ofDisableDepthTest();
    
   ofEnableBlendMode(OF_BLENDMODE_DISABLED);
   
    interact_speed.draw();
    interact_volume.draw();
    
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
    
    if (key == 'f'){cam.set_fullscreen=!cam.set_fullscreen;}
    
    if (key >=48  && key <= 57)
    {
        preset_index=key-48;
        preset_load_b =1;
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
    
    feedback.allocate(w,h);
    fbo_feedback.allocate(w,h);

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
    cam.cam_get_param(b);
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
    cam.cam_set_param(b);
}


//--------------------------------------------------------------
