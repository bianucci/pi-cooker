#include <stdio.h> 

int main(){

	char message[10];

	int i = 10023;

	int length = transform_to_char_array(message, i);

	for (int i = length -1 ; i >= 0; i--)
	{
		printf("%c", message[i]);		
	}

	printf("Length: %d\n", length);	

}

int shift(char* int_as_char, int length){
	for(int i = 0;i < length;i++){		
		int_as_char[i] = int_as_char[i] + 48;
	}	
	return 0;
}

int transform_to_char_array(char *int_as_char, int i){

	int mod_result = -1;
	int counter = 0;
	do {
		mod_result = i%10;
		int_as_char[counter] = mod_result;
		i = i / 10;
		counter++;
	}while(i!=0);
	shift(int_as_char, counter);
	return counter;	
}