#include <algorithm>
#include <cstdint>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct node
{
    string name;
    string nextPerson;
    int64_t happinessChange;
};

int64_t getMaxHappiness(const vector<node>& nodes)
{
    /**
     * 1. Build lookup structures
     *   - Map each person's happiness change towards every other person
     *   - Set of all unique people
     * 2. Generate all permutations of people (n!)
     *  - For each permutation, calculate total happiness and track the best
     */
    int64_t bestHappiness = 0;

    unordered_map<string, unordered_map<string, int64_t>> happinessMap;
    set<string> people;
    /// Build the happiness map and people set
    for (const auto& n : nodes)
    {
        happinessMap[n.name][n.nextPerson] = n.happinessChange;
        people.insert(n.name);
        people.insert(n.nextPerson);
    }

    /// Build a vector of people for permutation
    vector<string> peopleList(people.begin(), people.end());
    sort(peopleList.begin(), peopleList.end()); // ensure starting order

    /** Note: this is n! can be improved by fixing the first person */
    /// Try all permutations to find the maximum happiness
    size_t n = peopleList.size();

    do
    {
        int64_t currentHappiness = 0;
        for (size_t i = 0; i < n; ++i)
        {
            const int leftIdx = (i - 1 + n) % n;
            const int rightIdx = (i + 1) % n;
            currentHappiness += happinessMap[peopleList[i]][peopleList[leftIdx]];
            currentHappiness += happinessMap[peopleList[i]][peopleList[rightIdx]];
        }
        bestHappiness = max(bestHappiness, currentHappiness);
    } while (next_permutation(peopleList.begin(), peopleList.end()));


    return bestHappiness;
}

/** Helper to parse the input gain/lose and build the list */
vector<node> parseInput(const vector<string>& inputLines)
{
    vector<node> nodes;
    for (const string& line : inputLines)
    {
        node n;
        size_t pos = 0;
        size_t isGain = line.find(" gain ");
        size_t isLose = line.find(" lose ");

        // Get the person's name
        n.name = line.substr(0, line.find(" would"));
        // Get the happiness change
        if (isGain != string::npos)
        {
            pos = isGain + 6; // length of " gain "
            size_t endPos = line.find(" happiness units", pos);
            n.happinessChange = stoi(line.substr(pos, endPos - pos));
        }
        else if (isLose != string::npos)
        {
            pos = isLose + 6; // length of " lose "
            size_t endPos = line.find(" happiness units", pos);
            n.happinessChange = -stoi(line.substr(pos, endPos - pos));
        }
        // Get the next person's name
        size_t nextPos = line.find(" to ");
        n.nextPerson = line.substr(nextPos + 4, line.length() - nextPos - 5); // remove the final '.'
        nodes.push_back(n);
    }
    return nodes;
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
    vector<node> nodes = parseInput(inputLines);

    int64_t maxHappiness = getMaxHappiness(nodes);
    cout << maxHappiness << endl;

    return 0;
}