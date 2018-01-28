//
//  audio_sampler.cpp
//  oscillographe
//
//  Created by Guillaume Arseneault on 18-01-28.
//
//

#include "audio_sampler.hpp"


void Audio_sampler::setup(int _file_index, int _buffer_size, int _gui_offset, string _name)
{
    
// setup player
    buffer_size=_buffer_size;
    player_load_file_index(_file_index);
    
// setup selection preset?
    
// setup recorder
    recorder_buffer.setNumChannels(2);
    setup_gui(_gui_offset, _name);
}


void Audio_sampler::setup_gui(int _gui_offset, string _name)
{

    //player

    player_gui.setup();
    player_gui.setName("player");
    
    player_gui.add(player_enable.set("enable", 0));
    player_gui.add(player_volume.set("volume",1,0,2));
    player_gui.add(player_pan.set("pan",0,-1,1));
    player_gui.add(player_file_index.set("file_index",0,0,9));
    
    // mettre un label pour le filename?
    
    // recorder
    
    recorder_gui.setup();
    recorder_gui.setName("recorder");
    recorder_gui.add(recorder_enable.set("enable",0));
    
    
    // recaller
    // [...]
    
    // settings panel
    settings_panel.setup(_name, "sampler_A_settings.xml", _gui_offset,10);
    settings_panel.add(&player_gui);
    settings_panel.add(&recorder_gui);
    
    
    
    // recalled
    recalled_panel.setup("temporaire", "sampler_A_recalled.xml", _gui_offset,310);
    recalled_panel.add(player_speed.set("speed",1,-2,2));
    recalled_panel.add(player_position.set("position",0,0,1));
    recalled_panel.add(player_loop_selection.set("player_loop_selection",1));
    recalled_panel.add(player_loop_in.set("player_loop_in",0,0,1));
    recalled_panel.add(player_loop_out.set("player_loop_out",1,0,1));



    

    
    
 
    
    
    
    
    //
    player_enable.addListener(this, &Audio_sampler::player_enable_change);
    player_speed.addListener(this, &Audio_sampler::player_speed_change);
    player_volume.addListener(this, &Audio_sampler::player_volume_change);
    player_pan.addListener(this, &Audio_sampler::player_pan_change);
    player_position.addListener(this, &Audio_sampler::player_position_change);
    player_file_index.addListener(this, &Audio_sampler::player_file_index_change);
    player_loop_selection.addListener(this, &Audio_sampler::player_loop_selection_changed);
    player_loop_in.addListener(this, &Audio_sampler::player_loop_in_changed);
    player_loop_out.addListener(this, &Audio_sampler::player_loop_out_changed);
    
    recorder_enable.addListener(this, &Audio_sampler::recorder_enable_changed);
}

//--------------------------------------------------------------


void Audio_sampler::player_load_file_index(int _file_index)
{
    player_file_index = _file_index;
    if (player_file_index_old != player_file_index)
    {
        player_buffer.allocate(buffer_size, 2);
        std::ostringstream path;
        path << "sounds/audio_" << _file_index << ".wav";
        player.load(path.str());
        player.setLoop(1);
        player_buffer_1_wo.assign(buffer_size, 0.0);
        player_buffer_2_wo.assign(buffer_size, 0.0);
        
        
        bool _player_enable = player_enable;
        player_enable_change(_player_enable);
        player_file_index_old = player_file_index;
    }
}

//--------------------------------------------------------------

void Audio_sampler::audio_process(ofSoundBuffer& output)
{
    player.audioOut(output);
    player_buffer = output;
    
    
    for (int i = 0; i < output.getNumFrames(); i++)
    {
        if(player_enable) // traiter le player si actif
        {
            
            player_buffer_1_wo[i] = player_buffer[i*2  ];
            player_buffer_2_wo[i] = player_buffer[i*2+1];
        } else {
            player_buffer_1_wo[i] = 0;
            player_buffer_2_wo[i] = 0;
        }
    }
}


//--------------------------------------------------------------

void Audio_sampler::player_enable_change(bool &player_enable)
{
    if(player_enable)
    {
        player.play();
        
    } else {
        player.stop();
        
    }
}

//--------------------------------------------------------------


void Audio_sampler::player_set_speed(float f)
{   //est appele par la classe interact dans ofApp
    player.setSpeed(f);
}

//--------------------------------------------------------------


void Audio_sampler::player_speed_change(float &f)
{   //est appele par le gui/preset de audio_io
    player.setSpeed(f);
}

//--------------------------------------------------------------


void Audio_sampler::player_pan_change(float &f)
{   //est appele par le gui/preset de audio_io
    player.setPan(f);
}

//--------------------------------------------------------------


void Audio_sampler::player_volume_change(float &f)
{   //est appele par le gui/preset de audio_io
    player.setVolume(f);
}

//--------------------------------------------------------------


void Audio_sampler::player_position_change(float &f)
{   //est appele par le gui/preset de audio_io
    player.setPosition(f);
}

//--------------------------------------------------------------

void Audio_sampler::player_file_index_change(int &i)
{   //est appele par le gui/preset de audio_io
    player_load_file_index(i);
}

//--------------------------------------------------------------

void Audio_sampler::player_loop_selection_changed(bool &b)
{   // fonction sur mesure
    player.set_loop_selection(b);
}

//--------------------------------------------------------------

void Audio_sampler::player_loop_in_changed(float &f)
{   // fonction sur mesure
    if (f>player_loop_out)
    {
        f = player_loop_in = player_loop_out;
    }
    player.set_loop_in(f);
}

//--------------------------------------------------------------

void Audio_sampler::player_loop_out_changed(float &f)
{   // fonction sur mesure
    if (f<player_loop_in)
    {
        f = player_loop_out = player_loop_in;
    }
    player.set_loop_out(f);
}

string Audio_sampler::player_get_filename()
{
    std::ostringstream filename;
    filename <<"sounds/"<<"audio_" << player_file_index;
    return filename.str();
}

//--------------------------------------------------------------

void Audio_sampler::recorder_enable_changed(bool &b)
{
    if (!recorder_enable)
    {
        recorder_sound_file.save("loop1.wav", recorder_buffer);
    }
}

//--------------------------------------------------------------

void Audio_sampler::recaller_preset_save(bool &b)
{
    std::string str = "loop_";
    str += ofToString(sampler_preset_index);
    sampler_preset_panel.setName(str);
    std::ostringstream preset_path;
    preset_path<<player_get_filename()<<".xml";
    
    sampler_preset_panel.saveToFile(preset_path.str());
    sampler_preset_save_b =0;
    sampler_preset_panel.setName("sampler");
}


//--------------------------------------------------------------

void Audio_sampler::recaller_preset_load(bool &b)
{
    
    std::string str = "loop_";
    str += ofToString(sampler_preset_index);
    sampler_preset_panel.setName(str);
    
    
    std::ostringstream preset_path;
    preset_path<<player_get_filename()<<".xml";
    
    
    sampler_preset_panel.loadFromFile(preset_path.str());
    sampler_preset_load_b =0;
    
    sampler_preset_panel.setName("sampler");
}

