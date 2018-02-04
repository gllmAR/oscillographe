//
//  Oscillo.hpp
//  oscillographe
//
//  Created by Guillaume Arseneault on 17-11-09.
//
//

#ifndef graphe_hpp
#define graphe_hpp

#include "ofMain.h"
#include "ofxGui.h"
#include "presets.hpp"



class Graphe

{
public:
    string graphe_name;
    ofxGuiGroup gui; //--
    ofxGuiGroup settings_gui;
    
    void draw_gui();
    int gui_x_offset=0;
    int gui_y_offset=0;
    
    ofParameter<bool> graphe_active = 1;
    ofParameter<ofColor> line_color;
    ofParameter<float> shape_scale =.5;
    ofParameter<float> line_width = 1;
    ofParameter<int> buffer_history = 1024;
    ofParameter<int> buffer_size = 256;
    int buffer_size_old = 0;
    ofParameter<float> mesh_width_z = 1;
    ofParameter<float> graphe_saturation =0;
    ofParameter<float> graphe_hue =0;
    ofParameter<float> graphe_brightness =0;
    
    ofVboMesh vbo_mesh;
    
    void setup(string name);

    void update(int input_buffer_size, vector <float> input_buffer_x, vector <float> input_buffer_y);
    void draw();
    void set_size(int w, int h);
    
    void set_hue(float &f);
    void set_saturation(float &f);
    void set_brightness(float &f);
    
    
    int app_size_w = 100000;
    int app_size_h = 100000;
    
    
    // preset
    Presets presets;
//
//    ofParameter <int> preset_index;
//    ofParameter <string> preset_comment;
//    ofxGuiGroup preset_gui;
//    
//    ofParameter<bool> preset_load_b;
//    ofParameter<bool> preset_save_b;
//
//    void preset_save(bool &b);
//    void preset_load(bool &b);
//    
};

#endif /* graphe_hpp */
