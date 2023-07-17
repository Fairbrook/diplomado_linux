#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/errno.h>
#include "kamv_linked_list.h"

static dev_t major;
static struct cdev cdevice;
struct kamv_node{
    struct list_head list;
    unsigned long magic;
};
LIST_HEAD(head_node);

static int list_m_open(struct inode *inode, struct file *file) {
  pr_info("List char device opened\n");
  return 0;
}

static int list_m_release(struct inode *inode, struct file *file) {
  pr_info("List char device released\n");
  return 0;
}

static long int list_m_ioctl (struct file *filp, unsigned int cmd, unsigned long arg){
  struct kamv_node *node;
  int sum;
  pr_info("List ioctl cmd %ud\n", cmd);

  switch (cmd){
    case LINKED_LIST_POP: {
      pr_info("List ioctl pop action\n");
      if(list_empty(&head_node)) return 0;
      node = list_last_entry(&head_node, struct kamv_node, list);
      list_del(&node->list);
      kfree(node);
      node = NULL;
      return 0;
    }
    case LINKED_LIST_SUM: {
      pr_info("List ioctl sum action\n");
      if(list_empty(&head_node)) return 0;
      sum = 0;
      list_for_each_entry(node, &head_node, list) {
        sum += node->magic;
      }
      node = NULL;
      return sum;
    }
  }
  pr_err("List ioctl bad cmd %d\n", cmd);
  return -ENOTTY;
}

    
static ssize_t list_m_write(struct file *file, const char __user * buf, size_t lbuf, loff_t * ppos) {
    struct kamv_node *new_node;
    ssize_t ret = 0;
    char *kbuf;
    unsigned long magic;
	pr_info("Linked list write\n");

    kbuf = kmalloc(sizeof(lbuf), GFP_KERNEL);
    if(kbuf == NULL) return -ENOMEM;
    if(copy_from_user(kbuf, buf, lbuf)) {
        kfree(kbuf);
        return -EFAULT;
    }
        
    // Could have used kstrtoul_from_user
    ret = kstrtoul(kbuf, 0, &magic);
    kfree(kbuf);
    kbuf = NULL;
    if(ret < 0) return ret;

    new_node = kmalloc(sizeof(struct kamv_node), GFP_KERNEL);
    if(new_node == NULL) return -ENOMEM;
    new_node->magic = magic;
    INIT_LIST_HEAD(&new_node->list);
    list_add_tail(&new_node->list, &head_node);
    *ppos += lbuf;
    return lbuf;
}

static ssize_t list_m_read(struct file *file, char __user * buf, size_t lbuf, loff_t * ppos) {
    char *kbuf;
    size_t len;
    int ret;
	pr_info("Linked list read\n");
    if(list_empty(&head_node)) return 0;
    if(*ppos != 0) return 0;

    len = lbuf;
    if(len > MAX_READ_SIZE) len = MAX_READ_SIZE;
    kbuf = kmalloc(len, GFP_KERNEL);
    if(kbuf == NULL) return -ENOMEM;
    // Could have writen directly to user buffer?
    len = snprintf(kbuf, lbuf, "%lu", list_last_entry(&head_node, struct kamv_node, list)->magic);
    ret = copy_to_user(buf, kbuf, len); 
    kfree(kbuf);
    if(ret) return -EFAULT;
    *ppos += len;
    return len;
}

static struct file_operations list_m_fops = {
  .owner = THIS_MODULE,
  .open = list_m_open,
  .release = list_m_release,
  .write = list_m_write,
  .read = list_m_read,
  .unlocked_ioctl = list_m_ioctl,
};

static int __init list_m_init(void) {
  int ret = -EINVAL;
  pr_info("Linked list module loaded at 0x%p\n", list_m_init);
  ret = alloc_chrdev_region(&major, 0, 1, "kamv_list");
  if (ret) {
    pr_err("Error: %d While allocating major number", ret);
    return ret;
  }
  cdev_init(&cdevice, &list_m_fops);
  ret = cdev_add(&cdevice, major, 1);
  if (ret) {
    unregister_chrdev_region(major, 1);
    pr_err("Error: %d While adding character device", ret);
    return ret;
  }

  return 0;
}

static void __exit list_m_exit(void) {
  struct kamv_node *cursor, *temp;

  // Delete list elements
  list_for_each_entry_safe(cursor, temp, &head_node, list) {
    pr_info("Freeing node with data = %lu\n", cursor->magic);
    
    // Not really needed since we are going to delete the whole list
    // But better to keep it in since we dont want dangling references
    list_del(&cursor->list);
    kfree(cursor);
  }

  // Handled automatic for the kernel, but better to do it anyway
  // Deregister the device
  cdev_del(&cdevice);
  // Free major number
  unregister_chrdev_region(major, 1);

  pr_info("Linked list module unloaded from 0x%p\n", list_m_exit);
}

module_init(list_m_init);
module_exit(list_m_exit);

MODULE_AUTHOR("Kevin Martinez");
MODULE_LICENSE("GPL v2");
