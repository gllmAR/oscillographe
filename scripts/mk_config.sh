#!/bin/bash

echo "Reminder:must be run as sudo"

CONFIG=/boot/config.txt

echo "dtparam=audio=on">>$CONFIG
echo "audio_pwm_mode=2">>$CONFIG
echo "gpu_mem=128">>$CONFIG
echo "disable_overscan=1">>$CONFIG
echo "disable_audio_dither">>$CONFIG


cat $CONFIG
