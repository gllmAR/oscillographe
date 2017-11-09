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

class Graphe
{
public:
    ofxGuiGroup gui;
    
    ofParameter<ofColor> line_color;
    ofParameter<float> shapeScale =.5;
    ofParameter<float> line_width = 1;
    ofParameter<int> buffer_history = 1024;
    ofParameter<int> buffer_size = 256;
    ofParameter<float> mesh_width_z = 1;
    
    ofVboMesh vbo_mesh;
    
    void setup();
    void update(int input_buffer_size, vector <float> input_buffer_x, vector <float> input_buffer_y);
    void draw();
    void set_size(int w, int h);
    
    int app_size_w = 100000;
     int app_size_h = 100000;
    
};

#endif /* graphe_hpp */
