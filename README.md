# Roadrunner64

This operating system image runs on a 64-bit x86_64 QEMU virtual machine.
The system will dump some output and then present the user with a simple
echo command line.  You can type anything and it will be echo'd back to
you.  It uses simple UART access to send and receive characters from the
user.

The kernel is single-threaded and boots the virtual processor into 64-bit
long mode with a flat memory model and no memory protection.

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
