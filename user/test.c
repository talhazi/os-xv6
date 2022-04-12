#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"


int main(int argc, char** argv){
    pause_system(2);
    int pid = fork();
    if(pid!=0){ //parent
        int status;
        wait(&status);
        fprintf(2,"Child %d finished with exit status %d\n", pid, status);
    } else{ //child
        fprintf(2, "Child is running\n");
    }
    exit(0);
}