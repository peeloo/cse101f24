
/*
Phil Liu
phzliu
2024 Fall CSE101 PA6
Arithmetic.cpp
Implements BigInteger ADT and its operations
*/

#include<iostream>
#include<string>
#include<stdexcept>
#include<fstream>
#include"BigInteger.h"

using namespace std;

int main(int argc, char* argv[]){
    ifstream in;
    ofstream out;
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return(EXIT_FAILURE);
    }

    in.open(argv[1]);
    out.open(argv[2]);
    if (!in.is_open()) {
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }
    if (!out.is_open()) {
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }
    //read infile
    string str1, str2;
    in >> str1;
    in >> str2;

    //calculate
    BigInteger A = str1;
    BigInteger B = str2;

    //print result
    //A
    out << A << endl << endl;
    //B
    out << B << endl << endl;
    //A+B
    out << A+B << endl << endl;
    //A-B
    out << A-B << endl << endl;
    //A-A
    out << A-A << endl << endl;
    //3A-2B
    out << 3*A-2*B << endl << endl;
    //AB
    out << A*B << endl << endl;
    //A^2
    out << A*A << endl << endl;
    //B^2
    out << B*B << endl << endl;
    //9A^4+16B^5
    out << 9*(A*A*A*A)+16*(B*B*B*B*B) << endl << endl;

    //close file
    in.close();
    out.close();

    return 0;
}
