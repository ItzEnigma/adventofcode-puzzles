import unittest
import subprocess
import os
import sys

# Detect platform and set executable name
if os.name == "nt":
    CPP_EXECUTABLE = "ex_day3.exe"
else:
    CPP_EXECUTABLE = "ex_day3"


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


class IsValidTriangle(unittest.TestCase):
    def test_empty(self):
        self.assertEqual(
            executable_cpp_to_test(""),
            0,
        )

    def test_case_1(self):
        self.assertEqual(
            executable_cpp_to_test("5 10 25"),
            0,
        )

    def test_case_2(self):
        self.assertEqual(
            executable_cpp_to_test("3 4 5"),
            1,
        )

    def test_case_3(self):
        input: str = """5 10 25\n3 4 5\n5 5 5"""
        self.assertEqual(
            executable_cpp_to_test(input),
            2,
        )

    def test_case_4(self):
        input: str = """3 3 3\n1 1 2\n2 2 3\n10 10 10\n1 2 3\n-4 2 0"""
        self.assertEqual(
            executable_cpp_to_test(input),
            3,
        )

    def test_adv(self):
        # read input from input.txt
        adv_input = read_input_from_file("input.txt")
        self.assertEqual(
            executable_cpp_to_test(adv_input),
            993,
        )


if __name__ == "__main__":
    unittest.main()
