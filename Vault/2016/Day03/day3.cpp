#include <array>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

bool isTriangle(int a, int b, int c) { return (a + b > c) && (a + c > b) && (b + c > a); }

/** Helper to parse directions */
vector<string> getInput()
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

/** @brief Part2 read input in columns
 *
 * Example:
 * 101 301 501
 * 102 302 502
 * 103 303 503
 *
 * is read as triangles (101, 102, 103), (301, 302, 303), (501, 502, 503)
 */
void part2(vector<string>& input)
{
    int count = 0;
    for (size_t i = 0; i < input.size(); i += 3)
    {
        int a1, b1, c1;
        int a2, b2, c2;
        int a3, b3, c3;
        sscanf(input[i].c_str(), "%d %d %d", &a1, &b1, &c1);
        sscanf(input[i + 1].c_str(), "%d %d %d", &a2, &b2, &c2);
        sscanf(input[i + 2].c_str(), "%d %d %d", &a3, &b3, &c3);
        if (isTriangle(a1, a2, a3))
            count++;
        if (isTriangle(b1, b2, b3))
            count++;
        if (isTriangle(c1, c2, c3))
            count++;
    }
    cout << count << endl;
}

int main()
{
    vector<string> input = getInput();
    int count = 0;
    for (const string& line : input)
    {
        int a, b, c;
        sscanf(line.c_str(), "%d %d %d", &a, &b, &c);
        if (isTriangle(a, b, c))
            count++;
    }
    cout << count << endl;

    // part2(input);
    return 0;
}
