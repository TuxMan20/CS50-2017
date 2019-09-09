
## Infinite loop to get an Int from the user, breaks when it is accepted
while True:
    try:
        h = int(input("Height: "))
    except ValueError:
        continue
    else:
        if h >= 0 and h < 20:
            break
        else:
            continue

hashes = 1
spaces = h-1


for i in range(h):
    for j in range(spaces):
        print(" ", end="")
    for k in range(hashes):
        print("#", end="")
    print("")
    spaces = spaces - 1
    hashes = hashes + 1




