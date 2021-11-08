#include <SimpleJSON.hpp>
#include <iostream>

void print(const JSONObj &obj) {
    if (obj.isString()) {
        std::cout << obj.string() << "," << std::endl;
    } else {
        std::cout << '{' << std::endl;
        for (const auto &mem : obj.members()) {
            std::cout << mem.first << ": ";
            print(mem.second);
            std::cout << "," << std::endl;
        }
        std::cout << '}' << std::endl;
    }
}

int main() {

    auto obj = SimpleJSON::parse("{ \"hello\": \"world\" }");
    std::cout << obj;

    JSONObj ob2;
    ob2["hello"] = "world";
    std::cout << ob2["hello"] << std::endl;

    return 0;
}