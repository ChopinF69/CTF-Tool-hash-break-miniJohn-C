//
// Created by lazar on 24.02.2024.
//
#include "include/include_hashes.h"
#include <iostream>
/*
 * How to run:
 * g++ brute.cpp -o brute
 * ./brute <hash> <hash_name> <number_of_characters>
 *
 * Example:
 * ./brute ab56b4d92b40713acc5af89985d4b786 MD5 5
 *
 * If you want to modify the characters that you want to contain the password, modify the letters variable
 * at the line 54 of the code - std::string letters = "..";
 */
void generateCombinations(const std::string& letters, std::string prefix,
                          int length,
                          const std::string& hashToFind,
                          const std::string& hashName
                          ) {

    if (prefix.size() == length) {
        std::string output = hash::h_md5(prefix);
        if (output == hashToFind) {
            std::cout << "Found: " << prefix << std::endl;
            std::cout << "Algo: " << hashName << std::endl;
            exit(0);
        }
        return;
    }

    for (char letter : letters) {
        generateCombinations(letters, prefix + letter, length, hashToFind, hashName);
    }
}

int main(int argc , char *argv[]) {
    // Expecting 4 arguments: program name, hash, hash name, number of characters
    if(argc != 4)
    {
        std::cout << "Usage: " << argv[0] << " <hash> <hash_name> <number_of_characters>" << std::endl;
        return 1;
    }

    std::string hashToFind = argv[1];
    std::string hashName = argv[2];
    std::string numberOfCharacters = argv[3];

    int length = std::stoi(numberOfCharacters);

    //---------------------------------------------------------------------------
    //Here if you want to modify the characters that you want to contain the password
    std::string letters = "abcdefghijklmnopqrstuvwxyz";

    generateCombinations(letters, "", length, hashToFind, hashName);

    return 0;
}