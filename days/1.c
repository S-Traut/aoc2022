/*
Advent Of Code 2022 - Stéphane Traut
This version is pretty rough and not scalable, and can be optimized / clean up

It basically just loop through each characters of the input string, after each line return it
increase the current elf_value, if there is 2 line return it take the elf value and check for its
order in the TOP 3.
*/

#include <lib.h>

int main(void)
{
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  size_t read;

  int elf_value = 0;
  int first, second, third;

  fp = fopen("./data/d1.txt", "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  // Reading the file for each line:
  while ((read = getline(&line, &len, fp)) != -1)
  {
    // If the current line is a line return
    // switch to the next elf
    if ('\n' == line[0])
    {
      if (elf_value > first)
      {
        third = second;
        second = first;
        first = elf_value;
      }
      else if (elf_value > second)
      {
        third = second;
        second = elf_value;
      }
      else if (elf_value > third)
      {
        third = elf_value;
      }
      elf_value = 0;
    }
    else
    {
      // Else we simply increase the elf value by converting the line to an integer
      elf_value += atoi(line);
    }
  }

  printf("top 3: %d %d %d\n", first, second, third);
  printf("sum: %d\n", first + second + third);

  fclose(fp);
  if (line)
    free(line);
  exit(EXIT_SUCCESS);
}
