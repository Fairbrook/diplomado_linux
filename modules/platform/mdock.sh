#!/bin/bash

docker run --rm --name make -ti \
    -v .:/project \
    --workdir /project \
    -v $HOME/Documentos/projects/beagle-linux:/src \
    -v $HOME/Documentos/projects/beagle-output:/linux \
    fairbrook/gcc-arm-linux-gnueabihf \
    ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- KROOT=/linux ${@:1}
