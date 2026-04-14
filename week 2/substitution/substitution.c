#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
bool valid_key(string key);
bool has_unique_letters(string key);
char substitute(char c, string key);
int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    string key = argv[1];
    if (!valid_key(key))
    {
        printf("Key must contain 26 unique alphabetic characters.\n");
        return 1;
    }
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++)
    {
        printf("%c", substitute(plaintext[i], key));
    }
    printf("\n");
    return 0;
}
bool valid_key(string key)
{
    if (strlen(key) != 26)
        return false;
    for (int i = 0; i < 26; i++)
    {
        if (!isalpha(key[i]))
            return false;
    }
    if (!has_unique_letters(key))
        return false;
    return true;
}
bool has_unique_letters(string key)
{
    bool seen[26] = {false};
    for (int i = 0; i < 26; i++)
    {
        int index = toupper(key[i]) - 'A';
        if (seen[index])
            return false;
        seen[index] = true;
    }
    return true;
}
char substitute(char c, string key)
{
    if (isupper(c))
        return toupper(key[c - 'A']);
    else if (islower(c))
        return tolower(key[c - 'a']);
    else
        return c; 
}
