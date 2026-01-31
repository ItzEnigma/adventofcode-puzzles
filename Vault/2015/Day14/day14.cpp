#include <algorithm>
#include <cstdint>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

enum class ReindeerState
{
    Flying,
    Resting
};

struct Reindeer
{
    string name;
    int64_t speed;        // in km/s
    int64_t flyDuration;  // in seconds
    int64_t restDuration; // in seconds

    // Runtime state
    ReindeerState state = ReindeerState::Flying;
    uint64_t timeInState = 0;
    uint64_t distanceTravelled = 0;
    uint64_t points = 0;
};

void updateReindeers(vector<Reindeer>& reindeers, uint64_t raceDuration)
{
    for (uint64_t t = 0; t < raceDuration; ++t)
    {
        // Update each reindeer's state and distance
        for (auto& r : reindeers)
        {
            if (r.state == ReindeerState::Flying)
            {
                r.distanceTravelled += r.speed;
                r.timeInState++;
                if (r.timeInState == r.flyDuration)
                {
                    r.state = ReindeerState::Resting;
                    r.timeInState = 0;
                }
            }
            else // Resting
            {
                r.timeInState++;
                if (r.timeInState == r.restDuration)
                {
                    r.state = ReindeerState::Flying;
                    r.timeInState = 0;
                }
            }
        }

        // Determine the maximum distance travelled so far
        uint64_t maxDistance = 0;
        for (const auto& r : reindeers)
        {
            if (r.distanceTravelled > maxDistance)
            {
                maxDistance = r.distanceTravelled;
            }
        }

        // Award points to reindeers that are tied for the lead
        for (auto& r : reindeers)
        {
            if (r.distanceTravelled == maxDistance)
            {
                r.points++;
            }
        }
    }
}

uint64_t getWinningReindeerDistance(const vector<Reindeer>& reindeers)
{
    uint64_t maxDistance = 0;
    for (const auto& r : reindeers)
    {
        if (r.distanceTravelled > maxDistance)
        {
            maxDistance = r.distanceTravelled;
        }
    }
    return maxDistance;
}

uint64_t getWinningReindeerPoints(const vector<Reindeer>& reindeers)
{
    uint64_t maxPoints = 0;
    for (const auto& r : reindeers)
    {
        if (r.points > maxPoints)
        {
            maxPoints = r.points;
        }
    }
    return maxPoints;
}

/** Helper to parse the input gain/lose and build the list */
vector<Reindeer> parseInput(const vector<string>& inputLines)
{
    vector<Reindeer> reindeers;
    for (const string& line : inputLines)
    {
        Reindeer r;
        // Example line: "Comet can fly 14 km/s for 10 seconds, but then must rest for 127 seconds."
        sscanf(line.c_str(),
               "%s can fly %ld km/s for %ld seconds, but then must rest for %ld seconds.",
               r.name.data(),
               &r.speed,
               &r.flyDuration,
               &r.restDuration);
        reindeers.push_back(r);
    }
    return reindeers;
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
    vector<Reindeer> reindeers = parseInput(inputLines);
    uint64_t raceDuration = 2503; // seconds

    updateReindeers(reindeers, raceDuration);
    uint64_t winningReindeerDistance = getWinningReindeerDistance(reindeers);
    cout << winningReindeerDistance << endl;

    // uint64_t winningReindeerPoints = getWinningReindeerPoints(reindeers);
    // cout << winningReindeerPoints << endl;
    return 0;
}