#!/bin/sh

dir="/tmp/pics/raw/"
ext=".jpg"

temp_k=`/home/root/code/thermistor`
temp=`awk -v temp_k="$temp_k" 'BEGIN{print temp_k - 273.15}'`
#temp= `$temp_k - 273.15 | bc`
#echo $temp
#echo "Converting ...."
#echo `date +%N`
nice -n -20 convert $1 -gravity south \
-font /usr/share/fonts/ttf/LiberationMono-Bold.ttf \
-stroke '#000C' -strokewidth 2 -annotate 0 'Temperature : '$temp \
-stroke none -fill white     -annotate 0 'Temperature : '$temp \
/tmp/pics/test.jpg
#echo `date +%N`
#mv /tmp/pcs/raw/test.jpg /tmp/pics/ 
rm $dir*.jpg
