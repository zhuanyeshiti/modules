#include <linux/module.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <asm/uaccess.h> // access_ok(type, addr, size)
#include <linux/slab.h>
#include <linux/string.h>

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
ssize_t mem_write(struct file *filp, const char __user *buf, size_t count, loff_t *fpos)
{
	int result;
	char *ch;
	result = access_ok(VERIFY_READ, buf, count);
	if(!result)
	{
		printk("write error!\n");
	}
	ch = kmalloc(count, GFP_KERNEL);
	memset(ch, 0, strlen(ch));
	copy_from_user(ch, buf, count);
	printk("write: %s\n", ch);
	return (ssize_t)count;
}
long mem_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	int result, size, value, *port1, *port2;
	char *ch;
	printk("int mem_ioctl\n");
	port1 = kmalloc(200, GFP_KERNEL);
	memset(port1, 0, 200);
	value = 0;
	/******check rw access************/
	if(cmd != 22) {
		size = 1;
	}
	else {
		size = *(int *)(arg+1)-*(int *)arg;
	}
	result = access_ok(VERIFY_READ, (void *)arg, size);
	if(!result) {
		printk("error verify_read\n");
	}
	result = access_ok(VERIFY_WRITE, (void *)arg, size);
	if(!result) {
		printk("error verify_write\n");
	}
	/********************************/
	copy_from_user(port1, (int *)arg, 8);
	port2 = port1;
	switch(cmd) {
		case 0:
			value = inb(*port1);
			break;
		case 1:
			value = inw(*port1);
			printk("do you know what the fuck????\n");
			break;
		case 3:
			outb(*(++port2), *port1);
			printk("0x%x\n", *port2);
			value = inb(*port1);
			break;
		default:
			break;
	}
	//value = inl(*port1);
	//printk("cmd is %d, arg is %s\n", cmd, (char *)arg);
	printk("port1 is %x, arg is %x\n", *port1, value);
	*port1 = value;
	copy_to_user((int *)arg, port1, 4);

done:
	//kfree(port1);
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
	.read = NULL,
	.write = mem_write,
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

