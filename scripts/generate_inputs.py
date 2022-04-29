#This script is for generating test inputs.
import random
import hashlib
import sys
LOCATION_PREFIX="../feeds/in/"
GROUP_ID = "9"
GENERATION_METHOD = "Python"



def write_to_textfile(length,sequence,valid=True):
    salt = str(random.randint(0,10000000))
    identifier = hashlib.sha1(salt.encode("UTF-8")).hexdigest()
    identifier_str = str(identifier)[:5]
    file_name ="-".join([
        GROUP_ID,str(length),
        "VALID" if valid else "INVALID"
        ,GENERATION_METHOD,
        identifier_str,
    ])
    file_name = LOCATION_PREFIX+file_name+".txt"
    with open(file_name,"w") as f:
        f.write("".join([str(length),"\n"]))
        #generate one liner
        f.write("".join([str(i)+" " for i in sequence]).rstrip())



def generate_valid_input(min_size=1,max_size=50):
    size = random.randint(min_size,max_size)
    degrees = [random.randint(0,size - 1) for i in range(size)]
    write_to_textfile(size,degrees)

def generate_invalid_input(min_size=1,max_size=50):
    size = random.randint(min_size,max_size)
    degrees = [random.randint(max_size,max_size * 2) for i in range(size)]
    write_to_textfile(size,degrees,False)

if __name__ == "__main__":
    if len(sys.argv) <= 1:
        print("Enter parameters for generating inputs.")
    else:
        valid_count = int(sys.argv[1])
        invalid_count = int(sys.argv[2])
        print("Generating:")
        print("\t-",valid_count," valid inputs")
        print("\t-",invalid_count," invalid inputs")

        for i in range(valid_count):
            generate_valid_input()
        for i in range(invalid_count):
            generate_invalid_input()

        print("Done.")
