from generate_inputs import *

if __name__ == "__main__":
    if len(sys.argv) <= 1:
        print("Enter parameters for generating inputs.")
    else:
        valid_count = int(sys.argv[1])
        invalid_count = int(sys.argv[2])
        print("Generating:")
        print("\t-", valid_count, " valid inputs")
        print("\t-", invalid_count, " invalid inputs")

        for i in range(valid_count):
            generate_valid_input(i)
        for i in range(invalid_count):
            generate_invalid_input(i)

        print("Done.")
