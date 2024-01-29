#include "bitset.hpp"

Bitset::Bitset()
{
    // Default constructor: Size 8, all bits set to 0
    bitsetSize = 8;
    bitsetPtr = new uint8_t[bitsetSize];
    for (int i = 0; i < 8; i++)
    {
        *(bitsetPtr + i) = 0;
    }
}

Bitset::Bitset(intmax_t size)
{
    // Constructor with size argument, all bits set to 0
    bitsetSize = size;
    bitsetPtr = new uint8_t[bitsetSize];
    for (int i = 0; i < 8; i++)
    {
        *(bitsetPtr + i) = 0;
    }
}

Bitset::Bitset(const std::string &value)
{
    // sets size of bitset to string size
    bitsetSize = value.size();
    bitsetPtr = new uint8_t[bitsetSize];

    for (int i = 0; i < bitsetSize; i++)
    {
        // checks the validity of the string
        if (value[i] != '0' && value[i] != '1')
        {
            bitsetValidity = false;
        }

        // casts the char to uint8_t, ASCII code is 48 higher than value, so subtracts 48, and then sets it to the bitset element
        *(bitsetPtr + i) = static_cast<uint8_t>(value[i]) - 48;
    }
}

Bitset::~Bitset()
{

    delete[] bitsetPtr;
}

intmax_t Bitset::size() const
{
    return bitsetSize;
}

bool Bitset::good() const
{
    return bitsetValidity;
}

void Bitset::set(intmax_t index)
{
    if (index >= 0 && index < bitsetSize)
    {
        *(bitsetPtr + index) = 1;
    }
    else
    {
        bitsetValidity = false;
    }
}

void Bitset::reset(intmax_t index)
{
    if (index >= 0 && index < bitsetSize)
    {
        *(bitsetPtr + index) = 0;
    }
    else
    {
        bitsetValidity = false;
    }
}

void Bitset::toggle(intmax_t index)
{
    if (index >= 0 && index < bitsetSize)
    {
        *(bitsetPtr + index) = (*(bitsetPtr + index) + 1) % 2;
    }
    else
    {
        bitsetValidity = false;
    }
}

bool Bitset::test(intmax_t index)
{
    if (index >= 0 && index < bitsetSize)
    {
        return *(bitsetPtr + index);
    }
    else
    {
        bitsetValidity = false;
        return false;
    }
}

std::string Bitset::asString() const
{
    std::string bitsetString = "";
    for (int i = 0; i < bitsetSize; i++)
    {
        bitsetString += std::to_string(*(bitsetPtr + i));
    }
    return bitsetString;
}
