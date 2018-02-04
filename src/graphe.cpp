//
//  Graphe.cpp
//  oscillographe
//
//  Created by Guillaume Arseneault on 17-11-09.
//
//

#include "graphe.hpp"

void Graphe::setup(string name)
{
    std::string str = name;
    str+="_graphe";
    name=str;
    graphe_name = name;
    
    settings_gui.setup("settings");
    
    
    
    presets.setup("graphe");
    //presets.recalled_gui.add(&settings_gui);
    

presets.recalled_gui.add(graphe_active.set("active",1));
presets.recalled_gui.add(buffer_history.set("buffer_history", 512,buffer_size+1,4096));
presets.recalled_gui.add(shape_scale.set("shape_scale",0.10,0,1));
presets.recalled_gui.add(line_width.set("line_width",1, 0.1, 10));
presets.recalled_gui.add(mesh_width_z.set("mesh_width_z", .1, -2, 2));
    //settings_gui.add(line_color.set("color",ofColor(255),ofColor(0,0),ofColor(255)));
presets.recalled_gui.add(graphe_saturation.set("saturation", 255, 0, 255));
presets.recalled_gui.add(graphe_hue.set("hue", 255, 0, 255));
presets.recalled_gui.add(graphe_brightness.set("brightness", 255, 0, 255));
    
    graphe_saturation.addListener(this, &Graphe::set_saturation);
    graphe_hue.addListener(this, &Graphe::set_hue);
    graphe_brightness.addListener(this, &Graphe::set_brightness);
    
    
//    preset_gui.setup("presets");
//    preset_gui.add(preset_index.set("index",0,0,9));
//    preset_gui.add(preset_load_b.set("load",0));
//    preset_gui.add(preset_save_b.set("save",0));
//    
//    preset_load_b.addListener(this, &Graphe::preset_load);
//    preset_save_b.addListener(this, &Graphe::preset_save);
    
    gui.setup(graphe_name);

    //gui.add(&preset_gui);

    //gui.add(&settings_gui);

    gui.add(&presets.gui);
    
    

    
    // todo update de la grosseur quand...!
    set_size(ofGetWidth(), ofGetHeight());

}

//--------------------------------------------------------------

void Graphe::update(int input_buffer_size, vector <float> input_buffer_x, vector <float> input_buffer_y)
{
    if (graphe_active) {
        if (buffer_size_old != input_buffer_size)
        {
            buffer_history.setMin(input_buffer_size+1);
            buffer_size_old = input_buffer_size;
            cout<<input_buffer_size<<endl;
        }
        
        vbo_mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
        vbo_mesh.enableColors();
        int vertex_buffer = vbo_mesh.getNumVertices();
        
        for (unsigned int i = 0; i < (input_buffer_size); i++)
        {
            ofVec3f coord (input_buffer_x[i]*app_size_w/2*shape_scale*50,
                           input_buffer_y[i]*app_size_h/2*shape_scale*50,
                           buffer_history-i);
            
            if (vertex_buffer > buffer_history)
            {
                vbo_mesh.removeVertex(i);
                vbo_mesh.setVertex(buffer_history-i, coord);
            } else {
                vbo_mesh.addVertex(coord);
            }
        }
        
        for (unsigned int i =0; i< vbo_mesh.getNumVertices(); i++)
        {
            ofVec3f coord = vbo_mesh.getVertex(i);
            coord[2] = mesh_width_z*i;
            vbo_mesh.setVertex(i, coord);
            
        }
    }
}



//--------------------------------------------------------------

void Graphe::draw()
{
    if (graphe_active)
    {
        // draw the OSCILO channel:
        ofPushStyle();
        ofPushMatrix();
            ofNoFill();
            ofSetLineWidth(line_width);
            ofSetColor(line_color);
            vbo_mesh.draw();
        ofPopMatrix();
        ofPopStyle();
    }
}

//--------------------------------------------------------------

void Graphe::draw_gui()
{
    gui.draw();
}
//--------------------------------------------------------------

void Graphe::set_size(int w, int h)
{
    app_size_w = w;
    app_size_h = h;
}

//--------------------------------------------------------------

void Graphe::set_saturation(float &f)
{
    ofColor color = line_color.get();
    color.setSaturation(f);
    line_color.set(color);
}

//--------------------------------------------------------------

void Graphe::set_brightness(float &f)
{
    ofColor color = line_color.get();
    color.setBrightness(f);
    line_color.set(color);
}

//--------------------------------------------------------------

void Graphe::set_hue(float &f)
{
    ofColor color = line_color.get();
    color.setHue(f);
    line_color.set(color);
}


//--------------------------------------------------------------

//void Graphe::preset_save(bool &b)
//{
//    if(preset_save_b)
//    {
//    preset_save_b = 0;
//    std::string str = "graphe_";
//    str += ofToString(preset_index);
//    settings_gui.setName(str);
//    settings_gui.saveToFile("graphe.json");
//    settings_gui.setName( graphe_name);
//    }
//}
//
//
////--------------------------------------------------------------
//
//void Graphe::preset_load(bool &b)
//{
//    if (preset_load_b)
//    {
//    preset_load_b = 0;
//    std::string str = "graphe_";
//    str += ofToString(preset_index);
//    settings_gui.setName(str);
//    settings_gui.loadFromFile("graphe.json");
//    
//    settings_gui.setName( graphe_name);
//    }
//}


//--------------------------------------------------------------


