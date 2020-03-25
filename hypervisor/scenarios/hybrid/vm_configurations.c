/*
 * Copyright (C) 2018 Intel Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <vm_config.h>
#include <vuart.h>
#include <pci_dev.h>

struct acrn_vm_config vm_configs[CONFIG_MAX_VM_NUM] = {
	{	/* VM0 */
		.load_order = PRE_LAUNCHED_VM,
		.name = "ACRN PRE-LAUNCHED VM0",
		/* fc836901-8685-4bc0-8b71-6e31dc36fa47 */
		.uuid = SAFETY_VM_UUID1,
		.guest_flags = 0UL,
		.vcpu_num = 1U,
		.vcpu_affinity = VM0_CONFIG_VCPU_AFFINITY,
		.clos = 0U,
		.severity = SEVERITY_SAFETY_VM,
		.memory = {
			.start_hpa = VM0_CONFIG_MEM_START_HPA,
			.size = VM0_CONFIG_MEM_SIZE,
		},
		.os_config = {
			.name = "Zephyr",
			.kernel_type = KERNEL_ZEPHYR,
			.kernel_mod_tag = "Zephyr_RawImage",
			.bootargs = "",
			.kernel_load_addr = 0x100000,
			.kernel_entry_addr = 0x100000,
		},
		.vuart[0] = {
			.type = VUART_LEGACY_PIO,
			.addr.port_base = COM1_BASE,
			.irq = COM1_IRQ,
		},
		.vuart[1] = {
			.type = VUART_LEGACY_PIO,
			.addr.port_base = COM2_BASE,
			.irq = COM2_IRQ,
			.t_vuart.vm_id = 1U,
			.t_vuart.vuart_id = 1U,
		}
	},
	{	/* VM1 */
		.load_order = SOS_VM,
		.name = "ACRN SOS VM",
		.uuid = {0xdbU, 0xbbU, 0xd4U, 0x34U, 0x7aU, 0x57U, 0x42U, 0x16U,	\
			 0xa1U, 0x2cU, 0x22U, 0x01U, 0xf1U, 0xabU, 0x02U, 0x40U},
			/* dbbbd434-7a57-4216-a12c-2201f1ab0240 */

		.guest_flags = 0UL,
		.clos = 0U,
		.severity = SEVERITY_SOS,
		.memory = {
			.start_hpa = 0UL,
			.size = CONFIG_SOS_RAM_SIZE,
		},
		.os_config = {
			.name = "ACRN Service OS",
#if !defined(CONFIG_OVMF_FOR_ACRN_SOS)
			.kernel_type = KERNEL_BZIMAGE,
			.kernel_mod_tag = "Linux_bzImage",
			.bootargs = SOS_VM_BOOTARGS,
#else
			.kernel_type = KERNEL_OVMF,
			.kernel_mod_tag = "OVMF",
			.bootargs = "",
			.kernel_load_addr = 0x100000000ULL-CONFIG_OVMF_IMG_SIZE_SOS, 
			.kernel_entry_addr = 0xFFF0U, // real mode
#endif
		},
		.vuart[0] = {
			.type = VUART_LEGACY_PIO,
			.addr.port_base = SOS_COM1_BASE,
			.irq = SOS_COM1_IRQ,
		},
		.vuart[1] = {
			.type = VUART_LEGACY_PIO,
			.addr.port_base = SOS_COM2_BASE,
			.irq = SOS_COM2_IRQ,
			.t_vuart.vm_id = 0U,
			.t_vuart.vuart_id = 1U,
		},
		.pci_dev_num = SOS_EMULATED_PCI_DEV_NUM,
		.pci_devs = sos_pci_devs,
	},
	{	/* VM2 */
		.load_order = POST_LAUNCHED_VM,
		.uuid = {0xd2U, 0x79U, 0x54U, 0x38U, 0x25U, 0xd6U, 0x11U, 0xe8U,	\
			 0x86U, 0x4eU, 0xcbU, 0x7aU, 0x18U, 0xb3U, 0x46U, 0x43U},
			/* d2795438-25d6-11e8-864e-cb7a18b34643 */
		.vcpu_num = 1U,
		.vcpu_affinity = VM2_CONFIG_VCPU_AFFINITY,
		.severity = SEVERITY_STANDARD_VM,
		.vuart[0] = {
			.type = VUART_LEGACY_PIO,
			.addr.port_base = COM1_BASE,
			.irq = COM1_IRQ,
		},
		.vuart[1] = {
			.type = VUART_LEGACY_PIO,
			.addr.port_base = INVALID_COM_BASE,
		}
	}
};
