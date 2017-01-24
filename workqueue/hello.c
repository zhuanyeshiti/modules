#include <linux/module.h> 

//Don't need to include this
//#include<linux/workqueue.h>

//for system_wq
static struct work_struct work;
static struct work_struct work1;

static void work_handler(struct work_struct *data)
{
	//pr_info("got into %s\n", __func__);
	for(int i=0;i<3000;i++)
		printk("1: %d\n",i);
}

static void work_handler1(struct work_struct *data)
{
	for(int i=3001;i<6000;i++)
		printk("2: %d\n",i);
}

//for my workqueue
static struct workqueue_struct *my_queue = NULL;

static int __init init_my_workqueue(void)
{
	my_queue = create_singlethread_workqueue("workqueue demo");
	if(!my_queue)
		return -1;

	pr_info("init my workqueue\n");
	return 0;
}

static int __init hello_init(void)
{
    printk(KERN_INFO "Hello\n");
	INIT_WORK(&work, work_handler);
	INIT_WORK(&work1,work_handler1);
	// In kernel, there is a default workqueue list, named system_wq.
	//schedule_work(&work);
	
	//my work queue, in USB system, there is a workqueue for USB transaction.
	init_my_workqueue();
	
	//queue work on my work queue
	queue_work(my_queue, &work);
	queue_work(my_queue, &work1);

    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_INFO "Goodbye\n");

	//destory your workqueue when you leave
	destroy_workqueue(my_queue);
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_DESCRIPTION("Work queue demo!");
MODULE_LICENSE("GPL");
