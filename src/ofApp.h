#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOscParameterSync.h"
#include "audio_in.hpp"
#include "graphe.hpp"

#define HOST "localhost"
#define SYNC_INPORT 9000
#define SYNC_OUTPORT 9001

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
    
    
    
    

    Audio_in audio_in;
    Graphe graphe;
    
    ofEasyCam cam;

    bool set_fullscreen_old = 0;
    

    int 	bufferCounter;
    int 	drawCounter;
    

    ofxOscParameterSync sync;
    ofxPanel gui;
    ofxGuiGroup camera_gui;
    ofParameter<bool> cam_set_ortho = 0;
    ofParameter<bool> cam_set_reset = 0;
    ofParameter<float> cam_set_distance = 0;
    ofParameter<bool> set_fullscreen = 0;
    
    bool gui_draw = 0;
    int app_size_w=100;
    int app_size_h=100;
    

    
    

    bool screen_workaround_to_update = 1;
};
