#include <stdio.h>
int main(int argc, char *argv[])
{
    int ret;
    unsigned lcore_id;
    ret = rte_eal_init(argc, argv);
    return 0;
}