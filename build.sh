#!/bin/sh

BUILD_DIR="Build"
BUILD_TYPE="Debug"

ln -sf build/compile_commands.json compile_commands.json

set -ex

if [ ! -d ${BUILD_DIR} ]; then
  mkdir -p ${BUILD_DIR}
fi

pushd ${BUILD_DIR}

cmake .. -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -DCMAKE_EXPORT_COMPILE_COMMANDS=1
cmake --build .

./bin/cpp-game-template

popd
