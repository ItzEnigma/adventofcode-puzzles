#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

/** Nice String is one with all following properties:
 * 1. It contains at least three vowels (aeiou only)
 * 2. It contains at least one letter that appears twice in a row
 * 3. It does not contain the strings "ab", "cd", "pq", or "xy"
 */
constexpr int MIN_VOWELS = 3;
const set<string> forbiddenStrings = {"ab", "cd", "pq", "xy"};

/**
 * Returns true if the string is a nice string based on the defined properties.
 *
 * Input: ugknbfddgicrmopn
 */
bool isNiceString(string str)
{
    int vowelCount = 0;
    bool hasDoubleLetter = false;

    for (size_t i = 0; i < str.size(); ++i)
    {
        char ch = str[i];
        // Check for vowels
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
        {
            vowelCount++;
        }

        // Check for double letters
        if (i > 0 && str[i] == str[i - 1])
        {
            hasDoubleLetter = true;
        }

        // Check for forbidden strings
        if (i > 0)
        {
            string pair = str.substr(i - 1, 2);
            if (forbiddenStrings.find(pair) != forbiddenStrings.end())
            {
                return false; // Contains a forbidden string
            }
        }
    }

    return (vowelCount >= MIN_VOWELS) && hasDoubleLetter;
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
 * 1. Using Regular Expressions to identify nice strings.
 *
 */