//
//  recall.cpp
//  oscillographe
//
//  Created by Guillaume Arseneault on 18-02-13.
//
//

#include "recall.hpp"

//--------------------------------------------------------------
void Recall::setup()
{
    index_folder();

    gui.setup("recall");
    gui.add(next_b.set("next",0));
    gui.add(prev_b.set("prev",0));
    gui.add(reindex_b.set("reindex",0));
    gui.add(index.set("index",0,0,file_count));
    
    next_b.addListener(this, &Recall::next);
    prev_b.addListener(this, &Recall::prev);
    reindex_b.addListener(this, &Recall::reindex);
    interact.setup("next", "/gpio/2");
    gui.add(&interact.gui);

}

//--------------------------------------------------------------
void Recall::set_panel(ofxPanel _setup_panel)
{
        setup_panel=_setup_panel;
}

//--------------------------------------------------------------
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

//--------------------------------------------------------------
void Recall::index_folder()
{
    string path = "recall";
    ofDirectory dir(path);
    dir.allowExt("json");
    dir.listDir();
    json_vector = dir.getFiles();
    file_count=json_vector.size()-1;
}

//--------------------------------------------------------------
void Recall::load_from_index()
{
    setup_panel.loadFromFile(json_vector[index].getAbsolutePath());
    cout<<json_vector[index].getAbsolutePath()<<endl;
}

//--------------------------------------------------------------
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

//--------------------------------------------------------------
void Recall::prev(bool &b)
{
    if(b)
    {
        index--;
        if(index<0){index=file_count;}
        load_from_index();
        prev_b=0;
    }
    
}

//--------------------------------------------------------------
void Recall::reindex(bool &b)
{
    if(b)
    {
        index_folder();
        index.setMax(file_count);
        reindex_b =0;
    }
    
}

//--------------------------------------------------------------
