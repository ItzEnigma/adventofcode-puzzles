import unittest
import subprocess
import os
import sys

# Detect platform and set executable name
if os.name == "nt":
    CPP_EXECUTABLE = "ex_day9.exe"
else:
    CPP_EXECUTABLE = "ex_day9"


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


class TestShortestHamiltonianPath(unittest.TestCase):
    def test_case_1(self):
        test_input = "\n".join(
            [
                "London to Dublin = 464",
                "London to Belfast = 518",
                "Dublin to Belfast = 141",
            ]
        )
        self.assertEqual(executable_cpp_to_test(test_input), 605)

    def test_case_2(self):
        test_input = "\n".join(
            [
                "A to B = 10",
                "A to C = 15",
                "B to C = 20",
            ]
        )
        self.assertEqual(executable_cpp_to_test(test_input), 25)

    def test_case_large(self):
        test_input = "\n".join(
            [
                "A to B = 5",
                "A to C = 10",
                "A to D = 8",
                "B to C = 7",
                "B to D = 12",
                "C to D = 6",
            ]
        )
        self.assertEqual(executable_cpp_to_test(test_input), 18)

    def test_case_many_edges(self):
        test_input = "\n".join(
            [
                "A to B = 3",
                "A to C = 4",
                "A to D = 2",
                "A to E = 7",
                "B to C = 5",
                "B to D = 6",
                "B to E = 8",
                "C to D = 1",
                "C to E = 9",
                "D to E = 10",
            ]
        )
        self.assertEqual(executable_cpp_to_test(test_input), 14)

    def test_adv(self):
        # read input from input.txt
        adv_input = read_input_from_file("input.txt")
        self.assertEqual(executable_cpp_to_test(adv_input), 141)


if __name__ == "__main__":
    unittest.main()
