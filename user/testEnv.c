#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"
#include "kernel/syscall.h"
#include "kernel/memlayout.h"
#include "kernel/riscv.h"

int loop_size = 10000;
int large_interval = 1000;
int large_size = 1000;
int freq_interval = 100;
int freq_size = 100;

void env(int size, int interval, char *env_name)
{
    int result = 1;
    for (int i = 0; i < loop_size; i++)
    {
        if (i % interval == 0)
        {
            result = result * size;
        }
    }
}

void env_large()
{
    env(large_size, large_interval, "env_large");
}

void env_freq()
{
    env(freq_size, freq_interval, "env_freq");
}

int main(int argc, char *argv[])
{
    int n_forks = 5;
    int pid = getpid();
    for (int i = 0; i < n_forks; i++)
    {
        fork();
    }
    int n_experiments = 10;
    for (int i = 0; i < n_experiments; i++)
    {
        env_large(10, 3, 100);
        if (pid == getpid())
        {
            printf("experiment %d\n", i);
            printf("env large\n");
            print_stats();
        }
        sleep(10);
        env_freq(10, 100);
        if (pid == getpid())
        {
            printf("\nenv freq\n");
            print_stats();
        }
    }
    exit(0);
}

// #include "kernel/param.h"
// #include "kernel/types.h"
// #include "kernel/stat.h"
// #include "user/user.h"
// #include "kernel/fs.h"
// #include "kernel/fcntl.h"
// #include "kernel/syscall.h"
// #include "kernel/memlayout.h"
// #include "kernel/riscv.h"

// int loop_size = 10000;
// int large_interval = 1000;
// int large_size = 1000;
// int freq_interval = 100;
// int freq_size = 100;

// void env(int size, int interval, char* env_name) {
//     int result = 1;
//     int n_forks = 2;
//     int pid;
//     for (int i = 0; i < n_forks; i++) {
//         pid = fork();
//     }
//     for (int i = 0; i < loop_size; i++) {
//         if (i % (loop_size / 10) == 0) {
//         	if (pid == 0) {
//         		printf("%s %d/%d completed.\n", env_name, i, loop_size);
//         	} else {
//                 printf(" ");
//             }
//         }
//         if (i % interval == 0) {
//             result = result * size;
//         }
//     }
//     printf("\n");
// }

// void env_large() {
//     env(large_size, large_interval, "env_large");
// }

// void env_freq() {
//     env(freq_size, freq_interval, "env_freq");
// }

// int
// main(int argc, char *argv[])
// {
//     env_freq();
//     print_stats();   
//     exit(0);
// }