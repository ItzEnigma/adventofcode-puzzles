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
def executable_cpp_to_test(input_str):
    result = subprocess.run(
        [
            os.path.join(
                os.path.dirname(__file__),
                CPP_EXECUTABLE,
            ),
            input_str,
        ],
        capture_output=True,
        text=True,
        input=input_str,
    )
    return int(result.stdout.strip())


class GetShortestDistanceToHq(unittest.TestCase):
    def test_empty(self):
        self.assertEqual(
            executable_cpp_to_test(""),
            0,
        )

    def test_case_1(self):
        self.assertEqual(
            executable_cpp_to_test("R2, L3"),
            5,
        )

    def test_case_2(self):
        self.assertEqual(
            executable_cpp_to_test("L2, R3"),
            5,
        )

    def test_case_3(self):
        self.assertEqual(
            executable_cpp_to_test("R2, R2, R2"),
            2,
        )

    def test_case_4(self):
        self.assertEqual(
            executable_cpp_to_test("R5, L5, R5, R3"),
            12,
        )

    def test_adv(self):
        # read input from input.txt
        adv_input = read_input_from_file("input.txt")
        self.assertEqual(
            executable_cpp_to_test(adv_input),
            234,
        )


if __name__ == "__main__":
    unittest.main()
