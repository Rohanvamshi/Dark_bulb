#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x367398b6, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xaa013a48, __VMLINUX_SYMBOL_STR(class_unregister) },
	{ 0x5eaebe1a, __VMLINUX_SYMBOL_STR(device_destroy) },
	{ 0xdb7c2b58, __VMLINUX_SYMBOL_STR(class_destroy) },
	{ 0xcbbf3ca9, __VMLINUX_SYMBOL_STR(device_create) },
	{ 0x6bc3fbc0, __VMLINUX_SYMBOL_STR(__unregister_chrdev) },
	{ 0x7e20ba1d, __VMLINUX_SYMBOL_STR(__class_create) },
	{ 0x78a9cfbf, __VMLINUX_SYMBOL_STR(__register_chrdev) },
	{ 0x4a74c285, __VMLINUX_SYMBOL_STR(try_module_get) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xa61e767e, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "B613402881ACDB07E14292D");
