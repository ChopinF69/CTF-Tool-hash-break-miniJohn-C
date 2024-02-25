//
// Created by lazar on 24.02.2024.
//

#include <iostream>
#include <vector>
#include <thread>

#include "include/include_hashes.h"
/*
 * How to run:
 * g++ -pthread -o dict dictionary.cpp
 * ./dictionary <hash_to_find>
 * You don't have to specify the hash name , the program will find it for you
 *
 * Example:
 * ./dictionary bc250e0d83c37b0953ada14e7bbc1dfd
 * Output:
 * Found: tesla
 * Algo: MD5
 * Path: somewhere in Passwords
 */
//or
/*
 * mkdir -p build
 * cd build
 * cmake ..
 * make
 * cd ..
 */
std::vector<std::string> LIST_OF_HASHES_ALGOS =
        {
                "MD5",
                "SHA1",
                "SHA256",
                "SHA512"
        };
/*
 * Vreau sa am 2 lucruri:
 * 1. Sa pot sa fac un thread pt fiecare algoritm de hash la un input dat dintr-un fisier
 * 2. Sa fac brute force , adica sa incerc toate combinatiile de caractere pana gasesc un hash care sa corespunda cu cel dat
 */

void make_md5(const std::string& input , const std::string& hash , const std::string& algo , const std::string& path)
{
    std::string output = hash::h_md5(input);
    if(output == hash)
    {
        std::cout << "Found: " << input << "\n";
        std::cout << "Algo: " << algo << "\n";
        std::cout << "Path: " << path << "\n";
        exit(0);

    }
}
void make_sha1(const std::string& input , const std::string& hash , const std::string& algo , const std::string& path)
{
    std::string output = hash::h_sha1(input);
    if(output == hash)
    {
        std::cout << "Found: " << input << "\n";
        std::cout << "Algo: " << algo << "\n";
        std::cout << "Path: " << path << "\n";
        exit(0);

    }
}
void make_sha256(const std::string& input , const std::string& hash , const std::string& algo , const std::string& path)
{
    std::string output = hash::h_sha256(input);
    if(output == hash)
    {
        std::cout << "Found: " << input << "\n";
        std::cout << "Algo: " << algo << "\n";
        std::cout << "Path: " << path << "\n";
        exit(0);

    }
}
void make_sha512(const std::string& input , const std::string& hash , const std::string& algo , const std::string& path)
{
    std::string output = hash::h_sha512(input);
    if(output == hash)
    {
        std::cout << "Found: " << input << std::endl;
        std::cout << "Algo: " << algo << std::endl;
        std::cout << "Path: " << path << std::endl;
        exit(0);
    }
}

void proccesFile(const std::string& fileName ,
                 const std::string& hashName ,
                 const std::string& hashToFind) {
    std::ifstream fin(fileName, std::ios::binary);

    if (!fin) {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return;
    }

    std::string password;
    while (std::getline(fin, password)) {
        //We need to find the index of the hashName
        int index = 0;
        for(int i = 0 ; i < LIST_OF_HASHES_ALGOS.size() ; ++i)
        {
            if(LIST_OF_HASHES_ALGOS[i] == hashName)
            {
                index = i;
                break;
            }
        }

        //Now we need to make the hash for the password and compare it with the hashToFind

        std::string hashed;
        switch(index)
        {
            case 0:
                make_md5(password , hashToFind , hashName , fileName);
                break;
            case 1:
                make_sha1(password , hashToFind , hashName , fileName);
                break;
            case 2:
                make_sha256(password , hashToFind , hashName , fileName);
                break;
            case 3:
                make_sha512(password , hashToFind , hashName , fileName);
                break;
        }
    }
}


int main(int argc , char *argv[])
{

    //We need only one argument - the hash to find

    if(argc == 1)
    {
        std::cout << "Usage: " << argv[0] << " <hash_to_find>" << std::endl;
        return 1;
    }
    std::string hashToFind = argv[1];

    //Example :
    //tesla md5
    //std::string hashToFind = "bc250e0d83c37b0953ada14e7bbc1dfd";

    std::ifstream fin_fisier("fisiere");
    std::vector<std::string> files;

    std::string fileRead;
    while(!fin_fisier.eof())
    {
        std::getline(fin_fisier, fileRead);
        files.push_back(fileRead);
    }

    files.emplace_back("cmake-build-debug/lista_romana");

    for(auto& file : files) {
        //We need to make a thread for each algorithm
        std::thread t_md5(proccesFile, file, "MD5", hashToFind);
        std::thread t_sha1(proccesFile, file, "SHA1", hashToFind);
        std::thread t_sha256(proccesFile, file, "SHA256", hashToFind);
        std::thread t_sha512(proccesFile, file, "SHA512", hashToFind);

        //We need to wait for all threads to finish
        t_md5.join();
        t_sha1.join();
        t_sha256.join();
        t_sha512.join();

    }
}