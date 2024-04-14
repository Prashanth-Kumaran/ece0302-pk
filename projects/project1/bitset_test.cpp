#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include <iostream>
#include "bitset.hpp"

TEST_CASE( "Test bitset default construction", "[bitset]" ) {

    Bitset b;  
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
}

TEST_CASE( "Test bitset construction with asString", "[bitset]" ) {
    Bitset b;
    REQUIRE(b.asString().compare("00000000") == 0);
}

TEST_CASE( "Test bitset construction size", "[bitset]" ) {
    Bitset b(64);
    std::string s(64, '0');
    REQUIRE(b.size() == 64);
    REQUIRE(b.good());
}

TEST_CASE("Test bitset construction invalid size", "[bitset]"){
    Bitset b(-1);
    REQUIRE_FALSE(b.good());
}

TEST_CASE( "Test bitset construction string", "[bitset]" ) {
    std::string s("00101110000011000001101000001");
    Bitset b(s);
    REQUIRE(b.size() == s.size());
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);
}

TEST_CASE( "Test bitset construction invalid string", "[bitset]" ) {
    std::string s("00101110000011002001101000001");
    Bitset b(s);
    REQUIRE_FALSE(b.good());
}

TEST_CASE( "Test set", "[bitset]" ) {
    std::string s("00010001");
    Bitset b;
    b.set(3);
    b.set(7);
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
    std::string q = b.asString();
    REQUIRE(b.asString().compare(s) == 0);
}

TEST_CASE( "Test set with size init", "[bitset]" ) {
    std::string s("00010");
    Bitset b(5);
    b.set(3);
    REQUIRE(b.size() == 5);
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);
}

TEST_CASE( "Test set with invalid index", "[bitset]" ){
    Bitset b;
    b.set(9);
    REQUIRE_FALSE(b.good());

    Bitset c;
    c.set(-1);
    REQUIRE_FALSE(c.good());
}

TEST_CASE( "Test size", "[bitset]" ) {
    std::string s("0000000");
    Bitset b(s);
    REQUIRE(b.size() == 7);
    REQUIRE(b.good());
}

TEST_CASE("Test good", "[bitset]"){
    Bitset b(5);
    REQUIRE(b.good());
    b.set(6);
    REQUIRE_FALSE(b.good());
}

TEST_CASE("Test reset"){
    std::string s("111111");
    std::string target("111110");
    Bitset b(s);
    b.reset(5);
    REQUIRE(b.asString().compare(target) == 0);

}

TEST_CASE( "Test reset with invalid index", "[bitset]" ){
    std::string s("111");
    Bitset b(s);
    b.reset(9);
    REQUIRE_FALSE(b.good());

    Bitset c(s);
    c.reset(-1);
    REQUIRE_FALSE(c.good());
}

TEST_CASE("Test toggle"){
    Bitset b(1);
    REQUIRE(b.asString().compare("0") == 0);
    b.toggle(0);
    REQUIRE(b.asString().compare("1") == 0);
    b.toggle(0);
    REQUIRE(b.asString().compare("0") == 0);
}

TEST_CASE( "Test toggle with invalid index", "[bitset]" ){
    std::string s("111");
    Bitset b(s);
    b.toggle(9);
    REQUIRE_FALSE(b.good());

    Bitset c(s);
    c.toggle(-1);
    REQUIRE_FALSE(c.good());
}

TEST_CASE( "Test combined", "[bitset]" ) {
    std::string s((1<<15) + 3, '0');
    Bitset b(s);
    REQUIRE(b.size() == s.size());
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);

    for (int i = 1; i < (1<<10); i++) {
        b.set(i);
        b.reset(i + (1<<10));
        b.toggle(i + (1<<11));
        REQUIRE(b.good());
        REQUIRE(b.test(i));
        REQUIRE_FALSE(b.test(i + (1<<10)));
        REQUIRE(((b.test(i + (1<<11)) == true && s.at(i + (1<<11)) == '0') || (b.test(i + (1<<11)) == false && s.at(i + (1<<11)) == '1')));
    }
}

