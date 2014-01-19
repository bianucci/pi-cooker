void send_int_to_uart(int value);

int main(){
	int value;
	value = 210;
	send_int_to_uart(value);
	return 0;
}

void send_int_to_uart(int value){
	char value_char[10];
	int length = transform_to_char_array(value_char, value);
	int index;
	for (index = length - 1; index >= 0; index--)
	{
//		bcm2835_uart_send(value_char[index]);
		printf("%c\n", value_char[index]);
	}
//	bcm2835_uart_send(CHAR_SPACE);
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

int shift(char* int_as_char, int length){
    int i;
    for(i = 0;i < length;i++){
		int_as_char[i] = int_as_char[i] + 48;
	}
	return 0;
}