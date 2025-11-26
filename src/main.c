#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Size of the array is 11 as there are 11 possible results for rolling 2 dice.
size_t sumCounts[11] = {};

// Function to roll 2 dice `count` times and increment the
// corresponding elements in `sumCounts`.
void rollDice(size_t count) {
  size_t sum = 0;
  for (size_t i = 0; i < count; i++) {
    sum = (rand() % 6) + 1 + (rand() % 6) + 1;
    sumCounts[sum - 2]++;
  }
}

// Function to print the counts of all of the sums in `sumCounts`.
void printSums() {
  for (size_t i = 0; i < 11; i++) {
    printf("%2zu: %zu\n", i + 2, sumCounts[i]);
  }
}

int main() {
  // Seed the rand() function with the current time.
  srand(time(NULL));

  rollDice(50000);

  printSums();
}