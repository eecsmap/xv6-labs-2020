#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

void xargs(char *args[]) {
    if (fork() == 0) {
        exec(args[0], args);
    } else {
        wait(0);
    }
}

char buf[512];

char *next_argument() {
    int n;
    char c;
    int inword = 1;
    char *end = buf;

    while (1) {
        n = read(0, &c, 1);
        if (n <= 0 || c == '\n') { // || c == '\n' || c == '\t') {
            if (n <= 0) return 0;
            if (inword) {
                inword = 0;
                if (end >= buf + sizeof buf) return 0;
                if (end != buf) {
                    *end = '\0';
                    return buf;
                }
            }
        } else {
            if (!inword) inword = 1;
            if (end >= buf + sizeof buf) return 0;
            *end++ = c;
        }
    }
    return buf;
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(2, "usage: %s exe [args...]\n", argv[0]);
        exit(1);
    }

    char *new_args[MAXARG], **p = new_args;
    argv++; // skip xargs itself
    while (*argv) *p++ = *argv++;

    char **base = p;

    char *arg;
    while ((arg = next_argument())) {
        p = base;
        *p++ = arg;
        *p = 0;
        xargs(new_args);
    }
    exit(0);
}
