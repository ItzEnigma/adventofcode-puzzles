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
    def test_case_1(self):
        self.assertEqual(executable_cpp_to_test("^>v<"), 3)

    def test_case_2(self):
        self.assertEqual(executable_cpp_to_test("^v^v^v^v^v"), 11)

    def test_complex_case(self):
        self.assertEqual(executable_cpp_to_test("^^>>vv<<"), 4)

    def test_empty_input(self):
        self.assertEqual(executable_cpp_to_test(""), 1)

    def test_large_input(self):
        large_input = "^" * 1000 + ">" * 1000 + "v" * 1000 + "<" * 1000
        self.assertEqual(executable_cpp_to_test(large_input), 2000)
    
    def test_large2_input(self):
        large_input = "^v" * 1000 + "><" * 1000
        self.assertEqual(executable_cpp_to_test(large_input), 4001)

    def test_adv(self):
        # read input from input.txt
        adv_input = read_input_from_file("input.txt")
        self.assertEqual(executable_cpp_to_test(adv_input), 2639)


if __name__ == "__main__":
    unittest.main()
