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
    ofParameter<int> delay;
    ofParameter<float> feedback;

    
    ofxGuiGroup gui;
    
    void setup()
    {
        gui.setup("delay");
        gui.add(enable.set("enable",0));
        gui.add(mix.set("mix",0,0,1));
        gui.add(delay.set("delay",1,1,44100));
        gui.add(feedback.set("feedback",0,0,1));
        
        delay.addListener(this, &Dsp_Delay::set_delay);
        
        buffer.resize(delay);
        buffer.assign(delay, 0);
        pos=0;
    }
    
    void set_delay(int &i)
    {
        if (pos>=i){pos=0;}
        
        buffer.resize(i);
        
    }
    
    float process(float in)
    {
        pos++;
        pos %= buffer.size();
        float out = buffer[pos];
        buffer[pos] = feedback*buffer[pos] + in;
        return in + (out - in)*mix;
    }
    
    void process(ofSoundBuffer &input, ofSoundBuffer &output)
    {
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
