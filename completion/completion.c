#include <linux/completion.h>
#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/delay.h>


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("completion!");

struct completion c;
int a=0;

static int func(void *a);

static int __init hello_init(void)
{
	struct task_struct *th;
	printk("allenliu: hello world!\n");
	init_completion(&c);
	th=kthread_run(func,&a,"completion_thread");
	wait_for_completion(&c);
	a=1;
	return 0;
}

static void __exit hello_exit(void)
{
	printk("allenliu: %d\n",a);
	printk("allenliu: bye bye world!\n");
}

static int func(void *a)
{
	int *b=(int *)a;
	//msleep(5);
	printk("allenliu: func %d\n",*b);
	complete(&c);
	return 0;
}

module_init(hello_init);
module_exit(hello_exit);
