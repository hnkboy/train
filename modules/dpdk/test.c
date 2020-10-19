#include <stdio.h>
#include <stdint.h>
#include <sched.h>
#include <time.h>
#include <rte_config.h>
#include <rte_compat.h>
#include <rte_per_lcore.h>
#include <rte_bus.h>
#include <rte_uuid.h>
#include <rte_pci_dev_feature_defs.h>
//参考，dpdk 的examples
int main(int argc, char *argv[])
{
    int ret;
    unsigned lcore_id;
    ret = rte_eal_init(argc, argv);
    return 0;
}