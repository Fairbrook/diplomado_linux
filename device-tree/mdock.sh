#!/bin/bash

docker run --rm --name make -ti -v .:/src fairbrook/gcc-arm-linux-gnueabihf ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- ${@:1}
