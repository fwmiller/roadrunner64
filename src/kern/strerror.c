#include <errno.h>
#include <string.h>

char*
strerror(int errno) {
    switch (errno) {
    case SUCCESS:
        return "Success";
    case EFAIL:
        return "Failed";
    case E2BIG:
        return "Argument list too long";
    case EACCES:
        return "Permission denied";
    case EAGAIN:
        return "Resource temporarily unavail";
    case EBADF:
        return "Bad file descriptor";
    case EBUSY:
        return "Device busy";
    case ECHILD:
        return "No child processes";
    case EDEADLK:
        return "Resource deadlock avoided";
    case EDOM:
        return "Numerical arg out of domain";
    case EEXIST:
        return "File exists";
    case EFAULT:
        return "Bad address";
    case EFBIG:
        return "File too large";
    case EINTR:
        return "Interrupted system call";
    case EINVAL:
        return "Invalid argument";
    case EIO:
        return "Input/output error";
    case EISDIR:
        return "Is a directory";
    case EMFILE:
        return "Too many open files";
    case EMLINK:
        return "Too many links";
    case ENAMETOOLONG:
        return "File name too long";
    case ENFILE:
        return "Too many open files in system";
    case ENODEV:
        return "Operation not supported by device";
    case ENOENT:
        return "No such file or directory";
    case ENOEXEC:
        return "Exec format error";
    case ENOLCK:
        return "No locks avail";
    case ENOMEM:
        return "Cannot allocate memory";
    case ENOSPC:
        return "No space left on device";
    case ENOSYS:
        return "Function not implemented";
    case ENOTDIR:
        return "Not a directory";
    case ENOTEMPTY:
        return "Directory not empty";
    case ENOTTY:
        return "Inappropriate ioctl for device";
    case ENXIO:
        return "Device not configured";
    case EPERM:
        return "Operation not permitted";
    case EPIPE:
        return "Broken pipe";
    case ERANGE:
        return "Result too large";
    case EROFS:
        return "Read-only file system";
    case ESPIPE:
        return "Illegal seek";
    case ESRCH:
        return "No such process";
    case EXDEV:
        return "Cross-device link";
    case EPROTONOSUPPORT:
        return "Protocol not supported";
    case ECONNREFUSED:
        return "Connection refused";
    case ENOTCONN:
        return "Not connected";
    case ENOTSOCK:
        return "Not a socket";
    case EDEVREAD:
        return "Device read failed";
    case EDEVWRITE:
        return "Device write failed";
    case ENOTISOFS:
        return "Not ISO9660 file system";
    };
    return "UNKNOWN";
}
