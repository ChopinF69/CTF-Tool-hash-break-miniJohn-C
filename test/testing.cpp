//
// Created by lazar on 14.02.2024.
//
#include "basic_test_framework.h"
#include "include_hashes.h"
#include <iostream>

TEST(MD5Test) {
    std::string input = "grape";
    std::string output1 = md5(input);
    ASSERT_CONDITION(output1 == "b781cbb29054db12f88f08c6e161c199")
}
TEST(SHA1Test)
{
    std::string input = "grape";
    std::string output1 = sha1(input);
    ASSERT_CONDITION(output1 == "bc8a2f8cdedb005b5c787692853709b060db75ff")
}
TEST(SHA256Test)
{
    std::string input = "grape";
    std::string output1 = sha256(input);
    ASSERT_CONDITION(output1 == "0f78fcc486f5315418fbf095e71c0675ee07d318e5ac4d150050cd8e57966496")
}
TEST(SHA512TEST)
{
    std::string input = "grape";
    std::string output1 = sha512(input);
    ASSERT_CONDITION(output1 == "9375d1abdb644a01955bccad12e2f5c2bd8a3e226187e548d99c559a99461453b980123746753d07c169c22a5d9cc75cb158f0e8d8c0e713559775b5e1391fc4")
}

TestResults runAllTests() {
    TestResults results;

    runTest(MD5TestTestCase , results);
    runTest(SHA1TestTestCase , results);
    runTest(SHA256TestTestCase , results);
    runTest(SHA512TESTTestCase , results);
    return results;
}
int main() {
    TestResults results = runAllTests();
    std::cout << "Passed " << results.passedTests << " out of " << results.totalTests << " tests" << std::endl;
    return 0;
}