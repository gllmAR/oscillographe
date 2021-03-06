#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOscParameterSync.h"
#include "audio_io.hpp"
#include "graphe.hpp"
#include "interact.hpp"
#include "ofxOsc.h"
#include "camera_ctl.hpp"
#include "feedback.hpp"
#include "recall.hpp"

#define HOST "localhost"
#define SYNC_SETTINGS_INPORT 9001
#define SYNC_SETUP_INPORT 9002
#define SYNC_OUTPORT 9000
#define INTERACT_PORT 8001



class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void setup_gui();
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    void windowResized(int w, int h);
    void gotMessage(ofMessage msg);
    void exit();
    
    Audio_io audio_io;
    Recall recall;
    
    Camera_ctl cam;
    
    ofxOscReceiver osc_receiver;
    ofxOscParameterSync settings_sync;
    ofxOscParameterSync setup_sync;
    
    // workaround pour faire fonctionner le fullscreen sur le raspberry pi
    bool screen_workaround_to_update = 1;
    
    int 	bufferCounter;
    int 	drawCounter;
    int     buffer_size_old=0;
    
    ofxPanel setup_panel;       // params qui sont statiqc par machine
    ofxPanel settings_panel;  // paramètre qui évolue

    ofxLabel fps_label;
    
    Screen_feedback feedback;
    
    void handle_gui();    
    bool gui_draw = 0;
    bool show_mouse = 0;
    int app_size_w=100;
    int app_size_h=100;
    
};
