# Introduction (Linux Environment, GNU Toolchain, and C++)

PLACEHOLDER

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

C++ source code exists as human-readable text, and cannot be executed directly by the computer's processor (CPU). Instead, the source code must first be transformed into an executable program targeting the CPU's instruction set architecture (ISA). The GNU toolchain is a collection of development tools used to facilitate this transformation process.

For C++ development, the primary interface to this toolchain is g++, the C++ compiler driver. 
