//
//  audio_param_smooth.hpp
//  oscillographe
//  design for smoothing audio parameters at DSP rate
//  use the struct Audio_param_smooth
//  create a smoother with new  [objectname].smoother(time,samplerate)
//  Created by Guillaume Arseneault on 18-04-26.
//
//

#ifndef audio_param_smooth_hpp
#define audio_param_smooth_hpp

#include "ofMain.h"

class Audio_param_smooth
{

public:
    int sample_rate =44100;
    int time_ms= 10000;
    float target_value =1;
    float current_value =1;
    
    
    void setup(float _value, float _time_ms, int _sample_rate)
    {
        target_value = _value;
        current_value = _value;
        time_ms = _time_ms;
        sample_rate = _sample_rate;
        calculate_ratio();
    }
    
    void set(float _value, float _time_ms)
    {
        target_value = _value;
        current_value = _value;
        time_ms = _time_ms;
        calculate_ratio();
    }
    
    void set(float _time_ms)
    {
        time_ms = _time_ms;
        calculate_ratio();
    }
    
    void calculate_ratio()
    {
        a=exp(-TWO_PI /( time_ms * 0.0001 * sample_rate));
        b= 1.0 -a;
    }
    
    inline float process ()
    {
       return current_value = (target_value * b) +( current_value * a );
    }
    
private:
    float a;
    float b;

};



#endif /* audio_param_smooth_hpp */
