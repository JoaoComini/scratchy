# scratchy
[![Build Status](https://github.com/joaocomini/scratchy/workflows/CI/badge.svg)](https://github.com/joaocomini/scratchy/actions) [![codecov](https://codecov.io/gh/JoaoComini/scratchy/branch/master/graph/badge.svg)](https://codecov.io/gh/JoaoComini/scratchy)

 Scratchy provides a simple API for serialization of C++ primitive types through bit scratching.
 It has two major classes `OutputBitStream` and `InputBitStream` whose are responsible for writing and reading the buffer.

 # OutputBitStream

This class is reponsible for writing primitive types in a buffer.

## Example
```cpp
#include "scratchy/scratchy.h"

int main ()
{
    // constructor receives the desired buffer size in bytes
    OutputBitStream out = new OuputBitStream(64);

    out->write<int>(999999);
    out->write<short>(9123);
    out->write<bool>(true);
    out->write<unsigned char>(102);
    out->write<float>(10.723f);

    // this call is mandatory, it's needed to flush all the bits to the buffer
    out->flush();

    // scratchy uses a 32-bit words buffer
    uint32_t* buffer = out->getBuffer();
}
```

# InputBitStream

This class is reponsible for reading primitive types from a buffer. We highly recommend that the buffer used be preaviously written by an 
`OutputBitStream`.

## Example
```cpp
#include "scratchy/scratchy.h"


int main ()
{
    OutputBitStream out = new OuputBitStream(8);

    out->write<int>(12);
    out->write<bool>(true);
    out->write<short>(9123);
    out->write<bool>(false);

    out->flush();

    uint32_t* buffer = out->getBuffer();

    InputBitStream in = new InputBitStream(8, buffer);

    assert(in->read<int>() == 12);
    assert(in->read<bool>());
    assert(in->read<short>() == 9123);
    assert(! in->read<bool>());
}
```

---

## Supported Types

These are all the types supported by this library:

```cpp
bool
char
unsigned char
short
unsigned short
int
unsigned int
float
```

# Install & Build

You you need this dependencies installed:

* g++
* cmake
* make
* git (if you would like to clone from this repo)

### Example install with git
```bash
$ git clone https://github.com/joaocomini/scratchy
$ cd scratchy
$ mkdir build && cd build
$ cmake ..
$ make
$ make install
```

### Example build with tests
```bash
$ cd scratchy
$ mkdir build && cd build
$ cmake -DBUILD_TESTING=ON ..
$ make
$ ./test_main
```