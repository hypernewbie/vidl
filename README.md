# Vidl - Simple IDL generator for C++

[![Download vidl.py](https://img.shields.io/badge/Download-vidl.py-blue?style=for-the-badge&logo=python)](https://raw.githubusercontent.com/hypernewbie/vidl/refs/heads/main/vidl.py)

[![CI](https://github.com/hypernewbie/vidl/actions/workflows/ci.yml/badge.svg)](https://github.com/hypernewbie/vidl/actions/workflows/ci.yml)

Vidl is a lightweight Python script that parses C++ header files for `// VIDL_GENERATE` comments and generates corresponding C++ structs and a command handler. It is useful for creating type-safe command buffers or RPC mechanisms.

> NOTE: Vidl is vide coded, without too much code oversight. Intended as a throwaway tool of sorts. Use at your own risk.

## What does Vidl do?

Vidl turns this:
```cpp
// VIDL_GENERATE
uint32_t FunctionTest1(
    uint32_t x,
    uint32_t y,
    bool a,
    TestEnum enum
);
```

into:

```cpp
struct VIDL_FunctionTest1
{
    static constexpr uint64_t kMagic = 0x68CE8796;
    uint64_t MAGIC = kMagic;
    uint32_t x;
    uint32_t y;
    bool a;
    TestEnum enum_;

    VIDL_FunctionTest1() = default;

    VIDL_FunctionTest1(uint32_t _x, uint32_t _y, bool _a, TestEnum _enum_)
        : x(_x), y(_y), a(_a), enum_(_enum_) {}
};
```

along with a corresponding handler:

```cpp
struct VIDLHandler
{
    virtual void Handle_FunctionTest1( VIDL_FunctionTest1* cmd ) { (void) cmd; };

    virtual void HandleCmd( void* cmd )
    {
        uint64_t magic = *(uint64_t*)cmd;
        switch ( magic )
        {
        case 0x68CE8796:
            Handle_FunctionTest1( (VIDL_FunctionTest1*) cmd );
            break;
        }
    }
};
```

## Usage

You can use `vidl.py` directly to generate code from a source file.

```bash
python vidl.py tests/test.cpp
python vidl.py tests/test.cpp output.h
```

## Prerequisites For Building

- Python 3
- CMake (3.10 or higher)
- A C++ Compiler (MSVC, GCC, Clang)

## Running Unit Tests

To verify that the `vidl.py` generator is working correctly, you can run the provided Python test suite:

```bash
# Run tests using the unittest module
python test.py
```

## Building with CMake

The project includes a `CMakeLists.txt` that automates the generation and compilation process.

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

This command will:
- Locate the Python interpreter.
- Run `vidl.py` to generate `vidl_generated.h` from `tests/test.cpp`.
- Compile `main.cpp` (which includes the generated header).
- Link everything into an executable named `MyGame` and a test suite named `VidlTest`.

**Run the executable:**

On Windows:
```bash
.\Debug\MyGame.exe
```

On Linux/macOS:
```bash
./MyGame
```

**Run the C++ Integration Tests:**

The CMake build also generates a `VidlTest` executable that verifies the runtime behavior of the generated code.

On Windows:
```bash
.\Debug\VidlTest.exe
```

On Linux/macOS:
```bash
./VidlTest
```

Expected output for `MyGame`:

```

Successfully instantiated VIDL_FunctionTest0 with magic: 0x610d85fb

```



Expected output for `VidlTest`:

```

Running C++ Integration Tests...

[Test 1] Constructors

[Test 2] Polymorphism & Dispatch

Handle_FunctionTest0 called with x=10

[Test 3] Pointers

Handle_FunctionTest2 called with pointer checking

[Test 4] Unique Magic Numbers

Magic 0: 610d85fb

Magic 1: 68ce8796

All C++ Tests Passed!

```
