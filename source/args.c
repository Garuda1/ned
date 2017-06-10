/*
 * args.c
 *
 * Licensed under GNU GPL v3
 *
 */

#include <args.h>
#include <err.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

void init_args(t_args *args)
{
  args -> file_name = NULL;
}

int parse_args(t_args *args, int argc, char **argv)
{
  ssize_t i;

  i = 1;
  while (i < argc)
  {
    if (args -> file_name == NULL)
      args -> file_name = argv[i];
    else
    {
      puts(ERR_SYNTAX);
      return (EXIT_FAILURE);
    }
    ++i;
  }
  return (EXIT_SUCCESS);
}

int check_args(t_args *args)
{
  if (args -> file_name == NULL)
  {
    puts(ERR_SYNTAX);
    return (EXIT_FAILURE);
  }
  return (EXIT_SUCCESS);
}
