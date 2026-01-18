#include <cstdint>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct CharsTaken
{
    int noOfCharsOfCode;
    int noOfCharsInMemory;
};

/**
 * @brief Calculates the number of characters of code and in memory for a given string
 * @param str The input string representing a string literal
 * @return CharsTaken struct containing counts of characters of code and in memory
 *
 * This function processes escape sequences and surrounding quotes to determine
 * the actual number of characters that would be stored in memory versus the
 * number of characters present in the code representation.
 *
 * @example "aaa\aaa\x27" --> 7 characters in memory (aaaaaa') vs 13 in code
 */
CharsTaken calculateNumberOfCharacters(string str)
{
    CharsTaken result = {0, 0};

    for (size_t i = 0; i < str.length(); ++i)
    {
        result.noOfCharsOfCode++; // Count every character in the code representation

        if (str[i] == '\\')
        {
            // Handle escape sequences
            if (i + 1 < str.length())
            {
                if (str[i + 1] == 'x' && i + 3 < str.length() && isxdigit(str[i + 2]) && isxdigit(str[i + 3]))
                {
                    // Hexadecimal escape sequence \xNN
                    result.noOfCharsInMemory++;
                    result.noOfCharsOfCode += 3; // x, and two hex digits
                    i += 3;                      // Skip the next three characters
                }
                else
                {
                    // Other escape sequences like \\ or \"
                    result.noOfCharsInMemory++;
                    result.noOfCharsOfCode++; // The escaped character
                    i++;                      // Skip the next character
                }
            }
        }
        else if (str[i] == '\"')
        {
            // Ignore the surrounding quotes in memory count
            continue;
        }
        else
        {
            // Regular character
            result.noOfCharsInMemory++;
        }
    }

    return result;
}

/** Helper function to parse input lines to a list of strings */
static vector<string> getInputLines()
{
    vector<string> lines;
    string line;
    while (getline(cin, line))
    {
        if (line.empty())
            break; // skip empty lines if needed
        lines.push_back(line);
    }
    return lines;
}

int main()
{
    vector<string> inputLines = getInputLines();
    CharsTaken total = {0, 0};

    for (const string& line : inputLines)
    {
        CharsTaken lineCounts = calculateNumberOfCharacters(line);
        total.noOfCharsOfCode += lineCounts.noOfCharsOfCode;
        total.noOfCharsInMemory += lineCounts.noOfCharsInMemory;
    }

    cout << (total.noOfCharsOfCode - total.noOfCharsInMemory) << endl;
    return 0;
}

/**
 * Possible Other Solutions:
 * - Using regular expressions to identify and count escape sequences.
 * - Implementing a state machine to parse the string character by character.
 *
 */