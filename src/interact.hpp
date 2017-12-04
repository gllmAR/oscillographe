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
    // ofxOscReceiver osc_receiver;
    
    ofxGuiGroup gui;
    
    ofParameter<bool> interact_enable = 1;
    ofParameter<bool> debug = 1;
    ofParameter<bool> draw_value = 0;
    ofParameter<int> stop_time_threshold = 500;
    ofParameter<float> value_trim = 1;
    int interact_value =0;
    
    uint64_t interval_time = 0;
    uint64_t now_time = 0;
    int last_increment_time = 0;
    int last_decrement_time = 0;
    
    bool  value_stop_flag=1;
    
    void setup(string name, string _interact_osc_path);
    void update();
    void draw();
    void parse_osc(ofxOscMessage m);
    void decrement_value();
    void increment_value();
    float get_value();
    float cooked_value;
    
    string interact_name;
    string interact_osc_path;
    
};
#endif /* interact_hpp */
