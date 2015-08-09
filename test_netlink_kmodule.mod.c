#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xb89a34a1, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x8730ec54, __VMLINUX_SYMBOL_STR(netlink_kernel_release) },
	{ 0xe3f86d68, __VMLINUX_SYMBOL_STR(__netlink_kernel_create) },
	{ 0x557b0bdf, __VMLINUX_SYMBOL_STR(init_net) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x69acdf38, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x73245660, __VMLINUX_SYMBOL_STR(netlink_unicast) },
	{ 0x3d5fcb3c, __VMLINUX_SYMBOL_STR(__nlmsg_put) },
	{ 0x4720a5ea, __VMLINUX_SYMBOL_STR(netlink_alloc_skb) },
	{ 0xd2b09ce5, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x906e6bc7, __VMLINUX_SYMBOL_STR(netlink_rcv_skb) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "8C321E1884DF039E069B7DE");
