#include <linux/module.h>
#include <linux/printk.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/sched.h>

static struct proc_dir_entry *entry;

/*function to keep track of the processes count*/
static int proc_count(struct seq_file *m, void *v){
	// TODO: it's all yours
	struct task_struct *processes;
	int n = 0;
	for_each_process(processes) {
		n++;
	}
	seq_printf(m,"%d\n", n);
	return 0;
}
/*
static int proc_count_open(struct inode *proc_node, struct file *proc_file) {
	return single_open(proc_file, proc_count, NULL);
}

static const struct file_operations proc_file_operations = {
    .owner      = THIS_MODULE,
    .open       = proc_count_open,
    .read       = seq_read,
    .llseek     = seq_lseek,
    .release    = single_release,
};
*/

/*init function for the module*/
static int __init proc_count_init(void) {
	entry = proc_create("count", 0, NULL, &proc_file_operations);
	pr_info("proc_count: init\n");
	return 0;
}

/*exit function for the module*/
static void __exit proc_count_exit(void)
{
	proc_remove(entry);
	pr_info("proc_count: exit\n");
}

/*metadata*/
module_init(proc_count_init);
module_exit(proc_count_exit);

MODULE_AUTHOR("Freddie Kiessling");
MODULE_DESCRIPTION("CS111 lab0 count proc number");
MODULE_LICENSE("GPL");
