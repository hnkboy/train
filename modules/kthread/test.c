#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/kthread.h>
#include<linux/err.h>            
#include <linux/kernel.h>
#include <linux/sched/signal.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <asm/uaccess.h>
#include <linux/wait.h>
#include <linux/mutex.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/poll.h>
#include <linux/cdev.h>
#include <linux/fcntl.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/semaphore.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <asm/atomic.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/delay.h>
#include <linux/cdev.h>	
#include <linux/uaccess.h>
#include <linux/kernel.h>
#include <linux/sched/signal.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <asm/uaccess.h>
#include <linux/wait.h>
#include <linux/mutex.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/poll.h>



#define DEV_NAME    "globalmem"

#include "test.h"
#define GLOBALMEN_LEN    1024

static struct task_struct *test_task;


struct globalmem_dev_t
{
	dev_t  dev_no;
	atomic_t available;
	struct semaphore sem;
	struct cdev cdev;
    struct class * class;
	wait_queue_head_t r_wait_head;
    wait_queue_head_t w_wait_head;
    struct mutex mutex;
    unsigned int curr_len;
    char buf[GLOBALMEN_LEN];
}globalmem_dev;




long globalmem_ioctl(struct file *filp, unsigned int cmd, unsigned long arg);

int globalmem_open(struct inode * inode, struct file * filp)
{
    filp->private_data = &globalmem_dev;
#if 0    // 不能放在这，因为每次写，例如echo命令，就会open一次，会重新初始化r_wait_head，导致read等待队列重新初始化，引起等待队列异常。 唉，基本常识都忘记了
    init_waitqueue_head(&globalmem_dev.r_wait_head);
    init_waitqueue_head(&globalmem_dev.w_wait_head);
    mutex_init(&globalmem_dev.mutex);
#endif
    printk("\r\nglobalmem open.");
    printk("\r\nglobalmem open.");
    return 0;
}
int globalmem_release(struct inode * inode, struct file * filp)
{
    return 0;
}
ssize_t globalmem_read(struct file *filp, char __user * buf, size_t len, loff_t * pos)
{
    struct globalmem_dev_t * globalmem_devp;
    size_t len_rd;
    int ret;

    globalmem_devp = filp->private_data;

    DECLARE_WAITQUEUE(wait,current);

    mutex_lock(&globalmem_devp->mutex);
    add_wait_queue(&globalmem_devp->r_wait_head,&wait);
    while(globalmem_devp->curr_len==0)
    {
        // non-block 
        if( filp->f_flags&O_NONBLOCK )
        {
            ret = -EAGAIN;
            goto out;
        }

        printk("\r\nglobelmem read before schedule.");
        __set_current_state( TASK_INTERRUPTIBLE );
        mutex_unlock(&globalmem_devp->mutex);    // 睡前一定要解锁，否则可能引起死锁
        schedule();        // schudule    
        printk("\r\nglobelmem read after schedule.");
        if( signal_pending( current ) ){
            ret = -ERESTARTSYS;
            goto out2;        
        }
        printk("\r\nglobelmem after signal_pending.");
        mutex_lock(&globalmem_devp->mutex);    
    }

    if( len>globalmem_devp->curr_len )
        len_rd = globalmem_devp->curr_len;
    else
        len_rd = len;    

    if( copy_to_user(buf,globalmem_devp->buf,len_rd) ){
        ret=-EFAULT;
        goto out;
    }
    else{
        memcpy(globalmem_devp->buf,&globalmem_devp->buf[len_rd],globalmem_devp->curr_len-len_rd);
        globalmem_devp->curr_len-=len_rd; 
        printk(KERN_INFO"read %d bytes,current_len %d bytes.",len_rd,globalmem_devp->curr_len);
        wake_up_interruptible(&globalmem_devp->w_wait_head);    // 唤醒等待队列里的写
        ret = len_rd;
    }

out:
    mutex_unlock(&globalmem_devp->mutex);
out2:
    remove_wait_queue(&globalmem_devp->r_wait_head,&wait);
    set_current_state(TASK_RUNNING);
    return ret;
}


