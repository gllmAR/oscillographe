//
//  interact.hpp
//  oscillographe
//
//  Created by Guillaume Arseneault on 17-12-01.
//
//

#ifndef interact_hpp
#define interact_hpp



#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOsc.h"


class Interact
{
public:
    ofxOscReceiver osc_receiver;
    
    ofxGuiGroup gui;
    
    ofParameter<bool> interact_enable = 1;
    ofParameter<bool> debug = 1;
    ofParameter<bool> draw_speed = 0;
    ofParameter<int> osc_input_port = 8001;
    ofParameter<int> stop_time_threshold = 500;
    ofParameter<float> speed_trim = 1;
    int interact_speed =0;
    
    uint64_t interval_time = 0;
    uint64_t now_time = 0;
    int last_increment_time = 0;
    int last_decrement_time = 0;
    
    bool  speed_stop_flag=1;
  
    
    void setup();
    void update();
    void draw();
    void parse_osc();
    void decrement_speed();
    void increment_speed();
    float get_speed();
    float cooked_speed;
    
    
    
    
};
#endif /* interact_hpp */
