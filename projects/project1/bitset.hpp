#ifndef BITSET_HPP
#define BITSET_HPP
#include <stdint.h>
#include <stdlib.h>
#include <string>

class Bitset{
public:

  // Default constructor - Sets size to 8 and sets all bits to 0
  Bitset();

  // Size specified constructor - Sets size to parameter and all bits to 0
  Bitset(intmax_t size);

  // Constructor with string argument - Sets the size to the length of the string and each char is casted to a bit
  Bitset(const std::string & value);

  // Destructor, deletes the allocated memory for the bitset
  ~Bitset();

  Bitset(const Bitset & ) = delete;
  Bitset & operator=(const Bitset &) = delete;

  // Returns the size of the bitset
  intmax_t size() const;

  // Returns the validity of the bitset
  bool good() const;

  // sets the bit at the specified index to 1, if index < 0 or index > size then bitset is set to invalid
  void set(intmax_t index);

   // sets the bit at the specified index to 0, if index < 0 or index > size then bitset is set to invalid
  void reset(intmax_t index);

  // toggles the bit at the specified index, if index < 0 or index > size then bitset is set to invalid
  void toggle(intmax_t index);

  // checks if the bit at the specified index is 1, if index is out of range then the bitset is set to invalid and false is returned
  bool test(intmax_t index);

  // returns the bitset as a string
  std::string asString() const;

private:
  // bitsetSize is the maximum of the array, bitSetPtr points to the address of the dynamically allocated memory for the bitset array
  // bitsetValidity is the validity of the bitset
  intmax_t bitsetSize;
  uint8_t *bitsetPtr;
  bool bitsetValidity = true;
};
#endif
