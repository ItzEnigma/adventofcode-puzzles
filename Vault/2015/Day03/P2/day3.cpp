#include <algorithm>
#include <iostream>
#include <set>

using namespace std;

static void move(int& x, int& y, char dir)
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
        break;
    }
}

/**
 * ^ : move north
 * > : move east
 * v : move south
 * < : move west
 * Visits start position (0,0) and delivers a present, how many houses receive
 * at least one present? Where Robo-Santa also delivers presents by alternating
 * moves with Santa.
 *
 * Input: ^>v<
 */
long long deliverPresents(string directions)
{
    set<pair<int, int>> visitedHousesSanta;
    set<pair<int, int>> visitedHousesRobo;
    int xSanta = 0, ySanta = 0;
    int xRobo = 0, yRobo = 0;
    visitedHousesSanta.insert({xSanta, ySanta}); // Starting position
    visitedHousesRobo.insert({xRobo, yRobo});    // Starting position

    for (size_t i = 0; i < directions.size(); ++i)
    {
        if (i % 2 == 0)
        {
            move(xSanta, ySanta, directions[i]);
            visitedHousesSanta.insert({xSanta, ySanta});
        }
        else
        {
            move(xRobo, yRobo, directions[i]);
            visitedHousesRobo.insert({xRobo, yRobo});
        }
    }

    // Combine the sets to get all unique visited houses
    set<pair<int, int>> allVisitedHouses = visitedHousesSanta;
    allVisitedHouses.insert(visitedHousesRobo.begin(), visitedHousesRobo.end());

    return allVisitedHouses.size();
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