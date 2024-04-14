#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "list.hpp"
#include "queue.hpp"



TEST_CASE("Testing all", "[queue]") {
  Queue<int, List<int>> queue;

  queue.enqueue(12);
  REQUIRE(!queue.isEmpty());
  REQUIRE(queue.peekFront() == 12);

  queue.enqueue(-4);
  REQUIRE_FALSE(queue.isEmpty());
  REQUIRE(queue.peekFront() == 12);

  queue.dequeue();
  queue.dequeue();
  REQUIRE(queue.isEmpty());

  queue.enqueue(241);
  REQUIRE_FALSE(queue.isEmpty());
  REQUIRE(queue.peekFront() == 241);

  queue.enqueue(45);
  REQUIRE(!queue.isEmpty());
  REQUIRE(queue.peekFront() == 241);

  queue.enqueue(62);
  REQUIRE_FALSE(queue.isEmpty());
  REQUIRE(queue.peekFront() == 241);

  Queue<int, List<int>> another_queue;
  another_queue = queue;

  REQUIRE_FALSE(another_queue.isEmpty());
  REQUIRE(another_queue.peekFront() == 241);
  another_queue.dequeue();
  REQUIRE(another_queue.peekFront() == 45);
  another_queue.dequeue();
  REQUIRE(another_queue.peekFront() == 62);
}


TEST_CASE("Test Constructor", "[list]") {
    List<int> intList;
    REQUIRE(intList.isEmpty());

    List<std::string> stringList;
    REQUIRE(stringList.isEmpty());
}

TEST_CASE("Test Copy Constructor", "[list]") {
    List<int> intList1;
    REQUIRE(intList1.isEmpty());
    intList1.insert(0, 87);
    List<int> intList2 = intList1;
    REQUIRE(intList2.getEntry(0) == intList1.getEntry(0));

    List<std::string> stringList1;
    REQUIRE(stringList1.isEmpty());
    stringList1.insert(0, "Sid");
    List<std::string> stringList2 = stringList1;
    REQUIRE(stringList2.getEntry(0) == stringList1.getEntry(0));

}

TEST_CASE("Test Copy Assignment", "[list]") {
    List<int> intList1;
    REQUIRE(intList1.isEmpty());
    intList1.insert(0, 87);
    List<int> intList2;
    intList2 = intList1;
    REQUIRE(intList2.getEntry(0) == intList1.getEntry(0));

    List<std::string> stringList1;
    REQUIRE(stringList1.isEmpty());
    stringList1.insert(0, "Sid");
    List<std::string> stringList2;
    stringList2 = stringList1;
    REQUIRE(stringList2.getEntry(0) == stringList1.getEntry(0));

}

TEST_CASE("Test insert", "[list]") {
    List<int> list;
    for (int i = 0; i < 100; i++) {
        list.insert(i, i);
    }

    REQUIRE(list.getEntry(99) == 99);
    list.insert(50, 0);
    REQUIRE(list.getEntry(50) == 0);
    REQUIRE(list.getEntry(51) == 50);
    REQUIRE_THROWS(list.insert(-1, 0));
    REQUIRE_THROWS(list.insert(150, 100));
}

TEST_CASE("Test Remove", "[list]") {
    List<int> list;
    for (int i = 0; i < 100; i++) {
        list.insert(i, i);
    }
    REQUIRE_NOTHROW(list.remove(0));
    REQUIRE_NOTHROW(list.remove(98));
    REQUIRE(list.getEntry(0) == 1);
    REQUIRE(list.getEntry(97) == 98);
    REQUIRE(list.getLength() == 98);
    REQUIRE_THROWS(list.remove(-1));
    REQUIRE_THROWS(list.remove(100));
}

TEST_CASE("Test Clear", "[list]") {
    List<int> list;
    for (int i = 0; i < 100; i++) {
        list.insert(i, i);
    }
    list.clear();
    REQUIRE(list.getLength() == 0);
}
