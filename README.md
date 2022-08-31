# Roadrunner64

Roadrunner64 is an operating system for Intel machines that support 64-bit addressing and data types.  The kernel is single-threaded and boots the processor into 64-bit long mode with a flat memory model and no virtual addressing or memory protection.

There is support for a simple command line interface.

An ATA driver has been added for access to the QEMU virtual machine image as the primary hard drive.  The driver is used to enumerate the ATA connected devices at boot time.  The first partition on the first device that must be a hard drive on the first ATA controller is used at the primary volume.

Support for access to the ISO9660 file system resident in the QEMU virtual machine image has been added.

The OS provides a single application environment within a QEMU virtual machine.

<p align="center"><img width="480px" src="doc/Roadrunner64.png"></p>

To run this you will need to have xorriso and QEMU installed on your Linux distro.  For Ubuntu you can do this:

```
$ sudo apt-get install xorriso
$ sudo apt-get install qemu
```

One you have these installed you can type:

```
$ make run
...
Roadrunner 64-bit
Type ctrl-a x to exit
>
```

The 64-bit long mode boot code is based on
https://github.com/winksaville/baremetal-x86_64
