# This script is for generating test inputs.
import random
import sys

LOCATION_PREFIX = "../feeds/in/"
GROUP_ID = "9"
GENERATION_METHOD = "Python"


def write_to_textfile(length, sequence, identifier, valid=True):
    identifier_str = str(identifier)
    file_name = "-".join([
        GROUP_ID, str(length),
        identifier_str,
        GENERATION_METHOD,
        "VALID" if valid else "INVALID",

    ])
    file_name = LOCATION_PREFIX + file_name + ".txt"
    with open(file_name, "w") as f:
        f.write("".join([str(length), "\n"]))
        f.write("".join([str(i) + " " for i in sequence]).rstrip())


def generate_valid_input(identifier, min_size=1, max_size=50):
    size = random.randint(min_size, max_size)
    degrees = [random.randint(0, size - 1) for i in range(size)]
    degrees.sort(reverse=True)
    write_to_textfile(size, degrees, identifier)


def generate_invalid_input(identifier, min_size=1, max_size=50):
    size = random.randint(min_size, max_size)
    degrees = [random.randint(max_size, max_size * 2) for i in range(size)]
    degrees.sort(reverse=True)
    write_to_textfile(size, degrees, identifier, False)
