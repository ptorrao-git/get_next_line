# get_next_line

## Overview

The **get_next_line** project consists of implementing a function that reads a single line from a file descriptor (either a file or standard input). The bonus part extends this functionality by allowing multiple file descriptors to be handled simultaneously. The goal is to improve your understanding of file handling, memory management, and efficient code design in C.

## Files

- `get_next_line.c`: The main implementation of the `get_next_line()` function.
- `get_next_line.h`: The header file that contains function prototypes, macros, and necessary includes.
- `get_next_line_utils.c`: Helper functions that provide utilities like string manipulation, memory handling, etc.
  
## Functions

### `get_next_line`

```c
int get_next_line(int fd, char **line);
```

**Description**:  
This function reads a single line from the file descriptor `fd` and stores it in the string pointed to by `line`. The function returns:
- `1` if a line is successfully read,
- `0` if the end of the file (EOF) is reached,
- `-1` if there is an error.

- **Parameters**:
  - `fd`: The file descriptor from which to read. This could be any file or even `STDIN`.
  - `line`: A pointer to the string that will hold the read line. The caller should free the allocated memory after use.

- **Return Values**:
  - `1`: A line was successfully read.
  - `0`: EOF is reached.
  - `-1`: An error occurred.

### Bonus: Multiple File Descriptors

For the bonus part, you need to handle multiple file descriptors at once, meaning that each call to `get_next_line` with a different file descriptor should return the correct line for that specific file descriptor, without interfering with others.

This is achieved by using static variables (or structures, depending on the implementation) to track the state of each file descriptor individually.

---

## How to compile

To compile the project, simply use the provided `Makefile`. It will generate the necessary object files and create the executable.

```bash
make
```

You can also use the following commands to clean up your project:
- `make clean`: Removes the compiled object files.
- `make fclean`: Cleans up the object files and the executable.
- `make re`: Recompiles the entire project.

---

## Usage

The `get_next_line` function reads one line at a time from the provided file descriptor. Here is an example of how you might use it:

```c
#include "get_next_line.h"
#include <fcntl.h>

int main(void)
{
    int fd = open("test_file.txt", O_RDONLY);
    char *line;
    
    if (fd == -1)
        return 1;

    // Read lines from the file
    while (get_next_line(fd, &line) == 1)
    {
        printf("Line: %s\n", line);
        free(line);  // Free the memory allocated for the line
    }
    
    close(fd);
    return 0;
}
```

In this example, `get_next_line` reads each line from `test_file.txt` and prints it. The program continues until EOF is reached.

### Bonus: Handling Multiple File Descriptors

The bonus part involves handling multiple file descriptors. Here’s an example of reading from two different files simultaneously:

```c
#include "get_next_line.h"
#include <fcntl.h>

int main(void)
{
    int fd1 = open("file1.txt", O_RDONLY);
    int fd2 = open("file2.txt", O_RDONLY);
    char *line1;
    char *line2;

    if (fd1 == -1 || fd2 == -1)
        return 1;

    // Read lines from both file descriptors
    while (get_next_line(fd1, &line1) == 1 || get_next_line(fd2, &line2) == 1)
    {
        if (line1) {
            printf("file1: %s\n", line1);
            free(line1);
        }
        if (line2) {
            printf("file2: %s\n", line2);
            free(line2);
        }
    }

    close(fd1);
    close(fd2);
    return 0;
}
```

In this example, `get_next_line` is called twice, once for each file descriptor (`fd1` and `fd2`). The function will read from both files and print each line as it is read, independently managing the state of both file descriptors.

---

## Edge Cases

- **Empty lines**: Handle empty lines that contain no characters before the newline character.
- **Multiple newlines**: Handle cases where multiple newline characters appear consecutively in a file.
- **File with no newline at EOF**: Ensure that a file that does not end with a newline character is handled correctly.
- **Large files**: Ensure the program efficiently handles large files by managing memory correctly and not reading too much into memory at once.

### Error Handling

- **Invalid file descriptor**: If an invalid file descriptor is passed, `get_next_line` should return `-1`.
- **Memory allocation errors**: Always check if memory allocation (e.g., with `malloc`) was successful.
- **EOF without a newline**: Handle files that end without a newline, ensuring that the last part of the file is returned correctly.

---

## Testing

You can test the functionality by running the example program or by writing your own test cases. Ensure that your implementation correctly handles:
- Reading from one or more files.
- Handling different edge cases such as EOF, empty lines, and multiple newlines.
- Proper memory management (allocating and freeing memory).

To test the bonus functionality with multiple file descriptors, ensure that each file descriptor reads independently and that there are no side effects between them.
