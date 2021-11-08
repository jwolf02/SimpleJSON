#include <SimpleJSON.hpp>
#include <stdexcept>

#define OBJ_START   0
#define OBJ_END     1
#define KEY_START   2
#define KEY_END     3
#define VALUE_START 4
#define VALUE_END   5

typedef const char*   Iterator;

static bool _expected(char c, int state) {
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
    }
}

static char _get_next_character(Iterator &begin, Iterator &end, int state) {
    while (begin != end && (*begin == ' ' || *begin == '\t' || *begin == '\n')) {
        begin++;
    }
    if (begin == end) {
        throw std::runtime_error("unexpected end of file");
    }
    char c = *begin;
    begin++;
    return c;
}

static std::string _read_string(Iterator &begin, Iterator &end) {
    bool escaped = false;
    std::string str;
    while (begin != end && (*begin != '"' || !escaped)) {
        char c = *begin;
        begin++;
        if (escaped) {
            escaped = false;
        } else if (!escaped && c == '\'') {
            escaped = true;
            continue;
        }
        str += c;
    }
    return str;
}

// This function parses a valid JSON object from the stream.
// It must be entered with BEGIN pointing to the next character after
// the opening braces.
JSONObj _parse(Iterator &begin, Iterator &end) {
    int state = KEY_START;
    std::string key;
    JSONObj value;
    JSONObj obj;
    while (state != OBJ_END) {
        char c = _get_next_character(begin, end, state);
        if (!_expected(c, state)) {
            throw std::runtime_error("invalid token encountered '" + std::to_string(c) + '\'');
        }
        switch (state) {
            case KEY_START: {
                key = _read_string(begin, end);
                state = KEY_END;
                break;
            }
            case KEY_END: {
                state = VALUE_START;
                break;
            }
            case VALUE_START: {
                if (c == '"') {
                    value = _read_string(begin, end);
                } else {
                    value = _parse(begin, end);
                }
                obj[key] = value;
                state = VALUE_END;
                break;
            }
            case VALUE_END: {
                if (c == ',') {
                    state = KEY_START;
                } else if (c == '}') {
                    state = OBJ_END;
                }
                break;
            }
        }
    }
    return obj;
}

JSONObj SimpleJSON::parse(const std::string &str) {
    auto idx = str.find_first_of("{");
    Iterator begin = &str[idx + 1];
    Iterator end = begin + str.size();
    if (begin == end) {
        throw std::runtime_error("syntax error: no object starting token encountered");
    }
    return _parse(begin, end);
}
