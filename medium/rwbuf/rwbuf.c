#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <asm/io.h>
#include <linux/gfp.h>
// 用于 ioctl 命令
#define RW_CLEAR 0x909090
#define RW_RDOLD 0x909091
#define RW_RDNEW 0x909092

// 设备名称
#define DEVICE_NAME "rwbuf"
// 锁机制，保证只能有一个打开的设备。0 为未打开，1 为已打开
static int inuse = 0;
// 缓冲区最大长度
#define RWBUF_MAX_SIZE 1024
// 模式
static int mode = 1;
// 缓冲区，初始值需要是学号以便能在设备安装后立刻读出
static char* rwbuf_old;
static int old_cnt = 3;
static char* rwbuf_new;
static int new_cnt = 3;

/**
 * 打开设备
 * 
 * @return 0 表示成功，-1 表示失败
 */
int rwbuf_open(struct inode *inode, struct file *file)
{
    if (inuse == 0)
    {
        inuse = 1;
        // increase the use count in struct module
        try_module_get(THIS_MODULE);
        return 0;
    }
    else
        return -1;
}

/**
 * 关闭设备
 * 
 * @return 0 表示成功 
 */
int rwbuf_release(struct inode *inode, struct file *file)
{
    inuse = 0;
    // decrease the use count in struct module
    module_put(THIS_MODULE);
    return 0;
}

/**
 * 将内容写入到设备
 * 
 * @param buf 存放待写入内容的缓冲区
 * @return 正数表示成功，-1 表示错误 
 */
ssize_t rwbuf_write(struct file *file, const char *buf, size_t count, loff_t *f_pos)
{
    if (count > 0)
    {
        // rwbuf_old = rwbuf_new;
        strcpy(rwbuf_old, rwbuf_new);
        old_cnt = new_cnt;
        new_cnt = count > RWBUF_MAX_SIZE ? RWBUF_MAX_SIZE : count;
        copy_from_user(rwbuf_new, buf, new_cnt);
        printk("[rwbuf] Write successful. After writing, new_cnt = %d\n", new_cnt);
        return new_cnt;
    }
    else
    {
        printk("[rwbuf] Write failed. Length of string to be written = %lu\n", count);
        return -1;
    }
}

/**
 * 从设备中读取内容
 * 
 * @param buf 存放读取内容的缓冲区
 */
ssize_t rwbuf_read(struct file *file, char *buf, size_t count, loff_t *f_pos)
{
    if (mode == 1) {
        copy_to_user(buf, rwbuf_new, count);
    } else {
        copy_to_user(buf, rwbuf_old, count);
    }
    // printk("[rwbuf] Read successful. After reading, new_cnt = %d\n", new_cnt);
    return count;
}

/**
 * ioctl 操作
 * 
 * @param arg 要执行的操作
 * @return 0 表示成功，-1 表示错误 
 */
long rwbuf_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    printk("[rwbuf] [RW_CLEAR:%x],[cmd:%x]\n", RW_CLEAR, cmd);
    if (cmd == RW_CLEAR) // 清空缓冲区
    {
        new_cnt = 0;
        printk("[rwbuf] Do ioctl successful. After doing ioctl, new_cnt = %d\n", new_cnt);
    }
    else if (cmd == RW_RDNEW) {
        mode = 1;
    }
    else if (cmd == RW_RDOLD) {
        mode = 0;
    }
    else // 无效命令
    {
        printk("[rwbuf] Do ioctl failed. new_cnt = %d\n", new_cnt);
        return -1;
    }
    return 0;
}

int rwbuf_mmap(struct file *file, struct vm_area_struct *vma) {
    unsigned long offset = vma->vm_pgoff << PAGE_SHIFT;
    unsigned long pfn_start = (virt_to_phys(rwbuf_new) >> PAGE_SHIFT) + vma->vm_pgoff;
    unsigned long virt_start = (unsigned long)rwbuf_new + offset;
    unsigned long size = vma->vm_end - vma->vm_start;
    if (remap_pfn_range(vma, vma->vm_start, pfn_start,
        size,
        vma->vm_page_prot
    ))
        return -EAGAIN;
    return 0;
}

static struct file_operations rwbuf_fops =
    {
        open : rwbuf_open,
        release : rwbuf_release,
        read : rwbuf_read,
        write : rwbuf_write,
        unlocked_ioctl : rwbuf_ioctl,
        mmap : rwbuf_mmap,
    };

static int __init rwbuf_init(void)
{
    int ret = -1;
    rwbuf_new = kzalloc(RWBUF_MAX_SIZE, GFP_KERNEL);
    strcpy(rwbuf_new, "223\0");
    rwbuf_old = kzalloc(RWBUF_MAX_SIZE, GFP_KERNEL);
    strcpy(rwbuf_old, "223\0");
    printk("[rwbuf] Initializing device...\n");
    // 60: 主设备号，与创建 /dev/rwbuf 时使用的对应
    // DEVICE_NAME: 上面定义的设备名称
    // &rwbuf_fops: VFS 相关
    ret = register_chrdev(60, DEVICE_NAME, &rwbuf_fops);
    if (ret != -1)
        printk("[rwbuf] Initialize successful\n");
    else
        printk("[rwbuf] Initialize failed\n");
    return ret;
}

static void __exit rwbuf_exit(void)
{
    unregister_chrdev(60, DEVICE_NAME);
    printk("[rwbuf] Uninstall successful\n");
}

module_init(rwbuf_init);
module_exit(rwbuf_exit);
MODULE_LICENSE("GPL");