#include "main.h"
#include "correction.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(void)
{

  correction();


  // Sans le typedef, la structure devrait etre utilise comme suit :
  // struct Book cthulhu;
  Book cthulhu;
  strcpy(cthulhu.title, "The Call of Cthulhu") ;
  cthulhu.length = 272;

  Book * hobbit = malloc(sizeof(Book));

  //(*hobbit).length = 432;
  hobbit->length = 432;

  strcpy(hobbit->title, "The hobbit") ;



  Book dune = {"Dune", 883, SYFY};


  printf("Le livre %s fait %d pages\n", cthulhu.title, cthulhu.length);
  printf("Le livre %s fait %d pages\n", hobbit->title, hobbit->length);
  printf("Le livre %s fait %d pages\n", dune.title, dune.length);



  cthulhu.type = HORROR;
  hobbit->type = FANTASY;

  // Un enum est un alias sur un int
  printf("Le type est %d\n", cthulhu.type) ;
  printf("Le type est %d\n", hobbit->type) ;

  free(hobbit);

  return 0;
}