/*
Advent Of Code 2022 - Stéphane Traut
DAY 6

NEED CLEANUP
*/

#include <lib.h>

bool has_repeated_chars(char *BUFFER, int size)
{
    for (u8 i = 0; i < size; ++i)
    {
        for (u8 j = i + 1; j < size; ++j)
        {
            if (BUFFER[i] == BUFFER[j])
                return AOC_TRUE;
        }
    }
    return AOC_FALSE;
}

int main(void)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    size_t read;

    fp = fopen("./data/d6.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    // Reading the file for each line:
    getline(&line, &len, fp);
    u64 size = strlen(line);
    char BUFFER[14];
    for (u64 i = 0; i < size; ++i)
    {
        memcpy(BUFFER, line + i, sizeof(char) * 14);
        if (!has_repeated_chars(BUFFER, 14))
        {
            printf("%d\n", i + 14);
            break;
        }
    }

    if (line)
        free(line);

    exit(EXIT_SUCCESS);
    return 0;
}
