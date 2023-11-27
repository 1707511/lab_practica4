#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define SIZE 1024
#define LF 10

int main(){
	int fd;
	int n, numlin, numintros=0;
	char buff[SIZE];

	printf("Introdueix el nom del arxiu: \n");
	scanf("%s", buff);
	printf("Introdueix quantes linies vols mostrar: \n");
	scanf("%d", &numlin);
	printf("\n");

	if((fd = open(buff, O_RDONLY)) == -1){
		printf("ERROR: L'arxiu introduït no existeix");
		exit(1);
	}

	if(numlin <= 0){
		printf("ERROR: El numero de linies a mostrar a de ser mes gran que zero \n");
		exit(1);
	}

	while((n=read(fd,buff, SIZE-1)) != 0){
		for( int i=0; i<n; i++){
			if(buff[i] == LF) numintros++;
			if(numintros == numlin){
				buff[i] = '\0';
				break;
			}
		}
		buff[n] = '\0';
		printf("%s", buff);
		if(numintros == numlin) break;
	}
	return 0;
}
