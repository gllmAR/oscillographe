//
//  recall.hpp
//  oscillographe
//
//  Created by Guillaume Arseneault on 18-02-13.
//  recall json sequence
//

/*
 doit avoir une fonction pour charger un json vers des ofparam
 */

#ifndef recall_hpp
#define recall_hpp

#include "ofMain.h"
#include "ofxGui.h"
#include "interact.hpp"


class Recall

{
public:
    void setup();
    void set_panel(ofxPanel _setup_panel);
    void next(bool &b);
    void prev(bool &b);
    void reindex(bool &b);
    void index_folder();
    void update();
    
    
    ofxGuiGroup gui;
    ofxPanel setup_panel;
    
    ofParameter<bool> next_b;
    ofParameter<bool> prev_b;
    ofParameter<bool> reindex_b;
    ofParameter<int> index;
    
    int file_count;
    
    vector<ofFile> json_vector;
    
    
    Interact_tic interact;
    
    void load_from_index();
    //void next_listener();
    
};


#endif /* recall_hpp */
