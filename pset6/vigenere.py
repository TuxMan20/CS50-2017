#!/usr/bin/env python3

import cs50
import sys

def main():
    ## Checks command line argument for an alphabetic key (a word)
    if len(sys.argv) == 2 and sys.argv[1].isalpha():
        keyWord = sys.argv[1].lower()
    else:
        print("USAGE: argument must contains an alphebetic key. Error 1")
        exit(1)

    ## Ensures the plain text is a String. Asks the user for a string to use as Plain Text
    while True:
        try:
            plain = str(input("Plaintext: "))
        except ValueError:
            continue
        else:
            if len(plain) < 256: ## Limit of 256 chars for the plain text
                break
            else:
                continue

    ## Keeps position inside the key word
    p = 0
    ## Will be used as the key value
    k = 0

    print("Cyphertext: ", end ="")

    ## Iterates over each character in the plaintext and reprints them as crypted (if alphabetic)
    for c in plain:
        k = ord(keyWord[p]) - 97
        print(crypt(c, k), end = "") ## This is where the magic happens
        if str.isalpha(c):
            p = (p + 1) % len(keyWord) ## If the current char was alphabetic, the key is moved along

    print("")

def crypt(c, k):

    ## Takes in the char and the current key
    if str.isalpha(c): ## If it's an alphabetic char..
        toCrypt = c.lower() ## First, it chages it to lowercase to ease the calculations
        crypted = chr((((ord(toCrypt) - 97) + k) % 26) + 97) ## The char is then crypted following the hash function

        if c.isupper(): ## If the inputed char was uppercase, crypted char becomes uppercase
            return crypted.upper()
        else:
            return crypted
    else: ## If the inputed char was not alphabetical, it is returned "As is"
        return c


if __name__ == "__main__":
    main()