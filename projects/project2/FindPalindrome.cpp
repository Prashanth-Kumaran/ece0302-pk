#include <string>
#include <vector>
#include <iostream>
#include "FindPalindrome.hpp"

using namespace std;

//------------------- HELPER FUNCTIONS -----------------------------------------

// non-class helper functions go here, should be declared as "static" so that
// their scope is limited

// helper function to convert string to lower case
static void convertToLowerCase(string &value)
{
    for (int i = 0; i < value.size(); i++)
    {
        value[i] = tolower(value[i]);
    }
}


// helper function to check if the input string is valid
static bool validString(std::string s, std::vector<std::string> vec)
{
    // checks if string is only alphabetic characters
    for (int i = 0; i < s.size(); i++)
    {
        if (!(std::isalpha(s[i])))
        {
            return false;
        }
    }
    // checks if string already is in vector
    convertToLowerCase(s);
    for (int i = 0; i < vec.size(); i++)
    {
        std::string vecStr = vec[i];
        convertToLowerCase(vecStr);
        if (s == vecStr)
        {
            return false;
        }
    }
    return true;
}

// helper function to convert ordered vector to string
static std::string convertToString(vector<std::string> candidateStringVector)
{
    std::string candidateString = "";
    for (int i = 0; i < candidateStringVector.size(); i++)
    {
        candidateString += candidateStringVector[i];
    }
    convertToLowerCase(candidateString);
    return candidateString;
}

//------------------- PRIVATE CLASS METHODS ------------------------------------

// private recursive function. Must use this signature!
void FindPalindrome::recursiveFindPalindromes(vector<string> candidateStringVector, vector<string> currentStringVector)
{
    // cutTest1: see if a palindrome can even be formed at all by the inputString;
    if(!(cutTest1(inputStringVector))){
        return;
    }

    // Base Case Check: if candidate length is the same as input length
    // base case occurs
    if (candidateStringVector.size() == inputStringVector.size())
    {
        // Converts ordered vector to a string
        std::string candidateString = convertToString(candidateStringVector);
        // Checks if the string is a palindrome
        if (isPalindrome(candidateString) == true)
        {
            palindromeVector.push_back(candidateStringVector);
        }
    }

    // loops through every branch possible for the candidateVector
    for (int i = 0; i < currentStringVector.size(); i++)
    {
        std::string nextWord = currentStringVector[i];
        candidateStringVector.push_back(nextWord);
        currentStringVector.erase(currentStringVector.begin() + i);

        // cutTest2: checks if the next branch can produce a palindrome, skips the branch if failed
        if(cutTest2(candidateStringVector, currentStringVector)){
            recursiveFindPalindromes(candidateStringVector, currentStringVector);
        }

        // backtracking, reforms the array before the recursive call
        currentStringVector.insert(currentStringVector.begin() + i, nextWord);
        candidateStringVector.pop_back();
    }

    return;
}

// private function to determine if a string is a palindrome (given, you
// may change this if you want)
bool FindPalindrome::isPalindrome(string currentString) const
{
    locale loc;
    // make sure that the string is lower case...
    convertToLowerCase(currentString);
    // see if the characters are symmetric...
    int stringLength = currentString.size();
    for (int i = 0; i < stringLength / 2; i++)
    {
        if (currentString[i] != currentString[stringLength - i - 1])
        {
            return false;
        }
    }
    return true;
}

//------------------- PUBLIC CLASS METHODS -------------------------------------

FindPalindrome::FindPalindrome()
{
}

FindPalindrome::~FindPalindrome()
{
    clear();
    // deallocates memory
    inputStringVector = std::vector<string>();
    candidateStringVector = std::vector<string>();
    palindromeVector = std::vector<std::vector<std::string>>();
}

int FindPalindrome::number() const
{
    return palindromeVector.size();
}

void FindPalindrome::clear()
{
    inputStringVector.clear();
    candidateStringVector.clear();
    palindromeVector.clear();
}

bool FindPalindrome::cutTest1(const vector<string> &stringVector)
{
    std::string testString = convertToString(stringVector);
    bool oddOccured = false;
    convertToLowerCase(testString);
    // loops through the lowercase letters of the alphabet
    for (int i = 97; i < 123; i++)
    {
        int letterCount = 0;
        char testChar = static_cast<char>(i);
        // loops through the string formed by the vector
        for (int j = 0; j < testString.size(); j++)
        {
            if (testString[j] == testChar)
            {
                letterCount++;
            }
        }
        // if the count of the letter is odd, oddOccured is triggered
        // if oddOccured is already triggered, then more than 1 letter has an odd count
        // therefore cutTest1 fails
        if (letterCount % 2 == 1)
        {
            if (oddOccured == true)
            {
                return false;
            }
            oddOccured = true;
        }
    }
    return true;
}

bool FindPalindrome::cutTest2(const vector<string> &stringVector1,
                              const vector<string> &stringVector2)
{
    std::string largeString = convertToString(stringVector1);
    std::string smallString = convertToString(stringVector2);

    // swaps the strings if large string < small string
    if (largeString.size() < smallString.size())
    {
        std::swap(largeString, smallString);
    }
    
    // loops through the alphabet
    for (int i = 97; i < 123; i++)
    {
        int smallLetterCount = 0;
        int largeLetterCount = 0;
        char testChar = static_cast<char>(i);

        //counts instances of the letter in each string
        for (int j = 0; j < smallString.size(); j++)
        {
            if (testChar == smallString[j])
            {
                smallLetterCount++;
            }
        }
        for (int j = 0; j < largeString.size(); j++)
        {
            if (testChar == largeString[j])
            {
                largeLetterCount++;
            }
        }

        // if the count in the small > count in large
        // smallString contains a letter that's not in the larger, and a palindrome cannot be formed
        if (smallLetterCount > largeLetterCount)
        {
            return false;
        }
    }
    return true;
}

bool FindPalindrome::add(const string &value)
{
    // checks validity
    if (!(validString(value, inputStringVector)))
    {
        return false;
    }
    // adds the string to the vector and reruns the recursive function
    inputStringVector.push_back(value);
    palindromeVector.clear();
    candidateStringVector.clear();
    recursiveFindPalindromes(candidateStringVector, inputStringVector);
    return true;
}

bool FindPalindrome::add(const vector<string> &stringVector)
{
    // checks the validity of each element of the vector
    for(int i = 0; i < stringVector.size(); i++){
        if(!(validString(stringVector[i], inputStringVector))){
            return false;
        }
        // adds the elements to the input vector
        inputStringVector.push_back(stringVector[i]);
    }
    // runs the recursive function
    palindromeVector.clear();
    candidateStringVector.clear();
    recursiveFindPalindromes(candidateStringVector, inputStringVector);
    return true;
}

vector<vector<string>> FindPalindrome::toVector() const
{
    return palindromeVector;
}
