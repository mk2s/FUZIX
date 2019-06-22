/*
 *	Generate the syscall functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "syscall_name.h"

static char namebuf[128];

static void write_call(int n)
{
  FILE *fp;
  int saves = 0;
  snprintf(namebuf, 128, "fuzixns32k/syscall_%s.S", syscall_name[n]);
  fp = fopen(namebuf, "w");
  if (fp == NULL) {
    perror(namebuf);
    exit(1);
  }
  /*
   *	We define _fork() as trashing all the registers except the return
   *	values a5 and a7. The userspace ick here allows us to avoid saving
   *	all the registers on syscall entry just in case we are doing a fork and
   *	have multiple udata blocks.
   *
   *	Note: this does mean if you want a register global you need to use a5
   *	or ensure you never take a signal in the fork() area - doable but ugly.
   */
  fprintf(fp, "\t.text\n\n"
	      "\t.globl %1$s\n"
	      "\t.type %1$s, @function\n"
	      "\t.align 2\n\n"
	      "%1$s:\n", syscall_name[n]);
  fprintf(fp, "\tmovw %d,r0\n", n);
  fprintf(fp, "\tsvc\n");
  fprintf(fp, "\tmovd r1,_errno(pc)\n");
  fprintf(fp, "\tret 0\n");

  fclose(fp);
}

static void write_call_table(void)
{
  int i;
  for (i = 0; i < NR_SYSCALL; i++)
    write_call(i);
}

static void write_makefile(void)
{
  int i;
  FILE *fp = fopen("fuzixns32k/Makefile", "w");
  if (fp == NULL) {
    perror("Makefile");
    exit(1);
  }
  fprintf(fp, "# Autogenerated by tools/syscall_ns32k\n");
  fprintf(fp, "CROSS_AS=ns32k-pc532-netbsd-gcc\nCROSS_LD=ns32k-pc532-netbsd-ld\nCROSS_AR=ns32k-pc532-netbsd-ar\n");
  fprintf(fp, "ASOPTS=\n\n");
  fprintf(fp, "ASRCS = syscall_%s.S\n", syscall_name[0]);
  for (i = 1; i < NR_SYSCALL; i++)
    fprintf(fp, "ASRCS += syscall_%s.S\n", syscall_name[i]);
  fprintf(fp, "\n\nASRCALL = $(ASRCS) $(ASYS)\n");
  fprintf(fp, "\nAOBJS = $(ASRCALL:.S=.o)\n\n");
  fprintf(fp, "syslib.lib: $(AOBJS)\n");
  fprintf(fp, "\techo $(AOBJS) >syslib.l\n");
  fprintf(fp, "\t$(CROSS_AR) rc syslib.lib $(AOBJS)\n\n");
  fprintf(fp, "$(AOBJS): %%.o: %%.S\n");
  fprintf(fp, "\t$(CROSS_AS) $(ASOPTS) -c $<\n\n");
  fprintf(fp, "clean:\n");
  fprintf(fp, "\trm -f $(AOBJS) $(ASRCS) syslib.lib syslib.l *~\n\n");
  fclose(fp);
}

int main(int argc, char *argv[])
{
  write_makefile();
  write_call_table();
  exit(0);
}