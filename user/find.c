#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void find(char *root, char *pattern) {
    int fd;
    if ((fd = open(root, 0)) < 0) {
        fprintf(2, "find: cannot open %s\n", root);
        return;
    }

    struct stat st;
    if (fstat(fd, &st) < 0) {
        fprintf(2, "find: cannot stat %s\n", root);
        close(fd);
        return;
    }

    struct dirent de;
    if (st.type == T_DIR) {
        char buf[512];
        int root_len = strlen(root);
        if (root_len + 1 < sizeof buf) {
            strcpy(buf, root);
            char *p = buf + root_len;
            *p++ = '/';
            while (read(fd, &de, sizeof de)) {

                if (de.inum == 0) continue;

                if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0) continue;

                if (strcmp(pattern, de.name) == 0) {
                    printf("%s/%s\n", root, pattern);
                }
                int name_len = strlen(de.name);
                if (sizeof buf - (p - buf) <= name_len) {
                    printf("find: path too long");
                    continue;
                }
                strcpy(p, de.name);
                find(buf, pattern);
            }
        }
    }
    close(fd);
}

int main(int argc, char *argv[])
{
    if (argc < 3) {
        fprintf(2, "usage: %s path pattern\n", argv[0]);
        exit(1);
    }

    char *root = argv[1];
    char *pattern = argv[2];

    find(root, pattern);

    exit(0);
}
