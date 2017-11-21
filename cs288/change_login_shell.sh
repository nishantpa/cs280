#!/bin/bash

while true; do
  read -p "Enter a USER_ID: " USERID
  case $USERID in
     [q] ) echo "You have terminated program" ; exit;;
  esac

EXISTS=`grep -w "$USERID" /etc/passwd`
size=${#EXISTS}

 if [ $size -gt 0 ]; then
    echo $EXISTS && echo ${EXISTS} > passwd.1
         read -p "Is this the entry you want to change? " yn 
	 case $yn in
	   [Yy]* ) ;;
	   [Nn]* ) continue
	 esac
    read -p "What is the new login shell? " newShell
    
    oldshell=`cat passwd.1 | cut -d":" -f1,2,3,4,5,6`
    echo $oldshell"/bin/"$newShell > passwd.1
    exit

   else 
      echo "User not found" 
 fi
done
