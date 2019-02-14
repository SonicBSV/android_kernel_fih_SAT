#ifndef __ASM_LIBGCC_H
#define __ASM_LIBGCC_H

#include <asm/byteorder.h>

typedef int word_type __attribute__ ((mode (__word__)));

#ifdef __BIG_ENDIAN
struct DWstruct {
	int high, low;
};
<<<<<<< HEAD

struct TWstruct {
	long long high, low;
};
=======
>>>>>>> efc49de... first commit
#elif defined(__LITTLE_ENDIAN)
struct DWstruct {
	int low, high;
};
<<<<<<< HEAD

struct TWstruct {
	long long low, high;
};
=======
>>>>>>> efc49de... first commit
#else
#error I feel sick.
#endif

typedef union {
	struct DWstruct s;
	long long ll;
} DWunion;

<<<<<<< HEAD
#if defined(CONFIG_64BIT) && defined(CONFIG_CPU_MIPSR6)
typedef int ti_type __attribute__((mode(TI)));

typedef union {
	struct TWstruct s;
	ti_type ti;
} TWunion;
#endif

=======
>>>>>>> efc49de... first commit
#endif /* __ASM_LIBGCC_H */
