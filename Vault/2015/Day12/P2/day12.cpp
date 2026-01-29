#include <iostream>
#include <string>
using namespace std;

long long parse(const string& s, size_t& i);

long long parseNumber(const string& s, size_t& i)
{
    bool neg = false;
    if (s[i] == '-')
    {
        neg = true;
        i++;
    }
    long long val = 0;
    while (i < s.size() && isdigit(s[i]))
    {
        val = val * 10 + (s[i] - '0');
        i++;
    }
    return neg ? -val : val;
}

string parseString(const string& s, size_t& i)
{
    string result;
    i++; // skip opening "
    while (s[i] != '"')
    {
        result += s[i++];
    }
    i++; // skip closing "
    return result;
}

long long parseArray(const string& s, size_t& i)
{
    long long sum = 0;
    i++; // skip '['
    while (s[i] != ']')
    {
        sum += parse(s, i);
        if (s[i] == ',')
            i++;
    }
    i++; // skip ']'
    return sum;
}

// Returns the sum of all numbers in the object, or 0 if "red" is found (but not in keys)
long long parseObject(const string& s, size_t& i)
{
    long long sum = 0;
    bool hasRed = false;
    i++; // skip '{'

    while (s[i] != '}')
    {
        // key
        (void)parseString(s, i);
        i++; // skip ':'

        // value
        if (s[i] == '"')
        {
            string val = parseString(s, i);
            if (val == "red")
                hasRed = true;
        }
        else
        {
            sum += parse(s, i);
        }

        if (s[i] == ',')
            i++;
    }

    i++; // skip '}'
    return hasRed ? 0 : sum;
}

long long parse(const string& s, size_t& i)
{
    if (s[i] == '{')
        return parseObject(s, i);
    if (s[i] == '[')
        return parseArray(s, i);
    if (s[i] == '"')
    {
        parseString(s, i);
        return 0;
    }
    return parseNumber(s, i);
}

int main()
{
    string input;
    getline(cin, input);

    size_t i = 0;
    cout << parse(input, i) << endl;
    return 0;
}
