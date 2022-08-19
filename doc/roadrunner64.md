# [Roadrunner64](https://github.com/fwmiller/roadrunner64)

Roadrunner64 is simple operating system.  It provides a deterministic,
high-performance operating environment for 64-bit Intel processors.  The
system is designed to be general purpose in that it allows and relies on
loading and running programs from disk.

The system is currently targeted at a QEMU emulated x86_64 environment.
The system image is built into an ISO9660 file system that can be booted
by QEMU.  When the system starts it will provide command-line access to
the ISO9660 file system through a POSIX compatible API.

## Features

- Single-threaded
- Single timer interrupt
- No virtual addressing or memory protection
- ATA support
- ISO9660 file system support
- POSIX compatible file system interface
- Command line interface

### Single Threaded

The system runs as a single thread of execution.

### Single timer interrupt

The only interrupt allowed in the system is the hardware timer tick.
All other devices are polled.

### Memory Model

The memory model is a single, 64-bit physical address space.  Pointer
types are 64-bits wide.  The amount of available physical memory will be
much smaller.

### ATA Support

The QEMU virtual machine provides access to a virtual disk through a
hardware compatible ATA interface.  The system includes a device driver
that allows access to this virtual disk.

### ISO9660 Support

The ISO9660 file system that is built by the host machine is accessible
through the ATA driver.  The system supports read access to this file
system.  This allows the host to pass files to the Roadrunner64 guest
that is running in the QEMU virtual machine.

### POSIX File I/O

Access to the file system is provided programmatically with a POSIX
compatible, i.e. open/close/read/write, interface.

### The Roadrunner Shell

The system includes a simple Command Line Interface (CLI).

The CLI provides a path oriented view of the ISO9660 file system.

| Command | Description                                                    |
| :------ | :------------------------------------------------------------- |
| cat     | Dumps the contents of a file as text                           |
| hexdump | Dumps the contents of a file as sequence of hexadecimal values |
| ls      | List the contents of a directory                               |
| pwd     | Print the current/working directory                            |
| cd      | Change the current/working directory                           |
| ft      | Print the open file table                                      |
