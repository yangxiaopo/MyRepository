//#include <linux/init.h>
//#include <linux/types.h>
#include <linux/module.h> //module
#include <linux/cdev.h> //cdev
#include <linux/fs.h> //file_operations
#include <linux/slab.h> //kmalloc
#include <linux/uaccess.h> //copy_from_user()
//#include <linux/errno.h>
//#include <linux/mm.h>
//#include <linux/sched.h>
//#include <asm/io.h>
//#include <asm/system.h>

#define SIZE 0x1000
#define _MAJOR 255

static int cdev_major = _MAJOR;
static int num = 1;
struct my_cdev{
	struct cdev character_dev;
	unsigned char memory[SIZE];
}(*mycdevp);

static int my_open(struct inode *inode, struct file *filp)
{
	//filp->private_data = mycdevp; //always the first one
	struct my_cdev *temp;
	temp = container_of(inode->i_cdev,struct my_cdev,character_dev);
	filp->private_data = temp; //point to the opened one
	return 0;
}

static ssize_t my_read (struct file *filp, char __user *buf, size_t size, loff_t *ppos)
{
	unsigned long p = *ppos;
	unsigned int count = size;
	int ret = 0;
	struct my_cdev *dev = filp->private_data;
	
	if(p >= SIZE)
		return 0;
	if(count > SIZE - p)
		count = SIZE - p;
		
	if(copy_to_user(buf,dev->memory,count))
		ret = -EFAULT;
	else{
		*ppos += count;
		ret = count;
		printk(KERN_INFO "read %u bytes(s) from %lu\n",count,p);
	}
	return ret;
}

static ssize_t my_write (struct file *filp, const char __user *buf, size_t size, loff_t *ppos)
{
	unsigned int count = size;
	unsigned long p = *ppos;
	int ret = 0;
	struct my_cdev *dev = filp->private_data;
	
	if(p >= SIZE)
		return 0;
	if(count > SIZE - p)
		count = SIZE - p;

	if(copy_from_user(dev->memory + p,buf,count))
		ret = -EFAULT;
	else{
		*ppos += count;
		ret = count;
		printk(KERN_INFO "written %u bytes(s) from %lu\n",count,p);
	}
	return ret;
}

static long my_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	return 0;
}

static const struct file_operations fops = {
	.owner = THIS_MODULE,
	.read = my_read,
	.write = my_write,
	.unlocked_ioctl = my_ioctl,
	.open = my_open,
};

static int __init my_init(void)
{
	int result,i;

	if(cdev_major)
		result = register_chrdev_region(MKDEV(cdev_major,0),num,"hello_cdev");
	else{
		dev_t devno;
		alloc_chrdev_region(&devno,0,num,"hello_cdev");
		cdev_major = MAJOR(devno);
	}
	
	mycdevp = kmalloc((num*sizeof(struct my_cdev)),GFP_KERNEL);
	memset(mycdevp,0,(num*sizeof(struct my_cdev)));
	
	for(i = 0;i < num;i++,mycdevp++){
		cdev_init(&mycdevp->character_dev,&fops);
		cdev_add(&mycdevp->character_dev,MKDEV(cdev_major,i),1);
		mycdevp->character_dev.owner = THIS_MODULE;
	}
	mycdevp -= num;
	printk(KERN_INFO "hello world enter!");
	return 0;
}

static void __exit my_exit(void)
{
	int i;
	
	for(i = 0;i < num;i++,mycdevp++)
		cdev_del(&mycdevp->character_dev);
	mycdevp -= num;
	kfree(mycdevp);
	unregister_chrdev_region(MKDEV(cdev_major,0),num);
	printk(KERN_INFO "hello world exit!");
}

module_init(my_init);
module_exit(my_exit);
module_param(num,int,S_IRUGO);
module_param(cdev_major,int,S_IRUGO);

MODULE_AUTHOR("yangxiaopo <xiaopoyang@gmail.com>");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_ALIAS("a simplest module");
