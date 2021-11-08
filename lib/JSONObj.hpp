#ifndef __JSONOBJ_HPP
#define __JSONOBJ_HPP

#include <string>
#include <map>
#include <iostream>

class JSONObj {
public:

    JSONObj() = default;

    JSONObj& operator=(const std::string &str) {
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

    JSONObj& operator[](const std::string &key) {
        return _members[key];
    }

    const std::map<std::string, JSONObj>& members() const {
        return _members;
    }

private:

    std::string _str;

    std::map<std::string, JSONObj> _members;

    bool _isObj = true;

};

inline std::ostream& operator<<(std::ostream &out, const JSONObj &obj) {
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

#endif // __JSONOBJ_HPP