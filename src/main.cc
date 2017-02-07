#include <iostream>
#include <memory>
#include "input.cpp"

int main() {
    //!For 2D - set z values to 0, code will adjust output for this.
    //!outputs input file - unsure how to read file not in working directory
    // DON'T FORGET TO CHANGE AMOUNT OF ROWS IN TEMPLATE
    const std::string fileforinput = "input.txt";
    std::fstream outfile;
    outfile.open(fileforinput, std::ios::out);
    outfile << "1,1,0" << '\n';
    outfile << "0,0,0:0,4,0" << '\n';
    outfile << "1,0,0:1,5,0" << '\n';
    outfile << "2,2,0:2,3,0" << '\n';
    outfile << "3,2,0:3,3,0" << '\n';
    outfile << "4,0,0:4,5,0" << '\n';
    outfile << "5,0,0:5,4,0";
    outfile.close();



    //! Input requires  (Dimension x2), and #Rows of coordinates in text file
    std::unique_ptr<Input<6, 6>> input1(new Input<6,6>({}, {}));
    input1->readfile();
    input1->outputcoords();
    input1->generatemesh();
}
/*
 *
 * Input file format must be:
 *         Top Row: xspacing, yspacing, zspacing
 * Subsequent Rows: xlow,ylow,zlow:xhigh,yhigh,zhigh
 * eg for:
 *
         0,5,5-------5,5,5
           /|      / |
          / |     /  |
         /  |    /   |
     0,5,0--|----5,5,0
         |  |    |   |
        0,0,5----|--5,0,5
         |  /    |  /
         | /     | /
         |/      |/
    0,0,0 -------5,0,0

    write:
         1,1,1
         0,0,0:0,5,0
         0,0,5:0,5,5
         5,0,0:5,5,0
         5,0,5:5,5,5

         or:

    outfile << "1,1,1" << '\n';
    outfile << "0,0,0:0,5,0" << '\n';
    outfile << "0,0,5:0,5,5" << '\n';
    outfile << "5,0,0:5,5,0" << '\n';
    outfile << "5,0,5:5,5,5";
    outfile.close();



 Modified 2D Shape:

    outfile << "1,1,0" << '\n';
    outfile << "0,0,0:0,4,0" << '\n';
    outfile << "1,0,0:1,5,0" << '\n';
    outfile << "2,2,0:2,3,0" << '\n';
    outfile << "3,2,0:3,3,0" << '\n';
    outfile << "4,0,0:4,5,0" << '\n';
    outfile << "5,0,0:5,4,0";
    outfile.close();

Modified 3D Shape:

     outfile << "1,1,1" << '\n';
    outfile << "0,0,0:0,5,0" << '\n';
    outfile << "0,0,5:0,5,5" << '\n';
    outfile << "2,2,0:2,5,0" << '\n';
    outfile << "2,2,5:2,5,5" << '\n';
    outfile << "4,2,0:4,5,0" << '\n';
    outfile << "4,2,5:4,5,5" << '\n';
    outfile << "5,0,0:5,5,0" << '\n';
    outfile << "5,0,5:5,5,5";
    outfile.close();

*/

