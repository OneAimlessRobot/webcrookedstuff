#!/bin/bash


for directory in $(ls ..);
do

cat template >> ../$directory/$directory.html

done
