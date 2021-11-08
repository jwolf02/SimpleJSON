# SimpleJSON
Simple JSON parser that provided two functions SimpleJSON::parse(x) in the header lib/SimpleJSON.hpp.  
x can be either a std::string or any kind of std::istream where a string is simply converted to  
a std::stringstream before being passed to the stream function.  

## Build and Test
The project is build on a CMake build system without fancy stuff. Simply run cmake .. to create the  
build scripts. There are two targets one building the static library. The other builds a test  
executable that run several test cases of various kind to ensure the library functions are correct.  

## Implementation
The algorithm has been implemented as a recursive finite state machine. There are 5 distictive states  
the FSM can encounter while parsing any type of input. So characters are read sequencially without  
the need to create an AST or do a two way parsing or buffering.  
Depending on the input byte read the algorithm decides how to proceed with it. The only really  
interesting states are when reading multi byte key strings, value strings or value objects.  
String are simply read bytewise until an unescaped " is read which marks the end of the string  
which makes the FSM move to the next state.  
In case the opening brace of a member object is read the routine calls itself recursively which  
causes the next object being read and parsed from the stream. Control is passed back up when  
either the closing brace of the new object is read or an error is encoutered.