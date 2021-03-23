#!/bin/bash

# Select a premake binary according to the current platform
if [ "$(uname)" == "Darwin" ]; then
  # If we don't do this, weird things happen due to what seems like a premake bug
  # (looks like it's mistaking the binary for a folder)
  mkdir -p bin/Debug-macosx-x86_64/sandbox

  PREMAKE_BIN="premake5-mac"       
elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
  mkdir -p bin/Debug-linux-x86_64/sandbox

  PREMAKE_BIN="premake5-linux"
else
  echo "Unsupported platform."
  exit 1
fi

./vendor/bin/premake/${PREMAKE_BIN} gmake
