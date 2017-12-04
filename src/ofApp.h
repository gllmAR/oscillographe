#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOscParameterSync.h"
#include "audio_io.hpp"
#include "graphe.hpp"
#include "interact.hpp"
#include "ofxOsc.h"

#define HOST "localhost"
#define SYNC_INPORT 9000
#define SYNC_OUTPORT 9001
#define INTERACT_PORT 8001



class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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
    
    
    Interact interact_speed;
    Interact interact_volume;
    
    ofEasyCam cam;
    // workaround pour faire fonctionner le fullscreen sur le raspberry pi
    bool set_fullscreen_old = 0;
    bool screen_workaround_to_update = 1;
    
    int 	bufferCounter;
    int 	drawCounter;
    int     buffer_size_old=0;
    
    ofxOscReceiver osc_receiver;
    ofxOscParameterSync sync;


    ofxPanel gui;
    
    
    ofxGuiGroup camera_gui;
    ofxGuiGroup graphe_gui;
    
    
    
    ofParameter<bool> cam_set_ortho = 0;
    ofParameter<bool> cam_set_reset = 0;
    ofParameter<float> cam_set_distance = 0;
    ofParameter<bool> set_fullscreen = 0;
    ofxLabel fps_label;
    
    ofTexture screen_texture;
    ofPlanePrimitive feedback_plane;
    ofxGuiGroup feedback_gui;
    ofParameter<bool> feedback_enable=0;
    ofParameter<float> feedback_ammount = 0 ;
    ofParameter<float> feedback_pos_x = 0;
    ofParameter<float> feedback_pos_y = 0;
    ofParameter<float> feedback_scale = 0;
    
    bool gui_draw = 0;
    int app_size_w=100;
    int app_size_h=100;
    
    void cam_set_distance_change(float &f);
    bool cam_workaroud_to_update = 1;
    
    

};
