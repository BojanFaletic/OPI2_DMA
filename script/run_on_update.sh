#!/bin/bash

### Set initial time of file
LTIME=`stat -c %Z test`

while true
do
   ATIME=`stat -c %Z test`

   if [[ "$ATIME" != "$LTIME" ]]
   then
       clear
       date
       ./test
       LTIME=$ATIME
   fi
   sleep 1
done
