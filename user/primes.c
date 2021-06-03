#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main()
{
    int p[2];
    pipe(p);

    int buf[1];
    for (int i = 2; i < 35; ++i) {
        buf[0] = i;
        write(p[1], buf, 1);
    }

    int input = p[0];
    int output = p[1];
    int n;

start:
    close(output);
    output = 0;
    n = 0;
    while (read(input, buf, 1) > 0) {
        if (n == 0) {
            n = buf[0];
            printf("prime %d\n", n);

            int p[2];
            pipe(p);
            output = p[1];
            if (fork() == 0) {
                input = p[0];
                goto start;
            }
        } else if (buf[0] % n != 0) {
            write(output, buf, 1);
        }
    }
    close(input);
    if (output) close(output);
    wait(0);

    exit(0);
}
