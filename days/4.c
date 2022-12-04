/*
Advent Of Code 2022 - Stéphane Traut
DAY 4

For this problem I have decided to use the function strtok, which provide a pretty simple way
to split the strings to parse the data into 2 inverval struct, one for each assignments.

For the first part it's pretty easy, simply check if the first start is higher or equal to the second,
and the end is lower or equal to the second. Do the check vice-versa and you got the answer.

For the second one it's pretty simple aswell, I've made a little function that check if a number exist
in an inverval struct, then loop through each number of the first one and check if the second have it aswell.
*/

#include <lib.h>
#include <string.h>

interval_t parse_assignment(char *assignment)
{
  interval_t interval = {0};
  char *token = strtok(assignment, "-");
  interval.start = atoi(token);
  token = strtok(NULL, "-");
  interval.end = atoi(token);
  interval.length = interval.end - interval.start;
  return interval;
}

u8 process_assignments(interval_t first, interval_t second)
{
  if (first.start >= second.start && first.end <= second.end)
    return 1;

  if (second.start >= first.start && second.end <= first.end)
    return 1;

  return 0;
}

u8 process_assignments_2(interval_t first, interval_t second)
{
  for (u64 i = first.start; i <= first.end; ++i)
  {
    if (aoc_interval_contains(second, i))
      return 1;
  }
  return 0;
}

int main(void)
{
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  size_t read;

  u32 fully_overlapping = 0;
  u32 overlapping = 0;

  fp = fopen("./data/d4.txt", "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  // Reading the file for each line:
  while ((read = getline(&line, &len, fp)) != -1)
  {
    char *first = strtok(line, ",");
    char *second = strtok(NULL, ",");
    interval_t i1 = parse_assignment(first);
    interval_t i2 = parse_assignment(second);

    fully_overlapping += process_assignments(i1, i2);
    overlapping += process_assignments_2(i1, i2);
  }

  printf("fully overlapping: %d\n", fully_overlapping);
  printf("overlapping: %d\n", overlapping);

  fclose(fp);
  if (line)
    free(line);
  exit(EXIT_SUCCESS);
  return 0;
}
