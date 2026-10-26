#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_TEXT 256

int trimiteNumar(int c, uint16_t numar) {
    numar = htons(numar);
    return send(c, &numar, sizeof(numar), 0) > 0;
}

int primesteNumar(int c, uint16_t *numar) {
    if (recv(c, numar, sizeof(*numar), MSG_WAITALL) <= 0)
        return 0;
    *numar = ntohs(*numar);
    return 1;
}
int trimiteCod(int c, uint8_t cod) {
    return send(c, &cod, sizeof(cod), 0) > 0;
}

int primesteCod(int c, uint8_t *cod) {
    return recv(c, cod, sizeof(*cod), MSG_WAITALL) > 0;
}


int trimiteText(int c, char text[]) {
    uint16_t lungime = strlen(text);

    if (!trimiteNumar(c, lungime))
        return 0;
    return send(c, text, lungime, 0) > 0;
}

int primesteText(int c, char text[]) {
    uint16_t lungime;

    if (!primesteNumar(c, &lungime))
        return 0;
    if (lungime >= MAX_TEXT)
        return 0;
    if (recv(c, text, lungime, MSG_WAITALL) <= 0)
        return 0;
    text[lungime] = '\0';
    return 1;
}

int main(int argc, char *argv[]) {
    int c;
    struct sockaddr_in server;
    uint8_t raspuns;
    char username[MAX_TEXT], destinatar[MAX_TEXT], mesaj[MAX_TEXT];
    fd_set multime;

    if (argc != 3) {
        printf("Utilizare: %s IP PORT\n", argv[0]);
        return 1;
    }

    c = socket(AF_INET, SOCK_STREAM, 0);
    if (c < 0) {
        printf("Eroare la crearea socketului client\n");
        return 1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_port = htons(atoi(argv[2]));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(argv[1]);

    if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
        printf("Eroare la conectarea la server\n");
        close(c);
        return 1;
    }

    do {
        printf("Username = ");
        fflush(stdout);
        fgets(username, MAX_TEXT, stdin);
        username[strcspn(username, "\n")] = '\0';

        trimiteCod(c, 0);
        trimiteText(c, username);

        if (!primesteCod(c, &raspuns)) {
            printf("Serverul s-a deconectat\n");
            close(c);
            return 1;
        }

        if (raspuns == 5)
            printf("Username deja folosit\n");
        if (raspuns == 6)
            printf("Username-ul nu poate fi gol\n");
    } while (raspuns != 4);

    printf("Conectat la chat\n");
    printf("Mesaj public: mesaj\n");
    printf("Mesaj privat: /private username mesaj\n");
    printf("Iesire: /exit\n> ");
    fflush(stdout);

    while (1) {
        FD_ZERO(&multime);
        FD_SET(STDIN_FILENO, &multime);
        FD_SET(c, &multime);

        if (select(c + 1, &multime, NULL, NULL, NULL) < 0) {
            printf("Eroare la select\n");
            break;
        }

        if (FD_ISSET(c, &multime)) {
            if (!primesteCod(c, &raspuns)) {
                printf("\nServerul s-a deconectat\n");
                break;
            }

            if (raspuns == 1) {
                primesteText(c, username);
                primesteText(c, mesaj);
                printf("\n%s: %s\n", username, mesaj);
            } else if (raspuns == 2) {
                primesteText(c, username);
                primesteText(c, mesaj);
                printf("\n[privat] %s: %s\n", username, mesaj);
            } else if (raspuns == 3) {
                primesteText(c, username);
                printf("\n%s has left the chat\n", username);
            } else if (raspuns == 7) {
                printf("\nUtilizatorul nu este in chat\n");
            }
            printf("> ");
            fflush(stdout);
        }

        if (FD_ISSET(STDIN_FILENO, &multime)) {
            if (fgets(mesaj, MAX_TEXT, stdin) == NULL) {
                trimiteCod(c, 3);
                break;
            }
            mesaj[strcspn(mesaj, "\n")] = '\0';

            if (strcmp(mesaj, "/exit") == 0) {
                trimiteCod(c, 3);
                break;
            }

            if (strncmp(mesaj, "/private ", 9) == 0) {
                char *continut = strchr(mesaj + 9, ' ');
                if (continut == NULL) {
                    printf("Format: /private username mesaj\n> ");
                    fflush(stdout);
                    continue;
                }

                *continut = '\0';
                strcpy(destinatar, mesaj + 9);
                continut++;

                trimiteCod(c, 2);
                trimiteText(c, destinatar);
                trimiteText(c, continut);
            } else if (strlen(mesaj) > 0) {
                trimiteCod(c, 1);
                trimiteText(c, mesaj);
            }

            printf("> ");
            fflush(stdout);
        }
    }

    close(c);
    return 0;
}
