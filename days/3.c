/*
Advent Of Code 2022 - Stéphane Traut
DAY 3

For this problem I have created a struct ruckstack_t that allow me to simply store
a char* that is the data, and it's size.

Because of C I had to create few functions to make the code more cleaner and explicit.

For the first problem it's pretty easy and straight forward to get an answer, simply loop from 0 to
size / 2 of a rucksack, and iterate another time on the second half of the rucksack to check if there
is the same occurence of a char. If yes, return the priority of it.

For the second problem, it was a bit more annoying because I had to store the 3 rucksack data in the heap to
perform some check more easily with them. Every 3 rucksacks I give a group to a function that simple loop through
the first one, and check if there is a char occurence in the 2 others.

The 2 algorithms can be surely optimized, but for now, I prefer using these 2 simple solutions.
*/

#include <lib.h>
#include <string.h>
#include <ctype.h>

bool rucksack_contain(rucksack_t rucksack, char item)
{
  for (u32 i = 0; i < rucksack.size; i++)
  {
    if (rucksack.data[i] == item)
      return AOC_TRUE;
  }
  return AOC_FALSE;
}

u32 get_rucksack_item_priority(char item)
{
  if (isupper(item))
    return item - 38;

  return item - 96;
}

u32 get_rucksack_priorities(rucksack_t rs)
{
  for (u64 i = 0; i < rs.compartment_size; ++i)
  {
    for (u64 j = 0; j < rs.compartment_size; ++j)
    {
      if (rs.data[i] == rs.data[rs.compartment_size + j])
        return get_rucksack_item_priority(rs.data[i]);
    }
  }
}

u32 find_badge(const rucksack_t group[])
{
  for (u32 i = 0; i < group[0].size; i++)
  {
    char current_item = group[0].data[i];
    if (rucksack_contain(group[1], current_item) && rucksack_contain(group[2], current_item))
      return get_rucksack_item_priority(current_item);
  }
}

int main(void)
{
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  size_t read;

  u32 priority_sum = 0;
  u32 badge_sum = 0;
  u32 i = 0;
  rucksack_t group[3];

  fp = fopen("./data/d3.txt", "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  // Reading the file for each line:
  while ((read = getline(&line, &len, fp)) != -1)
  {
    u64 rucksack_size = strlen(line);
    char *data = malloc(sizeof(char) * rucksack_size);
    strcpy(data, line);
    rucksack_t rucksack = {
        .data = data,
        .size = rucksack_size,
        .compartment_size = rucksack_size / 2,
    };
    group[i % 3] = rucksack;
    priority_sum += get_rucksack_priorities(rucksack);

    // Every 3 rucksack, try to find a badge.
    if ((i + 1) % 3 == 0)
    {
      badge_sum += find_badge(group);
      for (u8 i = 0; i < 3; ++i)
        free(group[i].data);
    }
    i++;
  }

  printf("Sum of all priorities: %d\n", priority_sum);
  printf("Sum of badges: %d\n", badge_sum);

  fclose(fp);
  if (line)
    free(line);
  exit(EXIT_SUCCESS);
  return 0;
}
