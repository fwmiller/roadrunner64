# Roadrunner64

Roadrunner64 is a 64-bit operating system.  It runs on Intel 64-bit machines
in 64-bit long mode.  The kernel is single-threaded and boots the processor
into 64-bit long mode with a flat memory model and no virtual addressing or
memory protection.  There is support for a simple command line interface.

An ATA driver has been added for access to the QEMU virtual machine image
as the primary hard drive.  You should see the storage devices connected
to QEMU at boot time.

This code was originally based on
https://github.com/winksaville/baremetal-x86_64 so I've included the
Apache license document as required.

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
