#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include "array_list.hpp"

//force class expansion
template class ArrayList<int>;

TEST_CASE("Test Constructor", "[ArrayList]") {
    ArrayList<int> intList;
    REQUIRE(intList.isEmpty());

    ArrayList<std::string> stringList;
    REQUIRE(stringList.isEmpty());
}

TEST_CASE("Test Copy Constructor", "[ArrayList]") {
    ArrayList<int> intList1;
    REQUIRE(intList1.isEmpty());
    intList1.insert(0, 87);
    ArrayList<int> intList2 = intList1;
    REQUIRE(intList2.getEntry(0) == intList1.getEntry(0));

    ArrayList<std::string> stringList1;
    REQUIRE(stringList1.isEmpty());
    stringList1.insert(0, "Sid");
    ArrayList<std::string> stringList2 = stringList1;
    REQUIRE(stringList2.getEntry(0) == stringList1.getEntry(0));

}

TEST_CASE("Test Copy Assignment", "[ArrayList]") {
    ArrayList<int> intList1;
    REQUIRE(intList1.isEmpty());
    intList1.insert(0, 87);
    ArrayList<int> intList2;
    intList2 = intList1;
    REQUIRE(intList2.getEntry(0) == intList1.getEntry(0));

    ArrayList<std::string> stringList1;
    REQUIRE(stringList1.isEmpty());
    stringList1.insert(0, "Sid");
    ArrayList<std::string> stringList2;
    stringList2 = stringList1;
    REQUIRE(stringList2.getEntry(0) == stringList1.getEntry(0));

}

TEST_CASE("Test insert", "[ArrayList]") {
    ArrayList<int> list;
    for (int i = 0; i < 100; i++) {
        list.insert(i, i);
    }

    REQUIRE(list.getEntry(99) == 99);
    list.insert(50, 0);
    REQUIRE(list.getEntry(50) == 0);
    REQUIRE(list.getEntry(51) == 50);
    REQUIRE_FALSE(list.insert(-1, 0));
    REQUIRE_FALSE(list.insert(150, 100));
}

TEST_CASE("Test Remove", "[ArrayList]") {
    ArrayList<int> list;
    for (int i = 0; i < 100; i++) {
        list.insert(i, i);
    }
    REQUIRE(list.remove(0));
    REQUIRE(list.remove(98));
    REQUIRE(list.getEntry(0) == 1);
    REQUIRE(list.getEntry(97) == 98);
    REQUIRE(list.getLength() == 98);
    REQUIRE_FALSE(list.remove(-1));
    REQUIRE_FALSE(list.remove(100));
}

TEST_CASE("Test Clear", "[ArrayList]") {
    ArrayList<int> list;
    for (int i = 0; i < 100; i++) {
        list.insert(i, i);
    }
    list.clear();
    REQUIRE(list.getLength() == 0);
}