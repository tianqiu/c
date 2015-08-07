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
	{ 0x53a8e63d, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x9ce03c2a, __VMLINUX_SYMBOL_STR(netlink_kernel_release) },
	{ 0xa2368a07, __VMLINUX_SYMBOL_STR(__netlink_kernel_create) },
	{ 0x8fc7f61a, __VMLINUX_SYMBOL_STR(init_net) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x69acdf38, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xa4269b3f, __VMLINUX_SYMBOL_STR(netlink_unicast) },
	{ 0x6695d4a5, __VMLINUX_SYMBOL_STR(__nlmsg_put) },
	{ 0x4343fecb, __VMLINUX_SYMBOL_STR(netlink_alloc_skb) },
	{ 0xd2b09ce5, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x52824d3f, __VMLINUX_SYMBOL_STR(netlink_rcv_skb) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "AB9F859036FBC9107BEFEB8");
