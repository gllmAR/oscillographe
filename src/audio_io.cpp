//
//  audio_in.cpp
//  oscillograph
//
//  Created by Guillaume Arseneault on 17-08-07.
//
//  gestion de l audio (input et output )
// ainsi que lecture sonore d echantillon

#include "audio_io.hpp"

void Audio_io::setup()
{
    setup_gui();
    setup_audio();
    setup_player(0);
    setup_gui_listener();
}

void Audio_io::reset_audio(bool &b)
{
    if(reset_audio_b)
    {
        exit();
        setup_audio();
        int _io_select = io_select;
        io_select_change(_io_select);
        
        bool _io_enable = io_enable;
        io_enable_change(_io_enable);
        
        int _input_select = input_select;
        io_select_change(_io_select);
        
        bool _input_enable = input_enable;
        input_enable_change(_input_enable);
        
        int _output_select = output_select;
        io_select_change(_io_select);
        
        bool _output_enable = output_enable;
        output_enable_change(_output_enable);
        
        
        reset_audio_b=0;
    }
}


void Audio_io::setup_gui()
{
    gui.setup();
    gui.setName("audio_io");
    gui_device.setup("");
    gui_device.setName("device");
    // a mettre dans un gui group
    gui_device.add(reset_audio_b.set("reset_audio",0));
    gui_device.add(buffer_size.set("buffer_size",512,64,4096));
    gui_device.add(sample_rate.set("sample_rate",44100,8000,192000));
    gui_device.add(master_vol.set("master_vol",1,0,2));
    
    // io
    gui_device_io.setup();
    gui_device_io.setName("set_io");
    gui_device_io.add(io_enable.set("io_enable", 0));
    gui_device_io.add(io_select.set("select",0,0,1));
    gui_device_io.add(io_label.setup("", ""));
    gui_device_io.add(io_input_enable.set("in_enable", 0));
    gui_device_io.add(io_output_enable.set("out_enable", 0));
    
    gui_device_input.setup();
    gui_device_input.setName("set_input");
    gui_device_input.add(input_enable.set("enable", 0));
    gui_device_input.add(input_select.set("select",0,0,1));
    gui_device_input.add(input_label.setup("", ""));
    
    gui_device_output.setup();
    gui_device_output.setName("set_output");
    gui_device_output.add(output_enable.set("enable", 0));
    gui_device_output.add(output_select.set("select",0,0,1));
    gui_device_output.add(output_label.setup("", ""));
    
    
    // input
    gui_input.setup();
    gui_input.setName("input");
    gui_input.add(input_mute.set("mute", 0));
    gui_input.add(input_trim.set("trim", 1, 0, 100));
    gui_input.add(input_volume.set("volume",1,0,2));
    gui_input.add(input_pan.set("pan",0,-1,1));
    
    //player
    gui_player.setup();
    gui_player.setName("player");
    
    gui_player.add(player_enable.set("enable", 0));
    gui_player.add(player_volume.set("volume",1,0,2));
    gui_player.add(player_pan.set("pan",0,-1,1));
    gui_player.add(player_file_index.set("file_index",0,0,9));
    gui_player.add(player_speed.set("speed",1,-2,2));
    gui_player.add(player_position.set("position",0,0,1));
    
    //output
    gui_output.setup();
    gui_output.setName("output");
    gui_output.add(output_mute.set("mute", 0));
    gui_output.add(output_volume.set("volume",1,0,2));
    gui_output.add(output_pan.set("pan",0,-1,1));
    
    
    
    
    gui_device.add(&gui_device_io);
    gui_device.add(&gui_device_input);
    gui_device.add(&gui_device_output);
    gui.add(&gui_device);
    gui.add(&gui_input);
    gui.add(&gui_player);
    gui.add(&gui_output);
}

