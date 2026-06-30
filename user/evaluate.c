#include "kernel/types.h"
#include "user/user.h"

#define SIZE 30000

int data[SIZE];

void
fill_array(void)
{
  for (int i = 0; i < SIZE; i++) {
    data[i] = (SIZE - i) % 97;
  }
}

int
sum_array(void)
{
  int sum = 0;
  for (int i = 0; i < SIZE; i++) {
    sum += data[i];
  }

  return sum;
}

int
normalize_array(void)
{
  int min = data[0], max = data[0];
  
  for (int i = 1; i < SIZE; i++) {
    if (data[i] < min) {
      min = data[i];
    }
    if (data[i] > max) {
      max = data[i];
    }
  }
  int range = max - min;
  int checksum = 0;
  for (int i = 0; i < SIZE; i++) {
    if (range != 0) {
      checksum += (data[i] - min) / range;
    }
  }
  
  return checksum;
}

int
bubble_sort(void)
{
  for (int i = 0; i < SIZE - 1; i++) {
    for (int j = 0; j < SIZE - i - 1; j++) {
      if (data[j] > data[j + 1]) {
        int temp = data[j];
        data[j] = data[j + 1];
        data[j + 1] = temp;
      }
    }
  }
  
  return data[0] + data[SIZE - 1];
}

int
main(int argc, char *argv[])
{
  fill_array();

  int start = uptime();

  if (fork() == 0) {
    rude(5);
    int child_start = uptime();
    int result = sum_array();
    int child_end = uptime();
    printf("RESULT rudeness=5 task=sum value=%d ticks=%d\n", result, child_end - child_start);
    exit(0);
  }

  if (fork() == 0) {
    rude(15);
    int child_start = uptime();
    int result = normalize_array();
    int child_end = uptime();
    printf("RESULT rudeness=15 task=normalize value=%d ticks=%d\n", result, child_end - child_start);
    exit(0);
  }

  if (fork() == 0) {
    rude(30);
    int child_start = uptime();
    int result = bubble_sort();
    int child_end = uptime();
    printf("RESULT rudeness=30 task=bubble_sort value=%d ticks=%d\n", result, child_end - child_start);
    exit(0);
  }

  wait(0);
  wait(0);
  wait(0);

  int end = uptime();
  printf("Total time taken = %d ticks\n", end - start);
  exit(0);
}