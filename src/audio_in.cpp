//
//  ofxSoundSettingsGui.
//  oscillograph
//
//  Created by Guillaume Arseneault on 17-08-07.
//
//
// todo: clean
// 
#include "audio_in.hpp"

void Audio_in::setup()
{
    
    gui.setup();
    gui.setName("sound_setup");
    gui.add(audio_select.set("audio_select",0,0,1));
    gui.add(audio_label.setup("", ""));
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
    
    left.assign(buffer_size, 0.0);
    right.assign(buffer_size, 0.0);
}

void Audio_in::init(int selection)
{
    

auto devices = soundStream.getDeviceList();
//settings.setInDevice(devices[selection]);
//#ifdef TARGET_LINUX_ARM
//
//    settings.setInDevice(devices[0]);
//    
//    
//#else
//
//#endif
    
    
    //cout<< devices[0].name << endl;
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
        
    left.assign(buffer_size, 0.0);
    right.assign(buffer_size, 0.0);
    }
    
}

// voir si channel out ce comporte de la meme facon

void Audio_in::audioIn(ofSoundBuffer & input){
    
   // float curVol = 0.0;
    
    // au lieu d avoir left right mieux de travailler en un vecteur de channel input
    // samples are "interleaved"
    
    for (int i = 0; i < input.getNumFrames(); i++)
    {
        left[i]	 = input[i*2];
        right[i] = input[i*2+1];
    }
    
    bufferCounter++;
     
}

void Audio_in::exit()
{
    
    left.assign(buffer_size, 0.0);
    right.assign(buffer_size, 0.0);

}

void Audio_in::audio_select_change(int &audio_select)
{
    init(audio_select);
}





