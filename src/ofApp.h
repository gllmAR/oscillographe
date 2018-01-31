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
#define SYNC_INPORT 9001
#define SYNC_OUTPORT 9000
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
    


   
    ofxPanel setup_panel;
    
    ofxGuiGroup graphe_gui;
    
    

    ofxLabel fps_label;
    
    Screen_feedback feedback;
    Fbo_feedback fbo_feedback;
    

    
    bool gui_draw = 0;
    int app_size_w=100;
    int app_size_h=100;
    
    
    // save et load preset visual
    ofxOscParameterSync viz_preset_recall_sync;
    ofxPanel viz_preset_recal_panel;
    ofxOscParameterSync viz_preset_sync;
    ofxPanel viz_preset_panel;
    void viz_preset_save(bool &b);
    void viz_preset_load(bool &b);
    ofxGuiGroup viz_preset_gui;
    ofParameter<int> viz_preset_index;
    ofParameter<bool> viz_preset_save_b;
    ofParameter<bool> viz_preset_load_b;
    
    
//    ofxPanel audio_sampler_A_settings_panel;
//    ofxPanel audio_sampler_A_recalled_panel;
//    ofxPanel audio_sampler_B_settings_panel;
//    ofxPanel audio_sampler_B_recalled_panel;
    //--->

      
};
