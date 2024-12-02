/*
Phil Liu
phzliu
2024 Fall CSE101 PA8
WordFrequency.cpp
Second Top Level Client for Dictionary ADT
*/

#include <iostream>
#include <fstream>
#include <string>
#include "Dictionary.h"

using namespace std;

int main(int argc, char * argv[]) {
    size_t begin, end, len;
    ifstream in;
    ofstream out;
    string line, key;
    string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
    Dictionary D;

    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return EXIT_FAILURE;
    }

    in.open(argv[1]);
    out.open(argv[2]);

    if (!in.is_open()) {
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return EXIT_FAILURE;
    }

    if (!out.is_open()) {
        cerr << "Unable to open file " << argv[2] << " for reading" << endl;
        return EXIT_FAILURE;
    }

    while (getline(in, line)) {
        len = line.length();

        begin = min(line.find_first_not_of(delim, 0), len);
        end = min(line.find_first_of(delim, begin), len);
        key = line.substr(begin, (end - begin));

        while (key != "") {
            for (size_t i = 0; i < key.length(); i++) {
                key[i] = tolower(key[i]);
            }

            if (D.contains(key)) {
                D.getValue(key)++;
            }
            else {
                D.setValue(key, 1);
            }

            begin = min(line.find_first_not_of(delim, (end + 1)), len);
            end = min(line.find_first_of(delim, begin), len);
            key = line.substr(begin, (end - begin));
        }
    }

    out << D << endl;
    
    D.clear();
    in.close();
    out.close();

    return 0;
}