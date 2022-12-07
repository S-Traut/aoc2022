/*
Advent Of Code 2022 - Stéphane Traut
DAY 6

NEED CLEANUP
*/

#include <lib.h>

bool capture_ls = AOC_FALSE;

void process_command(fs_file_t **fs, char *command, char *parameter)
{
    capture_ls = AOC_FALSE;
    if (!strcmp("ls\n", command))
    {
        capture_ls = AOC_TRUE;
        return;
    }

    fs_file_t *current = *fs;
    if (!strcmp("cd", command))
    {
        if (!strcmp("..\n", parameter))
        {
            *fs = current->parent;
            printf("Moving up a dir (%s)\n", current->parent->name);
        }
        else
            aoc_change_directory(fs, parameter);
    }
}

int main(void)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    size_t read;

    fp = fopen("./data/d7t.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    fs_file_t *fs = malloc(sizeof(fs_file_t));
    fs->name = "/";
    fs->files = NULL;
    fs->file_count = 0;
    fs->size = 0;
    fs->type = 0;
    fs->buffer_size = 0;
    fs->parent = NULL;
    fs_file_t *root = fs;

    // Reading the file for each line:
    while ((read = getline(&line, &len, fp)) != -1)
    {
        if (line[0] == '-')
            break;

        char *token_1 = strtok(line, " ");
        char *token_2 = strtok(NULL, " ");
        char *token_3 = strtok(NULL, " ");

        if (token_1[0] == '$')
            process_command(&fs, token_2, token_3);
        else if (capture_ls)
        {
            fs_file_t file = {
                .name = token_2,
                .parent = fs,
                .type = token_1[0] != 'd',
                .size = token_1[0] != 'd' ? atoi(token_1) : 0,
                .buffer_size = 0,
                .file_count = 0,
            };

            aoc_fs_add_file(fs, file);
        }
    }

    aoc_fs_print(fs, 0);

    if (line)
        free(line);

    exit(EXIT_SUCCESS);
    return 0;
}
