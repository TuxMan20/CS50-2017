#include <cs50.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <crypt.h>

#define _GNU_SOURCE         /* See feature_test_macros(7) */
#define _XOPEN_SOURCE
#define SALT "50"

int main (int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./crypt cryptedText");
        return -1;
    }

    //string toDecrypt = argv[1];

    string tries = "";
    string cryptTries = "";

    for(int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            tries[i] = j + 'A';
            cryptTries = crypt(tries, SALT);
            printf("%s",cryptTries);
        }
    }

}

/*
1. get crypted text as argv
2. create a 5 bytes array
3. make the string tries as "a"
4. crypt() it
5. compare with string toDecrypt
6. If same, password found... if not
7. make the string tries as "b"
8. repeat 5-6 iterating each letters

*/