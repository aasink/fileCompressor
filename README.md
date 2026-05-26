# Compressor

A fast, modular file compression and decompression tool written in **C++20**, supporting multiple algorithms including Run-Length Encoding (RLE), Huffman Coding, and Lempel–Ziv–Welch (LZW).

---

## Overview

Compresso provides a unified command-line interface for compressing and decompressing files using classical algorithms. It is designed with a clean, extensible architecture — adding a new compression algorithm is as simple as subclassing `Compressor` and registering it with the `Application` layer.

**Key features:**
- Three compression algorithms: RLE, Huffman, LZW
- Unified CLI for compression and decompression
- Modular design — easy to extend with new algorithms
- File I/O abstraction via `FileHandler`
- Algorithm correctness verified by a dedicated test suite

---

## Repository Structure

```
project/
├── include/                  # Header files
│   ├── app.h         # CLI orchestration and argument parsing
│   ├── compressor.h          # Abstract base class for all compressors
│   ├── RLEcompressor.h       # Run-Length Encoding implementation
│   ├── Huffmancompressor.h   # Huffman Coding implementation
│   ├── LZWcompressor.h       # Lempel–Ziv–Welch implementation
│   └── filehandler.h         # File read/write utilities
├── src/                      # Source files
│   ├── algorithms/
│   │   ├── RLEcompressor.cpp
│   │   ├── Huffmancompressor.cpp 
│   │   └── LZWcompressor.cpp
│   ├── app.cpp
│   ├── filehandler.cpp
│   └── main.cpp              # Entry point
├── tests/                    # Unit tests per algorithm
│   ├── test_rle.cpp
│   ├── test_huffman.cpp
│   └── test_lzw.cpp
├── data/                     # Sample input and output
│   ├── sample.txt
│   ├── sample.rle
│   └── output.txt
├── Makefile
└── README.md
```

---

## Build Instructions

### Prerequisites

- Clang or GCC with C++20 support (`clang++ --version` / `g++ --version`)
- GNU Make

### Build the main binary

```bash
make
```

This compiles all source files and produces the `main` executable in the project root.

### Build and run tests

```bash
make test
```

Compiles and runs all test files under `tests/`.

### Clean build artifacts

```bash
make clean
```

---

## Usage

```
./compressor <command> <input_file> --output <output_file> --algorithm <algorithm>
```

### Commands

| Command      | Description                        |
|--------------|------------------------------------|
| `compress`   | Compress the input file            |
| `decompress` | Decompress a previously compressed file |

### Algorithms

| Flag         | Algorithm                     |
|--------------|-------------------------------|
| `rle`        | Run-Length Encoding           |
| `huffman`    | Huffman Coding                |
| `lzw`        | Lempel–Ziv–Welch              |

### Examples

**Compress a file using Huffman coding:**
```bash
./compressor compress data/sample.txt --output data/sample.huff --algorithm huffman
```

**Decompress it back:**
```bash
./compressor decompress data/sample.huff --output data/output.txt --algorithm huffman
```

**Compress using RLE:**
```bash
./compressor compress data/sample.txt --output data/sample.rle --algorithm rle 
```

**Compress using LZW:**
```bash
./compressor compress data/sample.txt --output data/sample.lzw --algorithm lzw 
```

---

## Running Tests

Each algorithm has its own test file. After building with `make test`, results are printed to stdout. To run an individual test binary directly:

```bash
./tests/test_huffman
./tests/test_rle
./tests/test_lzw
```

---

## Roadmap

- [ ] **Benchmark mode** — compare compression ratios and speed across algorithms on the same file
- [ ] **Streaming support** — compress/decompress large files without loading them fully into memory
- [ ] **DEFLATE algorithm** — combine LZ77 and Huffman for higher compression ratios
- [ ] **Archive support** — compress multiple files into a single `.cmpz` archive
- [ ] **Progress bar** — real-time CLI progress indicator for large files
- [ ] **CMake support** — add `CMakeLists.txt` as an alternative build system
- [ ] **GUI frontend** — drag-and-drop desktop interface using Qt or Dear ImGui

---

## License

This project is licensed under the **MIT License**.

```
MIT License

Copyright (c) 2026

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```