#include "custom.h"
#include "bcm2835.h"

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

int read_temp(void){
	bcm2835_spi_begin();
	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_64);    // ~ 4 MHz
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default
	bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default

	char mosi[10] = { 0x60, 0x00 };
	char miso[10] = { 0 };

	bcm2835_spi_transfernb(mosi, miso, 2);
	bcm2835_spi_end();
			
	return (miso[1] + ((miso[0] & 3) << 8));
}

void uart_send_string(char *string){
	int i = 0;
	while (string[i]!=0){
		bcm2835_uart_send(string[i]);
		i++;
	}
}
