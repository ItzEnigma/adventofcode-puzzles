#include <array>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

/**
 * Keypad:
    1 2 3
    4 5 6
    7 8 9
 */

string getBathroomCode(const vector<string>& directions)
{
    string code{};
    constexpr pair<int, int> initialPosition{1, 1}; // button 5
    pair<int, int> currentPosition = initialPosition;

    for (const auto& direction : directions)
    {
        for (char step : direction)
        {
            pair<int, int> nextPosition = currentPosition;

            switch (step)
            {
            case 'U':
                nextPosition.second -= 1;
                break;
            case 'D':
                nextPosition.second += 1;
                break;
            case 'L':
                nextPosition.first -= 1;
                break;
            case 'R':
                nextPosition.first += 1;
                break;
            }

            // Check if the next position is within the bounds of the keypad
            if (nextPosition.first >= 0 && nextPosition.first <= 2 && nextPosition.second >= 0 &&
                nextPosition.second <= 2)
            {
                currentPosition = nextPosition; // Move to the next position
            }
        }
        // Append the current position (button) to the code string
        code += to_string(currentPosition.second * 3 + currentPosition.first + 1);
    }

    return code;
}

/** Helper to parse directions */
vector<string> parseDirections()
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
    vector<string> directions = parseDirections();
    string code = getBathroomCode(directions);
    cout << code << endl;
    return 0;
}

/**
 * Possible Other Solutions:
 *  - Use a 2D array to represent the keypad and directly access the button values based on the current position.
 *  - Implement a mapping of directions to coordinate changes and use it to update the current position
 *  - Use a set of valid positions to check if the next position is valid instead of checking bounds.
 */
