#include "zephyr/sys/printk.h"
#include <mica.h>
#include <zephyr/irq.h>
#include <zephyr/sys/atomic.h>
#include <zephyr/arch/riscv/irq.h>
#define IPI_MCS			0x01
#define CPU_OFF_FUNCID     0x84000002

#define OS_SEC_RSC_TABLE __attribute__((section(".resource_table")))
OS_SEC_RSC_TABLE static struct fw_resource_table resource_table = {
    .ver = 1,
    .num = 2,
    .offset = {
        offsetof(struct fw_resource_table, ept_table),
        offsetof(struct fw_resource_table, vdev),
    },

    .ept_table = {
        .type = 128,
	.num_of_epts = 0,
    },
    .vdev = {
        3, 7, 2, 1, 0, 0, 0,
        2, {0, 0},
    },

    /* Vring rsc entry - part of vdev rsc entry */
    .vring0 = {-1, 4, 8, 0, 0},
    .vring1 = {-1, 4, 8, 1, 0},
};

void rsc_table_get(void **table_ptr, int *length)
{
    *table_ptr = (void *)&resource_table;
    *length = sizeof(resource_table);
}

void mica_ipi_handler(const void *unused)
{
	// FIXME:
	/**csr_read_clear(xip, 1 << 1);*/

	/**void *rsc;*/
	/**int rsc_size;*/
	/**uint32_t status;*/
	/**struct fw_resource_table *rsc_table;*/

	/**rsc_table_get(&rsc, &rsc_size);*/
	/**rsc_table = (struct fw_resource_table *)rsc;*/
	/**status = rsc_table->reserved[0];*/

	/**printk("xcause 0x%lx status 0x%x\n",csr_read(xcause),status);*/
	/**printk("*************************\n");*/
	/**printk("* mica recive interrupt *\n");*/
	/**printk("*************************\n");*/

	/**if(status == CPU_OFF_FUNCID){*/
	/**        sbi_hsm_hart_stop();*/
	/**}*/
}

int mica_init(void)
{
	IRQ_CONNECT(IPI_MCS, 0, mica_ipi_handler, NULL, 0);
	irq_enable(IPI_MCS);

	return 0;
}

