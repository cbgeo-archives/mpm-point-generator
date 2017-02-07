#include "mesh.h"
#include "point.cc"
//! Mesh constructor
//! \param[in]
template <unsigned Tdim>
Mesh<Tdim>::Mesh(unsigned id, std::array<double, Tdim> param) : id_{ id }{
    param_ = param;
    ni_ = (param_[0] / param_[3]) + 1;
    nj_ = (param_[1] / param_[4]) + 1;
    nz_ = (param_[2] / param_[5]) + 1;
}
template <unsigned Tdim>
void Mesh<Tdim>::generatecoordinates() {
    unsigned pointid = 0;


    //!Find origin of shape, so coordinates of points will fit in shape
    const std::string infilename = "input.txt";
    std::fstream infile;
    infile.open(infilename, std::ios::in);

    std::string line;

    int t = 0;
    int q = 0;

    if (q == 0) {
        //!Ignore spacing line
        infile >> spacingline;
        getline (infile, line);
        ++q;
    }

    while (infile){

        //!gets first coordinate to use as origin
        infile >> xorigin;
        getline(infile, line, ',');

        infile >> yorigin;
        getline(infile, line, ',');

        infile >> zorigin;
        getline(infile, line, ':');

        infile >> xhigh;
        getline(infile, line, ',');

        infile >> yhigh;
        getline(infile, line, ',');

        infile >> zhigh;
        getline (infile, line);


        origin2darray[t][0] = {xorigin};
        origin2darray[t][1] = {yorigin};
        origin2darray[t][2] = {zorigin};
        origin2darray[t][3] = {xhigh};
        origin2darray[t][4] = {yhigh};
        origin2darray[t][5] = {zhigh};

        originarray = {xorigin,yorigin,zorigin};
        originvector_.emplace_back(originarray);
        ++t;

    }infile.close();

    int m = 0;

    // Iterate through number of nodes in x and y directions

    for (auto i = origin2darray[0][0]; i < ni_ + origin2darray[0][0]; ++i,++m) {
        for (auto j = origin2darray[0][1]; j < nj_ + origin2darray[0][1]; ++j) {
            if (nz_ > 1) {
                for (auto k = origin2darray[0][2]; k < nz_ + origin2darray[0][2]; ++k) {
                    //check to see if any points need to be removed
                    if (j>= origin2darray[m][1] - origin2darray[m-1][1]){
                        std::array<double, 3> coord =
                                {static_cast<double>(i) * param_[3],
                                 static_cast<double>(j) * param_[4],
                                 static_cast<double>(k) * param_[5]};
                        // Create a point object based on id and coordinates
                        points_.emplace_back(new Point<3>(pointid, coord));
                        ++pointid;}}}

            else {

                //check to see if any points need to be removed - bump case
                if(i >= origin2darray[m][0]){
                    if (j >= origin2darray[m][1]){
                        if ( i <=origin2darray[m][3]) {
                            if (j <= origin2darray[m][4]) {
                                std::array<double, 3> coord =
                                        {static_cast<double>(i) * param_[3],
                                         static_cast<double>(j) * param_[4]};
                                // Create a point object based on id and coordinates
                                points_.emplace_back(new Point<3>(pointid, coord));
                                ++pointid;
                            } else {
                                //std::cout << "skipped j";
                            }
                        }
                        else {
                            //std::cout<< "skipped x";
                        }
                    }
                    else {
                        //std::cout << "skipped ylow";
                    }
                }
                else {
                    //std::cout << "skipped xlow";
                }

            }
        }
    }

    std::cout << "# Points: " << points_.size() << '\n';
}

template <unsigned Tdim>
void Mesh<Tdim>::coordinatesoutput() {
    const std::string outputfilename = "coords.txt";
    std::fstream outfile;
    outfile.open(outputfilename, std::ios::out);
    if (nz_ > 0){
        for (const auto& point : points_) {
            outfile << point->id() << "," << '\t';
            outfile << point->coordinates().at(0) << "," << point->coordinates().at(1)
                    << "," << point->coordinates().at(2) << '\n';
        }}
    else{
        for (const auto& point : points_) {
            outfile << point->id() << "," << '\t';
            outfile << point->coordinates().at(0) << "," << point->coordinates().at(1) <<'\n';
        }
    }
    outfile.close();
}
