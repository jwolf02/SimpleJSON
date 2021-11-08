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
    std::string str =   "{\n"
                        "\t\"key\":\"value\",\n"
                        "\t\"key2\": {\n"
                        "\t\t\"key\": \"value\",\n"
                        "\t\t\"key2\": \"value2\"\n"
                        "\t},\n"
                        "\t\"key3\": \"value3 is the \\\"supernormal\\\" value\"\n"
                        "}";
    auto obj = SimpleJSON::parse(str);
    assert(obj.isObject());
    assert(obj["key"].isString());
    assert(obj["key"].string() == "value");
    assert(obj["key2"].isObject());
    assert(obj["key3"].isString());
    assert(obj["key3"].string() == "value3 is the \"supernormal\" value");
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
    test_escaped_strings();
    test_multi_members();
    std::cout << "all test finished successfully" << std::endl;
    return 0;
}