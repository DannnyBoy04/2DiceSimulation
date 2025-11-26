/**
 * @file main.c
 * @author Dánjal Leitisstein Olsen (s255821@dtu.dk)
 * @brief Rolls 2 dice the provided number of times and outputs how many times
 * each sum appeared.
 * @version 0.1
 * @date 2025-11-26
 *
 * @copyright Copyright (c) 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define USAGE                                                                  \
  "Rolls 2 dice the provided number of times and outputs the number of times " \
  "each sum appeared.\n"                                                       \
  "%s rollCount [output-file]\n\n"                                             \
  "Example:\n"                                                                 \
  "%s 50000 output.txt\n"                                                      \
  "%s 50000 (output to stdout)\n"

char *ofile;
FILE *ostream;

int rollCount = 0;

// Size of the array is 11 as there are 11 possible results for rolling 2 dice.
size_t sumCounts[11] = {};

// Function to roll 2 dice `rollCount` times and increment the
// corresponding elements in `sumCounts`.
void rollDice() {
  size_t sum = 0;
  for (size_t i = 0; i < rollCount; i++) {
    sum = (rand() % 6) + 1 + (rand() % 6) + 1;
    sumCounts[sum - 2]++;
  }
}

// Function to print the counts of all of the sums in `sumCounts`.
void printSums(FILE *ostream) {
  for (size_t i = 0; i < 11; i++) {
    fprintf(ostream, "%2zu: %zu", i + 2, sumCounts[i]);
    // Skip the last newline.
    if (i < 10) {
      fprintf(ostream, "\n");
    }
  }
}

int main(int argc, char *argv[]) {
  // Seed the rand() function with the current time.
  srand(time(NULL));

  // Command Line Interface so the user can specify roll count and output file.
  switch (argc) {
  // If there are 3 arguments, the third one is always the output file.
  case 3:
    // rollCount ofile.
    ofile = argv[2];
  // If there are 2 arguments, the second one is always the roll count.
  case 2:
    // rollCount
    if (!sscanf(argv[1], "%d", &rollCount)) {
      fprintf(stderr, "ERROR: Argument is not a number.\n");
      exit(EXIT_FAILURE);
    }
    break;
  default:
    printf(USAGE, argv[0], argv[0], argv[0]);
    break;
  }

  // If there is an ouput file, set the output stream to it.
  // Otherwise, the output stream is stdout (the terminal).
  if (ofile) {
    ostream = fopen(ofile, "w");

    if (ostream == NULL) {
      fprintf(stderr, "ERROR: Not able to open output file.\n");
    }
  } else {
    ostream = stdout;
  }

  // If the program received a roll count, roll dice and print sums.
  if (argc >= 2) {
    rollDice();

    printSums(ostream);
  }
}