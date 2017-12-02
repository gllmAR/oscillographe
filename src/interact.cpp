//
//  interact.cpp
//  oscillographe
//
//  Created by Guillaume Arseneault on 17-12-01.
//
//

#include "interact.hpp"

void Interact::setup()
{
    gui.setup();
    gui.setName("interact");
    gui.add(interact_enable.set("interact_enable",1));
    gui.add(draw_speed.set("draw_speed",0));
    gui.add(debug.set("debug",0));
    gui.add(stop_time_threshold.set("stop_time_threshold",500,1,1000));
    gui.add(speed_trim.set("speed_trim",1,0,2));
    gui.add(osc_input_port.set("osc_input_port",8001,8000, 8010));
    osc_receiver.setup(osc_input_port);
}

void Interact::update()
{
    if(interact_enable)
    {
    now_time = ofGetElapsedTimeMillis();
    parse_osc();
    decrement_speed();
    } 
}

void Interact::draw()
{
  if (interact_enable && draw_speed)
  {
      ofPushMatrix();
      ofSetColor(255,255,255,255);
      ofDrawRectangle(0,15*ofGetHeight()/16,ofGetWidth()/2*cooked_speed,ofGetHeight()/16);
      ofPopMatrix();
  }
}

void Interact::parse_osc()
{
    if (interact_enable)
    {
        while(osc_receiver.hasWaitingMessages())
        {
            ofxOscMessage m;
            osc_receiver.getNextMessage(m);
            if (m.getAddress() == "/gpio/1")
            {
                increment_speed();
            }
        }
    }
}

void Interact::increment_speed()
{
 
    if(speed_stop_flag)
    {
        speed_stop_flag=0;
    }else{
        int delta_time=now_time-last_increment_time;
        interact_speed = ofMap(delta_time,stop_time_threshold,0,0,1000);
        if(debug){cout<<"inc "<< interact_speed << endl;}
    }
    last_increment_time=now_time;
}

void Interact::decrement_speed()
{
    if (interact_speed > 0 )
    {
            if(now_time-last_increment_time>stop_time_threshold)
            {
                interact_speed=0;
                speed_stop_flag = 1;
                if(debug){cout<<"stoped!!"<<endl;}
            }else{
                interact_speed -= now_time-last_decrement_time;
                if (interact_speed < 0){interact_speed = 0;}
                if(debug){cout<<"dec "<< interact_speed << endl;}
            }
                
    
    }
    last_decrement_time = now_time;
    
    // a besoins d'un reference temporelle
    // si depasse un
}

float Interact::get_speed()
{
    cooked_speed = ofClamp(interact_speed*0.001*speed_trim, 0, 3);
    return cooked_speed;
}


