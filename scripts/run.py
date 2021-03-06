from generate_inputs import *
from benchmark_export import *
import subprocess
import os

# Helper script for construction of whole program.

if __name__ == "__main__":
    if len(sys.argv) <= 1:
        print("Enter parameters for generating inputs.")
    else:
        if (sys.argv[3] == "--cleanup"):
            os.system("rm ../feeds/in/*.txt && rm ../feeds/out/*.txt ../feeds/out/*.dot ../feeds/assets/*")
        print("Generating:")
        print("\t", sys.argv[1], "sequences")
        for i in range(0, int(sys.argv[1])):
            generate_valid_input(i, i)
        print("Done.")
        if (sys.argv[2] == "--generate"):
            print("Generation phase:")
            os.system("pwd")
            os.system("cd ../cmake-build-debug && cmake .. && cmake --build . && ./rgg \"../feeds/in/\" ")
        export_graph("../feeds/assets/results.csv", "../feeds/assets/plot.png")
        export_pair_graphs("../feeds/assets/results.csv")
        print("Done.\nYou can find the resulting benchmarks and plots under feeds/assets/")
