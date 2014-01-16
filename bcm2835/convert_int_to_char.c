#include <stdio.h> 

int main(){
	int i = 433;
	
	char int_as_char[10];

	printf("Length is %d\n", transform_to_char_array(int_as_char, i));

	printf("%s\n", int_as_char);
}

int shift_wtf(char* int_as_char, int length){
	for(int i = 0;i < length;i++){		
		int_as_char[i] = int_as_char[i] + 48;
	}	
	return 0;
}

int transform_to_char_array(char *int_as_char, int i){
	int mod_result = -1;
	int counter = 0;
	while (mod_result != 0){
		mod_result = i%10;
		if (mod_result!=0){
			int_as_char[counter] = mod_result;
			i = i / 10;
			counter++;
		}		 
	}
	shift_wtf(int_as_char, counter);
	return counter;	
}