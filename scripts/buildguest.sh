#!/bin/sh

GUEST_DIR="$PWD/../../guest"
BM_DIR="$GUEST_DIR/bmguest"
LOADER_DIR="$GUEST_DIR/guestloader"
BUILD_DIR="$PWD/../../build"
HYP_SRC_DIR="$PWD"

cd $BM_DIR
make
cd $LOADER_DIR
make
cd $BUILD_DIR
cp guestloader.bin guest0.bin
mv guestloader.bin guest1.bin
cd $HYP_SRC_DIR
