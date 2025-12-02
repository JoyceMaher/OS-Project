#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define MAXIMUM_LINE_LENGTH 1024


int read_line(int file_descriptor_number, char *buffer, int maximum_size)
{
  int index = 0;
  char character;

  while(read(file_descriptor_number, &character, 1) == 1) {
      if(character == '\n' || index == maximum_size - 1)
      {
          break;
      }

      buffer[index++] = character;
  }

  buffer[index] = 0;
  if(index == 0) return 0;
  return 1;
}

int compare_text(const char *text1, const char *text2)
{

  int index = 0;

  while(text1[index] && text2[index]) {

      if(text1[index] != text2[index]) {
          return 0;
      }

      index++;
  }

  if(text1[index] == 0 && text2[index] == 0) return 1;
  return 0;
}

int main(int number_of_inputs, char *input_list[])
{

  if(number_of_inputs < 3)
  {
      printf("Error: You must enter two file names to compare!\n");
      exit(1);
  }

  int file1 = open(input_list[1], 0);
  if(file1 < 0)
  {
      printf("diff: cannot open first file\n");
      exit(1);
  }

  int file2 = open(input_list[2], 0);
  if(file2 < 0)
  {
      printf("diff: cannot open second file\n");
      close(file1);
      exit(1);
  }

  char line1_buffer[MAXIMUM_LINE_LENGTH];
  char line2_buffer[MAXIMUM_LINE_LENGTH];
  int current_line_number = 1;
  int difference_found = 0;

  while(1)
  {
      int status1 = read_line(file1, line1_buffer, MAXIMUM_LINE_LENGTH);
      int status2 = read_line(file2, line2_buffer, MAXIMUM_LINE_LENGTH);

      if(status1 == 0 && status2 == 0)
      {
          break;
      }

      if(status1 == 1 && status2 == 1)
      {
          if(compare_text(line1_buffer, line2_buffer) == 0)
           {
              printf("Line %d differs:\n", current_line_number);
              printf("< %s\n", line1_buffer);
              printf("> %s\n", line2_buffer);
              difference_found = 1;
          }

      } else if(status1 == 0 && status2 == 1) {
          printf("Line %d only in second file:\n", current_line_number);
          printf("> %s\n", line2_buffer);
          difference_found = 1;

      } else if(status1 == 1 && status2 == 0) {
          printf("Line %d only in first file:\n", current_line_number);
          printf("< %s\n", line1_buffer);
          difference_found = 1;
      }

      current_line_number++;
  }

  if(difference_found == 0) {
      printf("Files are identical\n");
  }

  close(file1);
  close(file2);
  exit(0);
}
