//
//  recall.cpp
//  oscillographe
//
//  Created by Guillaume Arseneault on 18-02-13.
//
//

#include "recall.hpp"

void Recall::setup(ofxPanel _setup_panel)
{
    
    string path = "recall";
    ofDirectory dir(path);
    dir.allowExt("json");
    dir.listDir();
    json_vector = dir.getFiles();

    
    file_count=json_vector.size()-1;
    gui.setup("recall");
    gui.add(next_b.set("next",0));
    gui.add(index.set("index",0,0,file_count));
    
    setup_panel =_setup_panel;
    
    
    next_b.addListener(this, &Recall::next);
    interact.setup("next", "/gpio/2");
    gui.add(&interact.gui);
    
    
    
    
    
}
//------------------------------------------------
void Recall::update()
{
    interact.update();
    if(interact.return_flag)
    {
        bool b = 1;
        next(b);
        interact.return_flag=0;
    }

}

//------------------------------------------------
void Recall::load_from_index()
{
    setup_panel.loadFromFile(json_vector[index].getAbsolutePath());
    cout<<json_vector[index].getAbsolutePath()<<endl;
}
//------------------------------------------------

void Recall::next(bool &b)
{
    if(b)
    {
    index++;
    if(index>file_count){index=0;}
    load_from_index();
    next_b=0;
    }
}

//------------------------------------------------

void Recall::prev()
{
    
    
}
//------------------------------------------------



