// Project 3 -- XML Parsing Project

/** XML parsing class implementation.
    @file XMLParser.cpp */

#include <string>
#include <assert.h>
#include "XMLParser.hpp"

// helper function to test if a tag is valid
bool validTag(string tagString)
{
    //Checks if tag is empty
    if (tagString == "")
    {
        return false;
    }

    //Checks for invalid characters
    if ((tagString.find_first_of("!\"#$%&\'()*+,/;<=>?@[\\]^`{|}~)") != -1 || tagString.front() == '.' || tagString.front() == '-'))
    {
        return false;
    }

    //Checks for whitespace
    for (int i = 0; i < tagString.length(); i++)
    {
        if (std::isspace(tagString[i]))
        {
            return false;
        }
    }
    return true;
}

// TODO: Implement the constructor here
XMLParser::XMLParser()
{
    elementNameBag = new Bag<std::string>;
    parseStack = new Stack<std::string>;

} // end default constructor

// TODO: Implement the destructor here
XMLParser::~XMLParser()
{
    clear();
    delete elementNameBag;
    delete parseStack;
} // end destructor

// TODO: Implement the tokenizeInputString method
bool XMLParser::tokenizeInputString(const std::string &inputString)
{

    tokenized = false;
    clear();

    //trims whitespace from the outside of the string
    std::string trimmedString = inputString;
    while (std::isspace(trimmedString.front()))
    {
        trimmedString.erase(0, 1);
    }
    while (std::isspace(trimmedString.back()))
    {
        trimmedString.pop_back();
    }

    // finds the position of the initial bracket character
    int currentBracket = trimmedString.find_first_of("<>");
    int nextBracket = 0;
    // iterates through the string, creating substrings between pairs of brackets, until the last closing bracket is reached
    do
    {
        // Creates a Tokenstruct for the next token
        TokenStruct tolkien;
        // Checks to see if the string contains a bracket
        if (trimmedString.find_first_of("<>") == -1)
        {
            //If string is blank returns false, if not, the string is content
            if (trimmedString == "")
            {
                tokenizedInputVector.clear();
                return false;
            }
            tolkien.tokenType = CONTENT;
            tolkien.tokenString = trimmedString;
            return true;
        }

        // finds the position of the next bracket character
        nextBracket = trimmedString.find_first_of("<>", currentBracket + 1);
        if (nextBracket == -1)
        {
            tokenizedInputVector.clear();
            return false;
        }

        // if the next bracket is the same as the current one ("< ... <" or "> ... >"), the string is invalid and function returns false
        if (trimmedString.at(currentBracket) == trimmedString.at(nextBracket))
        {
            tokenizedInputVector.clear();
            return false;
        }

        // creates a substring of the string in between the brackets
        std::string tokenString = trimmedString.substr(currentBracket + 1, nextBracket - (currentBracket + 1));

        // if the current bracket is ">", then the next token type is CONTENT
        if (trimmedString.at(currentBracket) == '>')
        {
            tolkien.tokenType = CONTENT;

            //Checks to see if the content is all whitespace, if it is, continues to the next iteration
            bool isAllSpace = true;
            for (int i = 0; i < tokenString.length(); i++)
            {
                if (!std::isspace(tokenString[i]))
                {
                    isAllSpace = false;
                    break;
                }
            }
            if (isAllSpace)
            {
                currentBracket = nextBracket;
                continue;
            }

            tolkien.tokenString = tokenString;
            tokenizedInputVector.push_back(tolkien);
            // continues to next iteration, the character checks are not applied to CONTENT tokens
            currentBracket = nextBracket;
            continue;
        }

        // checks if the string is an end tag
        if (tokenString.front() == '/')
        {
            tolkien.tokenType = END_TAG;
            tokenString = tokenString.substr(1);

            if (!validTag(tokenString))
            {
                tokenizedInputVector.clear();
                return false;
            }

            tolkien.tokenString = tokenString;
            tokenizedInputVector.push_back(tolkien);
            currentBracket = nextBracket;
            continue;
        }

        // checks if the string is an empty tag
        else if (tokenString.back() == '/')
        {
            tolkien.tokenType = EMPTY_TAG;

            // removes the '/'
            tokenString.pop_back();

            // reads until the first space, rest of tagString is attributes and can be ignored
            for (int i = 0; i < tokenString.length(); i++)
            {
                if (std::isspace(tokenString[i]))
                {
                    tokenString = tokenString.substr(0, i);
                    break;
                }
            }

            if (!validTag(tokenString))
            {
                tokenizedInputVector.clear();
                return false;
            }

            tolkien.tokenString = tokenString;
            tokenizedInputVector.push_back(tolkien);
            currentBracket = nextBracket;
            continue;

            tokenizedInputVector.push_back(tolkien);
        }

        // checks if the string is a delceration tag
        else if (tokenString.front() == '?' && tokenString.back() == '?')
        {
            tolkien.tokenType = DECLARATION;
            tokenString.erase(0, 1);
            tokenString.pop_back();
            tolkien.tokenString = tokenString;
            tokenizedInputVector.push_back(tolkien);
            currentBracket = nextBracket;
            continue;
        }

        // last case is a start tag
        else
        {
            tolkien.tokenType = START_TAG;

            // reads until the first space, rest of tagString is attributes and can be ignored
            for (int i = 0; i < tokenString.length(); i++)
            {
                if (std::isspace(tokenString[i]))
                {
                    if (i == 0)
                    {
                        tokenizedInputVector.clear();
                        return false;
                    }
                    tokenString = tokenString.substr(0, i);
                    break;
                }
            }

            if (!validTag(tokenString))
            {
                tokenizedInputVector.clear();
                return false;
            }

            tolkien.tokenString = tokenString;
            tokenizedInputVector.push_back(tolkien);
            currentBracket = nextBracket;
            continue;

            tokenizedInputVector.push_back(tolkien);
        }
        //Looops until the next bracket isn't the last bracket in the string.
    } while (nextBracket != trimmedString.length() - 1);
    //sets tokenized to true upon successful tokenization
    tokenized = true;
    return true;
} // end

