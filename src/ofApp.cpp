#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetVerticalSync(true);
    ofBackground(0, 0, 0);
    
    ofSetFrameRate(60);

    audio_io.setup();

    cam.setup();
    feedback.setup();
    setup_gui();

    osc_receiver.setup(INTERACT_PORT); //pour input de senseur
    settings_sync.setup((ofParameterGroup&)setup_panel.getParameter(),SYNC_INPORT, "localhost", SYNC_OUTPORT);


    
}

//--------------------------------------------------------------

void ofApp::setup_gui()
{



    audio_io.gui.minimizeAll();
    audio_io.gui_device.minimizeAll();

    
    /* setup panel */
    setup_panel.setup("oscillographe", "oscillographe.json", 10, 10);
    setup_panel.add(fps_label.setup("FPS"," "));
    cam.camera_settings_gui.add(&feedback.feedback_gui);
    setup_panel.add(&cam.camera_settings_gui);
    setup_panel.add(&audio_io.gui_device);
    setup_panel.add(&audio_io.gui);
    setup_panel.minimizeAll();
    
    setup_panel.loadFromFile("oscillographe.json");
    
    

    
    
}

//--------------------------------------------------------------
void ofApp::update()
{
      audio_io.update();
    
    while(osc_receiver.hasWaitingMessages())
    {
        ofxOscMessage m;
        osc_receiver.getNextMessage(m);
    }
    

    cam.update();
    
    settings_sync.update();

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
   

    
    if (gui_draw)
    {
        audio_io.draw_gui();

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
