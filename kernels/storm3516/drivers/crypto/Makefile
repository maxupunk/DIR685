
obj-$(CONFIG_CRYPTO_DEV_PADLOCK) += padlock.o

obj-$(CONFIG_SL2312_IPSEC) += sl2312_ipsec.o 

padlock-objs-$(CONFIG_CRYPTO_DEV_PADLOCK_AES) += padlock-aes.o

padlock-objs := padlock-generic.o $(padlock-objs-y)
