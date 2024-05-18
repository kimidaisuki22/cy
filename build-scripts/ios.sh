#!/bin/bash

IOS_TARGET=13.0
cmake -G Ninja \
    -B build_ios \
    -DCMAKE_SYSTEM_NAME=iOS \
    -DCMAKE_Swift_COMPILER_FORCED=true \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=${IOS_TARGET}