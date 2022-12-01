/*
Advent Of Code 2022 - Stéphane Traut

The solution is very simple, but not scalable:
We iterate through each line of the file, if the line has a RETURN character a the first position
we check the value of the elf
otherwise we increase the value of the elf by converting the line to an integer and add it to the elf.
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
      // This section is not scalable
      // but I think it's sufficient for the problem.
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
