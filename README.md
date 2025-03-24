# PA5 File Tester

This project implements a command-line file tester utility in C. The program allows users to:

- Read specified number of bytes from a file
- Write text to a file
- Seek to different positions within a file

## Features

- Dynamic memory allocation for unlimited input sizes
- Proper file I/O with buffer flushing for reliable writes
- Robust handling of EOF (Ctrl+D) signals
- Support for all standard file seeking operations (SEEK_SET, SEEK_CUR, SEEK_END)

## Implementation Details

The implementation focuses on correct handling of file operations while maintaining compatibility with the expected behavior defined in the test suite.

For a complete reflection on the implementation process, challenges faced, and lessons learned, see the [Project Reflection](writeup.md).

## Building and Running

Compile the program:

```bash
gcc -o pa5test src/pa5test.c
```

Run the program with a file:

```bash
./pa5test <filename>
```

## Testing

A comprehensive Python test suite using `pexpect` is provided to verify the program's behavior:

```bash
./test_pa5.py
```