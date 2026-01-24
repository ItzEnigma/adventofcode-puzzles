#include <algorithm>
#include <cstdint>
#include <iostream>
#include <optional>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

/** Typical Shortest Hamiltonian path problem solution using permutations
 * This solution is not optimal for large datasets but works for small inputs.
 */

using namespace std;

struct Edge
{
    string from;
    string to;
    int distance;
};

// find shortest distance between the first node and itself visiting all nodes exactly once
optional<int> findShortestDistance(const vector<Edge>& adjMatrix)
{
    /**
     * Approach:
     * - Extract unique nodes from edges.
     * - Use permutations to try all possible paths starting and ending at the first node.
     * - Track the minimum distance found.
     * - Return nullopt if no valid path exists.
     */

    if (adjMatrix.empty())
        return nullopt;

    // Extract unique nodes
    set<string> nodes;
    for (const auto& e : adjMatrix)
    {
        nodes.insert(e.from);
        nodes.insert(e.to);
    }

    // Build distance lookup
    unordered_map<string, unordered_map<string, int>> dist;
    for (const auto& e : adjMatrix)
    {
        dist[e.from][e.to] = e.distance;
    }

    // create a list of nodes for permutation sorted at the beginning
    vector<string> nodeList(nodes.begin(), nodes.end());
    sort(nodeList.begin(), nodeList.end());

    // Try all permutations to find the shortest path
    int best = INT32_MAX;
    do
    {
        int total = 0;
        bool valid = true;

        for (size_t i = 1; i < nodeList.size(); ++i)
        {
            const string& from = nodeList[i - 1];
            const string& to = nodeList[i];

            if (!dist[from].count(to))
            {
                valid = false;
                break;
            }
            total += dist[from][to];
        }

        if (valid)
            best = min(best, total);

    } while (next_permutation(nodeList.begin(), nodeList.end()));

    return best == INT32_MAX ? nullopt : optional<int>(best);
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

/** Helper function to parse input lines to a list of strings */
static vector<Edge> buildAdjMatrix(const vector<string>& inputLines)
{
    vector<Edge> adjMatrix;
    // remove white spaces in each line
    for (const auto& line : inputLines)
    {
        size_t pos1 = line.find(" to ");
        size_t pos2 = line.find(" = ");
        if (pos1 != string::npos && pos2 != string::npos)
        {
            string from = line.substr(0, pos1);
            string to = line.substr(pos1 + 4, pos2 - (pos1 + 4));
            int distance = stoi(line.substr(pos2 + 3));
            adjMatrix.push_back({from, to, distance});
            adjMatrix.push_back({to, from, distance}); // assuming undirected graph
        }
    }
    return adjMatrix;
}

int main()
{
    vector<string> inputLines = getInputLines();
    vector<Edge> adjMatrix = buildAdjMatrix(inputLines);

    optional<int> shortestDistance = findShortestDistance(adjMatrix);
    if (shortestDistance)
    {
        cout << *shortestDistance << endl;
    }
    else
    {
        cout << "No valid round trip found." << endl;
    }

    return 0;
}

/**
 * Possible Other Solutions:
 * - Dynamic Programming with Bitmasking: More efficient for larger graphs.
 * - Approximation Algorithms: For very large datasets where exact solutions are impractical.
 * - Heuristic Methods: Such as Genetic Algorithms or Simulated Annealing for near-optimal solutions.
 *
 */