void Audio_io::setup_audio()
{
    
    auto io_devices = input_stream.getDeviceList();
    io_select.setMax(io_devices.size());
    
    auto input_devices = input_stream.getDeviceList();
    
    //input_stream.printDeviceList();
    input_select.setMax(input_devices.size());
    input_buffer_1.assign(buffer_size, 0.0);
    input_buffer_2.assign(buffer_size, 0.0);
    
    
    auto output_devices = output_stream.getDeviceList();
    
    output_stream.printDeviceList();
    output_select.setMax(output_devices.size());
    output_buffer_1.assign(buffer_size, 0.0);
    output_buffer_2.assign(buffer_size, 0.0);
    
    
    
}

void Audio_io::setup_player(int file_index)
{
    if (player_file_index_old != player_file_index)
    {
        player_buffer.allocate(buffer_size, 2);
        std::ostringstream path;
        path << "sounds/audio_" << file_index << ".wav";
        player.load(path.str());
        player.setLoop(1);
        player_buffer_1_wo.assign(buffer_size, 0.0);
        player_buffer_2_wo.assign(buffer_size, 0.0);
        
        /* workaround (double asservissement des lecteurs audio si audiobuffer non patché )
         // https://github.com/openframeworks/openFrameworks/pull/5815/files -> fix
         // https://github.com/roymacdonald/ofxSoundObjects/issues/21 -> report
         
         player_buffer_1.allocate(buffer_size, 2);
         player_buffer_2.allocate(buffer_size, 2);
         
         
         
         std::ostringstream path_1;
         std::ostringstream path_2;
         path_1 << "sounds/" << file_index << "_1.wav";
         path_2 << "sounds/" << file_index << "_2.wav";
         
         cout<<"loading sounds --> " <<path_1.str()<<" "<<path_2.str()<<endl;
         
         player_1.load(path_1.str());
         player_2.load(path_2.str());
         
         player_1.setLoop(1);
         player_2.setLoop(1);
         player_1.setPan(-1);
         player_2.setPan(1);
         */
        bool _player_enable = player_enable;
        player_enable_change(_player_enable);
        player_file_index_old = player_file_index;
    }
}


void Audio_io::setup_gui_listener()
{
    master_vol.addListener(this, &Audio_io::set_master_vol_change);
    
    reset_audio_b.addListener(this, &Audio_io::reset_audio);
    io_select.addListener(this, &Audio_io::io_select_change);
    io_enable.addListener(this, &Audio_io::io_enable_change);
    
    
    input_select.addListener(this, &Audio_io::input_select_change);
    input_enable.addListener(this, &Audio_io::input_enable_change);
    
    output_select.addListener(this, &Audio_io::output_select_change);
    output_enable.addListener(this, &Audio_io::output_enable_change);
    output_volume.addListener(this, &Audio_io::set_output_vol_change);
    
    player_enable.addListener(this, &Audio_io::player_enable_change);
    player_speed.addListener(this, &Audio_io::player_speed_change);
    player_volume.addListener(this, &Audio_io::player_volume_change);
    player_pan.addListener(this, &Audio_io::player_pan_change);
    player_position.addListener(this, &Audio_io::player_position_change);
    player_file_index.addListener(this, &Audio_io::player_file_index_change);
}

void Audio_io::exit()
{
    
    input_buffer_1.assign(buffer_size, 0.0);
    input_buffer_2.assign(buffer_size, 0.0);
    
    if(input_enable)
    {
        input_stream.stop();
        input_stream.close();
    }
    if(output_enable)
    {
        output_stream.stop();
        output_stream.close();
    }
    if(io_enable)
    {
        io_stream.stop();
        io_stream.close();
    }
}

void Audio_io::audioIn(ofSoundBuffer & input)
{
    if(input_enable || io_input_enable)
    {
        // process pan
        float pan_1 = 1-(input_pan*0.5 +0.5);
        float pan_2 = input_pan*0.5 +0.5;
        input_buffer = input;
        
        if(input_mute)
        {
            input_buffer_1.assign(buffer_size, 0.0);
            input_buffer_2.assign(buffer_size, 0.0);
        }else{
            for (int i = 0; i < input.getNumFrames(); i++)
            {
                input_buffer_1[i] = ofClamp(input_buffer[i*2  ] * input_volume * pan_1 *input_trim, -1, 1) ;
                input_buffer_2[i] = ofClamp(input_buffer[i*2+1] * input_volume * pan_2 *input_trim, -1, 1);
            } // pourquoi 20? test avec du signal et ca sort comme ca
        }
    }
    
    
}

