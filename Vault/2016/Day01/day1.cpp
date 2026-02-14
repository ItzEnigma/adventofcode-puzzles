#include <array>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

enum class Direction
{
    North,
    East,
    South,
    West
};

/** Helper to get ending location */
std::pair<int, int> getEndingLocation(std::vector<std::pair<char, int>> directions)
{
    std::pair<int, int> currentLocation = {0, 0};
    // 0 = north, 1 = east, 2 = south, 3 = west
    Direction currentDirection = Direction::North;

    for (const auto& [turnDirection, steps] : directions)
    {
        // Update direction based on turn
        if (turnDirection == 'R')
        {
            currentDirection = static_cast<Direction>((static_cast<int>(currentDirection) + 1) % 4);
        }
        else if (turnDirection == 'L')
        {
            currentDirection = static_cast<Direction>((static_cast<int>(currentDirection) + 3) % 4);
        }

        // Move in the current direction
        switch (currentDirection)
        {
        case Direction::North:
            currentLocation.second += steps;
            break;
        case Direction::East:
            currentLocation.first += steps;
            break;
        case Direction::South:
            currentLocation.second -= steps;
            break;
        case Direction::West:
            currentLocation.first -= steps;
            break;
        }
    }

    return currentLocation;
}

/** Helper to find first visited location twice */
std::pair<int, int> getFirstLocationVisitedTwice(std::vector<std::pair<char, int>> directions)
{
    std::pair<int, int> currentLocation = {0, 0};
    Direction currentDirection = Direction::North;

    auto pairHash = [](const std::pair<int, int>& p) { return std::hash<int>()(p.first) ^ std::hash<int>()(p.second); };
    unordered_set<std::pair<int, int>, decltype(pairHash)> visitedLocations(0, pairHash);
    visitedLocations.insert(currentLocation);

    for (const auto& [turnDirection, steps] : directions)
    {
        // Update direction based on turn
        if (turnDirection == 'R')
        {
            currentDirection = static_cast<Direction>((static_cast<int>(currentDirection) + 1) % 4);
        }
        else if (turnDirection == 'L')
        {
            currentDirection = static_cast<Direction>((static_cast<int>(currentDirection) + 3) % 4);
        }

        // Move step by step in the current direction
        for (int i = 0; i < steps; ++i)
        {
            switch (currentDirection)
            {
            case Direction::North:
                currentLocation.second += 1;
                break;
            case Direction::East:
                currentLocation.first += 1;
                break;
            case Direction::South:
                currentLocation.second -= 1;
                break;
            case Direction::West:
                currentLocation.first -= 1;
                break;
            }

            // Check if this location has been visited before
            if (visitedLocations.count(currentLocation) > 0)
            {
                return currentLocation; // Found the first location visited twice
            }
            visitedLocations.insert(currentLocation);
        }
    }

    return {0, 0}; // Default return if no location is visited twice (should not happen with valid input)
}

/** Helper to build directions array */
// directions are 'R', 'L' where 'R' means turn right and 'L' means turn left
// followed by a number of steps to take in that direction
vector<pair<char, int>> buildDirectionsArray(string directions)
{
    /** Example: R2, L3, R1 would be parsed into:
     * [
     *   {'R', 2},
     *   {'L', 3},
     *   {'R', 1}
     * ]
     */
    vector<pair<char, int>> result;

    for (size_t i = 0; i < directions.size();)
    {
        char turnDirection = directions[i];
        ++i;

        string stepsStr;
        while (i < directions.size() && isdigit(directions[i]))
        {
            stepsStr += directions[i];
            ++i;
        }

        int steps = stoi(stepsStr);
        result.emplace_back(turnDirection, steps);

        i += 2; // Skip ", " after each direction
    }

    return result;
}


long long getShortestDistanceToHq(std::vector<std::pair<char, int>> directions)
{
    /************ FOR PART 2, ENABLE THIS CODE AND COMMENT OUT THE CALL TO getEndingLocation() ************/
    bool secondPart = false; /** NOTE: test-cases are not adjusted for part2 */
    /******************************************************************************************************/

    if (secondPart)
    {
        std::pair<int, int> firstLocationVisitedTwice = getFirstLocationVisitedTwice(directions);
        return abs(firstLocationVisitedTwice.first) + abs(firstLocationVisitedTwice.second);
    }
    else
    {
        std::pair<int, int> endLocation = getEndingLocation(directions);
        // Manhattan distance from (0, 0) to endLocation
        return abs(endLocation.first) + abs(endLocation.second);
    }
}

int main()
{
    string directions;
    getline(cin, directions);
    std::vector<std::pair<char, int>> parsedDirections = buildDirectionsArray(directions);
    cout << getShortestDistanceToHq(parsedDirections) << endl;
    return 0;
}

/**
 * Possible Other Solutions:
 * 1. Instead of using a hash set to track visited locations, we could use a 2D grid (e.g., a vector of vectors) to mark
 * visited locations. This would be more memory-intensive but could simplify the logic for checking if a location has
 * been visited.
 *
 * 2. We could also use a more compact representation for directions, such as encoding the direction and steps into a
 * single integer
 *
 * 3. Instead of using a switch statement to update the current location based on the direction, we could use an array
 * of direction vectors (e.g., [(0, 1), (1, 0), (0, -1), (-1, 0)]) and update the location by multiplying the direction
 * vector by the number of steps.
 */
