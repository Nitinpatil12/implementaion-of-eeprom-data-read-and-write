#define F_CPU 4000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>

#include "EEPROM_AVR128DA64.h"
#include "UART_1_AVR128DA64.h"

#define eeprom_erase_write		0x13
#define mode_address			0x00
#define DATA_address            0x06

uint16_t   mode_address1=0, DATA_address1=0;
typedef uint16_t eeprom_addr_t;

void main()
{
	sei();
	USART1_init(9600);

	set_NVM_command_SPM(eeprom_erase_write);
	write_data_in_eeprom_SPM(DATA_address, 20);
	write_data_in_eeprom_SPM(mode_address, 30);
	DATA_address1 = read_data_in_eeprom_SPM(DATA_address);
	mode_address1 = read_data_in_eeprom_SPM(mode_address);
	
	while(1)
	{
		USART1_sendString("mode_address");
		USART1_sendInt(mode_address1);
		USART1_sendString("DATA_address ");
		USART1_sendInt(DATA_address1);
		_delay_ms(1000);
	}
}