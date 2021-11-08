#include <SimpleJSON.hpp>
#include <iostream>
#include <cassert>

void test_simple_string() {
    auto obj = SimpleJSON::parse("{ \"hello\": \"world\" }");
    std::cout << obj << std::endl;
    assert(obj.isObject());
    assert(obj["hello"].isString());
    assert(obj["hello"].string() == "world");
}

void test_simple_object() {
    auto obj = SimpleJSON::parse("{ \"hello\": { \"world\": \"hello\" } }");
    assert(obj.isObject());
    assert(obj["hello"].isObject());
    assert(obj["hello"]["world"].isString());
    assert(obj["hello"]["world"].string() == "hello");
}

void test_escaped_strings() {
    auto obj = SimpleJSON::parse("{ \"he\\\"llo\": \"world\" }");
    assert(obj.isObject());
    assert(obj["he\\\"llo"].isString());
    assert(obj["he\\\"llo"].string() == "world");
}

void test_invalid_objects() {
    try {
        SimpleJSON::parse("\"hello\": \"world\"");
        assert(!!false);
    } catch (const std::runtime_error &ex) {}

    try {
        SimpleJSON::parse("hello: world");
        assert(!!false);
    } catch (const std::runtime_error &ex) {}
}

int main() {
    test_simple_string();
    test_simple_object();
    test_invalid_objects();
    std::cout << "all test finished successfully" << std::endl;
    return 0;
}