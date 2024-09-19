if [ "$1" == "build" ]; then
    cd build;
    cmake .. -D CMAKE_BUILD_TYPE=Debug -G "Unix Makefiles"
    make;
    echo;
    cd ..;
elif [ "$1" == "run" ]; then
    cd build;
    ./md2html.exe;
    cd ..;
fi