ssize_t globalmem_write (struct file *filp, const char __user *buf, size_t len, loff_t *pos)
{
    struct globalmem_dev_t * globalmem_devp;
    size_t len_wr;
    int ret;

    printk("\r\nEnter glocalmem_write.");

    globalmem_devp = filp->private_data;
    DECLARE_WAITQUEUE(wait,current);

    mutex_lock(&globalmem_devp->mutex);
    add_wait_queue(&globalmem_devp->w_wait_head,&wait);
    while(globalmem_devp->curr_len==GLOBALMEN_LEN)
    {
        // non-block 
        if( filp->f_flags&O_NONBLOCK )
        {
            ret = -EAGAIN;
            goto out;
        }

        __set_current_state( TASK_INTERRUPTIBLE );
        mutex_unlock(&globalmem_devp->mutex);    // 睡前一定要解锁，否则可能引起死锁
        schedule();        // schudule    

        if( signal_pending( current ) ){
            ret = -ERESTARTSYS;
            goto out2;        
        }
        
        mutex_lock(&globalmem_devp->mutex);    
    }

    if( len>(GLOBALMEN_LEN-globalmem_devp->curr_len) )
        len_wr = GLOBALMEN_LEN - globalmem_devp->curr_len;
    else
        len_wr = len;    

    if( copy_from_user(globalmem_devp->buf+globalmem_devp->curr_len,buf,len_wr) ){
        ret=-EFAULT;
        goto out;
    }
    else{
        globalmem_devp->curr_len+=len_wr; 
        printk(KERN_INFO"write %d bytes,current_len %d bytes.",len_wr,globalmem_devp->curr_len);
        wake_up_interruptible(&globalmem_devp->r_wait_head);    // 唤醒等待队列里的写
        ret = len_wr;
    }
    

out:
    mutex_unlock(&globalmem_devp->mutex);
out2:
    remove_wait_queue(&globalmem_devp->w_wait_head,&wait);
    set_current_state(TASK_RUNNING);
    return ret;    
}


loff_t globalmem_llseek(struct file *filp, loff_t offset, int whence )
{
    loff_t ret;    // 注意要有返回值

    switch(whence){
    case SEEK_SET:
        if( offset < 0 )
            return -EINVAL;
        if( offset > GLOBALMEN_LEN )
            return -EINVAL;
        filp->f_pos = offset;
        ret = filp->f_pos;    
        break;
    case SEEK_CUR:
        if((filp->f_pos+offset)< 0 )
            return -EINVAL;
        if((filp->f_pos+offset)> GLOBALMEN_LEN )
            return -EINVAL;
        filp->f_pos += offset;
        ret = filp->f_pos;
        break;
    case SEEK_END:
        if((filp->f_pos+offset)< 0 )
            return -EINVAL;
        if((filp->f_pos+offset) > GLOBALMEN_LEN )
            return -EINVAL;
        filp->f_pos += (offset+GLOBALMEN_LEN);
        ret = filp->f_pos;
        break;
    default:
        return -EINVAL;
        break;
    }
    
    return ret;
}



int threadfunc(void *data)//线程
{	
	int i = 0;
    while(1)
	{

		printk("test.ko: output %d\n",i++);
	     /* mb paired w/ kthread_stop */
		set_current_state(TASK_INTERRUPTIBLE);
        schedule();	/*设置状态，切换内核线程，等待事件等再次触发，如果不schedule()，每次msleep结束该线程仍会调度*/
		if (kthread_should_stop()) {/*卸载的时候回调用进来，这是runing，break出*/
			__set_current_state(TASK_RUNNING);
			printk("test.ko: __set_current_state(TASK_RUNNING)");
			break;
		}
		if (need_resched()) 
		{
			schedule();	
			printk("test.ko: schedule()");
		}

	    set_current_state(TASK_RUNNING);
		msleep(1000);
    }
	return 0;
}

unsigned int globalmem_poll( struct file * filp, poll_table * wait )
{
    unsigned int mask=0;
    struct globalmem_dev_t * globalmem_devp;

    globalmem_devp = filp->private_data;

    mutex_lock( &globalmem_devp->mutex );
    poll_wait( filp, &globalmem_devp->r_wait_head, wait );
    poll_wait( filp, &globalmem_devp->w_wait_head, wait );

    if( globalmem_devp->curr_len != 0 )
        mask |= POLLIN | POLLRDNORM;

    if( globalmem_devp->curr_len != GLOBALMEN_LEN )
        mask |= POLLOUT | POLLWRNORM;
    mutex_unlock( &globalmem_devp->mutex );
    return mask;
}


