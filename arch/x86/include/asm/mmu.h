#ifndef _ASM_X86_MMU_H
#define _ASM_X86_MMU_H

#include <linux/spinlock.h>
#include <linux/mutex.h>
<<<<<<< HEAD
#include <linux/atomic.h>

/*
 * x86 has arch-specific MMU state beyond what lives in mm_struct.
 */
typedef struct {
	/*
	 * ctx_id uniquely identifies this mm_struct.  A ctx_id will never
	 * be reused, and zero is not a valid ctx_id.
	 */
	u64 ctx_id;

=======

/*
 * The x86 doesn't have a mmu context, but
 * we put the segment information here.
 */
typedef struct {
>>>>>>> efc49de... first commit
#ifdef CONFIG_MODIFY_LDT_SYSCALL
	struct ldt_struct *ldt;
#endif

#ifdef CONFIG_X86_64
	/* True if mm supports a task running in 32 bit compatibility mode. */
	unsigned short ia32_compat;
#endif

	struct mutex lock;
	void __user *vdso;

	atomic_t perf_rdpmc_allowed;	/* nonzero if rdpmc is allowed */
} mm_context_t;

<<<<<<< HEAD
#define INIT_MM_CONTEXT(mm)						\
	.context = {							\
		.ctx_id = 1,						\
	}

void leave_mm(int cpu);
=======
#ifdef CONFIG_SMP
void leave_mm(int cpu);
#else
static inline void leave_mm(int cpu)
{
}
#endif
>>>>>>> efc49de... first commit

#endif /* _ASM_X86_MMU_H */
