import unittest
import subprocess
import os
import sys

# Detect platform and set executable name
if os.name == "nt":
    CPP_EXECUTABLE = "ex_day13.exe"
else:
    CPP_EXECUTABLE = "ex_day13"


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
def executable_cpp_to_test(input_name):
    result = subprocess.run(
        [
            os.path.join(
                os.path.dirname(__file__),
                CPP_EXECUTABLE,
            ),
            input_name,
        ],
        capture_output=True,
        text=True,
        input=input_name,
    )
    return result.stdout.strip()


class TestGetMaxHappiness(unittest.TestCase):
    def test_case_1(self):
        test_input = \
"""
Alice would gain 54 happiness units by sitting next to Bob.
Alice would lose 79 happiness units by sitting next to Carol.
Alice would lose 2 happiness units by sitting next to David.
Bob would gain 83 happiness units by sitting next to Alice.
Bob would lose 7 happiness units by sitting next to Carol.
Bob would lose 63 happiness units by sitting next to David.
Carol would lose 62 happiness units by sitting next to Alice.
Carol would gain 60 happiness units by sitting next to Bob.
Carol would gain 55 happiness units by sitting next to David.
David would gain 46 happiness units by sitting next to Alice.
David would lose 7 happiness units by sitting next to Bob.
David would gain 41 happiness units by sitting next to Carol.
"""
        self.assertEqual(executable_cpp_to_test(test_input.strip()), "330")

    def test_adv(self):
        # read input from input.txt
        adv_input = read_input_from_file("input.txt")
        self.assertEqual(executable_cpp_to_test(adv_input), "709")

    def test_adv2(self):
        # read input from input.txt
        adv_input = read_input_from_file("input2.txt")
        self.assertEqual(executable_cpp_to_test(adv_input), "668")

if __name__ == "__main__":
    unittest.main()
