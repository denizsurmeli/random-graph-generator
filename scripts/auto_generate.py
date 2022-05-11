from generate_inputs import *
from benchmark_export import *

print("Generating:")
print("\t", sys.argv[1], "sequences")
for i in range(int(sys.argv[1])):
    if (i % 5 == 0):
        generate_invalid_input(i, i)
    else:
        generate_valid_input(i, i)
print("Done.")
