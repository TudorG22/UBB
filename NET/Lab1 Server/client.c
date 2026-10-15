#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main() {
    int c, i;
    struct sockaddr_in server;
    uint16_t n, x, suma, numar;

    c = socket(AF_INET, SOCK_STREAM, 0);
    if (c < 0) {
        printf("Eroare la crearea socketului client\n");
        return 1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
        printf("Eroare la conectarea la server\n");
        return 1;
    }

    printf("n = ");
    scanf("%hu", &n);
    numar = htons(n);
    send(c, &numar, sizeof(numar), 0);

    for (i = 0; i < n; i++) {
        printf("x = ");
        scanf("%hu", &x);
        x = htons(x);
        send(c, &x, sizeof(x), 0);
    }

    recv(c, &suma, sizeof(suma), MSG_WAITALL);
    printf("Suma este %hu\n", ntohs(suma));
    close(c);
}
