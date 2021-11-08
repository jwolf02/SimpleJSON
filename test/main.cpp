#include <SimpleJSON.hpp>
#include <iostream>
#include <cassert>

#define assertThrow(expr)       try { expr; assert(!!false); } catch(...) {}

void test_simple_string() {
    auto obj = SimpleJSON::parse("{ \"hello\": \"world\" }");
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

void test_multi_members() {
    auto obj = SimpleJSON::parse(" { \"hello\": \"world\",\n\t\"key\": {\n\t \"key2\": \"value1\", \"key3\": \"value3\" }}");
    assert(obj.isObject());
    assert(obj["hello"].isString());
    assert(obj["hello"].string() == "world");
    assert(obj["key"].isObject());
    assert(obj["key"]["key2"].isString());
    assert(obj["key"]["key2"].string() == "value1");
}

void test_invalid_objects() {
    assertThrow(SimpleJSON::parse("\"hello\": \"world\""));
    assertThrow(SimpleJSON::parse("hello: world"));
    assertThrow(SimpleJSON::parse("\"hello\" \"world\""));
    assertThrow(SimpleJSON::parse("{\"hello\": \"world\", \"hello\": \"hello\"}"));
}

int main() {
    test_simple_string();
    test_simple_object();
    test_invalid_objects();
    test_multi_members();
    std::cout << "all test finished successfully" << std::endl;
    return 0;
}