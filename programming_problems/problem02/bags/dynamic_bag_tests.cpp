#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "dynamic_bag.hpp"

using std::string;
// force template expansion for ints
template class DynamicBag<int>;

TEST_CASE("Calling all public members", "[DynamicBag]")
{
    DynamicBag<int> b;

    b.add(0);
    b.remove(0);
    b.isEmpty();
    b.getCurrentSize();
    b.clear();
    b.getFrequencyOf(0);
    b.contains(0);
}

TEST_CASE("Test Default Constructor", "[DynamicBag]")
{
    DynamicBag<int> intBag;
    DynamicBag<string> stringBag;

    REQUIRE(intBag.isEmpty());
    REQUIRE(stringBag.isEmpty());
}

TEST_CASE("Test Copy Constructor", "[DynamicBag]")
{
    DynamicBag<int> bag1;
    bag1.add(87);
    DynamicBag<int> bag2 = bag1;
    REQUIRE(bag2.contains(87));
    REQUIRE(bag2.getCurrentSize() == bag1.getCurrentSize());
}

TEST_CASE("Test Copy Assignment", "[DynamicBag]")
{
    DynamicBag<int> bag1;
    bag1.add(87);
    DynamicBag<int> bag2;
    bag2 = bag1;
    REQUIRE(bag2.contains(87));
    REQUIRE(bag2.getCurrentSize() == bag1.getCurrentSize());
}

TEST_CASE("Test swap", "[DynamicBag]")
{
    DynamicBag<int> bag1;
    bag1.add(87);
    bag1.add(59);
    DynamicBag<int> bag2;
    bag2.add(71);

    bag2.swap(bag1);

    REQUIRE(bag1.contains(71));
    REQUIRE(bag1.getCurrentSize() == 1);
    REQUIRE(bag2.contains(87));
    REQUIRE(bag2.contains(59));
    REQUIRE(bag2.getCurrentSize() == 2);
}

TEST_CASE("Test add/contains", "[DynamicBag]")
{
    DynamicBag<int> b;
    b.add(0);
    b.add(87);
    REQUIRE(b.contains(87));
    REQUIRE(b.getCurrentSize() == 2);

    DynamicBag<std::string> c;
    c.add("a");
    REQUIRE(c.contains("a"));
    REQUIRE(c.getCurrentSize() == 1);
}

TEST_CASE("Test remove", "[DynamicBag]")
{
    DynamicBag<int> b;
    b.add(0);
    b.add(87);
    b.add(59);
    b.remove(87);
    REQUIRE_FALSE(b.contains(87));
    REQUIRE(b.getCurrentSize() == 2);
    REQUIRE_FALSE(b.remove(87));

    DynamicBag<std::string> c;
    c.add("a");
    REQUIRE(c.contains("a"));
    REQUIRE(c.getCurrentSize() == 1);
    c.remove("a");
    REQUIRE_FALSE(c.contains("a"));
    REQUIRE(c.getCurrentSize() == 0);
}

TEST_CASE("Test clear/isEmpty", "[DynamicBag]"){
    DynamicBag<int> b;
    b.add(0);
    b.add(87);
    b.add(59);
    b.clear();
    REQUIRE_FALSE(b.contains(87));
    REQUIRE(b.getCurrentSize() == 0);
    REQUIRE(b.isEmpty());
}

TEST_CASE("Test getFrequencyOf", "[DynamicBag]"){
    DynamicBag<int> b;
    b.add(87);
    b.add(87);
    b.add(59);

    REQUIRE(b.getFrequencyOf(87) == 2);

    b.remove(87);

    REQUIRE(b.getFrequencyOf(87) == 1);
}