void Audio_io::audioOut(ofSoundBuffer& output)
{
    
    if (output_enable || io_output_enable)
    {
        // process pan
        float pan_1 = 1-(output_pan*0.5 +0.5);
        float pan_2 = output_pan*0.5 +0.5;

        player.audioOut(output);
        player_buffer = output;
        
        //player_buffer = player.getCurrentBuffer();
        
        for (int i = 0; i < output.getNumFrames(); i++)
        {
            // traiter le player si actif
            
            if(player_enable)
            {
                
                player_buffer_1_wo[i] = player_buffer[i*2  ];
                player_buffer_2_wo[i] = player_buffer[i*2+1];
            } else {
                player_buffer_1_wo[i] = 0;
                player_buffer_2_wo[i] = 0;
            }
            //            float ch1 = ofClamp((input_buffer_1[i] +  player_buffer_1[i*2  ]) * output_volume * pan_1*2*!output_mute, -1, 1);
            //            float ch2 = ofClamp((input_buffer_2[i] +  player_buffer_2[i*2+1]) * output_volume  * pan_2*2*!output_mute, -1, 1);
            float ch1 = ofClamp((input_buffer_1[i] +  player_buffer[i*2  ]) * output_vol_ammount * pan_1*2*!output_mute, -1, 1);
            float ch2 = ofClamp((input_buffer_2[i] +  player_buffer[i*2+1]) * output_vol_ammount  * pan_2*2*!output_mute, -1, 1);
            output_buffer_1[i] = ch1;
            output_buffer_2[i] = ch2;
            output[i*2  ] = ch1 * master_vol_ammount;
            output[i*2+1] = ch2 * master_vol_ammount;
            //traiter l'output
            //output_buffer_1[i] = output[i*2  ] =(input_buffer_1[i] +  player_buffer_1[i*2  ]) * output_volume * pan_1*2*!output_mute;
            
            //output_buffer_2[i] = output[i*2+1] =
            //(input_buffer_2[i] +  player_buffer_2[i*2+1]) * output_volume  * pan_2*2*!output_mute;
        }
    }
}





void Audio_io::io_init(int i)
{
    io_stream.stop();
    io_stream.close();
    auto devices = input_stream.getDeviceList();
    io_select.setMax(devices.size());
    if (!devices[i].inputChannels || !devices[i].outputChannels)
    {
        cout<<"error, no i/o on device"<<endl;
        io_label = "[X] " + devices[i].name;
    } else {
        io_label = devices[i].name;
        io_settings.setInListener(this);
        io_settings.setOutListener(this);
        io_settings.setInDevice(devices[i]);
        io_settings.sampleRate = sample_rate;
        io_settings.numInputChannels = 2;
        io_settings.numOutputChannels = 2;
        io_settings.bufferSize = buffer_size;
        io_stream.setup(io_settings);
        if(io_enable)
        {
            io_stream.start();
        } else {
            io_stream.stop();
        }
        
    }
}

void Audio_io::io_select_change(int &i)
{
    io_init(i);
}

void Audio_io::io_enable_change(bool &b)
{
    if (b)
    {
        input_enable.set(0);
        output_enable.set(0);
        io_init(io_select);
        
    }else{
        io_stream.stop();
        io_stream.close();
    }
}




