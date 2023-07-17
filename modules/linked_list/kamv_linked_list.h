#include <linux/ioctl.h>

#define MAX_READ_SIZE 11
#define KAMV_MAGIC '$'

#define LINKED_LIST_POP _IO(KAMV_MAGIC, 0)
#define LINKED_LIST_SUM _IOR(KAMV_MAGIC, 1, char)
