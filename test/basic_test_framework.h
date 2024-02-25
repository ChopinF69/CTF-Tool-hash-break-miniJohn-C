//
// Created by lazar on 14.02.2024.
//

#ifndef MINIJOHN_BASIC_TEST_FRAMEWORK_H
#define MINIJOHN_BASIC_TEST_FRAMEWORK_H
#include <functional>
#include <iostream>
#include <chrono>
// Define a structure to represent a test case
struct TestCase {
    std::function<void()> testFunction;
    std::string testName;
};
struct TestTime
{
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::chrono::time_point<std::chrono::high_resolution_clock> end;
    std::chrono::duration<double> duration;
    TestTime()
    {
        start = std::chrono::high_resolution_clock::now();
    }
    ~TestTime()
    {
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        std::cout << "Test duration: " << duration.count() << " seconds" << std::endl;
    }
};
// Define a structure to represent the test results
struct TestResults {
    int totalTests = 0;
    int passedTests = 0;
};

// Define a function to run a single test case
void runTest(const TestCase& testCase, TestResults& results) {
    std::cout << "Running test: " << testCase.testName << " ... ";
    auto startTime = std::chrono::high_resolution_clock::now();
    try {
        testCase.testFunction(); // Run the test
        std::cout << "Passed" << std::endl;
        results.passedTests++;
    } catch (const std::exception& e) {
        std::cout << "Failed: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "Failed: Unknown exception" << std::endl;
    }
    results.totalTests++;
}

// Define a macro for writing test cases
#define TEST(testName) \
    void testName(); \
    TestCase testName##TestCase{testName, #testName}; \
    void testName()

// Define an assertion macro
#define ASSERT_CONDITION(condition) \
    if (!(condition)) throw std::runtime_error("Assertion failed: " #condition "  \nIs false at " __FILE__ " ---LINE : " + std::to_string(__LINE__));
//Define a macro to get the time of the test
#define TEST_TIME TestTime testTime;

// Example of using the testing framework

TEST(MyTest) {
    ASSERT_CONDITION(1 + 1 == 1);
    ASSERT_CONDITION(2 * 2 == 4);
}

TEST(AnotherTest) {
    ASSERT_CONDITION(3 - 1 == 2);
}
//Here will test time
TEST(MyTestTime)
{
    TEST_TIME
    for (int i = 0; i < 1000000; i++)
    {
        i++;
    }
}
/*
TestResults runAllTests() {
    TestResults results;
    runTest(MyTestTestCase, results);
    runTest(AnotherTestTestCase, results);
    runTest(MyTestTimeTestCase, results);
    return results;
}*/

#endif
