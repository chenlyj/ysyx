#include <stdio.h>

int main(int argc, char *argv[])
{
    // go through each string in argv

    int i = argc-1;
    while(i) {
        printf("arg %d: %s\n", i, argv[i]);
        i--;
    }

    // let's make our own array of strings
    char *states[] = {
        "California", "Oregon",
        "Washington", "Texas"
    };
    
    int num_states = 4;
    i = 0;  // watch for this
    while(i < num_states) {
        printf("state %d: %s\n", i, states[i]);
        i++;
    }
    
	i = 0;
	while(i < argc){
		states[i] = argv[i];
		i++;
	}
	i=0;
	while(i < num_states) {
        printf("state %d: %s\n", i, states[i]);
        i++;
    }
	argv[0] = "abcde";
	for(i = 0;i<num_states;i++){
		printf("%s\n",states[i]);
	}
    return 0;
}
