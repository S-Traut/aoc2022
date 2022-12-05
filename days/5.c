/*
Advent Of Code 2022 - Stéphane Traut
DAY 5

For this problem I have cheated a bit by simplifying the puzzle input
because parsing the original one was a big mess I decided to just keep the
movements and make a static data array of the base state.

I've also made a custom struct to store a basic data and length variables.

The algorithm is very simple, For the part 1 I just changed the from_index to
be starting from the right, and the part 2 it start from the left.
For each move I just move the char from an array to another according to some indexes.
And at the end I just update the size of both cratestacks.
*/

#include <lib.h>

cratestack_t data[9] = {
    {.data = "WRF", .size = 3},
    {.data = "THMCDVWP", .size = 8},
    {.data = "PMZNL", .size = 5},
    {.data = "JCHR", .size = 4},
    {.data = "CPGHQTB", .size = 7},
    {.data = "GCWLFZ", .size = 6},
    {.data = "WVLQZJGC", .size = 8},
    {.data = "PNRFWTVC", .size = 8},
    {.data = "JWHGRSV", .size = 7},
};

void process_action(cratestack_t *cratestacks, int count, int from, int to)
{
    for (u16 i = 0; i < count; ++i)
    {
        // For part 1, just move from size - i - 1 instead of size - count + i;
        char from_char_index = cratestacks[from].size - count + i;
        char to_char_index = cratestacks[to].size + i;
        cratestacks[to].data[to_char_index] = cratestacks[from].data[from_char_index];
        cratestacks[from].data[from_char_index] = '\0';
    }

    cratestacks[from].size -= count;
    cratestacks[to].size += count;
}

void print_stacks(cratestack_t *cratestacks)
{
    for (u16 i = 0; i < 9; ++i)
        printf("%c", cratestacks[i].data[cratestacks[i].size - 1]);

    printf("\n");
}

int main(void)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    size_t read;

    cratestack_t *cratestacks = malloc(sizeof(cratestack_t) * 9);
    memcpy(cratestacks, data, sizeof(cratestack_t) * 9);

    fp = fopen("./data/d5.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    // Reading the file for each line:
    while ((read = getline(&line, &len, fp)) != -1)
    {
        int move_count = atoi(strtok(line, " "));
        int from = atoi(strtok(NULL, " ")) - 1;
        int to = atoi(strtok(NULL, " ")) - 1;
        process_action(cratestacks, move_count, from, to);
    }

    print_stacks(cratestacks);

    fclose(fp);
    if (line)
        free(line);

    free(cratestacks);
    exit(EXIT_SUCCESS);
    return 0;
}
