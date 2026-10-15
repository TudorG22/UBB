#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

int main() {
    int s, c, l, i;
    struct sockaddr_in server, client;

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        printf("Eroare la crearea socketului server\n");
        return 1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
        printf("Eroare la bind\n");
        return 1;
    }

    listen(s, 5);
    l = sizeof(client);
    memset(&client, 0, sizeof(client));

    while (1) {
        uint16_t n, x, suma = 0;

        c = accept(s, (struct sockaddr *) &client, (socklen_t *) &l);
        printf("S-a conectat un client.\n");

        recv(c, &n, sizeof(n), MSG_WAITALL);
        n = ntohs(n);
        for (i = 0; i < n; i++) {
            recv(c, &x, sizeof(x), MSG_WAITALL);
            suma = suma + ntohs(x);
        }

        suma = htons(suma);
        send(c, &suma, sizeof(suma), 0);
        close(c);
    }
}
