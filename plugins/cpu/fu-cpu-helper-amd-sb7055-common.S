/*
 * Copyright 2025 Richard Hughes <richard@hughsie.com>
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

	.text
	.globl	fu_cpu_helper_amd_sb7055_test_rdrand
	.type	fu_cpu_helper_amd_sb7055_test_rdrand, %function
fu_cpu_helper_amd_sb7055_test_rdrand:
	.cfi_startproc
	/* Execute RDRAND instruction with 16-bit output */
	rdrand %ax
	ret
	.cfi_endproc
	.size	fu_cpu_helper_amd_sb7055_test_rdrand, .-fu_cpu_helper_amd_sb7055_test_rdrand

	.globl	fu_cpu_helper_amd_sb7055_test_rdseed
	.type	fu_cpu_helper_amd_sb7055_test_rdseed, %function
fu_cpu_helper_amd_sb7055_test_rdseed:
	.cfi_startproc
	/* Execute RDSEED instruction with 16-bit output */
	rdseed %ax
	ret
	.cfi_endproc
	.size	fu_cpu_helper_amd_sb7055_test_rdseed, .-fu_cpu_helper_amd_sb7055_test_rdseed
	.section	.note.GNU-stack,"",%progbits
