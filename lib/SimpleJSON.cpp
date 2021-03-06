#include <SimpleJSON.hpp>
#include <stdexcept>
#include <FSMStates.hpp>
#include <sstream>

static bool _expected(char c, State state) {
    switch (state) {
        case KEY_START: {
            return c == '"';
        }
        case KEY_END: {
            return c == ':';
        }
        case VALUE_START: {
            return c == '{' || c == '"';
        }
        case VALUE_END: {
            return c == ',' || c == '}';
        }
        default: {return false; }
    }
    return false;
}

static char _read_char(std::istream &str) {
    if (str.eof()) {
        throw std::runtime_error("unexpected EOF encoutered");
    }
    char c;
    str.read(&c, 1);
    return c;
}

static char _get_next_character(std::istream &str, State state) {
    char c;
    do {
        c = _read_char(str);
    } while (c == ' ' || c == '\t' || c == '\n');
    return c;
}

static std::string _read_string(std::istream &str) {
    bool escaped = false;
    std::string s;
    while (str.good()) {
        char c = _read_char(str);
        if (escaped) {
            escaped = false;
        } else if (!escaped && c == '\\') {
            escaped = true;
            continue;
        } else if (!escaped && c == '"') {
            break;
        }
        s += c;
    }
    return s;
}

// This function parses a valid JSON object from the stream.
// It must be entered with BEGIN pointing to the next character after
// the opening braces.
JSONObject _parse(std::istream &str) {
    State state = KEY_START;
    // a buffer for keys
    std::string key;
    // the buffer object for values
    JSONObject value;
    // the currently parsed object returned at the end
    JSONObject obj;
    while (state != OBJECT_END) {
        // read the next non-whitespace character from the input and compare
        // it against out expectations (i.e. if the next character would occur in valid JSON)
        char c = _get_next_character(str, state);
        if (!_expected(c, state)) {
            throw std::runtime_error("invalid character encountered '" + std::string(&c, 1) + '\'');
        }
        switch (state) {
            case KEY_START: {
                key = _read_string(str);
                state = KEY_END;
                break;
            }
            case KEY_END: {
                state = VALUE_START;
                break;
            }
            case VALUE_START: {
                if (c == '"') {
                    value = _read_string(str);
                } else {
                    value = _parse(str);
                }
                if (obj.members().find(key) != obj.members().end()) {
                    throw std::runtime_error("duplicate key encoutered '" + key + '\'');
                }
                obj[key] = value;
                state = VALUE_END;
                break;
            }
            case VALUE_END: {
                if (c == ',') {
                    state = KEY_START;
                } else if (c == '}') {
                    state = OBJECT_END;
                }
                break;
            }
            default: {
                throw std::runtime_error("error");
            }
        }
    }
    return obj;
}

JSONObject SimpleJSON::parse(const std::string &str) {
    std::stringstream ss(str);
    return parse(ss);
}

JSONObject SimpleJSON::parse(std::istream &str) {
    char c;
    // check if we read all whitespace until we encounter the first opening brace
    do {
        c = _read_char(str);
        if (c != '{' && c != ' ' && c != '\t' && c != '\n') {
            throw std::runtime_error("invalid character encountered '" + std::string(&c, 1) + '\'');
        }
    } while (c != '{');
    return _parse(str);
}