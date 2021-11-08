#ifndef __JSONOBJECT_HPP
#define __JSONOBJECT_HPP

#include <string>
#include <map>
#include <iostream>

class JSONObject {
public:

    JSONObject() = default;

    JSONObject& operator=(const std::string &str) {
        _str = str;
        _isObj = false;
        return *this;
    }

    bool isObject() const {
        return _isObj;
    }

    bool isString() const {
        return !isObject();
    }

    const std::string string() const {
        return isString() ? _str : "";
    }

    JSONObject& operator[](const std::string &key) {
        return _members[key];
    }

    const std::map<std::string, JSONObject>& members() const {
        return _members;
    }

private:

    std::string _str;

    std::map<std::string, JSONObject> _members;

    bool _isObj = true;

};

inline std::ostream& operator<<(std::ostream &out, const JSONObject &obj) {
    if (obj.isString()) {
        out << '"' << obj.string() << '"';
    } else {
        out << "{\n";
        for (const auto &mem : obj.members()) {
            out << '"' << mem.first << "\": " << mem.second << ",\n";
        }
        out << '}' << std::endl;
    }
    return out;
}

#endif // __JSONOBJECT_HPP