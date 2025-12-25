#include <iostream>
#include <cassert>
#include <vector>
#include <cstdint>

struct TestStruct
{
    int a = 1;
    int b = 2;
};

typedef enum TestEnum
{
    TEST_ENUM_A,
    TEST_ENUM_B,
    TEST_ENUM_C
} TestEnum;

// VIDL_GENERATE
uint32_t FunctionTest0( uint32_t x, uint32_t y, bool a, TestEnum enumVal );

// VIDL_GENERATE
uint32_t FunctionTest1(
    uint32_t x,
    uint32_t y,
    bool a,
    TestEnum enumVal
);

// VIDL_GENERATE
void FunctionTest2(
    uint32_t* x,
    TestStruct* ptr
);

// VIDL_GENERATE
uint32_t FunctionTest3(
    uint32_t* x,
    TestStruct* ptr,
    TestEnum enumVal
);

// VIDL_GENERATE
uint32_t FunctionTest4(
    float x = 0.0f,
    double y = 1.0,
    uint64_t a = 0x2 | 0x1,
    TestEnum enumVal = TEST_ENUM_A
);

// VIDL_GENERATE
uint32_t FunctionTest5(
    float x = 0.0f,
    double y = 1.0,
    uint64_t a = 0x2 | 0x1,
    TestStruct s = TestStruct()
);

uint32_t FunctionTest4_SHOULD_NOT_BE_GENERATED(
    float x = 0.0f,
    double y = 1.0,
    uint64_t a = 0x2 | 0x1,
    TestStruct s = TestStruct()
);

// New VIDL Definitions
// VIDL_GENERATE
void TestKeywords(int cls, float virt);

// VIDL_GENERATE
void TestPointers(int* a, TestStruct* b);


// Include generated header
#include "vidl_generated.h"

class ValidationHandler : public VIDLHandler
{
public:
    bool visited_function0 = false;

    void Handle_FunctionTest0(VIDL_FunctionTest0* cmd) override
    {
        visited_function0 = true;
        assert(cmd->x == 99);
    }
};

int main()
{
    std::cout << "Running Integration Tests in tests/test.cpp..." << std::endl;

    // Test Construction
    {
        VIDL_FunctionTest0 cmd(10, 20, true, TEST_ENUM_A);
        assert(cmd.x == 10);
    }

    // Test Defaults
    {
        VIDL_FunctionTest4 defaultCmd;
        assert(defaultCmd.x == 0.0f);
    }

    // Test Keywords
    {
        VIDL_TestKeywords k(1, 2.0f);
        // names are not keywords, so no sanitization expected
        assert(k.cls == 1);
        assert(k.virt == 2.0f);
    }

    // Test Dispatch
    {
        ValidationHandler handler;
        VIDL_FunctionTest0 payload(99, 0, false, TEST_ENUM_A);
        handler.HandleCmd(&payload);
        assert(handler.visited_function0 == true);
    }

    std::cout << "All Integration Tests Passed!" << std::endl;
    return 0;
}
