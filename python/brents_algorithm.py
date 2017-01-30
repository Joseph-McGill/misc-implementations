import sha3

## Joseph McGill
## Fall 2016
##
# A semi-pure implementation of Brent's cylce finding algorithm
# It is modified to keep track of the previously found hashes
# The SHA3 implementation used can be downloaded from here
# https://github.com/bjornedstrom/python-sha3
#
# This program is meant to find partial hash collisions using SHA3_224 using
# input strings starting with the same characters defined by the 'start'
# variable
##

# Brent's Algorithm for cycle detection
# https://en.wikipedia.org/wiki/Cycle_detection#Brent.27s_algorithm
def brent(f, x0):

    # Initialize the tortoise and hare
    tortoise = x0
    hare = f(x0)

    # Previous tortoise and hare to keep track
    # of the most recent input string
    prev_tort = ''
    prev_hare = ''

    # Steadily move the hare and teleport the turtle
    power = lam = 1
    while tortoise != hare:

        # Teleport the turtle and increase the search distance
        if power == lam:

            # Teleport
            tortoise = hare
            power *= 2
            lam = 0

        # Advance the hare
        hare = f(str(hare))
        lam += 1

    # Retrace the steps to find the collision
    tortoise = hare = x0
    for i in range(lam):
        hare = f(str(hare))

    while tortoise != hare:

        prev_tort = tortoise
        prev_hare = hare
        tortoise = f(str(tortoise))
        hare = f(str(hare))

    # Return the tortoise, hare, and the input hashes that lead to them
    return prev_tort, prev_hare, tortoise, hare


# Function to calculate the next hash given an old hash
# This will act as the f function for Brent's algorithm
def calc_new_hash(old_hash):

    # Make the new input string
    input_string = start.encode() + old_hash.encode()

    # Find the next hash for the input (appended with the 'start' value)
    next_hash = h(input_string).hexdigest()[0:chars]

    # Return the next hash
    return next_hash


#### Run Brent's Algorithm ####
# beginning of the input strings
start = '1233456789'

# SHA3_224 hash function
h = sha3.sha3_224

# the number of characters of collision to find (starts at 1)
chars = 1

# run indefinitely
while (1):

    # increase the number of characters to find
    chars += 1

    # find the collision (note: this repeats a lot of work as it
    # runs through all of the previously found collisions. It was meant
    # to be ran once)
    prev_tort, prev_hare, tortoise, hare = brent(calc_new_hash, start)

    # retrace and output the partial collision
    input1 = start + str(prev_tort)
    input2 = start + str(prev_hare)
    hash1 = str(h(input1).hexdigest())[2:-1]
    hash2 = str(h(input2).hexdigest())[2:-1]
    print("\n------ %s character collision found! -----" % chars)
    print("Input string 1 -> %s" % input1)
    print("Input string 2 -> %s" % input2)
    print("Hash 1 -> %s" % hash1)
    print("Hash 2 -> %s" % hash2)
