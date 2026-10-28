# Introduction (Linux Environment, GNU Toolchain, and C++)

This document serves as a light introduction to the development and building of C++ programs in a Linux environment.

## Linux Environment

This portion of the introduction is meant to describe Linux as a software development environment,
as opposed to exploring the Linux kernel or operating system internals.

### Filesystem

When developing programs, developers need a place to store their data. This includes program source code, configuration files, build artifacts, and any information the program needs to read or write.

The Linux filesystem provides a hierarchical structure for storing and organizing these resources, allowing programs to create, modify, and remove files and directories.

One such program commonly used to interact with the filesystem is a shell, like Bash, which provides the developer with a command-line environment for navigating the filesystem, manipulating files and directories, and executing other programs.

Examples of commonly used shell commands and command-line utilities and their use cases are shown below:

- pwd - prints the path of the current working directory.
- ls - lists the contents of a directory.
- cd - changes the shell's current working directory.
- mkdir - creates directories.
- touch - creates an empty file if one does not exist, or updates an existing file's timestamps.
- cp - copies files or directories.
- mv - moves or renames files and directories.
- rm - removes files or directories.
- cat - writes the contents of one or more files to standard output.
- less - interactively views file contents one screen at a time.
- head - displays the beginning of a file.
- tail - displays the end of a file.
- file - examines a file and reports its apparent type.
- stat - displays filesystem metadata about a file or directory.
- find - searches a directory hierarchy for files and directories matching specified criteria.

Ultimately, the filesystem is the persistent workspace in which the software development process takes place.

## GNU Toolchain

C++ source code exists as human-readable text, and cannot be executed directly by the computer's processor (CPU). Instead, the source code must first be transformed into an executable program targeting the CPU's instruction set architecture (ISA), amongst other system conventions. The GNU toolchain is a collection of development tools used to facilitate this transformation process.

For C++ development, the primary interface to this toolchain is g++, the C++ compiler driver. g++ itself does not perform the work required to transform the code, rather it orchestrates a pipeline of specialized programs, each responsible for one stage of the transformation:

1. **Compiler proper (`cc1plus`)**: preprocesses the source, parses it, optimizes it, and emits assembly text for the target architecture
2. **Assembler (`as`)**: translates that assembly into a relocatable object file containing machine code and symbol information
3. **Linker (`ld`, invoked via `collect2`)**: combines object files and libraries, resolves symbols between them, and produces the final executable

From the user's perspective this appears as a single command, but the driver inspects its inputs and flags to decide which stages to run. For example, `-S` stops after compilation, `-c` stops after assembly, and passing an existing `.o` file skips directly to linking. The driver also supplies details the user would otherwise have to specify manually, such as the C++ standard library and C runtime startup files at link time.

You can observe this orchestration directly by running `g++ -v foo.cpp`, which prints each underlying command as it is invoked.

Various other flags exist for configuring orchestration and transformation behavior:

- -Wall: enable a broad set of common warnings
- -Wextra: enable additional warnings beyond -Wall
- -Wpedantic: warn on anything that violates strict ISO C++
- -Werror: treat all warnings as errors
- -Wshadow: warn when a variable shadows another in an outer scope
- -Wconversion: warn on implicit conversions that may change a value
- -Wsign-conversion: warn on implicit signed/unsigned conversions
- -Wold-style-cast: warn on C-style casts like `(int)x`
- -Wnull-dereference: warn when code may dereference a null pointer
- -Wformat=2: stricter checking of printf-style format strings
- -std=c++20: compile using the C++20 standard
- -O0: no optimization, fastest compile, best for debugging
- -O1: basic optimizations
- -O2: standard optimization level for most release builds
- -O3: aggressive optimization, may increase code size
- -Os: optimize for smaller code size
- -g: include debug symbols for gdb/lldb
- -c: compile and assemble only, produce a .o file, don't link
- -S: stop after compilation, output assembly (.s)
- -E: stop after preprocessing, output expanded source
- -o: set the output file name
- -v: verbose, print each underlying command the driver runs
- -I: add a directory to the header search path
- -L: add a directory to the library search path
- -l: link against a library (e.g. `-lm` for libm)
- -D: define a preprocessor macro (e.g. `-DDEBUG`)
- -fsanitize=address: detect memory errors like overflows and use-after-free
- -fsanitize=undefined: detect undefined behavior at runtime
- -fno-exceptions: disable C++ exception support
- -fno-rtti: disable runtime type information (typeid, dynamic_cast)
- -fno-omit-frame-pointer: keep frame pointers for better stack traces
- -fPIC: generate position-independent code, needed for shared libraries
- -shared: build a shared library (.so)
- -static: link libraries statically into the executable
- -pthread: enable POSIX threads support at compile and link time
- -march=native: optimize for the CPU you're compiling on
- -MMD: generate dependency files (.d) for Makefiles, skipping system headers
- -save-temps: keep intermediate files (.i, .s, .o) after compiling

## C++

C++ is a compiled, statically-typed, general-purpose language built on top of C, with additional abstraction mechanisms, including classes, templates, references, namespaces, etc. However, C++ is not a total superset of C. In fact, valid C can fail to compile as C++, or worse, compile and silently mean something different.

Some of the major design goals of C++ include "zero-overhead" abstractions, i.e., you don't pay for what you don't use, and what you do use, you couldn't hand-code any better.

Today, C++ is used in applications requiring high-speed performance, low-level hardware control, and efficient memory management. Such application domains include:

- Game engines
- Browsers
- Databases
- Trading systems
- Embedded systems
- Graphics
- Machine learning infrastructure