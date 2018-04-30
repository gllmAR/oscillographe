//
//  audio_sampler.hpp
//  oscillographe
//
//  Created by Guillaume Arseneault on 18-01-28.
//
//

#ifndef audio_sampler_hpp
#define audio_sampler_hpp

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxBasicSoundPlayer.h"
#include "ofxSoundFile.h"
#include "graphe.hpp"
#include "presets.hpp"
#include "interact.hpp"
#include "audio_param_smooth.hpp"


//#define GUI_INIT_OFFSET_X 640
//#define GUI_INIT_LOOPS_OFFSET_Y 260
class Audio_sampler
{
public:
    
    void setup(int _id, int _buffer_size);
    void setup_gui(string _name);
    
    void audio_input(ofSoundBuffer& input, ofSoundBuffer& output);
    void audio_process(ofSoundBuffer& output);
    
    
    void draw_gui();
    
    int buffer_size = 512;
    
    // sampler
    string sampler_name;
    string sampler_loops_name;
    int sampler_id;
    ofxGuiGroup sampler_gui;
    int gui_offset_x;
    
    
    // player stuff
    ofxGuiGroup player_gui;
    ofxBasicSoundPlayer player;
    ofSoundBuffer player_buffer;
    ofParameter <bool> player_enable;
    ofParameter <float> player_volume;
    
    ofParameter <float> player_speed;
    ofParameter <float> player_pan;
    ofParameter <float> player_position;
    ofParameter <bool> player_loop;
    ofParameter <bool> player_loop_selection;
    void player_loop_selection_changed(bool &b);
    ofParameter <float> player_loop_in;
    void player_loop_in_changed(float &f);
    ofParameter <float> player_loop_out;
    void player_loop_out_changed(float &f);
    ofParameter <int> player_file_index;
    int player_file_index_old = -1;
    vector <float> player_buffer_1_wo;
    vector <float> player_buffer_2_wo;
    
    
    
    void player_enable_change(bool &player_enable);
    void player_speed_change(float &f);
    void player_pan_change(float &f);
    void player_volume_change(float &f);
    void player_position_change(float &f);
    void player_load_file_index(int _file_index);
    void player_file_index_change(int &i);
    
    void player_set_speed(float f);
    
    string player_get_filename();
    
    // recorder stuff
    bool record_init_b;
    ofxGuiGroup recorder_gui;
    ofParameter <bool> recorder_enable;
    ofParameter <bool> recorder_record_output;
    ofParameter <int> recorder_file_index;
    ofSoundBuffer recorder_buffer;
    ofxSoundFile recorder_sound_file;
    void recorder_enable_changed(bool &b);
    void recorder_save_file();


    
    // recaller stuff
    ofxGuiGroup loop_recall_gui;

    ofxGuiGroup recaller_gui;
    void preset_save(bool &b);
    void preset_load(bool &b);
    //ofxGuiGroup sampler_preset_gui;
    ofParameter<int> recaller_preset_index;
    
    ofParameter<bool> recaller_preset_save_b;
    ofParameter<bool> recaller_preset_load_b;
    
    void recaller_preset_save(bool &b);
    void recaller_preset_load(bool &b);
    
    // graph stuff
    Graphe graphe;
    void update_graph();
    void draw_graph();

    //interact stuff
    Interact_struggle interact;
    
    // line stuff for crossfade when changing loop
    bool audio_line_flag=0;

    void recaller_preset_load_line();
    Audio_param_smooth amplitude_line;

    
};


#endif /* audio_sampler_hpp */
