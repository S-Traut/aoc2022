#include <lib.h>

//   R P S
// R 4 8 3
// P 1 5 9
// S 7 2 6
const char RULES[3][3] = {
    {4, 8, 3},
    {1, 5, 9},
    {7, 2, 6},
};

//   X Y Z
// R S R P
// P R P S
// S P S R
const char PLAY[3][3] = {
    {2, 0, 1},
    {0, 1, 2},
    {1, 2, 0},
};

const char MAPPINGS_L[6] = {'A', 'B', 'C', 'X', 'Y', 'Z'};
const char MAPPINGS_N[6] = {0, 1, 2, 0, 1, 2};

int get_index(char pick)
{
  for (int i = 0; i < 6; ++i)
  {
    if (MAPPINGS_L[i] == pick)
    {
      return MAPPINGS_N[i];
    }
  }
  return 0;
}

// RULES:
// ROCK, PAPER, CISOR
int rps_logic(char left, char right)
{
  int e_index = get_index(left);
  int u_index = get_index(right);
  int u_play = PLAY[e_index][u_index];
  return RULES[e_index][u_play];
}

int main(void)
{
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  size_t read;

  int score = 0;

  fp = fopen("./data/d2.txt", "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  // Reading the file for each line:
  while ((read = getline(&line, &len, fp)) != -1)
  {
    char e_play = line[0];
    char u_play = line[2];
    score += rps_logic(e_play, u_play);
  }

  printf("Score: %d\n", score);

  fclose(fp);
  if (line)
    free(line);
  exit(EXIT_SUCCESS);
}