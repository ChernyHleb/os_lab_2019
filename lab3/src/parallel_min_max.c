#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <getopt.h>

#include "find_min_max.h"
#include "utils.h"

int main(int argc, char **argv) {
  int seed = -1;
  int array_size = -1;
  int pnum = -1;
  bool with_files = false;

  while (true) {
    int current_optind = optind ? optind : 1;

    static struct option options[] = {{"seed", required_argument, 0, 0},
                                      {"array_size", required_argument, 0, 0},
                                      {"pnum", required_argument, 0, 0},
                                      {"by_files", no_argument, 0, 'f'},
                                      {0, 0, 0, 0}};

    int option_index = 0;
    int c = getopt_long(argc, argv, "f", options, &option_index);

    if (c == -1) break;

    switch (c) {
      case 0:
        switch (option_index) {
          case 0:
            seed = atoi(optarg);
            // your code here
            if (seed <= 0) {
                 printf("seed is a positive number\n");
                 seed = -1;
            }
            // error handling
            break;
          case 1:
            array_size = atoi(optarg);
            // your code here
            if (array_size <= 0) {
                printf("array_size is a positive number\n");
                array_size = -1;
            }
            // error handling
            break;
          case 2:
            pnum = atoi(optarg);
            // your code here
            if(pnum < 1 || pnum > array_size)
            {
                printf("pnum is positive number, less than array size");
                pnum = -1;
            }
            // error handling
            break;
          case 3:
            with_files = true;
            break;

          defalut:
            printf("Index %d is out of options\n", option_index);
        }
        break;
      case 'f':
        with_files = true;
        break;

      case '?':
        break;

      default:
        printf("getopt returned character code 0%o?\n", c);
    }
  }

  if (optind < argc) {
    printf("Has at least one no option argument\n");
    return 1;
  }

  if (seed == -1 || array_size == -1 || pnum == -1) {
    printf("Usage: %s --seed \"num\" --array_size \"num\" --pnum \"num\" \n",
           argv[0]);
    return 1;
  }

  int *array = malloc(sizeof(int) * array_size);
  GenerateArray(array, array_size, seed);
  int active_child_processes = 0;

  struct timeval start_time;
  gettimeofday(&start_time, NULL);

/////////////////////////////////////////////////////
int threadsAmount = array_size / pnum;

FILE  *myfile;
int **pipeFdPtr;
if(with_files)
{
    myfile = fopen("FileForThreads.txt", "w");
}
else
{
    pipeFdPtr = (int**)malloc(sizeof(int*) * pnum);
}
/////////////////////////////////////////////////////


  for (int i = 0; i < pnum; i++) {
      if(!with_files)
      {
          pipeFdPtr[i] = (int*)malloc(sizeof(int)*2);
          if(pipe(pipeFdPtr[i]) == -1)
          {
              printf("pipe failed");
              return 1;
          }
      }

    pid_t child_pid = fork();
    if (child_pid >= 0) {
      // successful fork
      active_child_processes += 1;
      if (child_pid == 0) {
        // child process
        printf("pipe create success");

        struct MinMax min_max_i;
// parallel somehow
        if(i != pnum - 1)
        {
            min_max_i = GetMinMax(array, i*threadsAmount, (i + 1) * threadsAmount);
        }
        else
        {
            min_max_i = GetMinMax(array, i*threadsAmount, array_size);

        }
        
        if (with_files) {
            fwrite(&min_max_i.min, sizeof(int), 1, myfile);
            fwrite(&min_max_i.max, sizeof(int), 1, myfile);
          // use files here
        } else {
            write(pipeFdPtr[i][1], &min_max_i.min, sizeof(int));
            write(pipeFdPtr[i][1], &min_max_i.max, sizeof(int));

            close(pipeFdPtr[i][1]);
          // use pipe here
        }
        return 0;
      }

    } else {
      printf("Fork failed!\n");
      return 1;
    }
  }

  if(with_files)
  {
      fclose(myfile);
      myfile = fopen("FileForThreads.txt", "r");
  }

  while (active_child_processes > 0) {
      wait(NULL);
    // your code here

    active_child_processes -= 1;
  }

  struct MinMax min_max;
  min_max.min = INT_MAX;
  min_max.max = INT_MIN;

  for (int i = 0; i < pnum; i++) {
    int min = INT_MAX;
    int max = INT_MIN;

    if (with_files) {
      // read from files
        fread(&min, sizeof(int), 1, myfile);
        fread(&max, sizeof(int), 1, myfile)
    } else {
        read(pipeFdPtr[i][0], &min, sizeof(int));
        read(pipeFdPtr[i][0], &max, sizeof(int));

        close(pipeFdPtr[i][0]);
        free(pipeFdPtr[i]);
      // read from pipes
    }

    if (min < min_max.min) min_max.min = min;
    if (max > min_max.max) min_max.max = max;
  }
/// освобождение данных
  if(with_files)
  {
      fclose(myfile);
  }
  else
  {
      free(pipeFdPtr);
  }

  struct timeval finish_time;
  gettimeofday(&finish_time, NULL);

  double elapsed_time = (finish_time.tv_sec - start_time.tv_sec) * 1000.0;
  elapsed_time += (finish_time.tv_usec - start_time.tv_usec) / 1000.0;

  free(array);

  printf("Min: %d\n", min_max.min);
  printf("Max: %d\n", min_max.max);
  printf("Elapsed time: %fms\n", elapsed_time);
  fflush(NULL);
  return 0;
}
