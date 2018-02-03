//
//  presets.hpp
//  oscillographe
//
//  Created by Guillaume Arseneault on 18-02-03.
//
//
//------------------------------------------------

// pour être utile, doit être setup(), puis,
// le guigroup que l'on veut preset,
// ajouter depuis la classe meta du genre
// presets.setup();
// presets.recalled_gui.add(&guiGroupAPreset)


#ifndef presets_hpp
#define presets_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxGui.h"

class Presets

{
public:
    // preset
    string name;
    string recaller_name;
    string recalled_name;
    ofParameter <int> index;
    ofParameter <string> comment;
    ofxGuiGroup gui;
    
    ofxGuiGroup recaller_gui;
    ofxGuiGroup recalled_gui;
    
    ofParameter<bool> load_b;
    ofParameter<bool> save_b;
    
    void setup(string _name);
    void save(bool &b);
    void load(bool &b);
    
};



#endif /* presets_hpp */
