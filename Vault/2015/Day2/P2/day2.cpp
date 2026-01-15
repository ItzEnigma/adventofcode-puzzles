#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * smallest perimeter of any one face : 2 * (smallest + second smallest) +
 * bow length : l * w * h
 *
 * Input: 2x3x4
 */
long long calculateRibbon(string dimensionsStr)
{
    long long l, w, h;
    // Parse the dimensions from the input string
    sscanf(dimensionsStr.c_str(), "%lldx%lldx%lld", &l, &w, &h);

    vector<long long> dims = {l, w, h};
    sort(dims.begin(), dims.end());

    long long smallestPerimeter = 2 * (dims[0] + dims[1]);
    long long bowLength = l * w * h;

    return smallestPerimeter + bowLength;
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
    vector<string> inputList = getInputLines();
    long long totalRibbon = 0;
    for (const string& dimensionsStr : inputList)
    {
        totalRibbon += calculateRibbon(dimensionsStr);
    }

    cout << totalRibbon << endl;

    return 0;
}

/**
 * Possible Other Solutions:
 * 1. Using a struct to represent the box dimensions and encapsulate ribbon calculations.
 * 2. Find smaller perimeter using min_element and nth_element instead of sorting.
 */