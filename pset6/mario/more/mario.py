from cs50 import get_int


validHeight = False
while validHeight == False:
    height = get_int("Height: ")

    if  height in range(1,9):
        validHeight = True

output = "  "
for i in range(height):
    output = '#' + output + '#'
    print(" " * (height-1-i), end = "")
    print(output)