#include <algorithm>
#include <cstdint>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

constexpr uint8_t TOTAL_TEASPOONS = 100;

struct Ingredient
{
    string name;
    int64_t capacity = 0;
    int64_t durability = 0;
    int64_t flavor = 0;
    int64_t texture = 0;
    int64_t calories = 0;
};

/** The following solution is a brute-force search over all possible ingredient combinations
 * of N teaspoons summing to TOTAL_TEASPOONS (100).  Since there are only 4 ingredients, we can use 3 nested loops
 * and compute the 4th ingredient's amount as the remainder.
 */
uint64_t getHighestScore(const vector<Ingredient>& ingredients, uint8_t totalTeaspoons)
{
    long best = 0;

    for (int a = 0; a <= totalTeaspoons; ++a)
        for (int b = 0; b <= totalTeaspoons - a; ++b)
            for (int c = 0; c <= totalTeaspoons - a - b; ++c)
            {
                int d = totalTeaspoons - a - b - c;

                long cap = a * ingredients[0].capacity + b * ingredients[1].capacity + c * ingredients[2].capacity +
                           d * ingredients[3].capacity;

                long dur = a * ingredients[0].durability + b * ingredients[1].durability +
                           c * ingredients[2].durability + d * ingredients[3].durability;

                long fla = a * ingredients[0].flavor + b * ingredients[1].flavor + c * ingredients[2].flavor +
                           d * ingredients[3].flavor;

                long tex = a * ingredients[0].texture + b * ingredients[1].texture + c * ingredients[2].texture +
                           d * ingredients[3].texture;

                /** Ignore negatives */
                cap = std::max(0L, cap);
                dur = std::max(0L, dur);
                fla = std::max(0L, fla);
                tex = std::max(0L, tex);

                long score = cap * dur * fla * tex;
                best = std::max(best, score);
            }

    return best;
}

uint64_t getHighestScoreWithCalories(const vector<Ingredient>& ingredients, uint8_t totalTeaspoons)
{
    long best = 0;

    for (int a = 0; a <= totalTeaspoons; ++a)
        for (int b = 0; b <= totalTeaspoons - a; ++b)
            for (int c = 0; c <= totalTeaspoons - a - b; ++c)
            {
                int d = totalTeaspoons - a - b - c;

                long cap = a * ingredients[0].capacity + b * ingredients[1].capacity + c * ingredients[2].capacity +
                           d * ingredients[3].capacity;

                long dur = a * ingredients[0].durability + b * ingredients[1].durability +
                           c * ingredients[2].durability + d * ingredients[3].durability;

                long fla = a * ingredients[0].flavor + b * ingredients[1].flavor + c * ingredients[2].flavor +
                           d * ingredients[3].flavor;

                long tex = a * ingredients[0].texture + b * ingredients[1].texture + c * ingredients[2].texture +
                           d * ingredients[3].texture;

                long cal = a * ingredients[0].calories + b * ingredients[1].calories + c * ingredients[2].calories +
                           d * ingredients[3].calories;

                if (cal != 500)
                    continue;

                cap = std::max(0L, cap);
                dur = std::max(0L, dur);
                fla = std::max(0L, fla);
                tex = std::max(0L, tex);

                long score = cap * dur * fla * tex;
                best = std::max(best, score);
            }

    return best;
}

/** Helper to parse input lines into Ingredient structures */
vector<Ingredient> parseInput(const vector<string>& inputLines)
{
    vector<Ingredient> ingredients;
    for (const string& line : inputLines)
    {
        Ingredient ingredient;
        // Example line: "Cinnamon: capacity 2, durability 3, flavor -2, texture -1, calories 3"
        ingredient.name = line.substr(0, line.find(':'));
        sscanf(line.c_str(),
               "%*[^:]: capacity %ld, durability %ld, flavor %ld, texture %ld, calories %ld",
               &ingredient.capacity,
               &ingredient.durability,
               &ingredient.flavor,
               &ingredient.texture,
               &ingredient.calories);
        ingredients.push_back(ingredient);
    }

    return ingredients;
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
    vector<Ingredient> ingredients = parseInput(inputLines);

    uint64_t highestScore = getHighestScore(ingredients, TOTAL_TEASPOONS);
    cout << highestScore << endl;

    // Part 2
    uint64_t highestScoreWithCalories = getHighestScoreWithCalories(ingredients, TOTAL_TEASPOONS);
    cout << highestScoreWithCalories << endl;

    return 0;
}

/**
 * Possible Other Solutions (as current solution is brute-force):
 * - Use Recursive Backtracking to explore all combinations of ingredient amounts summing to TOTAL_TEASPOONS.
 * - Implement Dynamic Programming to build up solutions for smaller totals and combine them.
 *
 */