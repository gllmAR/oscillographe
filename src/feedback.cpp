//
//  feedback.cpp
//  oscillographe
//
//  Created by Guillaume Arseneault on 17-12-26.
//
//

#include "feedback.hpp"


void Screen_feedback::setup()
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

void Screen_feedback::allocate(int w, int h)
{
    screen_size_w = w;
    screen_size_h = h;
    screen_texture.allocate(w,h,GL_RGBA);
    feedback_plane.resizeToTexture(screen_texture);
}
    
void Screen_feedback::begin()
{
    if(feedback_enable)
    {
        ofPushMatrix();
        ofSetColor(255, 255, 255, feedback_ammount*255);
        feedback_plane.setPosition(screen_size_w/2, screen_size_h/2, 0);
        screen_texture.bind();
        feedback_plane.setScale(feedback_scale);
        feedback_plane.setPosition(feedback_pos_x*screen_size_w/2, feedback_pos_y*screen_size_h/2, 0);
        
        feedback_plane.draw();
        screen_texture.unbind();
        ofPopMatrix();
    }
}

void Screen_feedback::end()
{
    
    if(feedback_enable)
    {
        screen_texture.loadScreenData(0,0,screen_size_w,screen_size_h);
    }
    
}


//------------------------------------------------



void Fbo_feedback::setup()
{
    
    feedback_gui.setup();
    feedback_gui.setName("fbo_feedback");
    feedback_gui.add(feedback_enable.set("enable",1));
    feedback_gui.add(feedback_ammount.set("ammount", 255, 0, 255));
    feedback_gui.add(feedback_pos_x.set("x", 1, 0, 2 ));
    feedback_gui.add(feedback_pos_y.set("y", 1, 0, 2 ));
    feedback_gui.add(feedback_scale.set("scale", 1, 0 ,2));
    
    allocate(ofGetWidth(), ofGetHeight());
    
//    feedback_plane.rotateDeg(180, 1, 0, 0); //flipper la texture de feedback car inverse
}

void Fbo_feedback::allocate(int w, int h)
{
    screen_size_w = w;
    screen_size_h = h;
    feedback_fbo.allocate(w,h,GL_RGBA);
    feedback_fbo.begin();
        ofClear(255,255,255,0);
    feedback_fbo.end();
    feed_fbo.allocate(w,h,GL_RGBA);
    
    feed_fbo.begin();
    ofClear(255,255,255,0);
    feed_fbo.end();

    
    //screen_texture.allocate(w,h,GL_RGBA);
    //feedback_plane.resizeToTexture(screen_texture);
}

void Fbo_feedback::begin()
{
    if(feedback_enable)
    {
        //ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        feedback_fbo.begin();
        ofSetColor(0,0,0,255-feedback_ammount);
        ofDrawRectangle(0,0,screen_size_w, screen_size_h);
        ofSetColor(255,255,255,255);
        feed_fbo.draw(screen_size_w-feedback_pos_x*screen_size_w,
                      screen_size_h-feedback_pos_y*screen_size_h,
                      screen_size_w*feedback_scale,
                      screen_size_h*feedback_scale);
        feedback_fbo.end();
 
        feed_fbo.begin();
        ofClear(255);
      
        ofPushMatrix();
        ofSetColor(255,255,255,feedback_ammount);
        ofTranslate(0, 0);
        feedback_fbo.draw(0,0,screen_size_w,screen_size_h);
        ofPopMatrix();
    }
}

void Fbo_feedback::end()
{
    
    if(feedback_enable)
    {
        feed_fbo.end();
        feed_fbo.draw(0,0,screen_size_w,screen_size_h);
    }
}
