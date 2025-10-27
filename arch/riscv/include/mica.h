#ifndef __MICA_H__
#define __MICA_H__
#include <stdint.h>

struct ept_info {
    char name[1];
    uint32_t addr;
    uint32_t dest_addr;
};
#define MAX_NUM_OF_EPTS 64
struct fw_rsc_ept {
    uint32_t type;
    uint32_t num_of_epts;
    struct ept_info endpoints[MAX_NUM_OF_EPTS];
};
struct fw_rsc_vdev_vring {
    uint32_t da;
    uint32_t align;
    uint32_t num;
    uint32_t notifyid;
    uint32_t reserved;
};


struct fw_rsc_vdev {
    uint32_t type;
    uint32_t id;
    uint32_t notifyid;
    uint32_t dfeatures;
    uint32_t gfeatures;
    uint32_t config_len;
    uint8_t status;
    uint8_t num_of_vrings;
    uint8_t reserved[2];
    struct fw_rsc_vdev_vring vring[0];
};


struct fw_resource_table {
    unsigned int ver;
    unsigned int num;
    unsigned int reserved[2];
    unsigned int offset[2];

    struct fw_rsc_ept ept_table;
    struct fw_rsc_vdev vdev;
    struct fw_rsc_vdev_vring vring0;
    struct fw_rsc_vdev_vring vring1;

};

int mica_init(void);
#endif

