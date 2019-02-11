#ifndef _ASM_GENERIC_FUTEX_H
#define _ASM_GENERIC_FUTEX_H

#include <linux/futex.h>
#include <linux/uaccess.h>
#include <asm/errno.h>

#ifndef CONFIG_SMP
/*
 * The following implementation only for uniprocessor machines.
 * It relies on preempt_disable() ensuring mutual exclusion.
 *
 */

/**
<<<<<<< HEAD
 * arch_futex_atomic_op_inuser() - Atomic arithmetic operation with constant
=======
 * futex_atomic_op_inuser() - Atomic arithmetic operation with constant
>>>>>>> efc49de... first commit
 *			  argument and comparison of the previous
 *			  futex value with another constant.
 *
 * @encoded_op:	encoded operation to execute
 * @uaddr:	pointer to user space address
 *
 * Return:
 * 0 - On success
 * <0 - On error
 */
static inline int
<<<<<<< HEAD
arch_futex_atomic_op_inuser(int op, u32 oparg, int *oval, u32 __user *uaddr)
{
	int oldval, ret;
	u32 tmp;

=======
futex_atomic_op_inuser(int encoded_op, u32 __user *uaddr)
{
	int op = (encoded_op >> 28) & 7;
	int cmp = (encoded_op >> 24) & 15;
	int oparg = (encoded_op << 8) >> 20;
	int cmparg = (encoded_op << 20) >> 20;
	int oldval, ret;
	u32 tmp;

	if (encoded_op & (FUTEX_OP_OPARG_SHIFT << 28))
		oparg = 1 << oparg;

>>>>>>> efc49de... first commit
	preempt_disable();
	pagefault_disable();

	ret = -EFAULT;
	if (unlikely(get_user(oldval, uaddr) != 0))
		goto out_pagefault_enable;

	ret = 0;
	tmp = oldval;

	switch (op) {
	case FUTEX_OP_SET:
		tmp = oparg;
		break;
	case FUTEX_OP_ADD:
		tmp += oparg;
		break;
	case FUTEX_OP_OR:
		tmp |= oparg;
		break;
	case FUTEX_OP_ANDN:
		tmp &= ~oparg;
		break;
	case FUTEX_OP_XOR:
		tmp ^= oparg;
		break;
	default:
		ret = -ENOSYS;
	}

	if (ret == 0 && unlikely(put_user(tmp, uaddr) != 0))
		ret = -EFAULT;

out_pagefault_enable:
	pagefault_enable();
	preempt_enable();

<<<<<<< HEAD
	if (ret == 0)
		*oval = oldval;

=======
	if (ret == 0) {
		switch (cmp) {
		case FUTEX_OP_CMP_EQ: ret = (oldval == cmparg); break;
		case FUTEX_OP_CMP_NE: ret = (oldval != cmparg); break;
		case FUTEX_OP_CMP_LT: ret = (oldval < cmparg); break;
		case FUTEX_OP_CMP_GE: ret = (oldval >= cmparg); break;
		case FUTEX_OP_CMP_LE: ret = (oldval <= cmparg); break;
		case FUTEX_OP_CMP_GT: ret = (oldval > cmparg); break;
		default: ret = -ENOSYS;
		}
	}
>>>>>>> efc49de... first commit
	return ret;
}

/**
 * futex_atomic_cmpxchg_inatomic() - Compare and exchange the content of the
 *				uaddr with newval if the current value is
 *				oldval.
 * @uval:	pointer to store content of @uaddr
 * @uaddr:	pointer to user space address
 * @oldval:	old value
 * @newval:	new value to store to @uaddr
 *
 * Return:
 * 0 - On success
 * <0 - On error
 */
static inline int
futex_atomic_cmpxchg_inatomic(u32 *uval, u32 __user *uaddr,
			      u32 oldval, u32 newval)
{
	u32 val;

	preempt_disable();
	if (unlikely(get_user(val, uaddr) != 0)) {
		preempt_enable();
		return -EFAULT;
	}

	if (val == oldval && unlikely(put_user(newval, uaddr) != 0)) {
		preempt_enable();
		return -EFAULT;
	}

	*uval = val;
	preempt_enable();

	return 0;
}

#else
static inline int
<<<<<<< HEAD
arch_futex_atomic_op_inuser(int op, u32 oparg, int *oval, u32 __user *uaddr)
{
	int oldval = 0, ret;
=======
futex_atomic_op_inuser (int encoded_op, u32 __user *uaddr)
{
	int op = (encoded_op >> 28) & 7;
	int cmp = (encoded_op >> 24) & 15;
	int oparg = (encoded_op << 8) >> 20;
	int cmparg = (encoded_op << 20) >> 20;
	int oldval = 0, ret;
	if (encoded_op & (FUTEX_OP_OPARG_SHIFT << 28))
		oparg = 1 << oparg;

	if (! access_ok (VERIFY_WRITE, uaddr, sizeof(u32)))
		return -EFAULT;
>>>>>>> efc49de... first commit

	pagefault_disable();

	switch (op) {
	case FUTEX_OP_SET:
	case FUTEX_OP_ADD:
	case FUTEX_OP_OR:
	case FUTEX_OP_ANDN:
	case FUTEX_OP_XOR:
	default:
		ret = -ENOSYS;
	}

	pagefault_enable();

<<<<<<< HEAD
	if (!ret)
		*oval = oldval;

=======
	if (!ret) {
		switch (cmp) {
		case FUTEX_OP_CMP_EQ: ret = (oldval == cmparg); break;
		case FUTEX_OP_CMP_NE: ret = (oldval != cmparg); break;
		case FUTEX_OP_CMP_LT: ret = (oldval < cmparg); break;
		case FUTEX_OP_CMP_GE: ret = (oldval >= cmparg); break;
		case FUTEX_OP_CMP_LE: ret = (oldval <= cmparg); break;
		case FUTEX_OP_CMP_GT: ret = (oldval > cmparg); break;
		default: ret = -ENOSYS;
		}
	}
>>>>>>> efc49de... first commit
	return ret;
}

static inline int
futex_atomic_cmpxchg_inatomic(u32 *uval, u32 __user *uaddr,
			      u32 oldval, u32 newval)
{
	return -ENOSYS;
}

#endif /* CONFIG_SMP */
#endif
