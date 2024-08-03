#!/bin/bash
set -o errexit # Прервать скрипт в случае ошибки любой из команд
echo "*******************************"
echo "*** Removing my_char_driver ***"

sudo rmmod my_char_driver.ko

echo "* my_char_driver was removed **"
echo "*******************************"