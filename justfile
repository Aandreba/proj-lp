build:
    rm -rf build/*
    cd build && cmake -DCMAKE_BUILD_TYPE=Debug ../src
    cd build && make

run *ARGS: build
    ./build {{ARGS}}
