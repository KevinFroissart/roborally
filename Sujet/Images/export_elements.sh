#!/bin/bash

if [ -z $1 ]
then
  echo "Usage : $0 <svg style file>"
  exit 1
fi

elements=(
  'robot' 'prev_robot'
  'background'
  'forward' 'turn' 'opp_join' 'perp_join' 
  'fast_forward' 'fast_turn' 'fast_opp_join' 'fast_perp_join' 
  'rotate'
  )

for elem in ${elements[@]}
do
  inkscape $1 -i $elem -A "$elem.pdf" -C
done
