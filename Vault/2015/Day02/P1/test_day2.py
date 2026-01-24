import unittest
import subprocess
import os
import sys

# Detect platform and set executable name
if os.name == "nt":
    CPP_EXECUTABLE = "ex_day2.exe"
else:
    CPP_EXECUTABLE = "ex_day2"


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


class TestTotalWrappingPaper(unittest.TestCase):
    def test_case_1(self):
        self.assertEqual(executable_cpp_to_test("2x3x4"), 58)

    def test_case_2(self):
        self.assertEqual(executable_cpp_to_test("1x1x10"), 43)

    def test_complex_case(self):
        self.assertEqual(executable_cpp_to_test("2x3x4\n1x1x10"), 101)

    def test_empty_input(self):
        self.assertEqual(executable_cpp_to_test(""), 0)

    def test_large_input(self):
        large_input = """2x3x4
                        1x1x10
                        5x5x5
                        10x20x30
                        3x2x1
                        4x4x4
                        6x7x8"""
        self.assertEqual(executable_cpp_to_test(large_input), 3146)

    def test_adv(self):
        # read input from input.txt
        adv_input = read_input_from_file("input.txt")
        self.assertEqual(executable_cpp_to_test(adv_input), 1606483)


if __name__ == "__main__":
    unittest.main()
