# Coderunner

## Overview

Coderunner is a command line tool for compiling and running code. The input is read from an input file and the output is redirected to an output file. Coderunner can be installed on Linux systems and is suitable for competitive programmers. Coderunner supports C++, Java and Python.

## Compiler / Interpreter used

| Language | Compiler / Interpreter |
| --- | --- |
| C++ | GNU G++ |
| Java | Default JDK |
| Python | Python 3.9.6 |

## Installation

To install coderunner, click [here](https://github.com/dhruva-shashi/coderunner/raw/master/coderunner.deb) to download the coderunner Debian file and perform the following steps.

### Steps

1. Navigate to `~/Downloads` to find the downloaded Debian package.
2. Install coderunner using the command `sudo dpkg -i coderunner.deb`.
3. Run the command `coderunner --version` to verify installation.

## How to Use

- Create a file for input and name it `input.txt`.
- Create a file for output and name it `output.txt`.
- For executing C++ code, write the code in a file named `codefile.cpp` and run the command `coderunner` or `coderunner -l cpp`.
- For executing Java code, write the code in a file named `codefile.java` and run the command `coderunner -l java`.
- For executing Python code, write the code in a file named `codefile.python` and run the command `coderunner -l python`.
- The input will be read from `input.txt` and the output will be written to `output.txt`.
- Note that the three files, input file, output file and the code file must be present in the same directory.
