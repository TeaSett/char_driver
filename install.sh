#!/bin/bash
echo "*******************************"
echo "*** Building my_char_driver ***"

make all

read -p "Enter buffer size in bytes (e.g. 1024): " input

echo "Installing my_char_driver..."
# Установка
sudo rmmod my_char_driver.ko
sudo insmod my_char_driver.ko size="$input"
sudo chmod 666 /dev/my_char_driver

echo "*******************************"
echo "*******   System logs   *******"
echo "-------------------------------"
sudo dmesg | tail | grep my_char_driver

echo "*******************************"
echo "* Cleaning \"make\" artifacts *"

# Очистка папки от файлов сборки
make clean