/*
Advent Of Code 2022 - Stéphane Traut
DAY 2

For this solution I've used some const arrays to find the right answer to play
This might be improved especially for the MAPPINGS constants

The technique is simple: there is an array RULES that defines what you score using a 2D array
E.G if your enemy play R which is 0 and you play P which is 1 the result is simple RULES[0][1] => 8

For the second part, I created a similar array which store what you should play and combine both
RULES and PLAY at the end to get the correct score.
*/

#include <lib.h>

#define A_OFFSET 65
#define X_OFFSET 88

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

int main(void)
{
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  size_t read;

  int score_step_1 = 0;
  int score_step_2 = 0;

  fp = fopen("./data/d2.txt", "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  // Reading the file for each line:
  while ((read = getline(&line, &len, fp)) != -1)
  {
    // Extract line inputs
    int e_play = line[0] - A_OFFSET;
    int u_play = line[2] - X_OFFSET;

    // Calculate the values
    score_step_1 += RULES[e_play][u_play];
    score_step_2 += RULES[e_play][PLAY[e_play][u_play]];
  }

  printf("Score (1): %d\n", score_step_1);
  printf("Score (2): %d\n", score_step_2);

  fclose(fp);
  if (line)
    free(line);
  exit(EXIT_SUCCESS);
}