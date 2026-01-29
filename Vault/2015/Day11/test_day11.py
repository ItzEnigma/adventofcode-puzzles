import unittest
import subprocess
import os
import sys

# Detect platform and set executable name
if os.name == "nt":
    CPP_EXECUTABLE = "ex_day11.exe"
else:
    CPP_EXECUTABLE = "ex_day11"


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


class TestGetNextPassword(unittest.TestCase):
    def test_case_1(self):
        test_input = "abcdefgh"
        self.assertEqual(executable_cpp_to_test(test_input), "abcdffaa")

    def test_case_2(self):
        test_input = "ghijklmn"
        self.assertEqual(executable_cpp_to_test(test_input), "ghjaabcc")

    def test_case_3(self):
        test_input = "xzzyzzzz"
        self.assertEqual(executable_cpp_to_test(test_input), "xzzzaabc")

    def test_case_empty(self):
        test_input = ""
        # Error : Password must be at least 8 characters long
        self.assertEqual(executable_cpp_to_test(test_input), "")

    def test_adv(self):
        # read input from input.txt
        adv_input = read_input_from_file("input.txt")
        self.assertEqual(executable_cpp_to_test(adv_input), "cqjxxyzz")


if __name__ == "__main__":
    unittest.main()
