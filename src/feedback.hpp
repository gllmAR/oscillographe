//
//  feedback.hpp
//  oscillographe
//
//  Created by Guillaume Arseneault on 17-12-26.
//  contient les classes lié au feedback vidéo
//

#ifndef feedback_hpp
#define feedback_hpp

#include "ofMain.h"
#include "ofxGui.h"

class Screen_feedback
{
public:
    ofTexture screen_texture;
    ofPlanePrimitive feedback_plane;
    ofxGuiGroup feedback_gui;
    ofParameter<bool> feedback_enable=0;
    ofParameter<float> feedback_ammount = 0 ;
    ofParameter<float> feedback_pos_x = 0;
    ofParameter<float> feedback_pos_y = 0;
    ofParameter<float> feedback_scale = 0;

    void setup();
    void allocate(int w, int h);
    void begin();
    void end();
    
    int screen_size_w =0;
    int screen_size_h=0;
    
    
};

class Fbo_feedback
{
public:
    ofFbo feedback_fbo;
    ofFbo feed_fbo;
    ofPlanePrimitive feedback_plane;
    ofxGuiGroup feedback_gui;
    
    ofParameter<bool> feedback_enable=0;
    ofParameter<float> feedback_ammount = 0 ;
    ofParameter<float> feedback_pos_x = 0;
    ofParameter<float> feedback_pos_y = 0;
    ofParameter<float> feedback_scale = 0;
    
    void setup();
    void allocate(int w, int h);
    void begin();
    void end();
    
    int screen_size_w =0;
    int screen_size_h=0;
    
    
};



#endif /* feedback_hpp */



