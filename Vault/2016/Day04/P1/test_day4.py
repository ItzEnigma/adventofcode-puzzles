import unittest
import subprocess
import os
import sys

# Detect platform and set executable name
if os.name == "nt":
    CPP_EXECUTABLE = "ex_day4.exe"
else:
    CPP_EXECUTABLE = "ex_day4"


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


# Helper to call the C++ executable with input through stdin
def executable_cpp_to_test(input_str):
    result = subprocess.run(
        [
            os.path.join(
                os.path.dirname(__file__),
                CPP_EXECUTABLE,
            ),
        ],
        capture_output=True,
        text=True,
        input=input_str,
    )
    return int(result.stdout.strip())


class SumOfRealRoomsSectorIds(unittest.TestCase):
    def test_empty(self):
        self.assertEqual(
            executable_cpp_to_test(""),
            0,
        )

    def test_case_1(self):
        self.assertEqual(
            executable_cpp_to_test("aaaaa-bbb-z-y-x-123[abxyz]"),
            123,
        )

    def test_case_2(self):
        self.assertEqual(
            executable_cpp_to_test(
                "a-b-c-d-e-f-g-h-987[abcde]\nnot-a-real-room-404[oarel]\ntotally-real-room-200[decoy]"
            ),
            1391,
        )

    def test_case_3(self):
        input: str = (
            """abx-yz-123[abxyz]\na-b-c-d-e-f-g-h-987[abcde]\nnot-a-real-room-404[oarel]\ntotally-real-room-200[decoy]"""
        )
        self.assertEqual(
            executable_cpp_to_test(input),
            1514,
        )

    def test_case_4(self):
        input: str = """ghijkl-987[ghijk]"""
        self.assertEqual(
            executable_cpp_to_test(input),
            987,
        )

    def test_adv(self):
        # read input from input.txt
        adv_input = read_input_from_file("input.txt")
        self.assertEqual(
            executable_cpp_to_test(adv_input),
            185371,
        )


if __name__ == "__main__":
    unittest.main()
