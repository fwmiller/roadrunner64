# Roadrunner64

This image runs as a standalone application on a 64-bit X86 machine.
The image will dump some output and then present the user with a simple
echo command line.  You can type anything and it will be echo'd back to
you.  The image is setup to run in a qemu virtual machine.  It uses
simple UART access to send and receive characters from the user.

An ATA driver with ATAPI support has been added.  You should see the
storage devices connected to qemu at boot time.

This code is based on https://github.com/winksaville/baremetal-x86_64
but has been modified quite a bit.  Even so I've included the Apache
license document as required.

To run this you will need to have xorriso and qemu installed on your
Linux distro.  For Ubuntu you can do this:

```
$ sudo apt-get install xorriso
$ sudo apt-get install qemu
```

One you have these installed you can type:

```
$ make run
```
