#include <linux/module.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>

static int mem_major = 0;
module_param(mem_major, int, S_IRUGO|S_IWUSR);

/********* memdev.h **********/
struct mem_dev
{
	char *data;
	unsigned long size;
};

int mem_open(struct inode *inode, struct file *filp)
{
	printk("in mem_open\n");
	return 0;
}
int mem_release(struct inode *inode, struct file *filp)
{
	printk("in mem_ralease\n");
	return 0;
}
long mem_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	printk("int mem_ioctl\n");
	printk("cmd is %d, arg is %lu\n", cmd, arg);
	return 0;
}

/*****************************/

struct cdev cdev;
struct mem_dev *mem_dev;
struct class *myclass;
static const struct file_operations mem_ops =
{
	.owner = THIS_MODULE,
	.open = mem_open,
	.release = mem_release,
	//.compat_ioctl = mem_ioctl,
	.unlocked_ioctl = mem_ioctl,
};

static int __init hello_init(void)
{
	int result;
	
	dev_t devno = MKDEV(mem_major, 0);
	printk("hello world!\n");
	/********** regist region********/
	if(mem_major)
	{
		result = register_chrdev_region(devno, 2, "memdev");
	}
	else
	{
		result = alloc_chrdev_region(&devno, 0, 2, "memdev");
		mem_major = MAJOR(devno);
	}
	if(result)
	{
		printk("fail\n");
	}
	/********* init cdev ************/
	cdev_init(&cdev, &mem_ops);
	cdev.owner = THIS_MODULE;
	cdev.ops = &mem_ops;
	/********* register dev *********/
	result = cdev_add(&cdev, MKDEV(mem_major, 0), 2);
	if(result)
	{
		printk("error\n");
	}
	/********* add dev node *********/
	myclass = class_create(THIS_MODULE, "memdev");
	device_create(myclass, NULL, MKDEV(mem_major, 0), NULL, "memdev");
	printk("register done\n");

	return 0;
}

static void __exit hello_exit(void)
{
	printk("hello exit\n");
	cdev_del(&cdev);
	//kfree(mem_dev);
	device_destroy(myclass, MKDEV(mem_major, 0));
	class_destroy(myclass);
	unregister_chrdev_region(MKDEV(mem_major, 0), 2);
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("al");
MODULE_VERSION("1.0");
MODULE_DESCRIPTION("chr dev");

