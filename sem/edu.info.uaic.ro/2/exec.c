/* exec.c

   Executia prin program a comenzii 'ls -a -l', folosind execlp()
   
   Autor: Sabin-Corneliu Buraga <busaco@info.uaic.ro> (c)
   Versiunea: 1.0
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int
main ()
{
  pid_t pid;			/* PID-ul procesului copil */
  int status;			/* starea de terminare a procesului copil */

  printf ("Vom executa comanda...\n");

  if ((pid = fork ()) < 0)
    {
      perror ("fork()");
      exit (1);
    }
  else if (pid)			/* parinte */
    {
      if (wait (&status) < 0)
	{
	  perror ("wait()");
	}
      printf ("Comanda a fost executata.\n");
      exit (0);
    }
  else				/* fiu */
    {
      /* vom folosi execlp() */
      execlp ("ls",
	      /* comanda de executat (se va cauta in directoarele din PATH) */
	      "ls",		/* argv[0] */
	      "-a",		/* argv[1] */
	      "-l",		/* argv[2] */
	      NULL);
      /* daca ajungem aici inseamna ca nu s-a putut executa */
      printf ("Eroare de executie!\n");
      exit (1);
    }
}
