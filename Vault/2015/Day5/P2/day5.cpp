#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

/** Nice String is one with all following properties:
 * 1. Contains a pair of any two letters that appears at least twice in the string without overlapping
 * 2. Contains at least one letter which repeats with exactly one letter between them

/**
 * Returns true if the string is a nice string based on the defined properties.
 *
 * Input: qjhvhtzxzqqjkmpb
 */
bool isNiceString(string str)
{
    bool hasPair = false;
    bool hasRepeatWithGap = false;

    // Check for pairs that appear at least twice without overlapping
    for (size_t i = 0; i < str.length() - 1; ++i)
    {
        string pair = str.substr(i, 2);
        hasPair = (str.find(pair, i + 2) != string::npos);
        if (hasPair)
            break;
    }

    // Check for repeating letters with one letter in between
    for (size_t i = 0; i < str.length() - 2; ++i)
    {
        if (str[i] == str[i + 2])
        {
            hasRepeatWithGap = true;
            break;
        }
    }
    return hasPair && hasRepeatWithGap;
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
    int niceStringCount = 0;
    for (const string& line : inputLines)
    {
        if (isNiceString(line))
        {
            niceStringCount++;
        }
    }

    cout << niceStringCount << endl;

    return 0;
}

/**
 * Possible Other Solutions:
 * 1. Regex-Based Approach: Use regular expressions to identify the required patterns in the strings.
 * 2. Sliding Window Technique: Implement a sliding window to efficiently check for pairs and repeating letters.
 *
 */