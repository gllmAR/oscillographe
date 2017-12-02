#!/bin/bash

# get the absoluth path
pushd `dirname $0` > /dev/null
SCRIPTPATH=`pwd -P`
popd > /dev/null

sudo systemctl stop oscillo.service

sudo ln -s -f $SCRIPTPATH/oscillo.service /etc/systemd/system/oscillo.service
sudo ln -s -f $SCRIPTPATH/sensor_1.service /etc/systemd/system/sensor_1.service

sudo systemctl daemon-reload
sudo systemctl start oscillo.service
sudo systemctl restart sensor_1.service


sudo cp $SCRIPTPATH/80-oscilloscope.sh /etc/X11/xinit/xinitrc.d/80-oscilloscope.sh
sudo chmod +x /etc/X11/xinit/xinitrc.d/80-oscilloscope.sh

sudo /etc/X11/xinit/xinitrc.d/80-oscilloscope.sh
