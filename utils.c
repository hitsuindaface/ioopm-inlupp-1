#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

<<<<<<< HEAD
int read_string(char *buf, int buf_siz)
{
    int readChars = 0;
    for (int i = 0; i < buf_siz; i++)
    {
        if (i == buf_siz - 1)
        {
            buf[i] = '\0';
        }
        int currChar = getchar();
        if (currChar != '\n' && currChar != '\0' && currChar != EOF)
        {
            buf[i] = currChar;
            readChars++;
        }
        else
        {
            buf[i] = '\0';
            break;
=======
int read_string(char *buf, int buf_siz) {
    int readChars = 0;
    for (int i = 0; i < buf_siz; i++) {
        if(i == buf_siz -1) {
            buf[i] = '\0';
        }
        int currChar = getchar();
        if ( currChar != '\n' && currChar != '\0' && currChar != EOF) {
            buf[i] = currChar;
            readChars++;
        } else { 
            buf[i] = '\0';
            break; 
>>>>>>> 6ec94e53762040073c7d3e04f4c51bd1a35e46dd
        }
    }
    return readChars;
}

<<<<<<< HEAD
char *ask_question_string(char *question, char *buf, int buf_siz)
{
=======
char *ask_question_string(char *question, char *buf, int buf_siz) {
>>>>>>> 6ec94e53762040073c7d3e04f4c51bd1a35e46dd
    int read = 0;

    while (true)
    {
        puts(question);
        read = read_string(buf, buf_siz);
<<<<<<< HEAD
        if (read == 0)
        {
=======
        if(read == 0) {
>>>>>>> 6ec94e53762040073c7d3e04f4c51bd1a35e46dd
            continue;
        }
        break;
    }
<<<<<<< HEAD

=======
    
>>>>>>> 6ec94e53762040073c7d3e04f4c51bd1a35e46dd
    return buf;
}

int ask_question_int(char *question)
{
<<<<<<< HEAD
    int result = 0;
    int conversions = 0;

    while (conversions < 1)
    {
        printf("%s\n", question);
        conversions = scanf("%d", &result);
        int c = 0;
        while (c != '\n' && c != EOF)
        {
            c = getchar();
        }
        putchar('\n');
=======
  int result = 0;
  int conversions = 0;

    while (conversions < 1) {
      printf("%s\n", question);
      conversions = scanf("%d", &result);
        int c = 0;
        while (c != '\n' && c != EOF) {
            c = getchar();
        }
      putchar('\n');
>>>>>>> 6ec94e53762040073c7d3e04f4c51bd1a35e46dd
    }
    return result;
}

bool is_number(char *str)
{
<<<<<<< HEAD
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        if (isdigit(str[i]) == false)
        {
            if (i == 0 && str[i] == '-')
            {
                continue;
            }
            printf("is false \n");
            return false;
        }
        else
        {
        }
    }
    printf("is true \n");
    return true;
=======
  int len = strlen(str);
  for ( int i = 0; i < len; i++ ) {
    if ( isdigit(str[i]) == false ) {
      if(i == 0 && str[i] == '-'){
        continue;
      }
      printf("is false \n");
      return false;
    } else {}
  }
  printf("is true \n");
  return true;
>>>>>>> 6ec94e53762040073c7d3e04f4c51bd1a35e46dd
}