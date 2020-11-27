sudo apt-get install libnl-3-dev libnl-genl-3-dev

gcc genl_ex.c   $(pkg-config --cflags --libs libnl-3.0 libnl-genl-3.0)

https://github.com/a-zaki/genl_ex/tree/master/kernel
