//
//  audio_io.hpp
//  oscillograph
//
//  Created by Guillaume Arseneault on 17-08-07.
//
//
// sert a configurer le soundstream (input et output)
// sert a jouer des sons
// sert a extraire les valeur de sons en array de buffersize




#ifndef audio_io_hpp
#define audio_io_hpp

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxBasicSoundPlayer.h"
#include "ofxSoundFile.h"
#include "audio_sampler.hpp"



class Audio_io
{
public:
    void setup();
    void exit();
    void setup_gui();
    void setup_gui_listener();
    void setup_audio();
    //--->
    void setup_player(int file_index);
    //<---
    void reset_audio(bool &b);
    void set_master_vol(float _master_vol);
    void set_master_vol_change(float &f);
    void set_output_vol(float _output_vol);
    void set_output_vol_change(float &f);
    
    vector <ofSoundDevice> audio_devices;
    
    //meta stuff
    ofxGuiGroup gui;
    ofxGuiGroup gui_device;
    ofParameter <bool> reset_audio_b;
    ofParameter <int> buffer_size;
    ofParameter <int> sample_rate;
    
    ofParameter <float> master_vol; //permet de controller le volume out
    float master_vol_ammount;
    float output_vol_ammount;
    
    // audio_io stuff
    ofxGuiGroup gui_device_io;
    
    
    ofSoundStreamSettings io_settings;
    ofSoundStream io_stream;
    
    
    ofParameter <int> io_select;
    ofParameter <bool> io_enable;
    ofParameter <bool> io_input_enable;
    ofParameter <bool> io_output_enable;
    ofxLabel io_label;
    ofParameter <float> io_input_volume;
    ofParameter <float> io_input_pan;
    ofParameter <float> io_output_volume;
    ofParameter <float> io_output_pan;
    
    
    
    
    
    void io_init(int i);
    void io_select_change(int &i);
    void io_enable_change(bool &b);
    
    // input stuff
    ofxGuiGroup gui_device_input;
    ofxGuiGroup gui_input;
    ofSoundStream input_stream;
    ofSoundStreamSettings input_settings;
    ofSoundBuffer input_buffer;
    ofParameter <bool> input_mute;
    ofParameter <float> input_trim;
    ofParameter <float> input_volume;
    ofParameter <float> input_pan;
    ofParameter <int> input_select;
    ofParameter <bool> input_enable;
    ofxLabel input_label;
    vector <float> input_buffer_1;
    vector <float> input_buffer_2;
    
    
    void input_init(int selection);
    void audioIn(ofSoundBuffer & input);
    void input_select_change(int &input_select);
    void input_enable_change(bool &input_enable);
    
    // output stuff
    ofxGuiGroup gui_device_output;
    ofxGuiGroup gui_output;
    ofSoundStream output_stream;
    ofSoundStreamSettings output_settings;
    ofParameter <bool> output_mute;
    ofParameter <float> output_volume;
    ofParameter <float> output_pan;
    ofParameter <int> output_select;
    ofParameter <bool> output_enable;
    ofxLabel output_label;
    vector <float> output_buffer_1;
    vector <float> output_buffer_2;
    void output_init(int selection);
    void audioOut(ofSoundBuffer & output);
    void output_select_change(int &output_select);
    void output_enable_change(bool &output_enable);
    
    // --->
    // sampler
    ofxGuiGroup gui_sampler;

    
    // player stuff
    ofxGuiGroup gui_player;
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
    void player_file_index_change(int &i);
    
    void player_set_speed(float f);
    
    string player_get_filename();
    
    // recorder stuff
    ofxGuiGroup gui_recorder;
    ofParameter <bool> recorder_enable;
    ofSoundBuffer recorder_buffer;
    ofxSoundFile recorder_sound_file;
    void recorder_enable_changed(bool &b);
    void recorder_save_file();

    // <---
    
    Audio_sampler audio_sampler_A;
    
};


#endif /* SoundStreamSettings_hpp */
