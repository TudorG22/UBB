#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int main() {
    int s;
    struct sockaddr_in server, client;
    int c, l;

    s = socket(AF_INET, SOCK_STREAM, 0); // socket tcp pe care asteptam conexiunile de la s1
    if (s < 0) {
        printf("Eroare la crearea socketului server\n");
        return 1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1235); // portul lui s2, pus in formatul folosit in retea
    server.sin_family = AF_INET; // folosim ipv4
    server.sin_addr.s_addr = INADDR_ANY; // ascultam pe toate adresele acestui calculator

    if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) { // legam socketul de portul 1235
        printf("Eroare la bind\n");
        return 1;
    }

    listen(s, 5); // pornim ascultarea; coada ceruta e de 5 conexiuni in asteptare
    l = sizeof(client);
    memset(&client, 0, sizeof(client));
    signal(SIGCHLD, SIG_IGN); // sistemul curata copiii terminati

    while (1) {
        char sir[4096];
        int n, total, i, p;
        char x;

        c = accept(s, (struct sockaddr *) &client, (socklen_t *) &l); // pentru s2, clientul este s1
        if (c < 0) {
            continue;
        }
        printf("S-a conectat un client.\n");
        fflush(stdout);

        if (fork() == 0) { // copilul se ocupa de aceasta conexiune, parintele asteapta altele
            close(s);
            total = 0;
            while (total < (int) sizeof(sir)) {
                n = recv(c, sir + total, sizeof(sir) - total, 0); // continuam dupa ce am primit deja, in spatiul ramas
                if (n < 0) {
                    close(c);
                    return 1;
                }
                if (n == 0) { // s1 a inchis trimiterea, deci avem tot sirul
                    break;
                }
                total += n;
            }
            for (i = 0; i < total / 2; i++) { // oglindim sirul
                x = sir[i];
                sir[i] = sir[total - i - 1];
                sir[total - i - 1] = x;
            }
            p = 0;
            while (p < total) {
                n = send(c, sir + p, total - p, MSG_NOSIGNAL); // trimitem tot raspunsul inapoi spre s1
                if (n <= 0) {
                    close(c);
                    return 1;
                }
                p += n;
            }
            close(c);
            exit(0);
        }
        close(c);
    }
}
