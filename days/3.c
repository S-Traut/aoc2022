/*
Advent Of Code 2022 - Stéphane Traut
DAY 3

This solution is pretty bad / messy, and need to be rewritten.
*/

#include <lib.h>
#include <string.h>
#include <ctype.h>

u32 get_rucksack_priorities(char *rucksack)
{
  u64 priority = 0;
  u64 rucksack_size = strlen(rucksack);
  u64 compartment_size = rucksack_size / 2;

  for (u64 i = 0; i < compartment_size; ++i)
  {
    for (u64 j = 0; j < compartment_size; ++j)
    {
      if (rucksack[i] == rucksack[compartment_size + j])
      {
        char shared_item = rucksack[i];
        if (isupper(shared_item))
          return (shared_item - 65) + 27;
        else
          return (shared_item - 97) + 1;
      }
    }
  }
}

u32 find_badge(char *old, char *old2, char *current)
{
  u64 old_length = strlen(old);
  u64 old2_length = strlen(old2);
  u64 cur_length = strlen(current);
  for (u64 i = 0; i < old_length; i++)
  {
    for (u64 j = 0; j < old2_length; ++j)
    {
      if (old[i] == old2[j])
      {
        char shared_item = old[i];
        for (u64 k = 0; k < cur_length; ++k)
        {
          if (current[k] == shared_item)
          {
            if (isupper(shared_item))
              return (shared_item - 65) + 27;
            else
              return (shared_item - 97) + 1;
          }
        }
      }
    }
  }
}

int main(void)
{
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  size_t read;

  u32 sum = 0;
  u32 badge_sum = 0;
  char badge = '\0';
  u32 line_number = 0;

  char *old_line = "";
  char *old_line_2 = "";

  fp = fopen("./data/d3.txt", "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  // Reading the file for each line:
  while ((read = getline(&line, &len, fp)) != -1)
  {
    sum += get_rucksack_priorities(line);

    if (line_number == 0)
    {
      old_line = malloc(sizeof(char) * len);
      strcpy(old_line, line);
    }

    if (line_number == 1)
    {
      old_line_2 = malloc(sizeof(char) * len);
      strcpy(old_line_2, line);
    }

    if (line_number == 2)
    {
      badge = find_badge(old_line, old_line_2, line);
      badge_sum += badge;
      line_number = 0;
      free(old_line);
      free(old_line_2);
      continue;
    }
    line_number++;
  }

  printf("Sum of all priorities: %d\n", sum);
  printf("Sum of badges: %d\n", badge_sum);

  fclose(fp);
  if (line)
    free(line);
  exit(EXIT_SUCCESS);
  return 0;
}
