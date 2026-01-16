#pragma once


#define ARRAY_SIZE 50

typedef enum TypeOfBook TypeOfBook;
enum TypeOfBook
{
  FANTASY, SYFY, HORROR
};

typedef enum TimeToRead TimeToRead;
enum TimeToRead
{
  SHORT = 10, MEDIUM = 20, LONG = 30
};

typedef struct Book Book;
struct Book
{
  char title[ARRAY_SIZE];
  int length;
  TypeOfBook type;
};
