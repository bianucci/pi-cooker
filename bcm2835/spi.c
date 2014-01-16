#include "bcm2835.h"

int notmain(void)
{
    	uint32_t data1 = 'c';
    	uint32_t data2 = 'c';
	uint32_t space = ' ';

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
		
		data1 = (0 | miso[0]);
		data2 = (0 | miso[1]);
		
		//data = miso[1] + ((miso[0] & 3) << 8);
	
		bcm2835_spi_end();
	
		bcm2835_uart_send(data1);
		bcm2835_uart_send(data2);
		bcm2835_uart_send(space);

		bcm2835_delayMicroseconds(1000000);
	}
	return 0;
}

