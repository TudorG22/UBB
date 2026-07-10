#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){

    int p1[2], p2[2];
    pipe(p1);
    pipe(p2);

    int f = fork();

    //parinte:
    if (f != 0){
        char stream[100];
        close(p1[0]);
        close(p2[1]);
        fgets(stream, sizeof(stream), stdin);
        write(p1[1], stream, 100 * sizeof(char));
        close(p1[1]);
        wait(NULL);
        int rez;
        read(p2[0], &rez, sizeof(int));
        close(p2[0]);
        printf("result: %d\n", rez);
    }

    //copil:
    if (f == 0){
        char stream[100];
        close(p1[1]);
        close(p2[0]);
        read(p1[0], stream, 100 * sizeof(char));
        close(p1[0]);
        int result = 0;
        char* numStr = strtok(stream, " \n");
        int num = atoi(numStr);
        while (num != 0){
            result += num;
            numStr = strtok(NULL, " \n");
            num = atoi(numStr);
        }
        write(p2[1], &result, sizeof(int));
        close(p2[1]);
    }

    return 0;
}
