import unittest
import subprocess
import os
import sys

# Detect platform and set executable name
if os.name == "nt":
    CPP_EXECUTABLE = "ex_day7.exe"
else:
    CPP_EXECUTABLE = "ex_day7"


# Helper to read input lines from a file
def read_input_from_file(filename):
    with open(
        os.path.join(
            os.path.dirname(__file__),
            filename,
        ),
        "r",
    ) as f:
        return f.read().strip()


# Helper to call the C++ executable with input as argument
def executable_cpp_to_test(directions):
    result = subprocess.run(
        [
            os.path.join(
                os.path.dirname(__file__),
                CPP_EXECUTABLE,
            ),
            directions,
        ],
        capture_output=True,
        text=True,
        input=directions,
    )
    return int(result.stdout.strip())


class TestWireCircuit(unittest.TestCase):
    def test_case_1(self):
        self.assertEqual(executable_cpp_to_test("123 -> a"), 123)

    def test_complex_case(self):
        multi_input = "\n".join(
            [
                "123 -> x",
                "456 -> y",
                "x AND y -> a",
                "x OR y -> e",
                "x LSHIFT 2 -> f",
                "y RSHIFT 2 -> g",
                "NOT x -> h",
                "NOT y -> i"
            ]
        )
        self.assertEqual(executable_cpp_to_test(multi_input), 72)

    def test_complex_case2(self):
        multi_input = "\n".join(
            [
                "123 -> x",
                "456 -> yy",
                "x AND yy -> d",
                "x OR yy -> e",
                "x LSHIFT 2 -> f",
                "yy RSHIFT 2 -> a",
                "NOT x -> h",
                "NOT y -> i"
            ]
        )
        self.assertEqual(executable_cpp_to_test(multi_input), 114)

    def test_adv(self):
        # read input from input.txt
        adv_input = read_input_from_file("input.txt")
        self.assertEqual(executable_cpp_to_test(adv_input), 956)


if __name__ == "__main__":
    unittest.main()
