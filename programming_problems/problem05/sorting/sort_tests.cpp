#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "linked_list.hpp"
#include "sort.hpp"

// write your test cases here
TEST_CASE("Test char", "sorting")
{

    LinkedList<char> lst;

    lst.insert(0, 'c');
    lst.insert(1, 'r');
    lst.insert(2, 'o');
    lst.insert(3, 's');
    lst.insert(4, 'b');
    lst.insert(5, 'y');

    LinkedList<char> sorted = sort(lst);

    // check sorted list
    REQUIRE(sorted.getEntry(0) == 'b');
    REQUIRE(sorted.getEntry(1) == 'c');
    REQUIRE(sorted.getEntry(2) == 'o');
    REQUIRE(sorted.getEntry(3) == 'r');
    REQUIRE(sorted.getEntry(4) == 's');
    REQUIRE(sorted.getEntry(5) == 'y');
}

TEST_CASE("Test string", "sorting")
{

    LinkedList<std::string> lst;
    lst.insert(0, "dragon");
    lst.insert(1, "tangerine");
    lst.insert(2, "cookie");

    LinkedList<std::string> sorted = sort(lst);

    REQUIRE(sorted.getEntry(0) == "cookie");
    REQUIRE(sorted.getEntry(1) == "dragon");
    REQUIRE(sorted.getEntry(2) == "tangerine");
}

TEST_CASE("Test double", "sorting")
{

    LinkedList<double> lst;
    lst.insert(0, 8.7);
    lst.insert(1, 5.8);
    lst.insert(2, 7.1);

    LinkedList<double> sorted = sort(lst);

    REQUIRE(sorted.getEntry(0) == 5.8);
    REQUIRE(sorted.getEntry(1) == 7.1);
    REQUIRE(sorted.getEntry(2) == 8.7);
}

TEST_CASE("Test case", "sorting")
{

    LinkedList<int> lst;

    lst.insert(0, 100);
    lst.insert(1, 4);
    lst.insert(2, 10);
    lst.insert(3, 25);
    lst.insert(4, 11);

    LinkedList<int> sorted = sort(lst);

    // check sorted list
    REQUIRE(sorted.getEntry(0) == 4);
    REQUIRE(sorted.getEntry(1) == 10);
    REQUIRE(sorted.getEntry(2) == 11);
    REQUIRE(sorted.getEntry(3) == 25);
    REQUIRE(sorted.getEntry(4) == 100);
}
