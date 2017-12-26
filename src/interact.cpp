//
//  interact.cpp
//  oscillographe
//
//  Created by Guillaume Arseneault on 17-12-01.
//  classe servant à faire fluctuer une valeur asservie à un capteur
//  s'initialise avec un nom et une path osc,
//  s'update (pour décrémenter)
//  lui passer un message osc pour incrémenter

#include "interact.hpp"

void Interact::setup(string name, string _interact_osc_path)
{
    interact_osc_path = _interact_osc_path;
    gui.setup();
    gui.setName(name);
    gui.add(interact_osc_path_label.setup("osc", interact_osc_path));
    gui.add(interact_enable.set("interact_enable",0));
    gui.add(stop_time_threshold.set("stop_time_threshold",500,1,1000));
    gui.add(value_trim.set("value_trim",1,0,2));
    gui.add(metronome_enable.set("metronome_enable",0));
    gui.add(metronome_interval_ms.set("metronome_interval_ms",100, 1,2000));
    gui.add(draw_value.set("draw_value",0));
    gui.add(smooth_enable.set("smooth_enable",0));
    gui.add(smooth_amount.set("smooth_ammount",5,1,30));
    gui.add(debug.set("debug",0));


}

void Interact::update()
{
    now_time = ofGetElapsedTimeMillis();
    
    if(metronome_enable && now_time-last_metronome_time>metronome_interval_ms)
    {
        increment_value();
        last_metronome_time = now_time;
    }
    if(interact_enable)
    {
        decrement_value();
        if(smooth_enable){do_smooth();}
    }
}

void Interact::draw()
{
    if (interact_enable && draw_value)
    {
        ofPushMatrix();
        ofSetColor(255,255,255,255);
        ofDrawRectangle(0,15*ofGetHeight()/16,ofGetWidth()/2*cooked_value,ofGetHeight()/16);
        ofPopMatrix();
    }
}

void Interact::parse_osc(ofxOscMessage m)
{
    if (m.getAddress() == interact_osc_path)
    {
        increment_value();
    }
}

void Interact::increment_value()
{
    
    if(value_stop_flag)
    {
        value_stop_flag=0;
    }else{
        int delta_time=now_time-last_increment_time;
        interact_value = ofMap(delta_time,stop_time_threshold,0,0,1000);
        if(debug){cout<<"inc "<< interact_value << endl;}
        
        //smooth stuff
        if (smooth_index>=smooth_amount){smooth_index=0;}
        smooth_array[smooth_index]=interact_value;
        smooth_index++;
    }
    last_increment_time=now_time;
}

void Interact::decrement_value()
{
    if (interact_value > 0 )
    {
        if(now_time-last_increment_time>stop_time_threshold)
        {
            interact_value=0.01;
            value_stop_flag = 1;
            if(debug){cout<<"stoped!!"<<endl;}
        }else{
            interact_value -= now_time-last_decrement_time;
            if (interact_value < 0){interact_value = 0;}
            if(debug){cout<<"dec "<< interact_value << endl;}
            //smooth stuff
            if (smooth_index>=smooth_amount){smooth_index=0;}
            smooth_array[smooth_index]=interact_value;
            smooth_index++;
        }
    }
    last_decrement_time = now_time;
}

float Interact::get_value()
{
    cooked_value = ofClamp(interact_value*0.001*value_trim, 0, 3);
    return cooked_value;
}

void Interact::do_smooth()
{
    int total = 0;
    for(int i=0; i < smooth_amount; i++)
    {
        total+=smooth_array[i];
    }
    interact_value=total/smooth_amount;

    if (interact_value < 0)
    {
        interact_value=0;
    }
    
}


