#ifndef BITSET_HPP
#define BITSET_HPP
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <cmath>

class Bitset
{
public:
  // Default constructor - Sets Array size to 1 byte and all bits to 0
  Bitset();

  // Size specified constructor - Sets size to appropriate number of bytes and all bits to 0
  Bitset(intmax_t size);

  // Constructor with string argument - Sets the size to the length of the string and each char is casted to a bit
  // The bits are then grouped into bytes, and the byte values are stored in the uint8_t array
  Bitset(const std::string &value);

  // Destructor, deletes the allocated memory for the bitset
  ~Bitset();

  Bitset(const Bitset &) = delete;
  Bitset &operator=(const Bitset &) = delete;

  // Returns the size of the bitset
  intmax_t size() const;

  // Returns the validity of the bitset
  bool good() const;

  // sets the bit at the specified index to 1, if index < 0 or index > size then bitset is set to invalid
  // uses the shift operator to create bitmask specified by the index
  // using a bitwise OR with the bitmask results in setting the index bit
  void set(intmax_t index);

  // sets the bit at the specified index to 0, if index < 0 or index > size then bitset is set to invalid
  // uses the shift operator to create bitmask specified by the index
  // using the negation of the bitwise AND with the bitmask results in resetting the index bit
  void reset(intmax_t index);

  // toggles the bit at the specified index, if index < 0 or index > size then bitset is set to invalid
  // uses the shift operator to create bitmask specified by the index
  // using a bitwise XOR with the bitmask results in toggling the index bit
  void toggle(intmax_t index);

  // checks if the bit at the specified index is 1, if index is out of range then the bitset is set to invalid and false is returned
  // uses the shift operator to create a bitmask specified by the index
  // The Byte ANDed with the bitmask results in the value of the index bit
  bool test(intmax_t index);

  // returns the bitset as a string
  // converts the byte array back to a binary string
  std::string asString() const;

private:
  // bitsetSize is the maximum of the array, bitSetPtr points to the address of the dynamically allocated memory for the bitset array
  // bitsetValidity is the validity of the bitset
  intmax_t bitsetSize;
  intmax_t numBytes;
  uint8_t *bitsetPtr;
  bool bitsetValidity = true;
};
#endif
