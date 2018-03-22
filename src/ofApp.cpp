#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetVerticalSync(true);
    ofBackground(0, 0, 0);
    ofSetFrameRate(60);

    audio_io.setup();

    cam.setup();
    feedback.setup();
    recall.setup();
    setup_gui();
    recall.set_panel(settings_panel);

    settings_panel.loadFromFile("oscillographe.json");
    setup_panel.loadFromFile("setup.json");
    osc_receiver.setup(INTERACT_PORT); //pour input de senseur
    settings_sync.setup((ofParameterGroup&)settings_panel.getParameter(),
                        SYNC_SETTINGS_INPORT, "localhost", SYNC_OUTPORT);
    setup_sync.setup((ofParameterGroup&)setup_panel.getParameter(),
                     SYNC_SETUP_INPORT, "localhost", SYNC_OUTPORT);
    ofHideCursor();
}

//--------------------------------------------------------------
void ofApp::setup_gui()
{

    audio_io.gui.minimizeAll();
    audio_io.gui_device.minimizeAll();
    
    /* setup panel */
    settings_panel.setup("oscillographe", "oscillographe.json", 10, 10);
    settings_panel.add(fps_label.setup("FPS"," "));
    cam.camera_settings_gui.add(&feedback.feedback_gui);
    settings_panel.add(&cam.camera_settings_gui);
    settings_panel.add(&audio_io.gui);
    settings_panel.minimizeAll();
    
    setup_panel.setup("setup", "setup.json", 220, 10);
    setup_panel.add(&audio_io.gui_device);
    setup_panel.add(&recall.gui);
    setup_panel.minimizeAll();
}

//--------------------------------------------------------------
void ofApp::update()
{
    audio_io.update();
    recall.update();
    
    while(osc_receiver.hasWaitingMessages())
    {
        ofxOscMessage m;
        osc_receiver.getNextMessage(m);
        // updater les reference à interact... devrait être plus dynamique
        audio_io.audio_sampler_A.interact.parse_osc(m);
        audio_io.audio_sampler_B.interact.parse_osc(m);
        recall.interact.parse_osc(m);
    }
    
    cam.update();
    settings_sync.update();
    setup_sync.update();
    if(gui_draw){fps_label= ofToString(ofGetFrameRate());}
    ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofEnableBlendMode( OF_BLENDMODE_ADD );
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

    recall.draw();
    audio_io.draw_gui();
    if (gui_draw)
    {
        audio_io.draw_gui();
        settings_panel.draw();
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
    if( key == 'g' ){handle_gui();}
    if( key == 'm' )
    {
        show_mouse =!show_mouse;
        if (show_mouse)
        {
            ofShowCursor();
        } else {
            ofHideCursor();
        }
    }
    
    if (key == 'c'){recall.toggle_draw_recall();};
    
    if (key == 'f'){cam.set_fullscreen=!cam.set_fullscreen;}
    
    if (key >=48  && key <= 57)
    {

    }
}

//--------------------------------------------------------------
void ofApp::handle_gui()
{
    gui_draw=!gui_draw;
    
    if (gui_draw)
    {
        ofShowCursor();
    } else {
        ofHideCursor();
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
     if( button == 2 ){handle_gui();}
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
    app_size_w = w;
    app_size_h = h;
    cout << "app size = " << w << " by " << h <<endl;
    audio_io.set_size(w,h);
    feedback.allocate(w,h);
    recall.set_size(w,h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void ofApp::exit(){
    audio_io.exit();
}

//--------------------------------------------------------------