void Audio_io::input_init(int selection)
{
    if(input_enable)
    {
        input_stream.stop();
        input_stream.close();
    }
    auto devices = input_stream.getDeviceList();
    input_select.setMax(devices.size());
    if (!devices[selection].inputChannels)
    {
        cout<<"error, no input on device"<<endl;
        input_label = "[X] " + devices[selection].name;
    } else {
        input_label = devices[selection].name;
        input_settings.setInListener(this);
        input_settings.setInDevice(devices[selection]);
        input_settings.sampleRate = sample_rate;
        input_settings.numInputChannels = 2;
        input_settings.bufferSize = buffer_size;
        input_stream.setup(input_settings);
        if(input_enable)
        {
            input_stream.start();
        } else {
            input_stream.stop();
        }
        input_buffer_1.assign(buffer_size, 0.0);
        input_buffer_2.assign(buffer_size, 0.0);
    }
}


void Audio_io::input_select_change(int &input_select)
{
    input_init(input_select);
}

void Audio_io::input_enable_change(bool &input_enable)
{
    if (input_enable)
    {
        io_enable.set(0);
        input_init(input_select);
        input_stream.start();
    }
    else
    {
        input_stream.close();
        input_stream.stop();
        input_buffer_1.assign(buffer_size, 0.0);
        input_buffer_2.assign(buffer_size, 0.0);
    }
}






void Audio_io::output_init(int selection)
{
    if(output_enable)
    {
        output_stream.stop();
        output_stream.close();
    }
    auto devices = output_stream.getDeviceList();
    output_select.setMax(devices.size());
    if (!devices[selection].outputChannels)
    {
        cout<<"error, no output on device"<<endl;
        output_label = "[X] " + devices[selection].name;
    } else {
        if(output_enable){output_stream.stop();}
        output_label = devices[selection].name;
        output_settings.setOutDevice(devices[selection]);
        output_settings.sampleRate = sample_rate;
        output_settings.numOutputChannels = 2;
        output_settings.bufferSize = buffer_size;
        output_settings.setOutListener(this);
        output_stream.setup(output_settings);
        if(output_enable)
        {
            output_stream.start();
        } else {
            output_stream.close();
            output_stream.stop();
        }
        output_buffer_1.assign(buffer_size, 0.0);
        output_buffer_2.assign(buffer_size, 0.0);
        player_buffer_1_wo.assign(buffer_size, 0.0);
        player_buffer_2_wo.assign(buffer_size, 0.0);
        
        
        
    }
}

void Audio_io::output_select_change(int &output_select)
{
    output_init(output_select);
}

void Audio_io::set_master_vol(float _master_vol)
{
    master_vol_ammount = _master_vol;
}

void Audio_io::set_master_vol_change(float &f)
{
    master_vol_ammount = f;
}


void Audio_io::set_output_vol(float _output_vol)
{
    output_vol_ammount = _output_vol;
}

void Audio_io::set_output_vol_change(float &f)
{
    output_vol_ammount = f;
}



void Audio_io::output_enable_change(bool &output_enable)
{
    if (output_enable)
    {
        io_enable.set(0);
        output_init(output_select);
        output_stream.start();
    }else{
        output_stream.stop();
        output_buffer_1.assign(buffer_size, 0.0);
        output_buffer_2.assign(buffer_size, 0.0);
    }
}

void Audio_io::player_enable_change(bool &player_enable)
{
    if(player_enable)
    {
        player.play();
        //        player_1.play();
        //        player_2.play();
    } else {
        player.stop();
        //        player_1.stop();
        //        player_2.stop();
    }
}

void Audio_io::player_set_speed(float f)
{
    player.setSpeed(f);
    //    player_1.setSpeed(f);
    //    player_2.setSpeed(f);
}


void Audio_io::player_speed_change(float &f)
{
    player.setSpeed(f);
    //    player_1.setSpeed(player_speed);
    //    player_2.setSpeed(player_speed);
}

void Audio_io::player_pan_change(float &f)
{
    player.setPan(f);
    //    player_1.setPan(player_pan);
    //    player_2.setPan(player_pan);
}


void Audio_io::player_volume_change(float &f)
{
    player.setVolume(f);
    
}


void Audio_io::player_position_change(float &f)
{
    player.setPosition(f);
    
}

void Audio_io::player_file_index_change(int &i)
{
    setup_player(i);
}




