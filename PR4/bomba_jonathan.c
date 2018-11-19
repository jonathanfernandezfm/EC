//gcc -Og bomba_jonathan.c -o bomba_jonathan -no-pie -fno-guess-branch-probability

#include <stdio.h>	// para printf(), fgets(), scanf()
#include <stdlib.h>	// para exit()
#include <string.h>	// para strncmp()
#include <sys/time.h>	// para gettimeofday(), struct timeval
#include <unistd.h>

#define SIZE 100
#define TLIM 5

int token=2;

void boom(void){
	printf(	"\n"
		"***************\n"
		"*** \033[31mBOOM!!! \033[37m***\n"
		"***************\n"
		"\n");
	exit(-1);
}

void defused(void){
	printf(	"\n"
		"·························\n"
		"··· \033[32mbomba desactivada \033[37m···\n"
		"·························\n"
		"\n");
	exit(0);
}

void encrypt(char pass[], int key){
	for(int i=0; i < strlen(pass); i++){
		pass[i] -= key;
	}
}

int main(){
	char pw[SIZE];
	int  pc, n, i=10;
	char password[]="ryvk\n";
	int  passcode  = 289322;

	struct timeval tv1,tv2;	// gettimeofday() secs-usecs
	gettimeofday(&tv1,NULL);

	do	printf("\nIntroduce la contraseña: ");
	while (	fgets(pw, SIZE, stdin) == NULL );
	password[1]-=63;
	pw[1]-=63;
	encrypt(password, 10);
	encrypt(pw, 10);

	if    (	strncmp(pw,password,sizeof(password)) )
	    boom();

	gettimeofday(&tv2,NULL);
	if    ( tv2.tv_sec - tv1.tv_sec > TLIM )
	    boom();

	do  {	printf("\nIntroduce el pin: ");
	 if ((n=scanf("%i",&pc))==0)
		scanf("%*s")    ==1;         }
	while (	n!=1 );

	if    (	pc-token != passcode+token )
	    boom();

	gettimeofday(&tv1,NULL);
	if    ( tv1.tv_sec - tv2.tv_sec > TLIM )
	    boom();

	defused();
}
