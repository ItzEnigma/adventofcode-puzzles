#include <cstdint>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

/** Generates the next look-and-say string from the input string */
string lookAndSayString(const string& input)
{
    string result = "";

    for (size_t i = 0; i < input.length();)
    {
        char currentChar = input[i];
        size_t count = 1;
        while (i + count < input.length() && input[i + count] == currentChar)
        {
            ++count;
        }
        result += to_string(count) + currentChar;
        i += count;
    }

    return result;
}

int main()
{
    string inp;
    cin >> inp;

    string result = inp;
    constexpr int iterations = 40; // Change to 50 for part 2

    for (int i = 0; i < iterations; ++i)
    {
        result = lookAndSayString(result);
    }

    cout << result.length() << endl;

    return 0;
}