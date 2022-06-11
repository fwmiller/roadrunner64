#if _DEBUG
#include <stdio.h>
#endif
#include <string.h>
#include <sys/isofs.h>

lba_t
isofs_search_dir(char *s, uint8_t *dir, int size, int *isdir) {
    directory_record_t rec;
    char *file_id;
    int len;

    len = strlen(s);
#if _DEBUG
    printf("isofs_search_dir: search for [%s] len %u\r\n", s, len);
#endif
    /* Loop over directory entries */
    for (int pos = 0; pos < size; pos += rec->dir_rec_len) {
        rec = (directory_record_t)(dir + pos);
        if (rec->dir_rec_len == 0)
            break;

        /* Check entry file id against path element */
        if (len != rec->file_id_len)
            continue;

        file_id = ((char *) rec) + sizeof(struct directory_record);
        if (strncmp(s, file_id, rec->file_id_len) == 0) {
#if _DEBUG
            printf("isofs_search_dir: found [%s] lba %u\r\n", s, rec->lba_le);
#endif
            if (rec->flags & FILE_FLAGS_DIRECTORY)
                *isdir = 1;
            else
                *isdir = 0;

            return rec->lba_le;
        }
    }
#if _DEBUG
    printf("isofs_search_dir: [%s] not found\r\n", s);
#endif
    return 0;
}
