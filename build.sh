#!/bin/bash

function error_exit() {
    echo $1
    popd > /dev/null
    exit 1
}

pushd `dirname $0` > /dev/null
SCRIPT_PATH=`pwd`
popd > /dev/null

wx-config --cxxflags

WORKSPACE_DIR=$SCRIPT_PATH/workspace

echo Workspace directory is "$WORKSPACE_DIR"

mkdir -p "$WORKSPACE_DIR" || (echo Can not create workspace directory && exit 1)
pushd "$WORKSPACE_DIR" > /dev/null || (echo Can not change dir to workspace directory && exit 1)

cmake . -G "CodeBlocks - Unix Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo "$@" .. || error_exit "Configuring failed"
make || error_exit "Build failed, try to cleanup the workspace and rebuild"
pwd

echo EVERYTHING OK
popd > /dev/null
