#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main() {
    int c;
    struct sockaddr_in server;
    char sir[1024];
    int n, total, p;

    c = socket(AF_INET, SOCK_STREAM, 0); // socket tcp cu adrese ipv4
    if (c < 0) {
        printf("Eroare la crearea socketului client\n");
        return 1;
    }

    memset(&server, 0, sizeof(server)); // golim structura inainte sa punem adresa
    server.sin_port = htons(1234); // htons pune portul in formatul folosit in retea
    server.sin_family = AF_INET; // folosim ipv4
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // adresa lui s1, aici pe acelasi calculator

    if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) { // ne conectam la s1
        printf("Eroare la conectarea la server\n");
        return 1;
    }

    if (fgets(sir, sizeof(sir), stdin) == NULL) {
        close(c);
        return 1;
    }
    sir[strcspn(sir, "\n")] = 0;

    total = strlen(sir);
    p = 0;
    while (p < total) {
        n = send(c, sir + p, total - p, MSG_NOSIGNAL); // trimitem ce a ramas; send poate trimite doar o parte
        if (n <= 0) {
            printf("Eroare la trimitere\n");
            close(c);
            return 1;
        }
        p += n;
    }
    shutdown(c, SHUT_WR); // nu mai trimitem, dar inca putem primi raspunsul

    while ((n = recv(c, sir, sizeof(sir) - 1, 0)) > 0) { // primim pe bucati; 0 inseamna ca s1 a terminat de trimis
        sir[n] = 0;
        printf("%s", sir);
    }
    if (n < 0) {
        printf("Eroare la primire\n");
    }
    printf("\n");
    close(c);
}
