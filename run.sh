#! /bin/sh

cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -H. -B./build -G "Unix Makefiles"

cmake --build ./build --config Relase --target app

cd bin

chmod +x ./app

echo Current Working Directory: $(pwd)
echo "Enter Path to file relative to pwd"
echo "Example: ./tests/source_code/full/swap.crst"

./app