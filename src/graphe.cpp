//
//  Graphe.cpp
//  Graphegraphe
//
//  Created by Guillaume Arseneault on 17-11-09.
//
//

#include "graphe.hpp"

void Graphe::setup()
{
    gui.setup();
    gui.setName("graphe");
    gui.add(graphe_active.set("active",1));
    gui.add(buffer_history.set("buffer_history", 512,buffer_size+1,4096));
    gui.add(shapeScale.set("shapeScale",0.10,0,1));
    gui.add(line_width.set("line_width",1, 0.1,1000));
    gui.add(mesh_width_z.set("mesh_width_z", 1, -2, 2));
    gui.add(line_color.set("color",ofColor(255),ofColor(0,0),ofColor(255)));
    gui.add(graphe_saturation.set("saturation", 255, 0, 255));
    gui.add(graphe_hue.set("hue", 255, 0, 255));
    gui.add(graphe_brightness.set("brightness", 255, 0, 255));
    graphe_saturation.addListener(this, &Graphe::set_saturation);
    graphe_hue.addListener(this, &Graphe::set_hue);
    graphe_brightness.addListener(this, &Graphe::set_brightness);
}

void Graphe::update(int input_buffer_size, vector <float> input_buffer_x, vector <float> input_buffer_y)
{
    if (graphe_active) {
    // ici, application devrait passer soundSettingGui.buffer_size vers une classe pour dessiner Graphe
    
    
    // timestamp=ofGetElapsedTimeMillis();
    
    vbo_mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    vbo_mesh.enableColors();
    
    
    int vertex_buffer = vbo_mesh.getNumVertices();
    
    for (unsigned int i = 0; i < (input_buffer_size); i++)
    {
        ofVec3f coord (input_buffer_x[i]*app_size_w/2*shapeScale*50,
                       input_buffer_y[i]*app_size_h/2*shapeScale*50,
                       buffer_history-i);
        
        if (vertex_buffer > buffer_history)
        {
            vbo_mesh.removeVertex(i);
            vbo_mesh.setVertex(buffer_history-i, coord);
        } else {
            vbo_mesh.addVertex(coord);
        }
    }
    
    //au lieu de faire une lecture et une ecriture, mieux vaudrait utiliser un pointeur pour changer la derniere donnee
    //
    
    //        for (unsigned int i =0; i< vertex_buffer; i++)
    
    for (unsigned int i =0; i< vbo_mesh.getNumVertices(); i++)
    {
        ofVec3f coord = vbo_mesh.getVertex(i);
        coord[2] = mesh_width_z*i;
        vbo_mesh.setVertex(i, coord);
        
    }
        if (buffer_size_old != input_buffer_size)
        {
//            buffer_history.setMin(input_buffer_size+1);
//            buffer_size_old = input_buffer_size;
//            cout<<input_buffer_size<<endl;
        }
    }
}

void Graphe::draw()
{
    if (graphe_active)
    {
    ofNoFill();
    
    // draw the OSCILO channel:
    ofPushStyle();
    ofPushMatrix();
    
    
    
    ofSetLineWidth(line_width);
    ofSetColor(line_color);
    
    vbo_mesh.draw();
    
    ofPopMatrix();
    ofPopStyle();
    }
}

void Graphe::set_size(int w, int h)
{
    app_size_w = w;
    app_size_h = h;
    
}

void Graphe::set_saturation(float &f)
{
    ofColor color = line_color.get();
    color.setSaturation(f);
    line_color.set(color);
}
void Graphe::set_brightness(float &f)
{
    ofColor color = line_color.get();
    color.setBrightness(f);
    line_color.set(color);
}

void Graphe::set_hue(float &f)
{
    ofColor color = line_color.get();
    color.setHue(f);
    line_color.set(color);
}
