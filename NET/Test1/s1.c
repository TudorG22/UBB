#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <stdlib.h>
#include <netdb.h>
#include <signal.h>

int trimite(int s, char *buf, int n) {
    int p = 0, k;
    while (p < n) {
        k = send(s, buf + p, n - p, MSG_NOSIGNAL); // buf+p sare peste ce am trimis, n-p e cat a ramas
        if (k <= 0) {
            return -1;
        }
        p += k;
    }
    return 0;
}

void transfera(int a, int b) { // a e legatura cu clientul, b e legatura cu serverul tinta
    char buf[4096];
    fd_set citire; // lista de socketuri pe care le urmarim
    int n, max = a > b ? a : b;
    int a_deschis = 1, b_deschis = 1; // tinem minte de unde mai putem primi date

    while (a_deschis || b_deschis) {
        FD_ZERO(&citire); // refacem lista inainte de fiecare select
        if (a_deschis) {
            FD_SET(a, &citire); // urmarim clientul
        }
        if (b_deschis) {
            FD_SET(b, &citire); // urmarim serverul tinta
        }
        if (select(max + 1, &citire, NULL, NULL, NULL) < 0) { // asteptam date sau inchidere; select cere cel mai mare socket + 1
            return;
        }
        if (a_deschis && FD_ISSET(a, &citire)) { // putem citi de la client fara sa asteptam
            n = recv(a, buf, sizeof(buf), 0);
            if (n < 0) {
                return;
            }
            if (n == 0) { // clientul nu mai trimite date
                shutdown(b, SHUT_WR); // anuntam si serverul tinta ca am terminat de trimis
                a_deschis = 0;
            } else if (trimite(b, buf, n) < 0) { // dam mai departe ce a trimis clientul
                return;
            }
        }
        if (b_deschis && FD_ISSET(b, &citire)) { // putem citi de la serverul tinta fara sa asteptam
            n = recv(b, buf, sizeof(buf), 0);
            if (n < 0) {
                return;
            }
            if (n == 0) { // serverul tinta nu mai trimite date
                shutdown(a, SHUT_WR); // anuntam clientul ca raspunsul s-a terminat
                b_deschis = 0;
            } else if (trimite(a, buf, n) < 0) { // dam raspunsul inapoi clientului
                return;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int s;
    struct sockaddr_in server, client;
    int c, l;
    int d;
    struct hostent *h;

    if (argc != 3) {
        printf("Utilizare: %s SERVER PORT\n", argv[0]);
        return 1;
    }

    s = socket(AF_INET, SOCK_STREAM, 0); // socket tcp pe care asteptam clientii
    if (s < 0) {
        printf("Eroare la crearea socketului server\n");
        return 1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1234); // portul lui s1, pus in formatul folosit in retea
    server.sin_family = AF_INET; // folosim ipv4
    server.sin_addr.s_addr = INADDR_ANY; // ascultam pe toate adresele acestui calculator

    if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) { // legam socketul de portul 1234
        printf("Eroare la bind\n");
        return 1;
    }

    listen(s, 5); // pornim ascultarea; 5 e marimea ceruta pentru coada de conexiuni in asteptare
    l = sizeof(client);
    memset(&client, 0, sizeof(client));
    signal(SIGCHLD, SIG_IGN); // sistemul curata copiii terminati, ca sa nu ramana zombie

    while (1) {
        c = accept(s, (struct sockaddr *) &client, (socklen_t *) &l); // c e noul socket pentru client; s ramane pentru ascultare
        if (c < 0) {
            continue;
        }
        printf("S-a conectat un client.\n");
        fflush(stdout);

        if (fork() == 0) { // doar copilul intra aici; parintele poate primi alti clienti
            close(s);
            d = socket(AF_INET, SOCK_STREAM, 0); // s1 devine client pentru serverul tinta
            if (d < 0) {
                printf("Eroare la crearea socketului client\n");
                close(c);
                return 1;
            }

            memset(&server, 0, sizeof(server));
            server.sin_port = htons(atoi(argv[2])); // al doilea argument e portul tintei
            server.sin_family = AF_INET;
            h = gethostbyname(argv[1]); // primul argument e adresa sau numele serverului tinta
            if (h == NULL) {
                printf("Eroare la gasirea adresei serverului\n");
                close(c);
                close(d);
                return 1;
            }
            memcpy(&server.sin_addr, h->h_addr_list[0], h->h_length); // punem primul ip gasit in adresa de conectare

            if (connect(d, (struct sockaddr *) &server, sizeof(server)) < 0) { // o conexiune separata la tinta pentru fiecare client
                printf("Eroare la conectarea la server\n");
                close(c);
                close(d);
                return 1;
            }
            printf("S1 s-a conectat la %s:%s.\n", argv[1], argv[2]);
            fflush(stdout);
            transfera(c, d);
            close(c);
            close(d);
            exit(0);
        }
        close(c);
    }
}
