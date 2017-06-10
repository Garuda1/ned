/*
 * main.c
 *
 * Licensed under GNU GPL v3
 *
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>

#include <args.h>
#include <cmd.h>

#define MEM_SIZE 128
#define BUF_SIZE 128

static void dump_mem(uint8_t *mem, size_t address)
{
  size_t i;

  i = 0;
  while (i < MEM_SIZE)
  {
    if (i == address)
      printf("\x1b[0;31m|%02X|\x1b[0m ", (unsigned int) mem[i]);
    else
      printf("|%02X| ", (unsigned int) mem[i]);
    ++i;
  }
  putchar('\n');
}

static int edit(t_args *args)
{
  int keep_running;
  char buf[BUF_SIZE];
  uint8_t mem[MEM_SIZE];
  size_t address;
  int fd;

  memset(mem, 0, MEM_SIZE);
  address = 0;

  keep_running = 1;
  while (keep_running)
  {
    printf("[ed | %s | address=%04X] ", args -> file_name, (unsigned int)address);
    scanf("%s", buf);
    if (!strcmp(buf, CMD_EXIT))
      keep_running = 0;
    else if (!strcmp(buf, CMD_DISP))
      dump_mem(mem, address);
    else if (!strcmp(buf, CMD_JUMP))
    {
      printf("Address: 0x");
      scanf("%04X", (unsigned int *) &address);
      if (address >= MEM_SIZE)
        address = MEM_SIZE - 1;
    }
    else if (!strcmp(buf, CMD_NEXT))
    {
      if (address < (MEM_SIZE - 1))
        ++address;
    }
    else if (!strcmp(buf, CMD_PREV))
    {
      if (address > 0)
        --address;
    }
    else if (!strcmp(buf, CMD_SET))
    {
      scanf("%02X", (unsigned int *) &(mem[address]));
      if (address < (MEM_SIZE -1))
        ++address;
    }
    else if (!strcmp(buf, CMD_SAVE))
    {
      fd = open(args -> file_name, O_CREAT | O_WRONLY);
      write(fd, mem, MEM_SIZE);
      close(fd);
      printf("File saved\n");
    }
    else
      printf("Command not found: %s\n", buf);
  }
  return (EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
  t_args args;

  init_args(&args);
  if (parse_args(&args, argc, argv) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if (check_args(&args) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (edit(&args));
}
