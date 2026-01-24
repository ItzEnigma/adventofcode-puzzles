import unittest
import subprocess
import os
import sys

# Detect platform and set executable name
if os.name == "nt":
    CPP_EXECUTABLE = "ex_day10.exe"
else:
    CPP_EXECUTABLE = "ex_day10"


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


class TestLookAndSay(unittest.TestCase):
    def test_case_1(self):
        test_input = "1"
        self.assertEqual(executable_cpp_to_test(test_input), 82350)

    def test_case_2(self):
        test_input = "11"
        self.assertEqual(executable_cpp_to_test(test_input), 107312)

    def test_case_3(self):
        test_input = "21"
        self.assertEqual(executable_cpp_to_test(test_input), 139984)

    def test_case_empty(self):
        test_input = ""
        self.assertEqual(executable_cpp_to_test(test_input), 0)

    def test_case_long(self):
        test_input = "111221"
        self.assertEqual(executable_cpp_to_test(test_input), 237746)

    def test_adv(self):
        # read input from input.txt
        adv_input = read_input_from_file("input.txt")
        self.assertEqual(executable_cpp_to_test(adv_input), 360154)


if __name__ == "__main__":
    unittest.main()
