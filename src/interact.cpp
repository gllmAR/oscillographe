//
//  interact.cpp
//  oscillographe
//
//  Created by Guillaume Arseneault on 17-12-01.
//
//

#include "interact.hpp"

void Interact::setup(string name, string _interact_osc_path)
{
    gui.setup();
    gui.setName(name);
    gui.add(interact_enable.set("interact_enable",1));
    gui.add(draw_value.set("draw_value",0));
    gui.add(debug.set("debug",0));
    gui.add(stop_time_threshold.set("stop_time_threshold",500,1,1000));
    gui.add(value_trim.set("value_trim",1,0,2));
    interact_osc_path = _interact_osc_path;
    //    gui.add(osc_input_port.set("osc_input_port",8001,8000, 8010));
//    osc_receiver.setup(osc_input_port);
}

void Interact::update()
{
    if(interact_enable)
    {
    now_time = ofGetElapsedTimeMillis();
    decrement_value();
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
            }
                
    
    }
    last_decrement_time = now_time;
    
    // a besoins d'un reference temporelle
    // si depasse un
}

float Interact::get_value()
{
    cooked_value = ofClamp(interact_value*0.001*value_trim, 0, 3);
    return cooked_value;
}


