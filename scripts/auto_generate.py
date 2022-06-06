from generate_inputs import *
from benchmark_export import *

print("Generating:")
print("\t", sys.argv[1], "valid sequences")
print("\t", sys.argv[2], "invalid sequences")
for i in range(int(sys.argv[1])):
    generate_valid_input(i, i)
for i in range(int(sys.argv[2])):
    generate_invalid_input(i, i)
print("Done.")
