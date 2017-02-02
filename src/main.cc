#include <iostream>
#include <memory>
#include "input.cpp"

/*
!!COPY input.txt FILE FROM SRC TO cmake-build-debug!!!
 !!or set SRC as Working Directory!!

input file:
5,5:5,10
10,5:10,10


*/

int main() {

    std::unique_ptr<Input<4,5>> input1(new Input<4,5>({}, {}));
    input1 -> readfile();
    input1 -> outputcoords();
    input1 ->generatemesh();
}
