/**
 * Copyright (c) 2011 Anup Patel.
 * All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * @file cpu_vcpu_emulate_arm.h
 * @version 1.0
 * @author Anup Patel (anup@brainfault.org)
 * @brief header file to emulate ARM instructions
 */
#ifndef _CPU_VCPU_EMULATE_ARM_H__
#define _CPU_VCPU_EMULATE_ARM_H__

#include <vmm_types.h>

enum arm_shift_type {
	arm_shift_lsl,
	arm_shift_lsr,
	arm_shift_asr,
	arm_shift_ror,
	arm_shift_rrx
};

#define ARM_INST_BIT(inst, start)		(((inst) >> (start)) & 0x1)
#define ARM_INST_BITS(inst, end, start)		(((inst) << (31-(end))) >> (31+(start)-(end)))
#define ARM_INST_DECODE(inst, mask, shift)	(((inst) & (mask)) >> (shift))
#define ARM_INST_ENCODE(val, mask, shift)	(((val) << (shift)) & (mask))

#define ARM_HYPERCALL_CPS_ID			0
#define ARM_HYPERCALL_CPS_SUBID			0
#define ARM_HYPERCALL_CPS_IMOD_END		16
#define ARM_HYPERCALL_CPS_IMOD_START		15
#define ARM_HYPERCALL_CPS_M_END			14
#define ARM_HYPERCALL_CPS_M_START		14
#define ARM_HYPERCALL_CPS_A_END			13
#define ARM_HYPERCALL_CPS_A_START		13
#define ARM_HYPERCALL_CPS_I_END			12
#define ARM_HYPERCALL_CPS_I_START		12
#define ARM_HYPERCALL_CPS_F_END			11
#define ARM_HYPERCALL_CPS_F_START		11
#define ARM_HYPERCALL_CPS_MODE_END		10
#define ARM_HYPERCALL_CPS_MODE_START		6

#define ARM_HYPERCALL_MRS_ID			0
#define ARM_HYPERCALL_MRS_SUBID			1
#define ARM_HYPERCALL_MRS_RD_END		16
#define ARM_HYPERCALL_MRS_RD_START		13
#define ARM_HYPERCALL_MRS_R_END			12
#define ARM_HYPERCALL_MRS_R_START		12

#define ARM_HYPERCALL_MSR_I_ID			0
#define ARM_HYPERCALL_MSR_I_SUBID		2
#define ARM_HYPERCALL_MSR_I_MASK_END		16
#define ARM_HYPERCALL_MSR_I_MASK_START		13
#define ARM_HYPERCALL_MSR_I_IMM12_END		12
#define ARM_HYPERCALL_MSR_I_IMM12_START		1
#define ARM_HYPERCALL_MSR_I_R_END		0
#define ARM_HYPERCALL_MSR_I_R_START		0

#define ARM_HYPERCALL_MSR_R_ID			0
#define ARM_HYPERCALL_MSR_R_SUBID		3
#define ARM_HYPERCALL_MSR_R_MASK_END		16
#define ARM_HYPERCALL_MSR_R_MASK_START		13
#define ARM_HYPERCALL_MSR_R_RN_END		12
#define ARM_HYPERCALL_MSR_R_RN_START		9
#define ARM_HYPERCALL_MSR_R_R_END		8
#define ARM_HYPERCALL_MSR_R_R_START		8

#define ARM_HYPERCALL_RFE_ID			0
#define ARM_HYPERCALL_RFE_SUBID			4
#define ARM_HYPERCALL_RFE_P_END			16
#define ARM_HYPERCALL_RFE_P_START		16
#define ARM_HYPERCALL_RFE_U_END			15
#define ARM_HYPERCALL_RFE_U_START		15
#define ARM_HYPERCALL_RFE_W_END			14
#define ARM_HYPERCALL_RFE_W_START		14
#define ARM_HYPERCALL_RFE_RN_END		13
#define ARM_HYPERCALL_RFE_RN_START		10

