#include <cstdint>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

void incrementPassword(string& password)
{
    for (int i = static_cast<int>(password.length()) - 1; i >= 0; --i)
    {
        if (password[i] == 'z')
        {
            password[i] = 'a';
        }
        else
        {
            password[i] += 1;
            break;
        }
    }
}

/** 3 Rules:
 * 1. Increasing straight: at least one sequence like abc, bcd, … xyz
 * 2. No i, o, or l
 * 3. At least two different, non-overlapping pairs: aa, bb, cc, etc.
 */
bool hasStraight(const string& password)
{
    for (size_t i = 0; i < password.length() - 2; ++i)
    {
        if (password[i + 1] == password[i] + 1 && password[i + 2] == password[i] + 2)
        {
            return true;
        }
    }
    return false;
}

bool hasNoInvalidChars(const string& password)
{
    for (char c : password)
    {
        if (c == 'i' || c == 'o' || c == 'l')
        {
            return false;
        }
    }
    return true;
}

bool hasTwoNonOverlappingPairs(const string& password)
{
    set<char> pairs;
    for (size_t i = 0; i < password.length() - 1;)
    {
        if (password[i] == password[i + 1])
        {
            pairs.insert(password[i]);
            i += 2; // Skip the next character to avoid overlapping
        }
        else
        {
            ++i;
        }
    }
    return pairs.size() >= 2;
}

string getNextPassword(const string& oldPassword)
{
    string result = oldPassword;

    do
    {
        incrementPassword(result);
    } while (!hasStraight(result) || !hasNoInvalidChars(result) || !hasTwoNonOverlappingPairs(result));

    return result;
}

int main()
{
    string inp;
    cin >> inp;

    if (inp.length() < 8)
    {
        cerr << "Password must be at least 8 characters long." << endl;
        return 1;
    }

    string result = getNextPassword(inp);

    cout << result << endl;

    return 0;
}