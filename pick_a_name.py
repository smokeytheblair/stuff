import sys
import argparse
import random


def pick_a_name(input_file):
    names = [name.strip() for name in list(input_file)]
    num = len(names)

    print(f"Choosing a name from {names}.")

    print(f"Creating a d{num}.")
    random.shuffle(names)
    print(names)

    print(f"Rolling the d{num}")
    pick = random.randrange(0, num)

    print(f"The winner is {names[pick]}")

def main():
    parser = argparse.ArgumentParser(description="Pick a name")
    parser.add_argument('file', type=argparse.FileType('r'))

    args = parser.parse_args()

    if len(sys.argv) > 1:
        with args.file as input_file:
            pick_a_name(input_file)


if __name__ == "__main__":
    main()