#ifndef BOOT_CPUFLAGS_H
#define BOOT_CPUFLAGS_H

<<<<<<< HEAD
#include <asm/cpufeatures.h>
=======
#include <asm/cpufeature.h>
>>>>>>> efc49de... first commit
#include <asm/processor-flags.h>

struct cpu_features {
	int level;		/* Family, or 64 for x86-64 */
	int model;
	u32 flags[NCAPINTS];
};

extern struct cpu_features cpu;
extern u32 cpu_vendor[3];

int has_eflag(unsigned long mask);
void get_cpuflags(void);

#endif
