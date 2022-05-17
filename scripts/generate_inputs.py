# This script is for generating test inputs.
import random
import sys

LOCATION_PREFIX = "../feeds/in/"
GROUP_ID = "9"
GENERATION_METHOD = "Python"


# Check a degree sequence is graphical or not
def havel_hakimi(seq):
    if len(seq) < 1 or all(deg == 0 for deg in seq):
        return True
    seq.sort()
    last = seq[len(seq) - 1]
    if last > len(seq) - 1:
        return False
    # remove last element
    seq.remove(last)
    # iterate seq backwards
    for num in range(len(seq) - 1, len(seq) - last - 1, -1):
        if seq[num] > 0:
            seq[num] -= 1
        else:
            return False
    # recursive call
    return havel_hakimi(seq)


# output to text files of the generated sequences
def write_to_textfile(length, sequence, identifier, valid=True):
    identifier_str = str(identifier)
    file_name = "-".join([
        GROUP_ID, str(length),
        identifier_str,
        GENERATION_METHOD,

    ])
    file_name = LOCATION_PREFIX + file_name + ".txt"
    with open(file_name, "w") as f:
        f.write("".join([str(length), "\n"]))
        f.write("".join([str(i) + " " for i in sequence]).rstrip())


### Following functions are self-explanatory we believe
def generate_valid_input(size, identifier, min_size=1, max_size=50):
    degrees = [random.randint(0, size - 1) for i in range(size)]
    if (not havel_hakimi(degrees.copy())):
        generate_valid_input(size, identifier, min_size, max_size)
    else:
        degrees.sort(reverse=True)
        write_to_textfile(size, degrees, identifier)


def generate_invalid_input(size, identifier, min_size=1, max_size=50):
    degrees = [random.randint(max_size, max_size * 2) for i in range(size)]
    degrees.sort(reverse=True)
    write_to_textfile(size, degrees, identifier, False)


def generate_input(identifier, min_size=1, max_size=50):
    size = random.randint(min_size, max_size)
    degrees = [random.randint(0, size - 1) for i in range(size)]
    degrees.sort(reverse=True)
    write_to_textfile(size, degrees, identifier, True)
