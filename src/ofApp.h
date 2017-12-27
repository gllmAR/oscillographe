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

#define HOST "localhost"
#define SYNC_INPORT 9000
#define SYNC_OUTPORT 9001
#define INTERACT_PORT 8001



class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        void setup_gui();
    
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    void exit();
    

    Audio_io audio_io;
    Graphe graphe_input;
    Graphe graphe_output;
    Graphe graphe_player;
    
    ofxGuiGroup interact_gui;
    Interact_struggle interact_speed;
    Interact_struggle interact_volume;
    Interact_tic interact_preset;

    
    Camera_ctl cam;
    
    // workaround pour faire fonctionner le fullscreen sur le raspberry pi
    bool screen_workaround_to_update = 1;
    
    int 	bufferCounter;
    int 	drawCounter;
    int     buffer_size_old=0;
    
    ofxOscReceiver osc_receiver;
    ofxOscParameterSync sync;


    ofxPanel preset_panel;
    ofxPanel setup_panel;
    
    ofxGuiGroup graphe_gui;
    
    

    ofxLabel fps_label;
    
    Screen_feedback feedback;
    Fbo_feedback fbo_feedback;
    

    
    bool gui_draw = 0;
    int app_size_w=100;
    int app_size_h=100;
    
    
    // save et load preset
    void preset_save(bool &b);
    void preset_load(bool &b);
    ofxGuiGroup preset_gui;
    ofParameter<int> preset_index;
    ofParameter<bool> preset_save_b;
    ofParameter<bool> preset_load_b;
    
};
