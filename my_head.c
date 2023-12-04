#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 1024
#define LF 10

int main(){
        int fd, num, num_linies, num_intros=0;
        char buf[SIZE];

        printf("Introdueix el nom del arxiu: ");
        scanf("%s", buf);
        printf("Introdueix quantes linies vols mostrar: ");
        scanf("%d", &num_linies);
        printf("\n");

        if((fd = open(buf, O_RDONLY)) == -1){
                perror("ERROR: L'arxiu introduït no existeix");
                exit(1);
        }

        if(num_linies <= 0){
                perror("ERROR: El número de línies a mostrar a de ser més gran que zero \n");
                exit(1);
        }

        while((num=read(fd,buf, SIZE-1)) != 0){
                for( int i = 0; i < num; i++){
                        if(buf[i] == LF){
                                num_intros++;
                        }
                        if(num_intros == num_linies){
                                buf[i] = '\0';
                                break;
                        }
                }

                buf[num] = '\0';
                printf("%s", buf);
                if(num_intros == num_linies) break;
        }

        printf("\n");
        close(fd);
        return 0;
}
