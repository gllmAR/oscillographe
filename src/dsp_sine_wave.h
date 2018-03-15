//
//  dsp_sine_wave.h
//  oscillographe
//
//  Created by Guillaume Arseneault on 18-02-14.
//
//

#ifndef dsp_sine_wave_h
#define dsp_sine_wave_h

#include "ofMain.h"
#include "ofxGui.h"


class Dsp_Sine_Wave
{
public:
    void setup()
    {
        current_phase = 0;
        gui.setup("sine_wave");
        gui.add(enable.set("enable",0));
        gui.add(freq.set("freq",440, 0,1250));
        gui.add(amplitude.set("amplitude", 1,0,1));
        
    }
    void process(ofSoundBuffer &in, ofSoundBuffer &out)
    
    {
        if(enable)
        {
        float m = TWO_PI* freq / in.getSampleRate();
        int numFrames = out.getNumFrames();
        int numChannels = out.getNumChannels();
        
        for(int i = 0; i < numFrames; i++)
        {
            float s = sin(m*i +current_phase) * amplitude;
            for(int c = 0; c < numChannels; c++)
            {
                out[i*numChannels + c ] = s;
            }
        }
        current_phase += (m*numFrames);
        }
    }
    
    ofxGuiGroup gui;
    ofParameter<bool> enable;
    ofParameter<float> freq;
    ofParameter<float> amplitude;
    
private:
    
    float current_phase;
    
};


#endif /* dsp_sine_wave_h */
