import unittest
import subprocess
import os
import sys

# Detect platform and set executable name
if os.name == "nt":
    CPP_EXECUTABLE = "ex_day1.exe"
else:
    CPP_EXECUTABLE = "ex_day1"


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


class TestDeliverPresents(unittest.TestCase):
    def test_empty(self):
        self.assertEqual(
            executable_cpp_to_test(""),
            -1,
        )

    def test_no_basement(self):
        self.assertEqual(
            executable_cpp_to_test("((("),
            -1,
        )
        self.assertEqual(
            executable_cpp_to_test("()()"),
            -1,
        )

    def test_basement_at_position_1(self):
        self.assertEqual(
            executable_cpp_to_test(")"),
            1,
        )

    def test_basement_at_position_5(self):
        self.assertEqual(
            executable_cpp_to_test("()())"),
            5,
        )

    def test_adv(self):
        # read input from input.txt
        adv_input = read_input_from_file("input.txt")
        self.assertEqual(
            executable_cpp_to_test(adv_input),
            1783,
        )


if __name__ == "__main__":
    unittest.main()
