/*
 * Copyright (C) 2015 Engicam srl
 *
 * Configuration parameters for the Engicam i.CoreM6SX and SMARCORE
 * module. Refer for all default parameter to this file
 */

#ifndef __COMMON_PARAMETER_H
#define __COMMON_PARAMETER_H


	/* NETWORK SETTINGS */

	#define CONFIG_SERVERIP		192.168.2.96
	#define CONFIG_IPADDR		192.168.2.75
	#define CONFIG_NETMASK		255.255.255.0
	#define CONFIG_ETHADDR		9C:53:CD:01:21:6A

	#if defined(CONFIG_SYS_BOOT_NAND)
		#define CONFIG_BOOTCMD		"bootcmd=run bootcmd_ubi\0"
	#elif defined(CONFIG_SYS_BOOT_SATA)
		#define CONFIG_BOOTCMD		"bootcmd=run bootcmd_sata\0"
	#elif defined(CONFIG_SYS_BOOT_EMMC)
		#define CONFIG_BOOTCMD		"bootcmd=run bootcmd_emmc\0"
	#else
		#define CONFIG_BOOTCMD		"bootcmd=run bootcmd_mmc\0"
	#endif
	
	#define EXTRA_OPTION_SOLO	" cma=96MB "
	#define BOOTCMD_MMC_YOCTO	"run loadfdt; fatload mmc ${mmcdev}:${mmcpart} ${loadaddr} uImage; bootm ${loadaddr} - ${fdt_addr}"
	#define BOOTCMD_MMC_LTIB	"mmc read ${loadaddr} 0x800 0x2000;bootm"
	
	#define YOCTO_BOOTCMD_MMC_ICORE	 "run bootargs; run bootargsy_mmc; setenv mmcdev ${mmcdev}; " BOOTCMD_MMC_YOCTO
	#define YOCTO_BOOTCMD_MMC_RQS	 "run bootargs; run bootargsy_mmc; setenv mmcdev 1; " BOOTCMD_MMC_YOCTO
	#define YOCTO_BOOTCMD_EMMC_RQS	 "run bootargs; run bootargsy_emmc; setenv mmcdev 0; " BOOTCMD_MMC_YOCTO
	#define YOCTO_BOOTCMD_MMC_SMARC	 "run bootargs; run bootargsy_mmc; setenv mmcdev 0; " BOOTCMD_MMC_YOCTO
	#define YOCTO_BOOTCMD_EMMC_SMARC "run bootargs; run bootargsy_emmc; setenv mmcdev 2; " BOOTCMD_MMC_YOCTO
	#define YOCTO_BOOTCMD_UBI	 "run bootargs; run bootargsy_ubi; nand read ${loadaddr} 0x400000 0x700000;nand read ${fdt_addr} 0xc00000 0x100000;bootm ${loadaddr} - ${fdt_addr}"	
	#define YOCTO_BOOTCMD_NET	 "run bootargs; run bootargsy_net; tftp uImage; tftp ${fdt_addr} uImage.dtb; bootm ${loadaddr} - ${fdt_addr}"
	#define YOCTO_MODE		 "yocto_mode=setenv mode YOCTO_MODE; setenv bootcmd_net ${bootcmdy_net}; setenv bootcmd_mmc ${bootcmdy_mmc};"
	
	#define LTIB_BOOTCMD_MMC_ICORE	"run bootargs; run bootargsl_mmc; mmc dev 0; " BOOTCMD_MMC_LTIB
	#define LTIB_BOOTCMD_MMC_RQS	"run bootargs; run bootargsl_mmc; mmc dev 1; " BOOTCMD_MMC_LTIB
	#define LTIB_BOOTCMD_EMMC_RQS	"run bootargs; run bootargsl_emmc; mmc dev 0; " BOOTCMD_MMC_LTIB
	#define LTIB_BOOTCMD_MMC_SMARC	"run bootargs; run bootargsl_mmc; mmc dev 0; " BOOTCMD_MMC_LTIB
	#define LTIB_BOOTCMD_EMMC_SMARC	"run bootargs; run bootargsl_emmc; mmc dev 2; " BOOTCMD_MMC_LTIB
	#define LTIB_BOOTCMD_UBI	"run bootargs; run bootargsl_ubi; nand read ${loadaddr} 0x400000 0x700000;bootm"	
	#define LTIB_BOOTCMD_NET	"run bootargs; run bootargsl_net; tftp uImage; bootm"
	#define LTIB_MODE		"ltib_mode=setenv mode LTIB_MODE; setenv bootcmd_net ${bootcmdl_net}; setenv bootcmd_mmc ${bootcmdl_mmc};"

	/* Common parameter
	 * For all modules SODIMM and QSEVEN
	 */
	#define COMMON_PARAMETER 			\
		"netdev=eth0\0" 			\
		"ethprime=FEC0\0" 			\
		"lcd_panel=Amp-WD\0" 			\
		"nfsroot=/nfs_icore\0"			\
		CONFIG_BOOTCMD				\
		"loadfdt=fatload mmc ${mmcdev}:${mmcpart} ${fdt_addr} ${fdt_file}\0"											\
		"bootargs=setenv bootargs console=" CONFIG_CONSOLE_DEV ",115200" EXTRA_OPTION_SOLO "video=${video_type},${lcd_panel}\0"		\
		"bootargsy_net=setenv bootargs ${bootargs} ${mtdparts_yocto} root=/dev/nfs ip=dhcp nfsroot=${serverip}:${nfsroot},v3,tcp\0" 				\
		"bootargsl_net=setenv bootargs ${bootargs} root=/dev/nfs ip=dhcp nfsroot=${serverip}:${nfsroot},v3,tcp\0" 						\
		"bootcmd_net="  YOCTO_BOOTCMD_NET "\0"															\
		"bootcmdy_net=" YOCTO_BOOTCMD_NET "\0"															\
		"bootcmdl_net=" LTIB_BOOTCMD_NET "\0" 															\
		"mode=YOCTO_MODE\0"																	\
		"mmcdev=0\0"																		\
		"mmcpart=1\0"																		\

	/* Customized parameter
	 * Customized parameter for SODIMM iCore modules
	 */
	#define	EXTRA_ENV_SETTINGS_ICORE 		\
		COMMON_PARAMETER 			\
		"bootargsy_ubi=setenv bootargs ${bootargs} ${mtdparts_yocto} ubi.mtd=3 root=ubi0:rootfs rootfstype=ubifs\0"			\
		"bootargsl_ubi=setenv bootargs ${bootargs} ubi.mtd=2 root=ubi0:rootfs rootfstype=ubifs rootwait rw\0"				\
		"bootargsy_mmc=setenv bootargs ${bootargs} ${mtdparts_yocto} root=/dev/mmcblk0p2 rootwait rw\0" 				\
		"bootargsl_mmc=setenv bootargs ${bootargs} root=/dev/mmcblk0p1 rootwait rw\0" 							\
		"mtdparts_yocto=mtdparts=gpmi-nand:4m(boot),8m(kernel),1m(dtb),-(rootfs)\0"							\
		"bootcmd_mmc="  YOCTO_BOOTCMD_MMC_ICORE "\0"											\
		"bootcmd_ubi="  YOCTO_BOOTCMD_UBI 	"\0" 											\
		"bootcmdy_mmc=" YOCTO_BOOTCMD_MMC_ICORE "\0"											\
		"bootcmdy_ubi=" YOCTO_BOOTCMD_UBI 	"\0" 											\
		"bootcmdl_mmc=" LTIB_BOOTCMD_MMC_ICORE 	"\0" 											\
		"bootcmdl_ubi=" LTIB_BOOTCMD_UBI 	"\0" 											\
		LTIB_MODE  " setenv bootcmd_ubi ${bootcmdl_ubi}\0" 										\
		YOCTO_MODE " setenv bootcmd_ubi ${bootcmdy_ubi}\0"										\
		"video_type=mxcfb0:dev=lcd\0"		\
		"fdt_file=" CONFIG_DEFAULT_FDT_FILE "\0" 	\
		"fdt_addr=0x18000000\0" 																\

																\

	/* Customized parameter
	 * Customized parameter for QSEVEN RQS modules
	 */
	#define	EXTRA_ENV_SETTINGS_ICORE_RQS 			\
		COMMON_PARAMETER 			\
		"bootargsy_emmc=setenv bootargs ${bootargs} root=/dev/mmcblk1p2 rootwait rw\0" 						\
		"bootargsl_emmc=setenv bootargs ${bootargs} root=/dev/mmcblk0p1 rootwait rw\0" 						\
		"bootargsy_mmc=setenv bootargs ${bootargs} root=/dev/mmcblk0p2 rootwait rw\0" 						\
		"bootargsl_mmc=setenv bootargs ${bootargs} root=/dev/mmcblk1p1 rootwait rw\0" 						\
		"bootcmd_mmc="   YOCTO_BOOTCMD_MMC_RQS 	"\0"										\
		"bootcmd_emmc="  YOCTO_BOOTCMD_EMMC_RQS	"\0"										\
		"bootcmdy_mmc="  YOCTO_BOOTCMD_MMC_RQS 	"\0"										\
		"bootcmdy_emmc=" YOCTO_BOOTCMD_EMMC_RQS	"\0"										\
		"bootcmdl_mmc="  LTIB_BOOTCMD_MMC_RQS 	"\0" 										\
		"bootcmdl_emmc=" LTIB_BOOTCMD_EMMC_RQS 	"\0"										\
		LTIB_MODE  " setenv bootcmd_emmc ${bootcmdl_emmc}\0" 									\
		YOCTO_MODE " setenv bootcmd_emmc ${bootcmdy_emmc}\0"									\
		"video_type=mxcfb0:dev=ldb,LDB-XGA,if=RGB666 video=mxcfb0:dev=hdmi,1920x1080M@60,if=RGB24\0"				\
		"fdt_file=" CONFIG_DEFAULT_FDT_FILE "\0" 	\
		"mmcpart=1\0"				\
		"fdt_addr=0x18000000\0" 																\
		
	/* Customized parameter
	 * Customized parameter for SMARCORE modules
	 */
	#define	EXTRA_ENV_SETTINGS_SMARC		\
		COMMON_PARAMETER 			\
		"bootargsy_emmc=setenv bootargs ${bootargs} root=/dev/mmcblk3p2 rootwait rw\0" 						\
		"bootargsl_emmc=setenv bootargs ${bootargs} root=/dev/mmcblk0p1 rootwait rw\0" 						\
		"bootargsy_mmc=setenv bootargs ${bootargs} root=/dev/mmcblk1p2 rootwait rw\0" 						\
		"bootargsl_mmc=setenv bootargs ${bootargs} root=/dev/mmcblk1p1 rootwait rw\0" 						\
		"bootcmd_mmc="   YOCTO_BOOTCMD_MMC_SMARC	"\0"									\
		"bootcmd_emmc="  YOCTO_BOOTCMD_EMMC_SMARC 	"\0"									\
		"bootcmdy_mmc="  YOCTO_BOOTCMD_MMC_SMARC 	"\0"									\
		"bootcmdy_emmc=" YOCTO_BOOTCMD_EMMC_SMARC 	"\0"									\
		"bootcmdl_mmc="  LTIB_BOOTCMD_MMC_SMARC 	"\0" 									\
		"bootcmdl_emmc=" LTIB_BOOTCMD_EMMC_SMARC 	"\0"									\
		LTIB_MODE  " setenv bootcmd_emmc ${bootcmdl_emmc}\0" 									\
		YOCTO_MODE " setenv bootcmd_emmc ${bootcmdy_emmc}\0"									\
		"video_type=mxcfb0:dev=ldb,LDB-XGA,if=RGB666 video=mxcfb0:dev=hdmi,1920x1080M@60,if=RGB24\0"				\
		"fdt_file=imx6sx-smarcore.dtb\0" 	\
		"mmcpart=1\0"				\
		"fdt_addr=0x83000000\0" 																\


	/* Additional defines */
	#define _SERVER_IP_ADDR_	CONFIG_SERVERIP	


#endif
