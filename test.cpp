#include <iostream>
#include <cassert>
#include <cstring>
#include <vector>
#include <map>
#include <string>

// Support Types required by the generated header
// These mock the types found in the original source
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

// Include generated header
#include "vidl_generated.h"

// Mock Handler
class TestHandler : public VIDLHandler
{
public:
    bool function0_called = false;
    bool function1_called = false;
    bool function2_called = false;
    
    // override Handle_FunctionTest0
    void Handle_FunctionTest0(VIDL_FunctionTest0* cmd) override
    {
        function0_called = true;
        std::cout << "Handle_FunctionTest0 called with x=" << cmd->x << std::endl;
        assert(cmd->x == 10);
        assert(cmd->y == 20);
        assert(cmd->a == true);
        assert(cmd->enum_ == TEST_ENUM_A);
    }

    void Handle_FunctionTest1(VIDL_FunctionTest1* cmd) override
    {
        function1_called = true;
    }

    void Handle_FunctionTest2(VIDL_FunctionTest2* cmd) override
    {
        function2_called = true;
        std::cout << "Handle_FunctionTest2 called with pointer checking" << std::endl;
        assert(cmd->x != nullptr);
        assert(*cmd->x == 999);
        assert(cmd->ptr != nullptr);
        assert(cmd->ptr->a == 123);
    }
};

int main()
{
    std::cout << "Running C++ Integration Tests..." << std::endl;

    // Test 1: Constructors
    {
        std::cout << "[Test 1] Constructors" << std::endl;
        VIDL_FunctionTest0 cmd(10, 20, true, TEST_ENUM_A);
        assert(cmd.x == 10);
        assert(cmd.y == 20);
        assert(cmd.a == true);
        assert(cmd.enum_ == TEST_ENUM_A);
        assert(cmd.MAGIC == VIDL_FunctionTest0::kMagic);
    }

    // Test 2: Polymorphism
    {
        std::cout << "[Test 2] Polymorphism & Dispatch" << std::endl;
        TestHandler handler;
        VIDL_FunctionTest0 cmd(10, 20, true, TEST_ENUM_A);
        
        // Dispatch
        handler.HandleCmd(&cmd);
        
        assert(handler.function0_called == true);
        assert(handler.function1_called == false);
    }

    // Test 3: Pointer/Complex Types
    {
        std::cout << "[Test 3] Pointers" << std::endl;
        TestHandler handler;
        
        uint32_t val = 999;
        TestStruct ts;
        ts.a = 123;
        
        VIDL_FunctionTest2 cmd(&val, &ts);
        
        handler.HandleCmd(&cmd);
        assert(handler.function2_called == true);
    }

    // Test 4: Magic Numbers
    {
        std::cout << "[Test 4] Unique Magic Numbers" << std::endl;
        assert(VIDL_FunctionTest0::kMagic != VIDL_FunctionTest1::kMagic);
        assert(VIDL_FunctionTest0::kMagic != VIDL_FunctionTest2::kMagic);
        std::cout << "Magic 0: " << std::hex << VIDL_FunctionTest0::kMagic << std::endl;
        std::cout << "Magic 1: " << std::hex << VIDL_FunctionTest1::kMagic << std::endl;
    }

    std::cout << "All C++ Tests Passed!" << std::endl;
    return 0;
}
