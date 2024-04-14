#include "bitset.hpp"

Bitset::Bitset()
{
    // Default constructor: Size 8, all bits set to 0
    bitsetSize = 8;
    // 8 bits per byte
    numBytes = 1;
    bitsetPtr = new uint8_t[1];
    bitsetPtr[0] = 0;
}

Bitset::Bitset(intmax_t size)
{
    // Constructor with size argument, all bits set to 0
    bitsetSize = size;
    if (size <= 0)
    {
        bitsetValidity = false;
        bitsetPtr = new uint8_t[8];
    }
    else
    {
        bitsetSize = size;
        // 8 bits per byte, size is decreased by 1 before integer division to account for 8/8 = 1
        numBytes = ((size - 1) / 8) + 1;
        bitsetPtr = new uint8_t[numBytes];
        // setting all bytes to 0;
        for (int i = 0; i < numBytes; i++)
        {
            *(bitsetPtr + i) = 0;
        }
    }
}

Bitset::Bitset(const std::string &value)
{
    // sets size of bitset to string size
    bitsetSize = value.size();
    // 8 bits per byte, size is decreased by 1 before integer division to account for 8/8 = 1
    numBytes = ((bitsetSize - 1) / 8) + 1;

    //set all bytes to 0
    bitsetPtr = new uint8_t[numBytes];
    for (int i = 0; i < numBytes; i++)
    {
        bitsetPtr[i] = 0;
    }

    //checking the validity of the input string
    for (int i = 0; i < bitsetSize; i++)
    {
        // checks the validity of the string
        if (value[i] != '0' && value[i] != '1')
        {
            bitsetValidity = false;
        }
    }

    //setting the value of each byte by looping through sets of 8 bits and computing the integer value;
    for (int i = 0; i < numBytes; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            int str_index = (i * 8) + j;
            int str_bit;
            if (((8 * i) + j) >= bitsetSize)
            {
                str_bit = 0;
            }
            else
            {
                str_bit = static_cast<int>(value[str_index]) - 48;
            }
            int bitVal = pow(2, j) * str_bit;
            bitsetPtr[i] += bitVal;
        }
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
        intmax_t arrIndex = (index / 8);
        intmax_t shift = (index % 8);

        //bitwise OR results in set
        bitsetPtr[arrIndex] |= (1 << shift);
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
        intmax_t arrIndex = (index / 8);
        intmax_t shift = (index % 8);

        //bitwise AND of negation results in reset
        bitsetPtr[arrIndex] &= ~(1 << shift);
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
        intmax_t arrIndex = (index / 8);
        intmax_t shift = (index % 8);

        //bitwise XOR results in toggle
        bitsetPtr[arrIndex] ^= (1 << shift);
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
        intmax_t arrIndex = (index / 8);
        intmax_t shift = (index % 8);

        //AND results in the value at the bit
        return bitsetPtr[arrIndex] & (1 << shift);
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
    //loops through each byte
    for (int i = 0; i < numBytes; i++)
    {
        int currentByte = bitsetPtr[i];
        //loops through each bit in the current byte
        for (int j = 0; j < 8; j++)
        {
            //if the bit is not used in the bitset, it's value is ignored
            if (((8 * i) + j) >= bitsetSize)
            {
            }
            else
            {
                //the value of the current bit is converted to a string
                int currentBit = currentByte & (1 << j);
                if (currentBit > 0)
                {
                    bitsetString += "1";
                }
                else
                {
                    bitsetString += "0";
                }
            }
        }
    }
    return bitsetString;
}