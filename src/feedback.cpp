//
//  feedback.cpp
//  oscillographe
//
//  Created by Guillaume Arseneault on 17-12-26.
//
//

#include "feedback.hpp"


void Feedback::setup()
{
    
    feedback_gui.setup();
    feedback_gui.setName("feedback");
    feedback_gui.add(feedback_enable.set("enable",0));
    feedback_gui.add(feedback_ammount.set("ammount", 0, 0, 1));
    feedback_gui.add(feedback_pos_x.set("x", 1, 0, 2 ));
    feedback_gui.add(feedback_pos_y.set("y", 1, 0, 2 ));
    feedback_gui.add(feedback_scale.set("scale", 1, 0 ,2));
    
    feedback_plane.rotateDeg(180, 1, 0, 0); //flipper la texture de feedback car inverse
}

void Feedback::allocate(int w, int h)
{
    screen_size_w = w;
    screen_size_h = h;
    screen_texture.allocate(w,h,GL_RGBA);
    feedback_plane.resizeToTexture(screen_texture);
}
    
void Feedback::begin()
{
    if(feedback_enable)
    {
        ofSetColor(255, 255, 255, feedback_ammount*255);
        feedback_plane.setPosition(screen_size_w/2, screen_size_h/2, 0);
        screen_texture.bind();
        feedback_plane.setScale(feedback_scale);
        feedback_plane.setPosition(feedback_pos_x*screen_size_w/2, feedback_pos_y*screen_size_h/2, 0);
        
        feedback_plane.draw();
        screen_texture.unbind();
    }
}

void Feedback::end()
{
    
    if(feedback_enable)
    {
        screen_texture.loadScreenData(0,0,screen_size_w,screen_size_h);
    }
    
}
