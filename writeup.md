# PA5 File Tester Project Reflection

The approach I took for this project involved first exploring the test script to understand the expected behavior, then implementing the C program to match it precisely. Creating a test suite with Python `pexpect` made a huge difference. Automating all interactions and made verification systematic rather than guesswork.

## Technical Implementation Details

The input handling system I implemented uses dynamic memory allocation to handle arbitrary input sizes. Instead of using a fixed buffer size which would limit the length of user input, I started with a small initial allocation and doubled the capacity whenever needed.

This approach efficiently handles inputs of any length without wasting memory on oversized fixed buffers. It's particularly useful for a file utility where you might need to write varying amounts of text.

Although it could be improved given the target, as the file will never be longer that it started, so I could start with the full file worth of allocated memory for the input string if it is small enough to reduce reallocations.

## Challenges Faced

The most interesting challenges came from subtle details:

**Ctrl+D handling** - Properly detecting and handling EOF at various points in the program was tricky. I implemented proper checks for all input functions and created a `shutdown()` function to ensure clean termination.

**Exit status detection** - One particularly frustrating issue was the test failing because it couldn't detect a proper exit status when Ctrl+D was pressed. Adding a newline and explicit flushing of stdout before exiting solved this problem.

**File writing reliability** - Getting the file writing to work consistently required extra attention. I found that simply calling fputs wasn't enough - I needed to call fseek before writing, and explicitly flush the file buffer with fflush afterward to ensure data was actually written to disk:

```c
// prepare file for writing
fseek(file, 0, SEEK_CUR);
// Write the string to the file
int res = fputs(input, file);
// Ensure data is written to disk
fflush(file);
```

Without the fseek, the file might still be in read mode and not ready to write, and without fflush, the data often remains in memory buffers rather than being written to the file. This was particularly annoying as I couldn't debug this and it required a bit of searching to find these intricacies of the fputs function.

The debugging process was interesting - I added detailed debug output to the test to see the exact interactions, which made it much easier to spot discrepancies.

## Thoughts on the Assignment

One thing that could improve this assignment would be including a simple test script alongside the reference implementation. This would make the expected behavior clearer from the start. While reverse engineering is a valuable skill, providing a basic test would help focus more on the file I/O concepts rather than figuring out what the prompts should be.

I learned that terminal I/O has many nuances, especially around signals like EOF. Proper flushing and buffer handling are essential for robust programs. I also gained appreciation for automated testing - having a test suite dramatically speeds up development by immediately identifying issues.
