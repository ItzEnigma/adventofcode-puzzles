import unittest
import os
import subprocess

"""
Test template for C++ executables.
- Replace `executable_name` with the actual name of your C++ executable.
- Replace `TestSuiteName` with the name of your test suite.
- Add test methods in the `TestSuiteName` class as needed.

Make sure to have the C++ executable compiled and available in the same directory as this test file.
"""

# Detect platform and set executable name
if os.name == "nt":
    CPP_EXECUTABLE = "executable_name.exe"
else:
    CPP_EXECUTABLE = "executable_name"


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
        [os.path.join(os.path.dirname(__file__), CPP_EXECUTABLE), input_name],
        capture_output=True,
        text=True,
        input=input_name,
    )
    return int(result.stdout.strip())


class TestSuiteName(unittest.TestCase):
    def test_example1(self):
        self.assertEqual(executable_cpp_to_test("example_input1"), "expected_output1")

    def test_adv(self):
        # read input from input.txt
        adv_input = read_input_from_file("input.txt")
        self.assertEqual(executable_cpp_to_test(adv_input), "expected_adv_output")
