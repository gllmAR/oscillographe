#!/bin/bash

## get the absoluth path
pushd `dirname $0` > /dev/null
SCRIPTPATH=`pwd -P`
popd > /dev/null

sudo systemctl stop oscillo.service

sudo cp  $SCRIPTPATH/oscillo.service /etc/systemd/system/oscillo.service
sudo cp  $SCRIPTPATH/sensor_1.service /etc/systemd/system/sensor_1.service
sudo cp  $SCRIPTPATH/sensor_2.service /etc/systemd/system/sensor_2.service

sudo systemctl daemon-reload
sudo systemctl restart sensor_1.service
sudo systemctl restart sensor_2.service
sudo systemctl enable sensor_1 sensor_2
sudo systemctl restart oscillo.service

## should be nested in a if statement (is xorg?)
# sudo cp $SCRIPTPATH/80-oscilloscope.sh /etc/X11/xinit/xinitrc.d/80-oscilloscope.sh
# sudo chmod +x /etc/X11/xinit/xinitrc.d/80-oscilloscope.sh
# sudo /etc/X11/xinit/xinitrc.d/80-oscilloscope.sh
##
## else no xorg found, running on tty?
sudo systemctl enable oscillo

