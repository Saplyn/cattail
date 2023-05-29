# [NOTICE] Repo Archived

**This is a repo for the Assignment of the Object-Oriented Technology course, and have already submitted. Archive because no further commit will take place.**

# Cattail

## Intro

```txt
     cattail, version 1.0.6
  The ANU-SDUW C++ OOP Assignment
 _________________________________
|                                 |
|    __  __  _|_ _|_  __  - |     |
|   /   /  |  |   |  /  | | |     |
|   \__ \_/|  |/  |/ \_/| | |/    |
|_________________________________|
```

## Build & Run

```bash
# change directory to where the RAEDME.md is stored
$ cd cattail/
# run make to compile
$ make
# execute the binary file
$ ./cattail
```

## Usage

Just like a normal interpreter, if you don't know how, type `help` (after launch).

```bash
cattail$ help
cattail, version 1.0.6
ANU-SDUW C++ OOP Assignment

set  - Set program status.
new  - Instantiate new shape object,
       store it in temporary memory.
tmp  - View temporary memory object.
stk  - Perform stack operation.
exit - Exit the program.

cattail$ _
```

## File Structure

```txt
cattail/                      |  Parent directory
├── README.md                 |  README file, Description & Usage
├── SampleOutput.txt          |  Sample output
├── auto.lyn                  |  Auto test input sample
├── makefile                  |  Makefile for `make`
├── include/                  |  Header file directory
│   ├── command/              |    Header for command handle
│   │   ├── Command.h         |  
│   │   ├── CommandTree.h     |  
│   │   └── Message.h         |  
│   ├── object/               |    Header for object implementation
│   │   ├── Circle.h          |  
│   │   ├── Rectangle.h       |  
│   │   ├── Shape.h           |  
│   │   └── Triangle.h        |  
│   ├── struct/               |    Header for data structure
│   │   ├── Stack.h           |  
│   │   └── StackException.h  |  
│   └── utility/              |    Header for others
│       ├── LynType.h         |  
│       ├── ProgramState.h    |  
│       └── ValidString.h     |  
└── src/                      |  Main source file directory
    └── main.cpp              |  
```

## Auto Test

```bash
$ ./cattail <auto.lyn &>out.txt
```