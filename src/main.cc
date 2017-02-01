#include <iostream>
#include <memory>

#include "input.cpp"

int main() {

    std::unique_ptr<Input<4>> input1(new Input<4>({}, {}));
    input1 -> readfile();
    input1 -> outputcoords();
    input1 ->generatemesh();
}
