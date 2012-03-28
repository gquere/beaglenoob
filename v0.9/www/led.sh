#!/bin/sh

if [ $1 -eq 1 ] 
then
	echo 1 > /sys/devices/platform/leds-gpio/leds/beaglebone::usr3/brightness
	echo 1 > /sys/devices/platform/leds-gpio/leds/beaglebone::usr2/brightness
else
	echo 0 > /sys/devices/platform/leds-gpio/leds/beaglebone::usr3/brightness
	echo 0 > /sys/devices/platform/leds-gpio/leds/beaglebone::usr2/brightness
fi
sleep 1
