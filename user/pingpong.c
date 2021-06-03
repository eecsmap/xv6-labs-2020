#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main()
{
    int pipe_ping[2]; // from parent to child
    int pipe_pong[2]; // from child to parent

    pipe(pipe_ping);
    pipe(pipe_pong);

    char buf[1];

    if (fork() == 0) {
        // child
        int pid = getpid();
        if (read(pipe_ping[0], buf, 1) > 0)
            printf("%d: received ping\n", pid);
        write(pipe_pong[1], buf, 1);
    } else {
        // parent
        int pid = getpid();
        write(pipe_ping[1], "c", 1);
        if (read(pipe_pong[0], buf, 1) > 0)
            printf("%d: received pong\n", pid);
    }

    exit(0);
}
