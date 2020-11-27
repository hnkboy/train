#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>

static int hello_open(struct inode *inode, struct file *file)
{
	printk("hello word!\n");
	return 0;
}

static struct file_operations hello_drv_fops = {
    .owner  =   THIS_MODULE,    /* 这是一个宏，推向编译模块时自动创建的__this_module变量 */
    .open   =   hello_open,  
};

/*把上述的结构体告诉内核，所以要注册*/
static int __init hello_init(void)
{

	register_chrdev(99,"hello_dev",&hello_drv_fops);/*参数依次为主设备号、设备名称、结构体*/
	return 0;
}

static void __exit hello_exit(void)
{

	unregister_chrdev(99,"hello_dev");/*参数依次为主设备号、设备名称*/
	return 0;
}

/*修饰*/
module_init(hello_init);
module_exit(hello_exit);

/*许可证*/
MODULE_LICENSE("GPL");


