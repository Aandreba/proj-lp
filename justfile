clean:
    rm -rf build/*

build: clean
    cd build && cmake -DCMAKE_BUILD_TYPE=Debug ../
    cd build && make

run *ARGS: build
    clear
    ./build/proj-lp {{ARGS}}
