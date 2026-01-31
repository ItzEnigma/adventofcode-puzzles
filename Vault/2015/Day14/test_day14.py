import unittest
import subprocess
import os
import sys

# Detect platform and set executable name
if os.name == "nt":
    CPP_EXECUTABLE = "ex_day14.exe"
else:
    CPP_EXECUTABLE = "ex_day14"


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


class TestGetReindeerPoints(unittest.TestCase):
    def test_case_1(self):
        test_input = """
Comet can fly 14 km/s for 10 seconds, but then must rest for 127 seconds.
Dancer can fly 16 km/s for 11 seconds, but then must rest for 162 seconds.
"""
        self.assertEqual(executable_cpp_to_test(test_input.strip()), "1564")

    def test_adv(self):
        # read input from input.txt
        adv_input = read_input_from_file("input.txt")
        self.assertEqual(executable_cpp_to_test(adv_input), "1084")


if __name__ == "__main__":
    unittest.main()