long globalmem_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	switch (cmd) {
		// Get the number of channel found
		case IOCTL_BASE_GET_MUIR:
			printk(KERN_INFO "<%s> ioctl: IOCTL_BASE_GET_MUIR\n", DEV_NAME);
			uint32_t value = 0x12345678;
			if (copy_to_user((uint32_t*) arg, &value, sizeof(value))){
				return -EFAULT;
			}
			wake_up_process(test_task);//使线程运行
			break;

		default:
			break;
	}

	return 0;
}

struct file_operations globalmem_fops = {
    .owner = THIS_MODULE,
    .open = globalmem_open,
    .release = globalmem_release,
	.read = globalmem_read,
    .write = globalmem_write,
	.unlocked_ioctl = globalmem_ioctl,
	.llseek = globalmem_llseek,
	.poll = globalmem_poll,

};


//入口函数--->安装驱动
static int __init globalmem_init(void)
{
	 
	int err;
    int ret;

    printk("enter globalmem_init()\r\n");
    
    cdev_init(&globalmem_dev.cdev,&globalmem_fops);
    globalmem_dev.cdev.owner=THIS_MODULE;

    if( (ret=alloc_chrdev_region(&globalmem_dev.dev_no,0,1,DEV_NAME))<0 )
    {
        printk("alloc_chrdev_region err.\r\n");    
        return ret;
    }
    ret = cdev_add(&globalmem_dev.cdev,globalmem_dev.dev_no,1);
    if( ret )
    {
        printk("cdev_add err.\r\n");    
        return ret;
    }

    /*
         * $ sudo insmod globalmem.ko    如果使用class_create,insmod时会报错，dmesg查看内核log信息发现找不到class相关函数
     *   insmod: ERROR: could not insert module globalmem.ko: Unknown symbol in module
     *   $ dmesg   
     *    [ 5495.606920] globalmem: Unknown symbol __class_create (err 0)
     *    [ 5495.606943] globalmem: Unknown symbol class_destroy (err 0)
     *    [ 5495.607027] globalmem: Unknown symbol device_create (err 0)
     */    

    globalmem_dev.class = class_create( THIS_MODULE, DEV_NAME );
    device_create(globalmem_dev.class,NULL,globalmem_dev.dev_no,NULL,DEV_NAME);

    /* init mem and pos */
    memset(globalmem_dev.buf,0,GLOBALMEN_LEN);

    init_waitqueue_head(&globalmem_dev.r_wait_head);
    init_waitqueue_head(&globalmem_dev.w_wait_head);
    mutex_init(&globalmem_dev.mutex);

    test_task = kthread_create(threadfunc, NULL, "test_task");//创建内核线程

    if(IS_ERR(test_task))//错误判断
	{

    printk("Unable to start kernel thread.\n");

    err = PTR_ERR(test_task);

    test_task =NULL;

    return err;

    }

	wake_up_process(test_task);//使线程运行
	
	
	printk( "This is Flyaudio init \n");
	

	return 0;
}



//出口函数--->卸载驱动
static void __exit globalmem_exit(void)
{
    printk("enter globalmem_exit()\r\n");
    unregister_chrdev_region(globalmem_dev.dev_no, 1);
    cdev_del(&globalmem_dev.cdev);
    device_destroy(globalmem_dev.class,globalmem_dev.dev_no);
    class_destroy(globalmem_dev.class);
}

//驱动程序的入口
module_init(globalmem_init);
//驱动程序的出口
module_exit(globalmem_exit);

//module的描述
MODULE_AUTHOR("flyaudio@163.com");
MODULE_DESCRIPTION("output driver for flyaudio");
//MODULE_LICENSE("DUAL BSD/GPL");
MODULE_VERSION("V1.1");
MODULE_LICENSE("GPL");    // 不加此声明，会报上述Unknown symbol问题