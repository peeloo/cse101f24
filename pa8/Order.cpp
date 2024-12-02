/*
Phil Liu
phzliu
2024 Fall CSE101 PA8
Order.cpp
First Top Level Client for Dictionary ADT
*/

#include <iostream>
#include <fstream>
#include <string>
#include "Dictionary.h"

using namespace std;

int main(int argc, char * argv[]) {
    ifstream in;
    ofstream out;
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return (EXIT_FAILURE);
    }

    in.open(argv[1]);
    out.open(argv[2]);
    if (!in.is_open()) {
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return (EXIT_FAILURE);
    }

    if (!out.is_open()) {
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return (EXIT_FAILURE);
    }

    Dictionary D;
    string k;
    int val = 1;
    while (getline(in, k))  {
        D.setValue(k, val);
        val++;
    }

    out << D << endl;
    out << D.pre_string() << endl;

    in.close();
    out.close();

    return 0;
}
