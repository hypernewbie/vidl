#include <cstdint>
#include <iostream>

// dependencies required by the generated header
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

#include "vidl_generated.h"

int main()
{
    VIDL_FunctionTest0 cmd;
    cmd.x = 10;
    cmd.y = 20;
    cmd.a = true;
    cmd.enumVal = TEST_ENUM_A;

    std::cout << "Successfully instantiated VIDL_FunctionTest0 with magic: 0x" 
              << std::hex << cmd.MAGIC << std::endl;

    return 0;
}
