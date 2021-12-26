# [Roadrunner64](https://github.com/fwmiller/roadrunner64)

Roadrunner64 is simple operating system.  It provides a high-performance
operating environment for 64-bit Intel processors.

The system is currently targeted at a QEMU emulated 64-bit Intel
environment.  The system is built into an ISO9660 file system that can be
booted by QEMU.  When the system starts it will provide command-line
access to the ISO9660 file system through a POSIX compatible API.


[Roadrunner64](https://github.com/fwmiller/roadrunner64)


## Features

- Single-threaded
- No virtual addressing or memory protection
- ATA support
- ISO9660 file system support
- POSIX compatible file system interface
- Command line interface

### Single Threaded

The system runs as a single thread of execution.

### Memory Model

The memory model is a single 64-bit physical address space.  Pointer types
are 64-bits wide.  The amount of available physical memory will be much
smaller.

### ATA Support

The QEMU virtual machine provides access to a virtual ATA disk through
a hardware compatible ATA interface.  The system includes a device driver
that allows access to this disk.

### ISO9660 Support

The ISO9660 file system that is built by the host machine is accessible
through the ATA driver.  The system support read access to this file
system.  This allows the host to pass files to the Roadrunner64 guest
that is running in the QEMU virtual machine.

### POSIX File I/O

Access to the file system is provided programmatically with a POSIX
compatible, i.e. open/close/read/write, interface.

### Command Line Interface

The system includes a simple command line interface.