#define ARM_HYPERCALL_SRS_ID			0
#define ARM_HYPERCALL_SRS_SUBID			5
#define ARM_HYPERCALL_SRS_P_END			16
#define ARM_HYPERCALL_SRS_P_START		16
#define ARM_HYPERCALL_SRS_U_END			15
#define ARM_HYPERCALL_SRS_U_START		15
#define ARM_HYPERCALL_SRS_W_END			14
#define ARM_HYPERCALL_SRS_W_START		14
#define ARM_HYPERCALL_SRS_MODE_END		13
#define ARM_HYPERCALL_SRS_MODE_START		10

#define ARM_HYPERCALL_LDM_UE_ID0		1
#define ARM_HYPERCALL_LDM_UE_ID1		2
#define ARM_HYPERCALL_LDM_UE_ID2		3
#define ARM_HYPERCALL_LDM_UE_ID3		4
#define ARM_HYPERCALL_LDM_UE_ID4		5
#define ARM_HYPERCALL_LDM_UE_ID5		6
#define ARM_HYPERCALL_LDM_UE_ID6		7
#define ARM_HYPERCALL_LDM_UE_ID7		8
#define ARM_HYPERCALL_LDM_UE_RN_END		19
#define ARM_HYPERCALL_LDM_UE_RN_START		16
#define ARM_HYPERCALL_LDM_UE_REGLIST_END	15
#define ARM_HYPERCALL_LDM_UE_REGLIST_START	0

#define ARM_HYPERCALL_STM_U_ID0			9
#define ARM_HYPERCALL_STM_U_ID1			10
#define ARM_HYPERCALL_STM_U_ID2			11
#define ARM_HYPERCALL_STM_U_ID3			12
#define ARM_HYPERCALL_STM_U_RN_END		19
#define ARM_HYPERCALL_STM_U_RN_START		16
#define ARM_HYPERCALL_STM_U_REGLIST_END		15
#define ARM_HYPERCALL_STM_U_REGLIST_START	0

#define ARM_HYPERCALL_SUBS_REL_ID0		13
#define ARM_HYPERCALL_SUBS_REL_ID1		14
#define ARM_HYPERCALL_SUBS_REL_OPCODE_END	19
#define ARM_HYPERCALL_SUBS_REL_OPCODE_START	16
#define ARM_HYPERCALL_SUBS_REL_RN_END		15
#define ARM_HYPERCALL_SUBS_REL_RN_START		12
#define ARM_HYPERCALL_SUBS_REL_IMM12_END	11
#define ARM_HYPERCALL_SUBS_REL_IMM12_START	0
#define ARM_HYPERCALL_SUBS_REL_IMM5_END		11
#define ARM_HYPERCALL_SUBS_REL_IMM5_START	7
#define ARM_HYPERCALL_SUBS_REL_TYPE_END		6
#define ARM_HYPERCALL_SUBS_REL_TYPE_START	5
#define ARM_HYPERCALL_SUBS_REL_RM_END		3
#define ARM_HYPERCALL_SUBS_REL_RM_START		0

#define ARM_INST_HYPERCALL_ID_MASK		0x00F00000
#define ARM_INST_HYPERCALL_ID_SHIFT		20
#define ARM_INST_HYPERCALL_SUBID_MASK		0x000E0000
#define ARM_INST_HYPERCALL_SUBID_SHIFT		17

#define ARM_INST_LDRSTR_REGFORM2_END		25
#define ARM_INST_LDRSTR_REGFORM2_START		25
#define ARM_INST_LDRSTR_P_END			24
#define ARM_INST_LDRSTR_P_START			24
#define ARM_INST_LDRSTR_U_END			23
#define ARM_INST_LDRSTR_U_START			23
#define ARM_INST_LDRSTR_REGFORM1_END		22
#define ARM_INST_LDRSTR_REGFORM1_START		22
#define ARM_INST_LDRSTR_W_END			21
#define ARM_INST_LDRSTR_W_START			21
#define ARM_INST_LDRSTR_RN_END			19
#define ARM_INST_LDRSTR_RN_START		16
#define ARM_INST_LDRSTR_RT_END			15
#define ARM_INST_LDRSTR_RT_START		12
#define ARM_INST_LDRSTR_IMM12_END		11
#define ARM_INST_LDRSTR_IMM12_START		0
#define ARM_INST_LDRSTR_IMM5_END		11
#define ARM_INST_LDRSTR_IMM5_START		7
#define ARM_INST_LDRSTR_TYPE_END		6
#define ARM_INST_LDRSTR_TYPE_START		5
#define ARM_INST_LDRSTR_IMM4H_END		11
#define ARM_INST_LDRSTR_IMM4H_START		8
#define ARM_INST_LDRSTR_IMM4L_END		3
#define ARM_INST_LDRSTR_IMM4L_START		0
#define ARM_INST_LDRSTR_RM_END			3
#define ARM_INST_LDRSTR_RM_START		0

