Current method to running
~to run `clear && g++ main.cpp` (clear && can be omited)~
To run will need have `cmake` install with at least version 3.10
  - for masOS can use `brew install cmake`

To Run:
  - from the parent dir run `cmake --build .`

  - for the unitTest run the `unitTest` exacutable in `./bin/`
    - `./bin/unitTest` or `./unitTest` when in bin 
  - for the running main do run the `MODELS_LIB` in `./bin/`
    - `./bin/MODELS_LIB` or `./MODELS_LIB` when in bin


attempted change to fail try 2
No unit test for unit test libray have been implemented yet


When to test for memory leaks some options are:
 - valgrind - for linux systems
 - leaks - for macOS from XCode
   use: `leaks --atExit --list -- EXACUTABLE`

