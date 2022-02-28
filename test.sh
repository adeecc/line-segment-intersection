#! /bin/sh

cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -H. -B./build -G "Unix Makefiles"

cmake --build ./build --config Relase --target all

cd bin/tests
echo $(pwd)
chmod +x ./lexer_tests
./lexer_tests