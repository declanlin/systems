# bininspect Design Document

## Overview

**Purpose**: `bininspect` is a simple command-line utility that reads the raw bytes of a file and displays those bytes in human-readable numerical and character representations.

## Data

All data in computers — whether it's text, image, sound, video, code, or memory addresses — is stored as a binary sequence of 0s and 1s. However, files and common software interfaces generally expose this data in byte-sized units. `bininspect` therefore treats a file as a sequence of raw bytes and does not initially assign any higher-level meaning to those bytes.

Binary representations quickly become lengthy as the amount of data increases. Numeral systems such as octal and hexadecimal provide more compact representations of the same values. Because their bases are powers of two, each octal digit corresponds to exactly 3 bits and each hexadecimal digit corresponds to exactly 4 bits, making conversion to and from binary straightforward.

One common misconception, is that a binary file looks something like this:

file.txt:
    010111010101011101000

In the example above, each visible 0 and 1 is itself a character encoded as a byte. Under ASCII:

- '0': '0' == 48 == 0011 0000
- '1': '1' == 49 == 0011 0001

## Bytes

A byte consists of 8 bits and can therefore encode $2^8$ distinct bit patterns. If interpreted as an unsigned integer, these correspond to values in [0, 255].

A byte's value can be represented using different numeral systems:
```
Binary (base-2): 0100 0001
Octal (base-8): 101
Decimal (base-10): 65
Hexadecimal (base-16): 41
```

Each representation describes the same underlying byte value. Changing the representation does not modify the byte itself.

## Program

The `bininspect` program simply reads bytes from a file, and displays them in the requested representation, as in the below loop:

```
for each byte in file:   
    display byte in requested representation
```

### Data Model

`bininspect` treats input files as sequences of bytes. A byte consists of 8 bits and, when interpreted as an unsigned integer, has a value in the range [0, 255].

Unless explicitly stated otherwise, bininspect does not interpret sequences of bytes as multi-byte integers or higher-level data structures. Therefore, endianness is out of scope for this utility.

### Modes of Operation

`bininspect` supports two modes of operation:

- **Forward mode** reads raw bytes from a file and produces a textual representation of those byte values.
- **Reverse mode** reads textual representations of byte values and produces the corresponding raw bytes.

Forward mode is the default.

### Supported Representations

The current implementation supports hexadecimal and octal representations.

Binary and decimal are used throughout the documentation for explanatory purposes but are not required output modes in the initial implementation.

### Hexadecimal
- Each byte is represented using exactly two hexadecimal digits in [00, FF].
- Hexadecimal input is treated case-insensitively.
- Hexadecimal output uses uppercase letters A through F.

### Octal
- Each byte is represented using exactly three octal digits.
- Valid octal byte values range from [000, 377]. Although three unrestricted octal digits can represent values through 777, values greater than 377 exceed the maximum value representable by a single byte.
- In reverse octal mode, each value must contain exactly three octal digits and represent a value in [000, 377].

### Forward Mode

Forward mode accepts any readable file as raw input.

The contents of the file are read as bytes. For each byte, bininspect produces the requested textual representation.

For example, suppose a file contains three raw bytes with the following values:

```
0100 0001
0100 0010
0100 0011
```

Hexadecimal output is:

`41 42 43`

Octal output is:

`101 102 103`

### Reverse Mode

Reverse mode accepts textual hexadecimal or octal byte values and reconstructs the corresponding raw bytes.

For example, hexadecimal input:

`41 42 43`

produces three raw bytes:

```
0100 0001
0100 0010
0100 0011
```

Likewise, octal input:

`101 102 103`

produces the same three raw bytes:

```
0100 0001
0100 0010
0100 0011
```

The general flow for parsing the textual input is as follows:

```
Read a token
   ↓
Validate the token
   ↓
Parse numeric value
   ↓
Verify that the value is in [0, 255]
   ↓
Emit the byte
```

### Whitespace

Whitespace is ignored across all input files. This includes tabs, spaces, newlines, and carriage returns.

### Invalid Input

Forward mode accepts arbitrary byte values, so the contents of the input file cannot be invalid merely because of their byte values.

Reverse mode requires validation because its input is textual.

Hexadecimal input is invalid if a value:
- does not consist of exactly two hexadecimal digits
- contains characters outside 0-9, A-F, or a-f
- cannot represent a single byte

Octal input is invalid if a value:
- does not consist of exactly three octal digits
- contains characters outside 0-7
- represents a value greater than 377

On invalid input, bininspect terminates with a nonzero exit status and reports the error to stderr.

### Padding

Forward mode does not perform bit padding.

Files are already exposed to the program as sequences of complete bytes, so there is no concept of encountering a partial byte at the end of a normal input file.

Likewise, reverse mode operates on complete textual byte values:
- Plain Text
- Hexadecimal: exactly 2 digits per byte
- Octal: exactly 3 digits per byte

Incomplete values are treated as invalid input rather than being implicitly padded.
