#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "list.hpp"
#include "sorted_list.hpp"
#include "priority_queue.hpp"

TEST_CASE("Testing Priority Queue", "[priority queue]")
{
    typedef SortedList<int, List<int>> SortedListType;
    typedef PriorityQueue<int, SortedListType> PriorityQueueType;

    PriorityQueueType pq;
    REQUIRE(pq.isEmpty());
    pq.add(1);
    REQUIRE(!pq.isEmpty());
    pq.add(0);
    REQUIRE(pq.peek() == 1);
    pq.add(2);
    pq.add(3);
    REQUIRE(pq.peek() == 3);

    pq.remove();
    REQUIRE(pq.peek() == 2);

    SortedListType lst;
    REQUIRE(lst.isEmpty());
    lst.insert(87);
    lst.insert(10);
    lst.insert(17);
    lst.insert(59);
    lst.insert(71);

    REQUIRE(!lst.isEmpty());
    REQUIRE(lst.getPosition(10) == 0);
    REQUIRE(lst.getEntry(2) == 59);

    REQUIRE(lst.getLength() == 5);
    lst.removeAt(3);
    lst.remove(59);

    REQUIRE(lst.getPosition(87) == 2);
    REQUIRE(lst.getEntry(1) == 17);



}
