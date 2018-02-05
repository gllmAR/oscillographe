//
//  presets.cpp
//  oscillographe
//
//  Created by Guillaume Arseneault on 18-02-03.
//
//
//------------------------------------------------


#include "presets.hpp"

void Presets::setup(string _name)
{
    //
    name = _name;
    recaller_name = "rec";
    //recaller_name += _name;
    recalled_name = "set";
    //recalled_name += _name;
    recaller_gui.setup(recaller_name);
    recalled_gui.setup(recalled_name);
  

    
    recaller_gui.add(index.set("index",0,0,9));
    recaller_gui.add(load_b.set("load",0));
    recaller_gui.add(save_b.set("save",0));
    
    gui.setup(_name);
 
    gui.add(&recaller_gui);
    gui.add(&recalled_gui);
 
    
    load_b.addListener(this, &Presets::load);
    save_b.addListener(this, &Presets::save);
    recaller_gui.minimizeAll();
    recaller_gui.minimizeAll();
    gui.minimizeAll();
}
//------------------------------------------------

void Presets::save(bool &b)
{
        if(save_b)
    {
        cout<<"[DEBUG] preset-save_param"<<endl;

        save_b = 0;
        std::string str = name;
        str += "_";
        str += ofToString(index);
        recalled_gui.setName(str);
        std::string str2 = name;
        str2 +=".json";
        recalled_gui.saveToFile(str2);
        recalled_gui.setName(recalled_name);
    }
}
//------------------------------------------------

void Presets::load(bool &b)
{

    if(load_b)
    {
    cout<<"[DEBUG] preset-load_param"<<endl;
        load_b = 0;
        std::string str = name;
        str += "_";
        str += ofToString(index);
        recalled_gui.setName(str);
        std::string str2 = name;
        str2 +=".json";
        recalled_gui.loadFromFile(str2);
        recalled_gui.setName(recalled_name);
    }
}
