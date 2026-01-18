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
    int noOfCharsOfCodeEncoded;
};

/**
 * @brief Calculates the number of characters of code and in encoded form for a given string
 * @param str The input string representing a string literal
 * @return CharsTaken struct containing counts of characters of code and in encoded form
 *
 * This function processes escape sequences and surrounding quotes to determine
 * the number of characters present in the code representation versus the encoded form.
 *
 * @note Where encoding adds extra characters for escape sequences and surrounding quotes.
 * @note opening and closing quotes are counted as well again in encoded form.
 *
 * @example "aaa\aaa\x27" --> "\"aaa\\aaa\\x27\""
 */
CharsTaken calculateNumberOfCharactersEncoded(string str)
{
    CharsTaken result = {0, 0};

    for (size_t i = 0; i < str.length(); ++i)
    {
        // Count every character in the code representation
        result.noOfCharsOfCode++;
        result.noOfCharsOfCodeEncoded++;

        if (str[i] == '\\')
        {
            // Handle escape sequences
            if (i + 1 < str.length())
            {
                if (str[i + 1] == 'x' && i + 3 < str.length() && isxdigit(str[i + 2]) && isxdigit(str[i + 3]))
                {
                    // Hexadecimal escape sequence \xNN
                    result.noOfCharsOfCode += 3;        // x, and two hex digits
                    result.noOfCharsOfCodeEncoded += 4; // \, x, and two hex digits \x50 --> \\x50
                    i += 3;                             // Skip the next three characters
                }
                else
                {
                    // Other escape sequences like \\ or \"
                    result.noOfCharsOfCode++;           // The escaped character
                    result.noOfCharsOfCodeEncoded += 3; // \ and the escaped character \\ --> \\\\ , \" --> \\\"
                    i++;                                // Skip the next character
                }
            }
        }
        else if (str[i] == '\"')
        {
            result.noOfCharsOfCodeEncoded += 2; // Each quote adds two characters in encoded form \"
            continue;
        }
        else
        {
            // Regular character
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
        CharsTaken lineCounts = calculateNumberOfCharactersEncoded(line);
        total.noOfCharsOfCode += lineCounts.noOfCharsOfCode;
        total.noOfCharsOfCodeEncoded += lineCounts.noOfCharsOfCodeEncoded;
    }

    cout << (total.noOfCharsOfCodeEncoded - total.noOfCharsOfCode) << endl;
    return 0;
}

/**
 * Possible Other Solutions:
 * - Using Regular Expressions to identify and count escape sequences.
 * - Using a state machine to parse the string character by character.
 * - Preprocessing the string to replace escape sequences with placeholders before counting.
 *
 */