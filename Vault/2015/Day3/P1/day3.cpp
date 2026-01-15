#include <algorithm>
#include <iostream>
#include <set>

using namespace std;

/**
 * ^ : move north
 * > : move east
 * v : move south
 * < : move west
 * Visits start position (0,0) and delivers a present, how many houses receive
 * at least one present?
 *
 * Input: ^>v<
 */
long long deliverPresents(string directions)
{
    set<pair<int, int>> visitedHouses;
    int x = 0, y = 0;
    visitedHouses.insert({x, y}); // Starting position
    for (char dir : directions)
    {
        switch (dir)
        {
        case '^':
            y += 1;
            break;
        case 'v':
            y -= 1;
            break;
        case '>':
            x += 1;
            break;
        case '<':
            x -= 1;
            break;
        default:
            // Ignore invalid characters
            continue;
        }
        visitedHouses.insert({x, y});
    }

    return visitedHouses.size();
}

int main()
{
    string directions;
    getline(cin, directions);
    long long totalHouses = deliverPresents(directions);
    cout << totalHouses << endl;

    return 0;
}

/**
 * Possible Other Solutions:
 * 1. Use a map or unordered_map to track visited houses for potentially faster lookups.
 * 2. Represent directions as coordinate deltas in a map for cleaner code. :
 *   map<char, pair<int, int>> directionDeltas = { {'^', {0, 1}}, {'v', {0, -1}}, {'>', {1, 0}}, {'<', {-1, 0}} };
 *
 */