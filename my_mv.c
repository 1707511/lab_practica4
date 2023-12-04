#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 1024

int main() {
    char ini_arxiu[SIZE];
    char dest_arxiu[SIZE];
    char buf[SIZE];
    int ini_fd, dest_fd, num_read, num_written;


    printf("Introdueix el nom de l'arxiu a moure: ");
    scanf("%s", ini_arxiu);


    printf("Introdueix el nou nom de l'arxiu: ");
    scanf("%s", dest_arxiu);


    if ((ini_fd = open(ini_arxiu, O_RDONLY)) == -1) {
        perror("ERROR: L'arxiu a moure no existeix");
        exit(1);
    }


    if ((dest_fd = open(dest_arxiu, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU)) == -1) {
        perror("ERROR: No s'ha pogut crear l'arxiu de destinació");
        close(ini_fd);
        exit(1);
    }


    while ((num_read = read(ini_fd, buf, SIZE)) > 0) {
        if ((num_written = write(dest_fd, buf, num_read)) != num_read) {
            perror("ERROR: Error escrivint a l'arxiu de destinació");
            close(ini_fd);
            close(dest_fd);
            exit(1);
        }
    }


    close(ini_fd);
    close(dest_fd);


    if (unlink(ini_arxiu) == -1) {
        perror("ERROR: No s'ha pogut esborrar l'arxiu original");
        exit(1);
    }

    printf("L'arxiu s'ha mogut amb èxit.\n");

    return 0;

}
