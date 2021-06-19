	.text

	/*
         * save the old thread's registers,
         * restore the new thread's registers.
         */

	.globl thread_switch
thread_switch:
	lui t0, 2
	add t1, a0, t0
	sd ra, 8(t1)
	sd sp, 16(t1)
	sd s0, 24(t1)
	sd s1, 32(t1)
	sd s2, 40(t1)
	sd s3, 48(t1)
	sd s4, 56(t1)
	sd s5, 64(t1)
	sd s6, 72(t1)
	sd s7, 80(t1)
	sd s8, 88(t1)
	sd s9, 96(t1)
	sd s10, 104(t1)
	sd s11, 110(t1)
	
	add t1, a1, t0
	ld ra, 8(t1)
	ld sp, 16(t1)
	ld s0, 24(t1)
	ld s1, 32(t1)
	ld s2, 40(t1)
	ld s3, 48(t1)
	ld s4, 56(t1)
	ld s5, 64(t1)
	ld s6, 72(t1)
	ld s7, 80(t1)
	ld s8, 88(t1)
	ld s9, 96(t1)
	ld s10, 104(t1)
	ld s11, 110(t1)
	ret    /* return to ra */
