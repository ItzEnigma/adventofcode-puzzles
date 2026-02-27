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
    return result.stdout.strip()


class GetBathroomCode(unittest.TestCase):
    def test_empty(self):
        self.assertEqual(
            executable_cpp_to_test(""),
            "",
        )

    def test_case_1(self):
        input: str = "UUL\nRLL\nDLLL\nRRLU"
        self.assertEqual(
            executable_cpp_to_test(input),
            "1142",
        )

    def test_case_2(self):
        input: str = "ULL\nRRDDD\nLURDL\nUUUUD"
        self.assertEqual(
            executable_cpp_to_test(input),
            "1985",
        )

    def test_case_3(self):
        input: str = "DLL\nRRR\nLLL\nRRL"
        self.assertEqual(
            executable_cpp_to_test(input),
            "7978",
        )

    def test_adv(self):
        # read input from input.txt
        adv_input = read_input_from_file("input.txt")
        self.assertEqual(
            executable_cpp_to_test(adv_input),
            "45973",
        )


if __name__ == "__main__":
    unittest.main()
