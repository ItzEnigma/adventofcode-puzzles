import unittest
import subprocess
import os
import sys

# Detect platform and set executable name
if os.name == "nt":
    CPP_EXECUTABLE = "ex_day5.exe"
else:
    CPP_EXECUTABLE = "ex_day5"


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


class TestNiceStrings(unittest.TestCase):
    def test_case_1(self):
        self.assertEqual(executable_cpp_to_test("ugknbfddgicrmopn"), 1)

    def test_case_2(self):
        self.assertEqual(executable_cpp_to_test("aaa"), 1)

    def test_case_3(self):
        self.assertEqual(executable_cpp_to_test("jchzalrnumimnmhp"), 0)

    def test_case_4(self):
        self.assertEqual(executable_cpp_to_test("haegwjzuvuyypxyu"), 0)

    def test_case_5(self):
        self.assertEqual(executable_cpp_to_test("dvszwmarrgswjxmb"), 0)

    def test_complex_case(self):
        multi_input = "\n".join(
            [
                "ugknbfddgicrmopn",  # nice
                "auu",  # nice
                "jchzalrnumimnmhp",  # naughty
                "haegwjzuvuyypxyu",  # naughty
                "dvszwmarrgswjxmb",  # naughty
                "abcdde",  # naughty
                "acgddefbziou",  # nice (example)
            ]
        )
        self.assertEqual(executable_cpp_to_test(multi_input), 3)

    def test_empty_input(self):
        self.assertEqual(executable_cpp_to_test(""), 0)

    def test_adv(self):
        # read input from input.txt
        adv_input = read_input_from_file("input.txt")
        self.assertEqual(executable_cpp_to_test(adv_input), 258)


if __name__ == "__main__":
    unittest.main()
