#!/bin/sh
cd ../../guest/bmguest
make
cp bmguest.bin ../guestloader/build
cd ../guestloader
make
cd ../../build
cp guestloader.bin guest0.bin
mv guestloader.bin guest1.bin
cd ../hypervisor/src
