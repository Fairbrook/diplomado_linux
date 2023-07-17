#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x1b96180a, "module_layout" },
	{ 0xaace4e2d, "cdev_del" },
	{ 0x51a910c0, "arm_copy_to_user" },
	{ 0xc358aaf8, "snprintf" },
	{ 0x2d6fcc06, "__kmalloc" },
	{ 0x86332725, "__stack_chk_fail" },
	{ 0x68f31cbd, "__list_add_valid" },
	{ 0x668b595, "_kstrtoul" },
	{ 0x5f754e5a, "memset" },
	{ 0xae353d77, "arm_copy_from_user" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0x2cfde9a2, "warn_slowpath_fmt" },
	{ 0x1492ed96, "kmem_cache_alloc_trace" },
	{ 0x8580387f, "kmalloc_caches" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0x37a0cba, "kfree" },
	{ 0xe1537255, "__list_del_entry_valid" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x6de73b5c, "cdev_add" },
	{ 0x65d951fa, "cdev_init" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0xc5850110, "printk" },
};

MODULE_INFO(depends, "");

