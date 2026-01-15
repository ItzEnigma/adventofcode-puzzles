#include <iostream>

using namespace std;

// directions are '(', ')' where '(' means go up a floor and ')' means go down a floor
long long deliverPresents(string directions)
{
    long long floor = 0;
    for (char c : directions)
    {
        if (c == '(')
        {
            floor++;
        }
        else if (c == ')')
        {
            floor--;
        }
    }
    return floor;
}

int main()
{
    string directions;
    cin >> directions;
    cout << deliverPresents(directions) << endl;
    return 0;
}

/**
 * Possible Other Solutions:
 * 1. Using a stack to track floor changes then summing the stack values.
 */