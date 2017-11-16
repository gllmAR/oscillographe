//
//  audio_in.cpp
//  oscillograph
//
//  Created by Guillaume Arseneault on 17-08-07.
//
//
// todo: -> audio in -> audio io
// tester dans le cas ou le sound stream est sur la même carte si ça enleve les glitch audio
// test
#include "audio_io.hpp"

void Audio_io::setup()
{
    
    gui.setup();
    gui.setName("audio_io");
    gui.add(buffer_size.set("buffer_size",64,64,4096));
    gui.add(sample_rate.set("sample_rate",44100,8000,192000));
    
    gui.add(input_active.set("input_active", 1));
    gui.add(input_select.set("input_select",0,0,1));
    gui.add(input_label.setup("", ""));
    gui.add(input_volume.set("input_volume",1,0,2));
    gui.add(input_pan.set("input_pan",0,-1,1));


    gui.add(output_active.set("output_active", 1));
    gui.add(output_select.set("output_select",0,0,1));
    gui.add(output_label.setup("", ""));
    gui.add(output_volume.set("output_volume",1,0,2));
    gui.add(output_pan.set("output_pan",0,-1,1));

    gui.add(player_active.set("player_active", 1));
    gui.add(player_speed.set("player_speed",1,-2,2));
    gui.add(player_volume.set("player_volume",1,0,2));
    gui.add(player_pan.set("player_pan",0,-1,1));

    
    init();
    

    player_1.load("sounds/lasers_1.wav");
    player_2.load("sounds/lasers_2.wav");

    player_1.play();
    player_2.play();

    player_1.setLoop(1);
    player_2.setLoop(1);
    player_1.setPan(-1);
    player_2.setPan(1);

    
    input_select.addListener(this, &Audio_io::input_select_change);
    input_active.addListener(this, &Audio_io::input_active_change);
    
    output_select.addListener(this, &Audio_io::output_select_change);
    output_active.addListener(this, &Audio_io::output_active_change);
    
    player_speed.addListener(this, &Audio_io::player_speed_change);
    player_volume.addListener(this, &Audio_io::player_volume_change);
    player_pan.addListener(this, &Audio_io::player_pan_change);

}



void Audio_io::init()
{
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
    
  
    //player_buffer.allocate(buffer_size, 2);
    player_buffer_1.allocate(buffer_size, 2);
    player_buffer_2.allocate(buffer_size, 2);

}

void Audio_io::exit()
{
	input_stream.start();
	output_stream.stop();
    input_buffer_1.assign(buffer_size, 0.0);
    input_buffer_2.assign(buffer_size, 0.0);
}


void Audio_io::audioIn(ofSoundBuffer & input)
{
    // process pan
    float pan_1 = 1-(input_pan*0.5 +0.5);
    float pan_2 = input_pan*0.5 +0.5;
    
    for (int i = 0; i < input.getNumFrames(); i++)
    {
        input_buffer_1[i] = input[i*2  ] * input_volume * pan_1 ;
        input_buffer_2[i] = input[i*2+1] * input_volume * pan_2 ;
    }
}



void Audio_io::input_init(int selection)
{
	input_stream.stop();
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
        if(input_active)
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

void Audio_io::input_active_change(bool &input_active)
{
    if (input_active)
    {
        input_stream.start();
    }
    else
    {
        input_stream.stop();
        input_buffer_1.assign(buffer_size, 0.0);
        input_buffer_2.assign(buffer_size, 0.0);
    }
}



void Audio_io::audioOut(ofSoundBuffer& output)
{
    // process pan
    float pan_1 = 1-(output_pan*0.5 +0.5);
    float pan_2 = output_pan*0.5 +0.5;
    
    player_1.audioOut(output);
    player_buffer_1 = output;
    
    player_2.audioOut(output);
    player_buffer_2 = output;
    
    
    //player_buffer = player.getCurrentBuffer();
    
        for (int i = 0; i < output.getNumFrames(); i++)
        {
            output_buffer_1[i] = output[i*2  ] =
            (input_buffer_1[i] +  player_buffer_1[i*2  ]) * output_volume * pan_1;
            
            output_buffer_2[i] = output[i*2+1] = 
            (input_buffer_2[i] +  player_buffer_2[i*2+1]) * output_volume * pan_2;
        }
}



void Audio_io::output_init(int selection)
{
	output_stream.stop();
    auto devices = output_stream.getDeviceList();
    output_select.setMax(devices.size());
    if (!devices[selection].outputChannels)
    {
        cout<<"error, no output on device"<<endl;
        output_label = "[X] " + devices[selection].name;
    } else {
        output_label = devices[selection].name;
        output_settings.setOutDevice(devices[selection]);
        output_settings.sampleRate = sample_rate;
        output_settings.numOutputChannels = 2;
        output_settings.bufferSize = buffer_size;
        output_settings.setOutListener(this);
        output_stream.setup(output_settings);
                if(output_active)
        	{
     			output_stream.start();
        	} else {
        		output_stream.stop();
        	}
        output_buffer_1.assign(buffer_size, 0.0);
        output_buffer_2.assign(buffer_size, 0.0);
    }
}


void Audio_io::output_select_change(int &output_select)
{
    output_init(output_select);
}

void Audio_io::output_active_change(bool &output_active)
{
    if (output_active)
    {
        output_stream.start();
    }
    else
    {
        output_stream.stop();
        output_buffer_1.assign(buffer_size, 0.0);
        output_buffer_2.assign(buffer_size, 0.0);
    }
}


void Audio_io::player_speed_change(float &f)
{
    //player.setSpeed(player_speed);
    player_1.setSpeed(player_speed);
    player_2.setSpeed(player_speed);
}

void Audio_io::player_pan_change(float &f)
{
   // player.setPan(player_pan);
    player_1.setPan(player_pan);
    player_2.setPan(player_pan);
}


void Audio_io::player_volume_change(float &f)
{
    //player.setVolume(player_volume);
      player_1.setVolume(player_volume);
      player_2.setVolume(player_volume);
}





