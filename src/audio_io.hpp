//
//  audio_in.hpp
//  oscillograph
//
//  Created by Guillaume Arseneault on 17-08-07.
//
//
// sert a configurer le soundstream et sauvegarder
// logique de parser le system (une config par system)



#ifndef audio_in_hpp
#define audio_in_hpp

#include "ofMain.h"
#include "ofxGui.h"



class Audio_in
{
public:
    void setup();
    void init();
    void init(int selection);
    void update();

    void exit();
    void audioIn(ofSoundBuffer & input);

    void audio_select_change(int &audio_select);
    
    ofSoundStream soundStream;
    ofSoundStreamSettings settings;
    
    vector <ofSoundDevice> audio_devices;

    
    ofxGuiGroup gui;
    ofParameter <float> volume;
    ofParameter <float> pan;
    ofParameter <int> buffer_size;
    ofParameter <int> sample_rate;
    ofParameter <int> audio_select;
    ofxLabel audio_label;


    vector <float> buffer_1;
    vector <float> buffer_2;

    vector <float> volHistory;
    int 	bufferCounter;

    


};


#endif /* SoundStreamSettings_hpp */
