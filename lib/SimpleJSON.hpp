#ifndef __SIMPLEJSON_HPP
#define __SIMPLEJSON_HPP

#include <map>
#include <string>
#include <JSONObject.hpp>
#include <istream>

// This is a simple implementation of a JSON parser
// that can only process string members and objects.
// Its is based on a FSM internally which's states are specified in
// the header FSMStates and uses a recursive algorithm to parse
// a JSON string or input from any kind of stream
namespace SimpleJSON {

    JSONObject parse(const std::string &str);

    JSONObject parse(std::istream &str);

}

#endif // __SIMPLEJSON_HPP
