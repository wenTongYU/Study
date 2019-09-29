#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module Data Structure");
MODULE_AUTHOR("YU_IT");


struct birthday{
    int day;
    int month;
    int year;
    struct list_head list;
};

static LIST_HEAD(birthday_list);


/* This function is called when the module is loaded. */
int simple_init(void)
{
    printk(KERN_INFO "Loading Module\n");

    printk(KERN_INFO "Create the list.");
    // create a birthday pointer;
    struct birthday* person[5] = { NULL };

    person[0] = kmalloc(sizeof(*person), GFP_KERNEL);
    person[0]->day = 2;
    person[0]->month = 8;
    person[0]->year = 1995;

    person[1] = kmalloc(sizeof(*person), GFP_KERNEL);
    person[1]->day = 3;
    person[1]->month = 4;
    person[1]->year = 1992;

    person[2] = kmalloc(sizeof(*person), GFP_KERNEL);
    person[2]->day = 5;
    person[2]->month = 1;
    person[2]->year = 1998;

    person[3] = kmalloc(sizeof(*person), GFP_KERNEL);
    person[3]->day = 8;
    person[3]->month = 12;
    person[3]->year = 1991;

    person[4] = kmalloc(sizeof(*person), GFP_KERNEL);
    person[4]->day = 25;
    person[4]->month = 4;
    person[4]->year = 1993;


    printk(KERN_INFO "Initialized the list head.");
    // initialized the list head
    INIT_LIST_HEAD(&person[0]->list);

    list_add_tail(&person[0]->list, &birthday_list);
    for(int i = 1; i < 5; ++i)
        list_add_tail(&person[i]->list, &person[i-1]->list);
    
    // iterate the list
    struct birthday *ptr = NULL;
    list_for_each_entry(ptr, &birthday_list, list)
    {
        printk(KERN_INFO "year: %d\n month: %d\n day: %d\n",
             ptr->year, ptr->month, ptr->day);
    }

    return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
	printk(KERN_INFO "Removing Module\n");

    printk(KERN_INFO "Delete the list.");

    
    struct birthdy * ptr, * next;
    ptr = next = NULL;
    list_for_each_entry_safe(ptr, next, &birthday_list, list)
    {
        list_del(&ptr->list);
        kfree(ptr);
    }
    printk(KERN_INFO "The list has been deleted.");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

