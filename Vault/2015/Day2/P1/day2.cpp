#include <iostream>
#include <vector>

using namespace std;

/**
 * surface area of the box, which is 2*l*w + 2*w*h + 2*h*l
 * plus the area of the smallest side.
 * Input: 20x3x11
 */
long long calculateWrappingPaper(string dimensionsStr)
{
    long long l, w, h;
    // Parse the dimensions from the input string
    sscanf(dimensionsStr.c_str(), "%lldx%lldx%lld", &l, &w, &h);

    long long smallestSideArea = min((l * w), min((w * h), (h * l)));
    long long surfaceArea = (2 * l * w) + (2 * w * h) + (2 * h * l);

    return surfaceArea + smallestSideArea;
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
    long long totalWrappingPaper = 0;
    for (const string& dimensionsStr : inputList)
    {
        totalWrappingPaper += calculateWrappingPaper(dimensionsStr);
    }

    cout << totalWrappingPaper << endl;

    return 0;
}

/**
 * Possible Other Solutions:
 * 1. Using STL algorithms to compute areas and find the minimum side area.
 * 2. Using a struct to represent the box dimensions and encapsulate area calculations.
 */