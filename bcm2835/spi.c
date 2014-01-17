#include "bcm2835.h"

int transform_to_char_array(char *int_as_char, int i);
int shift(char* int_as_char, int length);

int notmain(void)
{
	uint32_t data = 0;
    uint32_t data1 = 0;
    uint32_t data2 = 0;
	uint32_t space = '-';


	char message[10];
	int length;

	bcm2835_uart_begin();
    	
	while(1){

		bcm2835_spi_begin();
		bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
		bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
		bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_64);    // ~ 4 MHz
		bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default
		bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default

		char mosi[10] = { 0x60, 0x00 };
		char miso[10] = { 0 };

		bcm2835_spi_transfernb(mosi, miso, 2);
		
		data = miso[1] + ((miso[0] & 3) << 8);
	
		length = transform_to_char_array(message, data);

		int i;
		for(i=length-1;i>=0;i--){
			bcm2835_uart_send(message[i]);
            }

        bcm2835_uart_send(space);
        
		bcm2835_spi_end();

		bcm2835_delayMicroseconds(1000000);
	}
	return 0;
}

int shift(char* int_as_char, int length){
    int i;
    for(i = 0;i < length;i++){
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