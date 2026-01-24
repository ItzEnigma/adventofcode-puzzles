#include <cstdint>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Parser
{
public:
    enum class Operation
    {
        AND,
        OR,
        LSHIFT,
        RSHIFT,
        NOT,
        ASSIGN,
        UNDEFINED = 6
    };

    // Helper function to trim whitespace (spaces, tabs) from both ends of a string
    static string trim(const string& str)
    {
        size_t start = str.find_first_not_of(" \t\n\r");
        if (start == string::npos)
            return "";
        size_t end = str.find_last_not_of(" \t\n\r");
        return str.substr(start, end - start + 1);
    }

    struct Instruction
    {
        Operation op;
        string input1;
        string input2; // optional, depending on operation
        string outputWire;
    };

    /** @brief Parses a single instruction line into an Instruction struct
     * @param line The instruction line as a string
     *
     * @note Supports operations: AND, OR, LSHIFT, RSHIFT, NOT, ASSIGN
     * @note removes leading/trailing whitespace from inputs and outputs to avoid
     * bugs due to formatting issues.
     *
     * @return Parsed Instruction struct
     */
    Instruction parseInstruction(const string& line)
    {
        Instruction instr;
        size_t pos = line.find("->");
        string expr = trim(line.substr(0, pos));
        instr.outputWire = trim(line.substr(pos + 2));

        if (expr.find("AND") != string::npos)
        {
            instr.op = Operation::AND;
            size_t andPos = expr.find("AND");
            instr.input1 = trim(expr.substr(0, andPos));
            instr.input2 = trim(expr.substr(andPos + 3));
        }
        else if (expr.find("OR") != string::npos)
        {
            instr.op = Operation::OR;
            size_t orPos = expr.find("OR");
            instr.input1 = trim(expr.substr(0, orPos));
            instr.input2 = trim(expr.substr(orPos + 2));
        }
        else if (expr.find("LSHIFT") != string::npos)
        {
            instr.op = Operation::LSHIFT;
            size_t lshiftPos = expr.find("LSHIFT");
            instr.input1 = trim(expr.substr(0, lshiftPos));
            instr.input2 = trim(expr.substr(lshiftPos + 6));
        }
        else if (expr.find("RSHIFT") != string::npos)
        {
            instr.op = Operation::RSHIFT;
            size_t rshiftPos = expr.find("RSHIFT");
            instr.input1 = trim(expr.substr(0, rshiftPos));
            instr.input2 = trim(expr.substr(rshiftPos + 6));
        }
        else if (expr.find("NOT") != string::npos)
        {
            instr.op = Operation::NOT;
            instr.input1 = trim(expr.substr(3));
        }
        else
        {
            instr.op = Operation::ASSIGN;
            instr.input1 = trim(expr);
        }

        return instr;
    }
};

class Circuit
{
public:
    Circuit() = default;

    /**
     * @brief Assembles the circuit from a list of instruction strings
     * @param instructions Vector of instruction strings
     *
     * Each instruction is parsed and stored in the circuitKit map
     * with the output wire as the key.
     */
    void assembleCircuit(const vector<string>& instructions)
    {
        Parser parser;
        for (const auto& line : instructions)
        {
            auto instr = parser.parseInstruction(line);
            circuitKit[instr.outputWire] = instr;
        }
    }

    /**
     * @brief Evaluates the signal on a given wire
     * @param wire The wire identifier
     * @return The signal value as uint16_t
     *
     * This function recursively evaluates the signal on the specified wire,
     * using memoization to cache previously computed values.
     */
    uint16_t evaluate(const string& wire)
    {
        // Numeric literal
        if (!wire.empty() && isdigit(wire[0]))
            return static_cast<uint16_t>(stoi(wire));

        // Cached?
        if (cache.count(wire))
            return cache[wire];

        auto it = circuitKit.find(wire);
        if (it == circuitKit.end())
            throw runtime_error("Unknown wire: " + wire);

        const Parser::Instruction& instr = it->second;

        uint16_t val1 = 0, val2 = 0;

        if (!instr.input1.empty())
            val1 = evaluate(instr.input1);

        if (!instr.input2.empty())
            val2 = evaluate(instr.input2);

        uint16_t result = 0;
        switch (instr.op)
        {
        case Parser::Operation::AND:
            result = val1 & val2;
            break;
        case Parser::Operation::OR:
            result = val1 | val2;
            break;
        case Parser::Operation::LSHIFT:
            result = val1 << val2;
            break;
        case Parser::Operation::RSHIFT:
            result = val1 >> val2;
            break;
        case Parser::Operation::NOT:
            result = static_cast<uint16_t>(~val1);
            break;
        case Parser::Operation::ASSIGN:
            result = val1;
            break;
        default:
            throw runtime_error("Invalid operation");
        }

        cache[wire] = result;
        return result;
    }

    /** @brief Gets the signal on a specified wire */
    uint16_t getSignal(const string& wire) { return evaluate(wire); }

    /** @brief Overrides the value of a specified wire */
    void overrideWire(const string& wire, uint16_t value)
    {
        // Override the instruction for the specified wire to be a direct assignment
        Parser::Instruction instr;
        instr.op = Parser::Operation::ASSIGN;
        instr.input1 = to_string(value);
        instr.outputWire = wire;
        circuitKit[wire] = instr;

        // Clear the cache to ensure re-evaluation with the new value
        cache.clear();
    }

private:
    unordered_map<string, Parser::Instruction> circuitKit;
    unordered_map<string, uint16_t> cache;
};

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
    Circuit circuit;
    circuit.assembleCircuit(inputLines);

    /** Part2 just overridding value and recalculating, uncomment to use
     *
     *  uint16_t signalA = circuit.getSignal("a");
     *  circuit.overrideWire("b", signalA);
     *  // expected output based on puzzle input : 40149
     */

    cout << circuit.getSignal("a") << endl; // Output the signal on wire "a"

    return 0;
}

/**
 * Possible Other Solutions:
 * - Implement iterative evaluation instead of recursion to avoid stack overflow on deep circuits.
 * - Use bitset for more complex bit manipulations if needed in future extensions.
 * - Add error handling for circular dependencies in the circuit.
 * - Extend the parser to support additional operations if the instruction set expands.
 * - Optimize memory usage by clearing the cache when not needed anymore.
 * - Implement unit tests for the parser and circuit evaluation to ensure correctness.
 */