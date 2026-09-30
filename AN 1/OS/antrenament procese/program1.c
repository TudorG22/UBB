#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){

    int n = 10;
    
    for (int i = 0; i<n; i++){
        printf("Parinte zice: pid parinte: %d\n", getpid());
        int f = fork();
        if (f != 0){
            printf("Parinte zice: pid copil: %d\n", f);
        }
        else{
            printf("Copil zice: pid copil: %d; pid parinte: %d\n", getpid(), getppid());
            exit(0);
        }
    }

    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

    return 0;
}