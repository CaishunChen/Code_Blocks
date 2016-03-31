//required header files
#include<linux/kernel.h>    //for printk()
#include<linux/init.h>      //for init and exit functions
#include<linux/module.h>    //for MODULE_ functions
#include<linux/fs.h>        //for file_operations struct

#define MAJ_NO 60        //major number

//function prototypes
static int char_temp_open(struct inode *inode, struct file *filep);
static int char_temp_close(struct inode *inode, struct file *filep);
ssize_t char_temp_read(struct file *filep, char *buf, size_t count, loff_t *f_pos);
ssize_t char_temp_write(struct file *filep, char *buf, size_t count, loff_t *f_pos);
static void __exit char_temp_exit(void);
static int __init char_temp_init(void);

//associate standard file open, close, read & write operations to the ones implemented in the driver
struct file_operations char_temp_fops= 
{
  read: char_temp_read,
  write: char_temp_write,
  open: char_temp_open,
  release: char_temp_close
};

/*************Initialization & De-initialization*************/
//module initialization function
static int __init char_temp_init(void)         //static usage is optional
{
	//Registering device
  	if((register_chrdev(MAJ_NO, "char_tmp", &char_temp_fops))<0)        //failed to register
  	{
    	printk(KERN_ALERT "Char Driver Registration Failed!\n"); //printk() is equivalent of printf() in kernel space, print at priority KERN_ALERT
    	return -1;
  	}
  	else                                                 //successfully registered
  	{
    	printk(KERN_ALERT "Char Driver Initialized!\n"); //printk() is equivalent of printf() in kernel space, print at priority KERN_ALERT
    	return 0;
    }
}

//module de-initialization function
static void __exit char_temp_exit(void)        //static usage is optional
{
	unregister_chrdev(MAJ_NO, "char_tmp");          //unregister device with the mentioned major number & name
    printk(KERN_ALERT "Char Driver De-initialized!\n");  //printk() is equivalent of printf() in kernel space, print at priority KERN_ALERT
}

module_init(char_temp_init);                            //indicate to kernel that hello_init() is the module initialization function
module_exit(char_temp_exit);                            //indicate to kernel that hello_exit() is the module de-initialization function

/***********************File Operations**********************/
//file open function
static int char_temp_open(struct inode *inode, struct file *filep)
{
	printk(KERN_ALERT "Char Driver Device Opened!\n");  //printk() is equivalent of printf() in kernel space, print at priority KERN_ALERT
	return 0;
}

//file close function
static int char_temp_close(struct inode *inode, struct file *filep)
{
	printk(KERN_ALERT "Char Driver Device Closed!\n");  //printk() is equivalent of printf() in kernel space, print at priority KERN_ALERT
	return 0;
}

//file read function
ssize_t char_temp_read(struct file *filep, char *buf, size_t count, loff_t *f_pos)
{
	printk(KERN_ALERT "Char Driver Device Read!\n");    //printk() is equivalent of printf() in kernel space, print at priority KERN_ALERT
	return 1;
}

//file write function
ssize_t char_temp_write(struct file *filep, char *buf, size_t count, loff_t *f_pos)
{
	printk(KERN_ALERT "Char Driver Device Written!\n"); //printk() is equivalent of printf() in kernel space, print at priority KERN_ALERT
	return 1;
}

/**********************Module Attributes*********************/
MODULE_LICENSE("GPL");
MODULE_AUTHOR("UDAYAN PRABIR SINHA");
MODULE_DESCRIPTION("Char Driver Template Module");
MODULE_VERSION("V1.0");