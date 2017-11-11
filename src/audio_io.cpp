//
//  audio_in.cpp
//  oscillograph
//
//  Created by Guillaume Arseneault on 17-08-07.
//
//
// todo: -> audio in -> audio io
// 
#include "audio_in.hpp"

void Audio_in::setup()
{
    
    gui.setup();
    gui.setName("audio_in");
    gui.add(audio_select.set("audio_select",0,0,1));
    gui.add(audio_label.setup("", ""));
    gui.add(volume.set("volume",1,0,2));
    gui.add(pan.set("pan",0,-1,1));
    gui.add(buffer_size.set("buffer_size",64,64,4096));
    gui.add(sample_rate.set("sample_rate",44100,8000,192000));
    
    init();
    audio_select.addListener(this, &Audio_in::audio_select_change);

}

void Audio_in::init()
{
    auto devices = soundStream.getDeviceList();
    soundStream.printDeviceList();
    audio_select.setMax(devices.size());
    
    buffer_1.assign(buffer_size, 0.0);
    buffer_2.assign(buffer_size, 0.0);
}

void Audio_in::init(int selection)
{
    

auto devices = soundStream.getDeviceList();


    audio_select.setMax(devices.size());
    
    if (!devices[selection].inputChannels)
    {
        cout<<"error, no input on device"<<endl;
        audio_label = "[X] " + devices[selection].name;
        
    } else {
    audio_label = devices[selection].name;
    settings.setInListener(this);
    settings.setInDevice(devices[selection]);
    settings.sampleRate = sample_rate;
    settings.numInputChannels = 2;
    settings.bufferSize = buffer_size;
    soundStream.setup(settings);
        
    buffer_1.assign(buffer_size, 0.0);
    buffer_2.assign(buffer_size, 0.0);
    }
    
}


void Audio_in::audioIn(ofSoundBuffer & input){
    
    
    // au lieu d avoir left right mieux de travailler en un vecteur de channel input
    // samples are "interleaved"
    // process pan
    float pan_1 = 1-(pan*0.5 +0.5);
    float pan_2 = pan*0.5 +0.5;
    
    for (int i = 0; i < input.getNumFrames(); i++)
    {
        buffer_1[i]	= input[i*2  ] * volume * pan_1 ;
        buffer_2[i] = input[i*2+1] * volume * pan_2 ;
    }
    
    bufferCounter++;
     
}

void Audio_in::exit()
{
    
    buffer_1.assign(buffer_size, 0.0);
    buffer_2.assign(buffer_size, 0.0);

}

void Audio_in::audio_select_change(int &audio_select)
{
    init(audio_select);
}





