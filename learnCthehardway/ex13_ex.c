#include <stdio.h>

int main(int argc, char *argv[])
{
    //if(argc != 2) {
    //    printf("ERROR: You need one argument.\n");
        // this is how you abort a program
     //   return 1;
    //}
	char letter;
	int i = 0;
    for(int j = 1;j < argc ; j++){
	for(i = 0,letter = argv[j][0]; argv[j][i] != '\0'; i++) {
        letter = argv[j][i];
		printf("%c\n",letter);
		if(letter >='A' && letter<='Z') letter+='a'-'A';
		argv[j][i]=letter;    
		}
	printf("%s\n",argv[j]);
		
    }
    return 0;
}
