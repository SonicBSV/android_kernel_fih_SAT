#ifndef _ASM_IRQ_WORK_H
#define _ASM_IRQ_WORK_H

<<<<<<< HEAD
#include <asm/cpufeature.h>
=======
#include <asm/processor.h>
>>>>>>> efc49de... first commit

static inline bool arch_irq_work_has_interrupt(void)
{
	return cpu_has_apic;
}

#endif /* _ASM_IRQ_WORK_H */
