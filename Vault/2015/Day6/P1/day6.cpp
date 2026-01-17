#include <array>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

/** million lights */
array<array<bool, 1000>, 1000> lightsGrid = {false};

struct Command
{
    string operation; // "turn on", "turn off", "toggle"
    int x1;
    int y1;
    int x2;
    int y2;
};

/** Helper function to parse a command string into a Command struct */
Command parseCommand(const string& cmdStr)
{
    Command cmd;
    size_t pos = 0;

    if (cmdStr.find("turn on") == 0)
    {
        cmd.operation = "turn on";
        pos = 7;
    }
    else if (cmdStr.find("turn off") == 0)
    {
        cmd.operation = "turn off";
        pos = 8;
    }
    else if (cmdStr.find("toggle") == 0)
    {
        cmd.operation = "toggle";
        pos = 6;
    }

    // Parse coordinates
    sscanf(cmdStr.c_str() + pos, " %d,%d through %d,%d", &cmd.x1, &cmd.y1, &cmd.x2, &cmd.y2);

    return cmd;
}

/** Helper to count lit lights in the grid */
int getGridLitLights()
{
    int count = 0;
    for (const auto& row : lightsGrid)
    {
        for (bool light : row)
        {
            if (light)
                count++;
        }
    }
    return count;
}

/**
 * Lit lights of the grid based on the following properties and operations:
 * - Operations: "turn on", "turn off", "toggle"
 * - Coordinates: given as "x1,y1 through x2,y2" (inclusive)
 *
 * Input: turn on 0,0 through 999,999
 */
void countLitLights(string cmd)
{
    Command command = parseCommand(cmd);

    for (int i = command.x1; i <= command.x2; ++i)
    {
        for (int j = command.y1; j <= command.y2; ++j)
        {
            if (command.operation == "turn on")
            {
                lightsGrid[i][j] = true;
            }
            else if (command.operation == "turn off")
            {
                lightsGrid[i][j] = false;
            }
            else if (command.operation == "toggle")
            {
                lightsGrid[i][j] = !lightsGrid[i][j];
            }
        }
    }
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
    for (const string& line : inputLines)
    {
        countLitLights(line);
    }

    cout << getGridLitLights() << endl;
    return 0;
}

/**
 * Possible Other Solutions:
 * 1. Using Bitsets: Represent the grid using bitsets for memory efficiency and faster operations.
 * 2. Segment Trees: For large-scale grids, use segment trees to efficiently handle range updates and queries.
 * 3. Sparse Representation: If the grid is mostly off, use a sparse representation (like a set of coordinates) to track
 * only lit lights.
 *
 */