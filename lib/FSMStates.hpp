#ifndef __FSMSTATES_HPP
#define __FSMSTATES_HPP

enum State {

    // this is the FSM's initial state, but as we will deterministically read
    // a '{' as the first non-whitespace character in any valid JSON file
    // this will not be encountered in practice and in only included for 
    // completion as the FSM will move to KEY_START immediately
    OBJECT_START = 0,

    // this states specifies that the closing brace of the currently processed
    // object has been read and the parsing is complete so control can be
    // passed upward again
    OBJECT_END = 1,

    // this state specifies that the opening brace of an object has been read
    // to we expect the quotes of the member's key to be read next
    KEY_START = 2,

    // this state specifies that we have successfully read a complete string
    // as a key and expect the key-value delimiter colon to be read next
    KEY_END = 3,

    // this state specifies that we read the delimiter and decide by the next
    // character that will be read if we encouter a simple string or a new
    // object as the value
    VALUE_START = 4,

    // this state specifies that we successfully read either a string or an object
    // and expect either a comma because there are more members of the current 
    // object or the closing brace in case it was the final one
    VALUE_END = 5

};

#endif // __FSMSTATES_HPP