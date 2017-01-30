#! /bin/bash

nbdonnes=0
nbid=$(ls logs[0-9].txt | wc -l)
echo $nbid > geoloc-logs.txt
for i in $(seq 1 $nbid) 
do
	#echo $i
	echo - >> geoloc-logs.txt
	nblignes=$(cat logs$i.txt | wc -l)
	nbdonnes=$(($nbdonnes + $nblignes))
	#echo $nbdonnes
	echo $nblignes >> geoloc-logs.txt
	cat logs$i.txt >> geoloc-logs.txt
done
echo % >> geoloc-logs.txt
echo $nbdonnes >> geoloc-logs.txt	
	
