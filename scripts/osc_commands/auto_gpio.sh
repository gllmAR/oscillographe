#!/bin/bash
while true
do sendosc 127.0.0.1 8001 /gpio/1 i 1
sleep $1
done