// TODO: Implement the parseTokenizedInput method here
bool XMLParser::parseTokenizedInput()
{
    //Returns false if tokenization was not successful
    if (tokenized == false)
    {
        return false;
    }
    //elements before a root has been found are treated differently
    bool rootFound = false;
    //loops through the vector
    for (size_t i = 0; i < tokenizedInputVector.size(); i++)
    {
        TokenStruct tolkien = tokenizedInputVector[i];

        // Testing to see if the beginning is only declarations until the root element, and if root encapsulates entire rest of file
        if (rootFound == false)
        {
            //declerations are added normally
            if (tolkien.tokenType == DECLARATION)
            {
                elementNameBag->add(tolkien.tokenString);
                continue;
            }
            //if the first start tag matches the last tag in the file, then it is valid, if not, then returns false
            else if (tolkien.tokenType == START_TAG)
            {
                if (tokenizedInputVector.back().tokenString != tolkien.tokenString)
                {
                    clear();
                    return false;
                }

                rootFound = true;
                parseStack->push(tolkien.tokenString);
                elementNameBag->add(tolkien.tokenString);
                continue;
            }
            //if the element is anything other than a decleration or start tag, return false
            else
            {
                clear();
                return false;
            }
        }

        //decleration and empty are added to the bag
        if (tolkien.tokenType == DECLARATION)
        {
            elementNameBag->add(tolkien.tokenString);
        }

        if (tolkien.tokenType == EMPTY_TAG)
        {
            elementNameBag->add(tolkien.tokenString);
        }

        //start tags are added to bag and stack
        if (tolkien.tokenType == START_TAG)
        {
            elementNameBag->add(tolkien.tokenString);
            parseStack->push(tolkien.tokenString);
        }

        //for proper nesting, the end tag must be the same as the top of the stack, if so, stack is popped
        //if not, then return false
        if (tolkien.tokenType == END_TAG)
        {
            if (parseStack->peek() != tolkien.tokenString)
            {
                clear();
                return false;
            }
            parseStack->pop();
        }
    }

    //if the stack is not empty at the end, return false
    if(!parseStack->isEmpty()){
        return false;
    }

    return true;
}

// TODO: Implement the clear method here
void XMLParser::clear()
{
    tokenizedInputVector.clear();
    parseStack->clear();
    elementNameBag->clear();
}

vector<TokenStruct> XMLParser::returnTokenizedInput() const
{
    return tokenizedInputVector;
}

// TODO: Implement the containsElementName method
bool XMLParser::containsElementName(const std::string &inputString) const
{
    if (elementNameBag->isEmpty())
    {
        throw std::logic_error("Bag is empty");
    }
    return elementNameBag->contains(inputString);
}

// TODO: Implement the frequencyElementName method
int XMLParser::frequencyElementName(const std::string &inputString) const
{
    if (elementNameBag->isEmpty())
    {
        throw std::logic_error("Bag is empty");
    }
    return elementNameBag->getFrequencyOf(inputString);
}
