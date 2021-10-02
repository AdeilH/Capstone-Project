# CPPND: Capstone MockServer for test data

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

Working on a mockserver that publishes data based on the requirement of the client. 


## Working So far

1. Client Can Receive Proper Data when it sends One.
2. Client recieves unauthorized string.
3. Server Can Send Data and Error.
4. Internal logger implemented. 

## Future Work

1. Multiple Client
2. Add More Functionalities specially reading server data from a file or database. 
3. Multithreading Client Environment when Accepting Connections. 

## Rubric Points Addressed 

### LOOPS, FUNCTIONS, IO
1. Functions and Control Structures
2. Writes to a file

### Object Oriented Programming

1. Uses OOP technique
2. Appropriate Access Specifiers
3. Uses Member Initialization List in MockServer.cpp
4. Abstract Class
5. Templatized Function in Logger


### Memory Management

1. Destructors.
2. References in Functions. 

### Concurrency 

1. Mutex is used in Logger.


### Future Goals.

1. Multithreading for Clients



## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Update submodules git submodule update --init
3. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./Server`. to start the server and then start Client by `.\Client`