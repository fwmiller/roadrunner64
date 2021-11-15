# Roadrunner64

Roadrunner64 is an operating system for Intel machines with support for
64-bit addressing and data types.  The kernel is single-threaded and boots
the processor into 64-bit long mode with a flat memory model and no virtual
addressing or memory protection.  There is support for a simple command line
interface.

An ATA driver has been added for access to the QEMU virtual machine image
as the primary hard drive.  A list of the storage devices connected
to QEMU is presented at boot time.

To run this you will need to have xorriso and QEMU installed on your
Linux distro.  For Ubuntu you can do this:

```
$ sudo apt-get install xorriso
$ sudo apt-get install qemu
```

One you have these installed you can type:

```
$ make run
```

The 64-bit long mode boot code was originally based on
https://github.com/winksaville/baremetal-x86_64
