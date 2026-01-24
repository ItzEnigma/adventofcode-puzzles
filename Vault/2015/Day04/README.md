# Day 4 — Approach Overview

## Solution Approach

The solution for Day 4 is implemented in Python. The problem is solved by bruteforcing through numbers starting from 1 till we find the lowest number that, when concatenated with the given secret key and hashed using MD5, produces a hash that starts with a specified number of leading zeros (default is 5).

## Why Python?

Python was chosen over C++ for this puzzle to leverage its simplicity and ease of handling strings and hashing. Python's `hashlib` library provides a straightforward way to compute MD5 hashes, making the implementation concise and readable.

> Going with C++ would just require adding the external library for MD5 hashing, which adds unnecessary complexity for this particular problem.
