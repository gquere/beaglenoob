#!/bin/sh

mkdir /tmp/pics
mkdir /tmp/pics/raw

./mjpg_streamer -i "./input_file.so -f /tmp/pics -r" -o "./output_http.so" &
./mjpg_streamer -i "./input_uvc.so -d /dev/video0" -o "./output_file.so -f /tmp/pics/raw -d 500 -c /home/root/webcam/mjpg-streamer/bla.sh" &
