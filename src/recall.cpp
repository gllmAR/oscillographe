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
    gui.add(draw_recall_b.set("console",0));
    
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
void Recall::draw()
{
    if(draw_recall_b)
    {
        ofEnableBlendMode( OF_BLENDMODE_ADD );
      
        ofDrawBitmapStringHighlight( json_name_now, glm::vec2(20,size_y-120) );
       	ofDrawBitmapStringHighlight( json_string_now, glm::vec2(20,size_y-100) );
        ofDrawBitmapStringHighlight( json_name_next, glm::vec2(20,size_y-105) );
        ofDrawBitmapStringHighlight( json_string_next, glm::vec2(370,size_y-100) );

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
    get_json_to_strings();
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
void Recall::toggle_draw_recall()
{
    draw_recall_b=!draw_recall_b;
}
//--------------------------------------------------------------
void Recall::get_json_to_strings()
{
    json_buffer = ofBufferFromFile(json_vector[index].getAbsolutePath());
    json_name_now = json_vector[index].getFileName();
    json_string_now = json_buffer.getText();
    remove_chars_from_string( json_string_now, "{}");
    remove_chars_from_string( json_string_now, "\t");
    remove_chars_from_string( json_string_now, "\"");
    int temp_index = index+1;
    //kind of a modulo
    if (temp_index >file_count){temp_index=0;}
    json_name_next = json_vector[temp_index].getFileName();
    json_buffer = ofBufferFromFile(json_vector[temp_index].getAbsolutePath());
    json_string_next = json_buffer.getText();
    remove_chars_from_string( json_string_next, "{}");
    remove_chars_from_string( json_string_next, "\t");
    remove_chars_from_string( json_string_next, "\"");
    
}

    
//--------------------------------------------------------------
void Recall::remove_chars_from_string( string &str, char* charsToRemove ) {
    for ( unsigned int i = 0; i < strlen(charsToRemove); ++i ) {
        str.erase( remove(str.begin(), str.end(), charsToRemove[i]), str.end() );
    }
}
//--------------------------------------------------------------

void Recall::set_size(int x, int y)
{
    size_y = y;
}
