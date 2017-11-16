//
//  audio_io.hpp
//  oscillograph
//
//  Created by Guillaume Arseneault on 17-08-07.
//
//
// sert a configurer le soundstream et sauvegarder
// logique de parser le system (une config par system)



#ifndef audio_io_hpp
#define audio_io_hpp

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxBasicSoundPlayer.h"



class Audio_io
{
public:
    void setup();
    void init();
    void exit();
    vector <ofSoundDevice> audio_devices;
    
    ofxGuiGroup gui;
    ofParameter <int> buffer_size;
    ofParameter <int> sample_rate;
    
    ofSoundStream input_stream;
    ofSoundStreamSettings input_settings;
    ofParameter <float> input_volume;
    ofParameter <float> input_pan;
    ofParameter <int> input_select;
    ofParameter <bool> input_active;
    ofxLabel input_label;
    vector <float> input_buffer_1;
    vector <float> input_buffer_2;
    void input_init(int selection);
    void audioIn(ofSoundBuffer & input);
    void input_select_change(int &input_select);
    void input_active_change(bool &input_active);
    
    ofSoundStream output_stream;
    ofSoundStreamSettings output_settings;
    ofParameter <float> output_volume;
    ofParameter <float> output_pan;
    ofParameter <int> output_select;
    ofParameter <bool> output_active;
    ofxLabel output_label;
    vector <float> output_buffer_1;
    vector <float> output_buffer_2;
    void output_init(int selection);
    void audioOut(ofSoundBuffer & output);
    void output_select_change(int &output_select);
    void output_active_change(bool &output_active);
    
    ofxBasicSoundPlayer player_1;
    ofxBasicSoundPlayer player_2;
    ofSoundBuffer player_buffer_1;
    ofSoundBuffer player_buffer_2;
    ofParameter <bool> player_active;
    ofParameter <float> player_volume;
    ofParameter <float> player_speed;
    ofParameter <float> player_pan;
    ofParameter <bool> player_loop;
    
    void player_speed_change(float &f);
    void player_pan_change(float &f);
    void player_volume_change(float &f);

    
};


#endif /* SoundStreamSettings_hpp */
