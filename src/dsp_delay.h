//
//  dsp_delay.h
//  oscillographe
//
//  Created by Guillaume Arseneault on 18-02-14.
//
//

#ifndef dsp_delay_h
#define dsp_delay_h

#include "ofMain.h"
#include "ofxGui.h"

class Dsp_Delay
{
public:
    vector<float> buffer;
    ofParameter<bool> enable;
    ofParameter<float> mix;
    ofParameter<float> delay;
    ofParameter<float> feedback;
    ofParameter<bool> clear;
    int sample_rate;

    
    ofxGuiGroup gui;
    
    void setup(int _sample_rate)
    {
        gui.setup("delay");
        gui.add(enable.set("enable",0));
        gui.add(mix.set("mix",.5,0,1));
        gui.add(delay.set("delay",1,0.0001,10));
        gui.add(feedback.set("feedback",0,0,1));
        gui.add(clear.set("clear",0));
        delay.addListener(this, &Dsp_Delay::set_delay);
        
        buffer.resize(delay);
        buffer.assign(delay, 0);
        pos=0;
        sample_rate=_sample_rate;
    }
    
    void set_delay(float &f)
    {
        if (pos>=int(f*sample_rate)){pos=0;}
        
        buffer.resize(int(f*sample_rate+1));
        
    }
    
    float process(float in)
    {
        pos++;
        pos %= buffer.size();
        float out = buffer[pos];
        buffer[pos] = ofClamp(feedback*buffer[pos] + in, -1, 1);
        return in + (out - in)*mix;
    }
    
    void process(ofSoundBuffer &input, ofSoundBuffer &output)
    {
        if (clear)
        {
            pos=0;
            buffer.assign(buffer.size(), 0);
            clear=0;
        }
        if (enable)
        {
            for(int i = 0; i < output.size(); i++)
            {
                output[i] = process(input[i]);
            }
        }
    }

private:
    int pos;
    
};



#endif /* dsp_delay_h */
