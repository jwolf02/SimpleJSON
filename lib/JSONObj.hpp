#ifndef __JSONOBJ_HPP
#define __JSONOBJ_HPP

#include <string>
#include <map>

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

private:

    std::string _str;

    std::map<std::string, JSONObj> _members;

    bool _isObj;

};

#endif // __JSONOBJ_HPP