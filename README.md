# Coderunner

## Overview

Coderunner is a tool used by competitive programmers to compile and run their code. The latest version provides a UI interface for users to set paths to input, output and code files and also provides flexibility for users to set the time limit for code execution. Coderunner can be installed on Linux systems and supports C++, Java and Python.

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
4. Run the command `coderunner --install` to install the UI application.

## UI Elements

| UI Element | Type | Description |
| --- | --- | --- |
| Run | Button | Runs the code written in the path provided for the code file, and reads the input from the path provided for the input file, and writes the output to the path provided for the output file. |
| Resize | Button | Enlarges the window and allows the user to edit the paths for the files, execution time limit and the compiler to be used. |
| Path to code file | Textbox | Path for the code file must be provided. | 
| Path to input file | Textbox | Path for the input file must be provided. |
| Path to output file | Textbox | Path for the output file must be provided. |
| Time in seconds | Textbox | Execution time limit (in seconds) must be provided. |
| Select compiler | Drop down list | Select the desired compiler. |

![Screenshot from 2023-03-30 19-38-23](https://user-images.githubusercontent.com/63914756/228916065-43ad839b-9be7-48ff-9e83-188d3edbaf95.png)
![Screenshot from 2023-03-30 19-50-07](https://user-images.githubusercontent.com/63914756/228916086-4f9f1703-7295-4844-8b5c-1c246f5471d3.png)

## How to use

- Coderunner can be used on Linux systems.
- Coderunner can be started by running the command `coderunner` in the terminal.
- The paths provided in the textbox for the code, input and output files may either be absolute paths or relative paths.
- The execution time limit must have a value between 1 and 9 seconds.
