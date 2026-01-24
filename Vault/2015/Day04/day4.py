import hashlib
import unittest

"""
Find the lowest positive number that, when appended to the secret key,
produces an MD5 hash that starts with at least N-leading zeroes.
"""


def find_lowest_number_with_leading_zeros(secret_key, leading_zeros=5):
    number = 1
    target_prefix = "0" * leading_zeros

    while True:
        test_string = f"{secret_key}{number}"
        # To get MD5 hash --> convert to hexadecimal
        hash_result = hashlib.md5(test_string.encode()).hexdigest()

        if hash_result.startswith(target_prefix):
            return number

        number += 1


class TestFindLowestNumberWithLeadingZeros(unittest.TestCase):
    def test_case_1(self):
        self.assertEqual(find_lowest_number_with_leading_zeros("abcdef"), 609043)

    def test_case_2(self):
        self.assertEqual(find_lowest_number_with_leading_zeros("pqrstuv"), 1048970)

    def test_case_3(self):
        self.assertEqual(find_lowest_number_with_leading_zeros("xyz"), 23331)

    def test_case_4(self):
        self.assertEqual(find_lowest_number_with_leading_zeros("hello"), 105484)

    def test_case_5(self):
        self.assertEqual(find_lowest_number_with_leading_zeros("world"), 1982938)

    def test_adv(self):
        # Actual puzzle input
        secret_key = "yzbqklnj"
        self.assertEqual(find_lowest_number_with_leading_zeros(secret_key), 282749)

    def test_adv_part2(self):
        # Actual puzzle input for part 2
        secret_key = "yzbqklnj"
        self.assertEqual(find_lowest_number_with_leading_zeros(secret_key, leading_zeros=6), 9962624)


if __name__ == "__main__":
    unittest.main()
