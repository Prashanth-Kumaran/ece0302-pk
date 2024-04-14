#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "FindPalindrome.hpp"

using std::string;
using std::vector;
// There should be at least one test per FindPalindrome method

TEST_CASE("Test adding a non-allowable word", "[FindPalindrome]")
{
    
    FindPalindrome b;
    REQUIRE(!b.add("kayak1"));
}

TEST_CASE("Test adding a repeated word", "[FindPalindrome]"){
    FindPalindrome b;
    REQUIRE(b.add("Crosby"));
    REQUIRE(!b.add("Crosby"));
}

TEST_CASE("test recursion", "[FindPalindrome]")
{
    FindPalindrome b;

    REQUIRE(b.add("a"));
    REQUIRE(b.add("AA"));
    REQUIRE(b.add("AaA"));
    REQUIRE(b.number() == 6);
}

TEST_CASE("test cutTest1", "[FindPalindrome]")
{
    FindPalindrome b;
    vector<string> multiOdd{"aA", "ab", "cc"};
    REQUIRE_FALSE(b.cutTest1(multiOdd));

    vector<string> oneOdd{"aa", "Abb", "cC"};
    REQUIRE(b.cutTest1(oneOdd));

    vector<string> even{"aa", "aBb", "ACC"};
    REQUIRE(b.cutTest1(even));
}

TEST_CASE("test cutTest2", "[FindPalindrome]")
{
    FindPalindrome b;
    vector<string> largeString1{"Crosby"};
    vector<string> smallString1{"Roy"};
    vector<string> smallString2{"Robb"};
    REQUIRE(b.cutTest2(smallString1, largeString1));
    REQUIRE_FALSE(b.cutTest2(smallString2, largeString1));
}

TEST_CASE("test multi add", "[FindPalindrome]")
{
    FindPalindrome b;
    vector<string> addVector{"a", "AA", "AaA"};
    REQUIRE(b.add(addVector));
    REQUIRE(b.number() == 6);
}

TEST_CASE("test isPalindrome", "[FindPalindrome]"){
    FindPalindrome b;
    vector<string> sentence1{"Geese", "Do", "See", "God"};
    b.add(sentence1);
    REQUIRE(b.number() == 1);
    b.add("Santa");
    REQUIRE(b.number() == 0);
}
TEST_CASE("test toVector", "[FindPalindrome]")
{
    FindPalindrome b;
    vector<string> unsortedVector{"Geese", "Do", "See", "God"};
    b.add(unsortedVector);
    vector<string> solutionVector{"Do", "Geese", "See", "God"};
    vector<vector<string>> palinVector = b.toVector();
    REQUIRE(palinVector[0] == solutionVector);
}

TEST_CASE("test number", "[FindPalindrome]")
{
    FindPalindrome b;
    vector<string> inputVector{"a", "aa", "aaa", "aaaa"};
    b.add(inputVector);
    REQUIRE(b.number() == 24);
}

TEST_CASE("test clear", "[FindPalindrome]")
{
    FindPalindrome b;
    vector<string> unsortedVector{"Geese", "Do", "See", "God"};
    b.add(unsortedVector);
    REQUIRE(b.number() == 1);
    b.clear();
    REQUIRE(b.number() == 0);
    
}