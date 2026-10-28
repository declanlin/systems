# bininspect Design Document

## Overview

**Purpose**: `bininspect` is a simple command-line utility used to view and analyze raw binary data by translating it into human-readable formats like hexadecimal, octal, or ASCII text. Its inspiration draws from similar existing tools like `od`, `xxd`, and `hexdump`, but truth be told, this is moreso a primer for me to get used to writing C++.

**Intended users/use cases**: `bininspect`, like other binary analysis tools, are typically used by professionals working at the lowest layers of computing, where software directly touches hardware, storage, and networking. Example use cases are listed below:

- Debugging hidden text characters
- Reverse engineering a binary to reveal source code, patterns, headers, etc.
- Analyzing network packets
- Verifying cryptographic hashes and file integrity

## Conventions

### Modes of Operation

The primary modes of operation are:
1. Forward mode - binary data is ingested and transformed into a target format
2. Reverse mode - formatted data is ingested and transformed into its equivalent binary format

### Forward Mode

- The only valid characters in the input file are 0s and 1s. **Binary** data is ingested in forward mode.
- All whitespace is ignored. This includes spaces, tabs, carriage returns, and newlines.
- All invalid, non-whitespace characters generate an error, reported with its position.
- Bits are orderedfrom left to right with the most significant bit first, and the least significant bit last. The first 8 bits form byte 0, the next 8 bits form byte 1, and so on. For example, 0100 0001 == 65 (decimal) == 'A' (ASCII), if we interpret each byte as an ASCII character that is.
- Endianness is out of scope. There is no interpretation of multi-byte values.

### Padding

- If the number of bits in the input file is not aligned with the specific line width, the default behavior of `bitinspect` is to pad the right side with zeroes, and warn the caller on `stderr`.

### Output Layout

- Line width is 16 bytes by default.
- Byte formats are displayed as follows:
    - Hexadecimal (hex): 16 values; each digit holds 4 bits; 1 byte = 8 bits = 2 hex digits
    - Octal: 8 values; each digit holds 3 bits; since 2 digits reach a max of 77 in octal, we need at least 3 octal digits to cover the range for a byte ([0, 255]). However, this gives for 9 bits in the result, and a byte is only 8 bits. We drop the most significant bit, resulting in the leading octal byte being (0)11, or 3 in decimal. So we end up with a max octal value of 377, or 255 in decimal.
- One space between bytes, with a larger space between 8th bytes.
- For ASCII, bytes 0x20 (SP) to 0x7E (~) appear as themselves, while all others appear as '.'.