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


class Interact_struggle
{
public:
    // ofxOscReceiver osc_receiver;
    
    ofxGuiGroup gui;
    
    ofParameter<bool> interact_enable = 0;

    ofParameter<bool> debug = 1;
    ofParameter<bool> draw_value = 0;
    ofParameter<int> stop_time_threshold = 500;
    ofParameter<float> value_trim = 1;
    ofParameter<string> interact_osc_path;
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
    //string interact_osc_path;
    
    //smoothing
    ofParameter <bool> smooth_enable=0;
    int smooth_index = 0;
    ofParameter <int> smooth_amount = 1;
    int smooth_array[255];
    void do_smooth();
    
    //metro
    ofParameter<bool> metronome_enable =0;
    ofParameter<int> metronome_interval_ms=0;
    uint64_t last_metronome_time = 0;
    
};

class Interact_tic
{
public:
    // min max compteur à chaque nouvelle interact
    //
    void setup(string name, string _interact_osc_path);
    void update();
    
    bool return_flag =0;
    void parse_osc(ofxOscMessage m);
    uint64_t now_time = 0;

    ofxGuiGroup gui;
    
    ofParameter<string> interact_osc_path;
    ofParameter<bool> interact_enable = 0;
    ofParameter<bool> metronome_enable =0;
    ofParameter<int> metronome_interval_ms=0;
    uint64_t interval_time = 0;
    uint64_t last_metronome_time = 0;

};
#endif /* interact_hpp */
