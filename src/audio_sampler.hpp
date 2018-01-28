//
//  audio_sampler.hpp
//  oscillographe
//
//  Created by Guillaume Arseneault on 18-01-28.
//
// todo -> function pour set le buffersize qui resetup le player

#ifndef audio_sampler_hpp
#define audio_sampler_hpp

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxBasicSoundPlayer.h"
#include "ofxSoundFile.h"

class Audio_sampler
{
public:
    
    void setup(int _file_index, int _buffer_size, int _gui_offset, string _name);
    void setup_gui(int _gui_offset, string _name);
    
    void audio_process(ofSoundBuffer& output);
    
    
    void draw();
    
    int buffer_size = 512;
    
    // sampler
    ofxPanel settings_panel;
    
    ofxPanel recalled_panel;
    
    
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
    ofxGuiGroup recorder_gui;
    ofParameter <bool> recorder_enable;
    ofSoundBuffer recorder_buffer;
    ofxSoundFile recorder_sound_file;
    void recorder_enable_changed(bool &b);
    void recorder_save_file();

    
    
    
    // recaller stuff
    
    ofxPanel sampler_preset_recal_panel;
    ofxPanel sampler_preset_panel;
    void sampler_preset_save(bool &b);
    void sampler_preset_load(bool &b);
    ofxGuiGroup sampler_preset_gui;
    ofParameter<int> sampler_preset_index;
    ofParameter<bool> sampler_preset_save_b;
    ofParameter<bool> sampler_preset_load_b;
    
    void recaller_preset_save(bool &b);
    void recaller_preset_load(bool &b);
    
    
};


#endif /* audio_sampler_hpp */
