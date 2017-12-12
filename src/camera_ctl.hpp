//
//  camera_ctl.hpp
//  oscillographe
//
//  Created by Guillaume Arseneault on 17-12-12.
//
//

#ifndef camera_ctl_hpp
#define camera_ctl_hpp

#include "ofMain.h"
#include "ofxGui.h"

class Camera_ctl
{
    public:
    
    void setup();
    void update();
    void cam_get_param(bool &b);
    void cam_set_param(bool &b);
    
    
    ofxGuiGroup gui;
    
    ofEasyCam cam;
    
    
    ofxGuiGroup camera_preset_gui;
    ofxGuiGroup camera_settings_gui;

    
    ofParameter<glm::vec3> cam_view_position;
    
    ofParameter<string>cam_view_orientation_quat_string;
    
    

    
    ofParameter<bool> cam_set_ortho = 0;
    ofParameter<bool> cam_set_reset = 0;

    
    ofParameter<bool> cam_get_param_b = 0;
    ofParameter<bool> cam_set_param_b = 0;
    
    ofParameter<bool> set_fullscreen = 0;
    bool set_fullscreen_old =0;


};

#endif /* camera_ctl_hpp */
