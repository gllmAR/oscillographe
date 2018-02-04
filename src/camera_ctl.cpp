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
    

    

    
    // camera preset
    
    camera_preset_gui.setup("camera");
    camera_preset_gui.add(cam_set_ortho.set("cam_set_ortho", 1));
    camera_preset_gui.add(cam_view_position.set("position",
                                                glm::vec3(0),
                                                glm::vec3(-1000),
                                                glm::vec3(1000)));

    
    camera_preset_gui.add(cam_view_orientation.set("orientation",
                                                       glm::vec4(0),
                                                       glm::vec4(-1),
                                                       glm::vec4(1)));

    presets.setup("camera-setup");
    presets.recalled_gui.add(&camera_preset_gui);
    
    
    // camera settings
    camera_settings_gui.setup("render");
    camera_settings_gui.add(cam_set_reset.set("cam_set_reset", 1));
    camera_settings_gui.add(set_fullscreen.set("fullscreen", 0));
    camera_settings_gui.add(&presets.gui);
    
    

    
    // methode "creative" pour attacher un listener à une fonction dans une sous-classe
    cam_get_param_b.addListener(this, &Camera_ctl::cam_get_param);
    cam_set_param_b.addListener(this, &Camera_ctl::cam_set_param);
    
    presets.save_b.addListener(this, &Camera_ctl::cam_get_param);
    presets.load_b.addListener(this, &Camera_ctl::cam_set_param);
    
    
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

    cout<<"[DEBUG] cam_get_param"<<endl;
    //conversion manuelle quat->vec4 car pas de ofParameter<quat>
    //(offset de 1  (xyzw au lieu de wxyz) car sinon discrépence )
    cam_view_position=cam.getPosition();
    glm::quat temp_quat=cam.getOrientationQuat();
    glm::vec4 temp_vec4( temp_quat.x,
                         temp_quat.y,
                         temp_quat.z,
                         temp_quat.w );
    

    cam_view_orientation=temp_vec4;
    // pour redéclencher la sauvegarde de preset
    b=!b; //envoyer 1
    presets.save(b);

}
//--------------------------------------------------------------

void Camera_ctl::cam_set_param(bool &b)
{
    presets.load(b);
        cout<<"[DEBUG] cam_set_param"<<endl;
    //conversion manuelle vec4->quat car pas de ofParameter<quat>
    glm::vec4 temp_vec4=cam_view_orientation;
    
    glm::quat temp_quat(temp_vec4.w,temp_vec4.x,temp_vec4.y,temp_vec4.z);
    cam.setOrientation(temp_quat);
    cam.setPosition(cam_view_position);
    
}
