#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

struct signal_info {
    int num;
    const char *name;
    const char *desc;
};

static const struct signal_info signals[] = {
    {1, "SIGHUP", "Hangup"},
    {2, "SIGINT", "Interrupt"},
    {3, "SIGQUIT", "Quit"},
    {4, "SIGILL", "Illegal instruction"},
    {5, "SIGTRAP", "Trace/breakpoint trap"},
    {6, "SIGABRT", "Aborted"},
    {7, "SIGBUS", "Bus error"},
    {8, "SIGFPE", "Floating point exception"},
    {9, "SIGKILL", "Killed"},
    {10, "SIGUSR1", "User defined signal 1"},
    {11, "SIGSEGV", "Segmentation fault"},
    {12, "SIGUSR2", "User defined signal 2"},
    {13, "SIGPIPE", "Broken pipe"},
    {14, "SIGALRM", "Alarm clock"},
    {15, "SIGTERM", "Terminated"},
    {16, "SIGSTKFLT", "Stack fault"},
    {17, "SIGCHLD", "Child exited"},
    {18, "SIGCONT", "Continued"},
    {19, "SIGSTOP", "Stopped (signal)"},
    {20, "SIGTSTP", "Stopped"},
    {21, "SIGTTIN", "Stopped (tty input)"},
    {22, "SIGTTOU", "Stopped (tty output)"},
    {23, "SIGURG", "Urgent I/O condition"},
    {24, "SIGXCPU", "CPU time limit exceeded"},
    {25, "SIGXFSZ", "File size limit exceeded"},
    {26, "SIGVTALRM", "Virtual timer expired"},
    {27, "SIGPROF", "Profiling timer expired"},
    {28, "SIGWINCH", "Window changed"},
    {29, "SIGIO", "I/O possible"},
    {30, "SIGPWR", "Power failure"},
    {31, "SIGSYS", "Bad system call"},
    {0, NULL, NULL}  
};

void program_usage(const char *program) {
    printf("Usage: %s [options] <pid>\n", program);
    printf("Options:\n");
    printf("-s <signal> Sends <signal> to <pid>\n");
    printf("-l Lists all signal numbers with their names\n");
}

void list_signals(void) {
    for (int i = 0; signals[i].name != NULL; i++) {
        printf("%d) %s %s\n", 
               signals[i].num, 
               signals[i].name, 
               signals[i].desc);
    }
}

int main(int argc, char *argv[]) {
    int sig_num = SIGTERM;  
    pid_t pid;
    int opt;
    
    if (argc < 2) {
        program_usage(argv[0]);   
        return 1;
    }

    while ((opt = getopt(argc, argv, "ls:")) != -1) {
        switch (opt) {
            case 'l':
                list_signals();
                return 0;
            case 's':
                sig_num = atoi(optarg);
                break;
            default:
                program_usage(argv[0]);
                return 1;
        }
    }

    if (optind >= argc) {
        program_usage(argv[0]);
        return 1;
    }
    pid = atoi(argv[optind]);

    if (kill(pid, sig_num) == -1) {
        if (sig_num == 0) {
            if (errno == ESRCH) {
                printf("PID %d does not exist\n", pid);
            } else if (errno == EPERM) {
                printf("PID %d exists, but we can't send it signals\n", pid);
            }
        } else {
            perror("kill");
        }
        return 1;
    } else if (sig_num == 0) {
        printf("PID %d exists and is able to receive signals\n", pid);
    }

    return 0;
}
