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
    setup_gui();

    osc_receiver.setup(INTERACT_PORT); //pour input de senseur
    settings_sync.setup((ofParameterGroup&)setup_panel.getParameter(),SYNC_INPORT, "localhost", SYNC_OUTPORT);
    
//    viz_preset_recall_sync.setup((ofParameterGroup&)viz_preset_recal_panel.getParameter(),SYNC_INPORT,"localhost",SYNC_OUTPORT);
//    viz_preset_sync.setup((ofParameterGroup&)viz_preset_panel.getParameter(),SYNC_INPORT,"localhost",SYNC_OUTPORT);
    

    
}

//--------------------------------------------------------------

void ofApp::setup_gui()
{


    /* interact */

    interact_gui.setup();
    interact_gui.setName("interact");
    interact_gui.add(&interact_speed.gui);
    interact_gui.add(&interact_volume.gui);
    interact_gui.add(&interact_preset.gui);
    interact_gui.minimizeAll();

    


    audio_io.gui.minimizeAll();
    audio_io.gui_device.minimizeAll();

    
    /* setup panel */
    setup_panel.setup("oscillographe", "oscillographe.json", 10, 10);
    setup_panel.add(fps_label.setup("FPS"," "));
//    setup_panel.add(&viz_preset_gui);
    setup_panel.add(&cam.camera_settings_gui);
    setup_panel.add(&feedback.feedback_gui);
    setup_panel.add(&audio_io.gui_device);
    setup_panel.add(&audio_io.gui);
    setup_panel.add(&interact_gui);
    setup_panel.minimizeAll();
    
    setup_panel.loadFromFile("oscillographe.json");
    
    

    
    
}

//--------------------------------------------------------------
void ofApp::update()
{
      audio_io.update();
    interact_preset.update();
    
    while(osc_receiver.hasWaitingMessages())
    {
        ofxOscMessage m;
        osc_receiver.getNextMessage(m);
        interact_speed.parse_osc(m);
        interact_volume.parse_osc(m);
        interact_preset.parse_osc(m);
    }
    
    if (interact_preset.return_flag)
    {
//        if(viz_preset_index>=viz_preset_index.getMax())
//        {
////            viz_preset_index=0;
//        }else{
////            viz_preset_index++;
//        }
//        interact_preset.return_flag=0;
////        viz_preset_load_b=1;
    }
    
    if (interact_speed.interact_enable)
    {
        interact_speed.update();
       // audio_io.player_set_speed(interact_speed.get_value());
    } else { //pas top efficace car update toujours...
        //audio_io.player_set_speed(audio_io.player_speed);
    }
    
    if (interact_volume.interact_enable)
    {
        interact_volume.update();
        //audio_io.set_output_vol(interact_volume.get_value());
    } else { //pas top efficace
        //audio_io.set_output_vol(audio_io.output_volume.get());
    }
    cam.update();
    
    settings_sync.update();
//    viz_preset_recall_sync.update();
//    viz_preset_sync.update();
    
    if(gui_draw){fps_label= ofToString(ofGetFrameRate());}
    
    ofEnableAlphaBlending();
    
}

//--------------------------------------------------------------
void ofApp::draw()
{


    feedback.begin();
    ofEnableDepthTest();

    cam.cam.begin();
    ofSetColor(255);
    
    audio_io.draw_graphes();
    
    cam.cam.end();
    

    ofEnableBlendMode( OF_BLENDMODE_ADD );
    feedback.end();

    ofDisableDepthTest();
    
   ofEnableBlendMode(OF_BLENDMODE_DISABLED);
   
    interact_speed.draw();
    interact_volume.draw();
    
    if (gui_draw)
    {
        audio_io.draw_gui();
//        audio_io.audio_sampler_A.settings_panel.draw();
//        audio_io.audio_sampler_A.recalled_panel.draw();
//        audio_io.audio_sampler_A.graphe.gui.draw();
//        viz_preset_recal_panel.draw();
//        viz_preset_panel.draw();
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
//        viz_preset_index=key-48;
//        viz_preset_load_b =1;
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
    
    
    audio_io.set_size(w,h);
    
    feedback.allocate(w,h);

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
