#include <stdlib.h>
#include <sys/pci.h>

pci_func_t
pci_lookup(uint8_t devclass, uint8_t subclass) {
    for (int i = 0; i < pcifuncs; i++) {
        pci_func_t f = &(pcitab[i]);
        if (devclass == f->devclass && subclass == f->subclass)
            return f;
    }
    return NULL;
}
