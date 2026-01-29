import unittest
import subprocess
import os
import sys

# Detect platform and set executable name
if os.name == "nt":
    CPP_EXECUTABLE = "ex_day12.exe"
else:
    CPP_EXECUTABLE = "ex_day12"


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


class TestSumOfAllNumbersInJsonExceptRed(unittest.TestCase):
    def test_case_1(self):
        test_input = "[1,2,3]"
        self.assertEqual(executable_cpp_to_test(test_input), "6")

    def test_case_2(self):
        test_input = '[1,{"c":"red","b":2},3]'
        self.assertEqual(executable_cpp_to_test(test_input), "4")

    def test_case_3(self):
        test_input = '[1,"red",5]'
        self.assertEqual(executable_cpp_to_test(test_input), "6")

    def test_case_4(self):
        test_input = '{"d":"red","e":[1,2,3,4],"f":5}'
        self.assertEqual(executable_cpp_to_test(test_input), "0")

    def test_cornerCase_1(self):
        test_input = '{"a":"bred","b":5}'
        self.assertEqual(executable_cpp_to_test(test_input), "5")

    def test_cornerCase_2(self):
        test_input = '{"a":"redd","b":5}'
        self.assertEqual(executable_cpp_to_test(test_input), "5")

    def test_cornerCase_3(self):
        test_input = '{"red":"a","b":5}'
        self.assertEqual(executable_cpp_to_test(test_input), "5")

    def test_case_empty(self):
        test_input = ""
        self.assertEqual(executable_cpp_to_test(test_input), "0")

    def test_case_empty_json(self):
        test_input = "[]"
        self.assertEqual(executable_cpp_to_test(test_input), "0")

    def test_adv(self):
        # read input from input.txt
        adv_input = read_input_from_file("input.txt")
        self.assertEqual(executable_cpp_to_test(adv_input), "87842")


if __name__ == "__main__":
    unittest.main()