#define ARM_INST_DATAPROC_OP_MASK		0x02000000
#define ARM_INST_DATAPROC_OP_SHIFT		25
#define ARM_INST_DATAPROC_OP1_MASK		0x01F00000
#define ARM_INST_DATAPROC_OP1_SHIFT		20
#define ARM_INST_DATAPROC_RN_MASK		0x000F0000
#define ARM_INST_DATAPROC_RN_SHIFT		16
#define ARM_INST_DATAPROC_OP2_MASK		0x000000F0
#define ARM_INST_DATAPROC_OP2_SHIFT		4

#define ARM_INST_LDRSTR_A_MASK			0x02000000
#define ARM_INST_LDRSTR_A_SHIFT			25
#define ARM_INST_LDRSTR_OP1_MASK		0x01F00000
#define ARM_INST_LDRSTR_OP1_SHIFT		20
#define ARM_INST_LDRSTR_RN_MASK			0x000F0000
#define ARM_INST_LDRSTR_RN_SHIFT		16
#define ARM_INST_LDRSTR_B_MASK			0x00000010
#define ARM_INST_LDRSTR_B_SHIFT			4

#define ARM_INST_STCX_P_END			24
#define ARM_INST_STCX_P_START			24
#define ARM_INST_STCX_U_END			23
#define ARM_INST_STCX_U_START			23
#define ARM_INST_STCX_D_END			22
#define ARM_INST_STCX_D_START			22
#define ARM_INST_STCX_W_END			21
#define ARM_INST_STCX_W_START			21
#define ARM_INST_STCX_RN_END			19
#define ARM_INST_STCX_RN_START			16
#define ARM_INST_STCX_CRD_END			15
#define ARM_INST_STCX_CRD_START			12
#define ARM_INST_STCX_COPROC_END		11
#define ARM_INST_STCX_COPROC_START		8
#define ARM_INST_STCX_IMM8_END			7
#define ARM_INST_STCX_IMM8_START		0

#define ARM_INST_LDCX_I_P_END			24
#define ARM_INST_LDCX_I_P_START			24
#define ARM_INST_LDCX_I_U_END			23
#define ARM_INST_LDCX_I_U_START			23
#define ARM_INST_LDCX_I_D_END			22
#define ARM_INST_LDCX_I_D_START			22
#define ARM_INST_LDCX_I_W_END			21
#define ARM_INST_LDCX_I_W_START			21
#define ARM_INST_LDCX_I_RN_END			19
#define ARM_INST_LDCX_I_RN_START		16
#define ARM_INST_LDCX_I_CRD_END			15
#define ARM_INST_LDCX_I_CRD_START		12
#define ARM_INST_LDCX_I_COPROC_END		11
#define ARM_INST_LDCX_I_COPROC_START		8
#define ARM_INST_LDCX_I_IMM8_END		7
#define ARM_INST_LDCX_I_IMM8_START		0

#define ARM_INST_LDCX_L_P_END			24
#define ARM_INST_LDCX_L_P_START			24
#define ARM_INST_LDCX_L_U_END			23
#define ARM_INST_LDCX_L_U_START			23
#define ARM_INST_LDCX_L_D_END			22
#define ARM_INST_LDCX_L_D_START			22
#define ARM_INST_LDCX_L_W_END			21
#define ARM_INST_LDCX_L_W_START			21
#define ARM_INST_LDCX_L_CRD_END			15
#define ARM_INST_LDCX_L_CRD_START		12
#define ARM_INST_LDCX_L_COPROC_END		11
#define ARM_INST_LDCX_L_COPROC_START		8
#define ARM_INST_LDCX_L_IMM8_END		7
#define ARM_INST_LDCX_L_IMM8_START		0

