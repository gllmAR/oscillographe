//
//  camera_ctl.cpp
//  oscillographe
//
//  Created by Guillaume Arseneault on 17-12-12.
//
//

#include "camera_ctl.hpp"

void Camera_ctl::setup()
{
    // camera
    camera_preset_gui.setup("camera");
    camera_preset_gui.add(cam_set_ortho.set("cam_set_ortho", 1));
    //camera_preset_gui.add(cam_set_distance.set("cam_set_distance", 0, 0, 1000));
    camera_preset_gui.add(cam_view_position.set("position",
                                                glm::vec3(0),
                                                glm::vec3(-1000),
                                                glm::vec3(1000)));
    camera_preset_gui.add(cam_view_orientation_quat_string.set("orientation"," "));
    
    
    
    camera_settings_gui.setup("camera");
    //camera_settings_gui.add(fps_label.setup("FPS"," "));
    camera_settings_gui.add(cam_set_reset.set("cam_set_reset", 1));
    camera_settings_gui.add(set_fullscreen.set("fullscreen", 0));
    camera_settings_gui.add(cam_get_param_b.set("cam_get_param",0));
    camera_settings_gui.add(cam_set_param_b.set("cam_set_param",0));
    
    
    cam_get_param_b.addListener(this, &Camera_ctl::cam_get_param);
    cam_set_param_b.addListener(this, &Camera_ctl::cam_set_param);
    
}
//--------------------------------------------------------------

void Camera_ctl::update()
{
    if (set_fullscreen_old != set_fullscreen)
    {
        ofSetFullscreen(set_fullscreen);
        set_fullscreen_old = set_fullscreen;
    };
    
    if (cam_set_ortho){cam.enableOrtho();}else{cam.disableOrtho();};
    if (cam_set_reset){cam.reset(); cam_set_reset=0;};
    
}
//--------------------------------------------------------------

void Camera_ctl::cam_get_param(bool &b)
{
    cam_view_position=cam.getPosition();
    glm::quat cam_view_orientation_quat=cam.getOrientationQuat();
    //workaround pour sauvegarder un quat en string dans un ofParameter
    cam_view_orientation_quat_string =ofToString(cam_view_orientation_quat);
    cam_get_param_b = 0;
}
//--------------------------------------------------------------

void Camera_ctl::cam_set_param(bool &b)
{
    // workaround pour restaurer un quat a partir d une string
    glm::quat temp_orientation;
    vector <string> orientation_quat_vec = ofSplitString(cam_view_orientation_quat_string, " ");
    // comprendre pourquoi l'index est offset de 1 ici...?
    temp_orientation[0]=ofToFloat(orientation_quat_vec[1]);
    temp_orientation[1]=ofToFloat(orientation_quat_vec[2]);
    temp_orientation[2]=ofToFloat(orientation_quat_vec[3]);
    temp_orientation[3]=ofToFloat(orientation_quat_vec[0]);
   // cout<<ofToString(temp_orientation)<<endl;
    cam.setOrientation(temp_orientation);
    cam.setPosition(cam_view_position);
    cam_set_param_b = 0;
}
