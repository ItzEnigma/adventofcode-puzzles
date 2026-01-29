#include <cstdint>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

long long getSumOfAllNumbers(const string& jsonString)
{
    long long sum = 0;
    size_t i = 0;
    while (i < jsonString.length())
    {
        if ((jsonString[i] == '-') || isdigit(jsonString[i]))
        {
            size_t start = i;
            ++i;
            while (i < jsonString.length() && isdigit(jsonString[i]))
            {
                ++i;
            }
            sum += stoll(jsonString.substr(start, i - start));
        }
        else
        {
            ++i;
        }
    }
    return sum;
}

int main()
{
    string input;
    getline(cin, input);

    long long result = getSumOfAllNumbers(input);
    cout << result << endl;

    return 0;
}