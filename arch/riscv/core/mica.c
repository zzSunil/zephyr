#include "zephyr/sys/printk.h"
#include <mica.h>
#include <zephyr/irq.h>
#include <zephyr/sys/atomic.h>
#include <zephyr/arch/riscv/irq.h>
#include <zephyr/arch/riscv/sbi.h>
#define IPI_MCS			0x09

#define OS_SEC_RSC_TABLE __attribute__((section(".resource_table")))
OS_SEC_RSC_TABLE static struct fw_resource_table resource_table = {
    .ver = 1,
    .num = 2,
    .offset = {
        offsetof(struct fw_resource_table, ept_table),
#ifdef OS_GDB_STUB
        offsetof(struct fw_resource_table, rbufs),
#endif
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
	csr_read_clear(xip, 1 << 1);
	printk("xcause 0x%lx\n",csr_read(xcause));
	printk("*************************\n");
	printk("* mica recive interrupt *\n");
	printk("*************************\n");
	sbi_hsm_hart_stop();
}

int mica_init(void)
{
	IRQ_CONNECT(1, 0, mica_ipi_handler, NULL, 0);
	irq_enable(1);

	printk("init mica irq\n");

	return 0;
}
