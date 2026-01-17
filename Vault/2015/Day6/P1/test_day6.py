import unittest
import subprocess
import os
import sys

# Detect platform and set executable name
if os.name == "nt":
    CPP_EXECUTABLE = "ex_day6.exe"
else:
    CPP_EXECUTABLE = "ex_day6"


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


class TestLitLights(unittest.TestCase):
    def test_case_1(self):
        self.assertEqual(executable_cpp_to_test("turn on 0,0 through 999,999"), 1000000)

    def test_case_2(self):
        self.assertEqual(executable_cpp_to_test("toggle 0,0 through 0,0"), 1)

    def test_case_3(self):
        self.assertEqual(executable_cpp_to_test("turn off 0,0 through 999,999"), 0)

    def test_case_4(self):
        self.assertEqual(executable_cpp_to_test("turn on 4,10 through 88,690"), (88 - 4 + 1) * (690 - 10 + 1))

    def test_complex_case(self):
        multi_input = "\n".join(
            [
                "turn on 0,0 through 999,999",
                "toggle 0,0 through 0,0",
                "turn off 0,0 through 999,999",
                "turn on 4,10 through 88,690",
                "turn off 0,0 through 999,999",
                "turn on 4,10 through 88,690",
                "turn on 4,10 through 88,690",
            ]
        )
        self.assertEqual(executable_cpp_to_test(multi_input), 57885)

    def test_empty_input(self):
        self.assertEqual(executable_cpp_to_test(""), 0)

    def test_adv(self):
        # read input from input.txt
        adv_input = read_input_from_file("input.txt")
        self.assertEqual(executable_cpp_to_test(adv_input), 377891)


if __name__ == "__main__":
    unittest.main()