#define ARM_INST_MCRRX_RT2_END			19
#define ARM_INST_MCRRX_RT2_START		16
#define ARM_INST_MCRRX_RT_END			15
#define ARM_INST_MCRRX_RT_START			12
#define ARM_INST_MCRRX_COPROC_END		11
#define ARM_INST_MCRRX_COPROC_START		8
#define ARM_INST_MCRRX_OPC1_END			7
#define ARM_INST_MCRRX_OPC1_START		4
#define ARM_INST_MCRRX_CRM_END			3
#define ARM_INST_MCRRX_CRM_START		0

#define ARM_INST_MRRCX_RT2_END			19
#define ARM_INST_MRRCX_RT2_START		16
#define ARM_INST_MRRCX_RT_END			15
#define ARM_INST_MRRCX_RT_START			12
#define ARM_INST_MRRCX_COPROC_END		11
#define ARM_INST_MRRCX_COPROC_START		8
#define ARM_INST_MRRCX_OPC1_END			7
#define ARM_INST_MRRCX_OPC1_START		4
#define ARM_INST_MRRCX_CRM_END			3
#define ARM_INST_MRRCX_CRM_START		0

#define ARM_INST_CDPX_OPC1_END			23
#define ARM_INST_CDPX_OPC1_START		20
#define ARM_INST_CDPX_CRN_END			19
#define ARM_INST_CDPX_CRN_START			16
#define ARM_INST_CDPX_CRD_END			15
#define ARM_INST_CDPX_CRD_START			12
#define ARM_INST_CDPX_COPROC_END		11
#define ARM_INST_CDPX_COPROC_START		8
#define ARM_INST_CDPX_OPC2_END			7
#define ARM_INST_CDPX_OPC2_START		5
#define ARM_INST_CDPX_CRM_END			3
#define ARM_INST_CDPX_CRM_START			0

#define ARM_INST_MCRX_OPC1_END			23
#define ARM_INST_MCRX_OPC1_START		21
#define ARM_INST_MCRX_CRN_END			19
#define ARM_INST_MCRX_CRN_START			16
#define ARM_INST_MCRX_RT_END			15
#define ARM_INST_MCRX_RT_START			12
#define ARM_INST_MCRX_COPROC_END		11
#define ARM_INST_MCRX_COPROC_START		8
#define ARM_INST_MCRX_OPC2_END			7
#define ARM_INST_MCRX_OPC2_START		5
#define ARM_INST_MCRX_CRM_END			3
#define ARM_INST_MCRX_CRM_START			0

#define ARM_INST_MRCX_OPC1_END			23
#define ARM_INST_MRCX_OPC1_START		21
#define ARM_INST_MRCX_CRN_END			19
#define ARM_INST_MRCX_CRN_START			16
#define ARM_INST_MRCX_RT_END			15
#define ARM_INST_MRCX_RT_START			12
#define ARM_INST_MRCX_COPROC_END		11
#define ARM_INST_MRCX_COPROC_START		8
#define ARM_INST_MRCX_OPC2_END			7
#define ARM_INST_MRCX_OPC2_START		5
#define ARM_INST_MRCX_CRM_END			3
#define ARM_INST_MRCX_CRM_START			0

#define ARM_INST_COPROC_OP1_MASK		0x03F00000
#define ARM_INST_COPROC_OP1_SHIFT		20
#define ARM_INST_COPROC_RN_MASK			0x000F0000
#define ARM_INST_COPROC_RN_SHIFT		16
#define ARM_INST_COPROC_CPRO_MASK		0x00000F00
#define ARM_INST_COPROC_CPRO_SHIFT		8
#define ARM_INST_COPROC_OP_MASK			0x00000010
#define ARM_INST_COPROC_OP_SHIFT		4

#define ARM_INST_COND_MASK			0xF0000000
#define ARM_INST_COND_SHIFT			28
#define ARM_INST_OP1_MASK			0x0E000000
#define ARM_INST_OP1_SHIFT			25
#define ARM_INST_OP_MASK			0x00000010
#define ARM_INST_OP_SHIFT			4

/** Emulate Priviledged ARM instructions */
int cpu_vcpu_emulate_arm_inst(vmm_vcpu_t *vcpu, 
				vmm_user_regs_t * regs, bool is_hypercall);

#endif
