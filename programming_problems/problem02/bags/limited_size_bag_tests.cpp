#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "limited_size_bag.hpp"

// force template expansion for ints
template class LimitedSizeBag<int>;
using std::string;
TEST_CASE("Calling all public members", "[LimitedSizeBag]"){
  LimitedSizeBag<int> b;

  b.add(0);
  b.remove(0);
  b.isEmpty();
  b.getCurrentSize();
  b.clear();
  b.getFrequencyOf(0);
  b.contains(0);

}

TEST_CASE("Test Default Constructor", "[LimitedSizeBag]")
{
    LimitedSizeBag<int> intBag;
    LimitedSizeBag<string> stringBag;

    REQUIRE(intBag.isEmpty());
    REQUIRE(stringBag.isEmpty());
}

TEST_CASE("Test add/contains", "[LimitedSizeBag]")
{
    LimitedSizeBag<int> b;
    b.add(0);
    b.add(87);
    REQUIRE(b.contains(87));
    REQUIRE(b.getCurrentSize() == 2);

    LimitedSizeBag<std::string> c;
    c.add("a");
    REQUIRE(c.contains("a"));
    REQUIRE(c.getCurrentSize() == 1);
}

TEST_CASE("Test max size", "[LimetSizeBag]"){
    LimitedSizeBag<int> b;
    int a = LimitedSizeBag<int>::maxsize;
    REQUIRE(a == 100);
    for(int i = 0; i < 100; i++){
        b.add(0);
    }

    REQUIRE_FALSE(b.add(0));
}

TEST_CASE("Test remove", "[LimitedSizeBag]")
{
    LimitedSizeBag<int> b;
    b.add(0);
    b.add(87);
    b.add(59);
    b.remove(87);
    REQUIRE_FALSE(b.contains(87));
    REQUIRE(b.getCurrentSize() == 2);
    REQUIRE_FALSE(b.remove(87));

    LimitedSizeBag<std::string> c;
    c.add("a");
    REQUIRE(c.contains("a"));
    REQUIRE(c.getCurrentSize() == 1);
    c.remove("a");
    REQUIRE_FALSE(c.contains("a"));
    REQUIRE(c.getCurrentSize() == 0);
}

TEST_CASE("Test clear/isEmpty", "[LimitedSizeBag]"){
    LimitedSizeBag<int> b;
    b.add(0);
    b.add(87);
    b.add(59);
    b.clear();
    REQUIRE_FALSE(b.contains(87));
    REQUIRE(b.getCurrentSize() == 0);
    REQUIRE(b.isEmpty());
}

TEST_CASE("Test getFrequencyOf", "[LimitedSizeBag]"){
    LimitedSizeBag<int> b;
    b.add(87);
    b.add(87);
    b.add(59);

    REQUIRE(b.getFrequencyOf(87) == 2);

    b.remove(87);

    REQUIRE(b.getFrequencyOf(87) == 1);
}
