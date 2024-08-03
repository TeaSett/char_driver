#!/bin/bash
set -o errexit # Прервать скрипт в случае ошибки любой из команд
echo "*******************************"
echo "*** Building my_char_driver ***"

make all

read -p "Enter buffer size in bytes (input 0 to set the default value 1024): " input

echo "Installing my_char_driver..."
sudo insmod my_char_driver.ko size="$input"
sudo chmod 666 /dev/my_char_driver

echo "*******************************"
echo "*******   System logs   *******"

sudo dmesg | tail | grep my_char_driver

echo "*******************************"
echo "** Cleaning \"make\" artifacts **"

make clean # Очистка папки от файлов сборки