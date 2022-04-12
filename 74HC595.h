// Определяем порты вывода для регистра
#define F74HC595_PORT_RESET	PORTB	// Порт на который подключается RESET
#define F74HC595_PORT_CLK	PORTB	// Порт на который подключается CLK
#define F74HC595_PORT_SHIFT	PORTB	// Порт на который подключается SHIFT
#define F74HC595_PORT_DATA	PORTB	// Порт на который подключается DATA

#define F74HC595_DDR_RESET	DDRB	// Порт на который подключается RESET
#define F74HC595_DDR_CLK	DDRB	// Порт на который подключается CLK
#define F74HC595_DDR_SHIFT	DDRB	// Порт на который подключается SHIFT
#define F74HC595_DDR_DATA	DDRB	// Порт на который подключается DATA

#define F74HC595_RESET		3		// Разряд сброса регистра
#define F74HC595_CLK		0		// Разряд стробирования
#define F74HC595_SHIFT		1		// Разряд защелки
#define F74HC595_DATA		2		// Разряд данных

int Data[];							// Данные передаваемые с микроконтроллера на семисегментный индикатор		
unsigned char Segments[];			// Количество сегментов

// Инициализация регистра
void F74HC595_Init(void) {
	F74HC595_DDR_RESET |= (1 << F74HC595_RESET);
	F74HC595_DDR_CLK |= (1 << F74HC595_CLK);
	F74HC595_DDR_SHIFT |= (1 << F74HC595_SHIFT);
	F74HC595_DDR_DATA |= (1 << F74HC595_DATA); 
	F74HC595_PORT_CLK &= ~(1 << F74HC595_CLK);
	F74HC595_PORT_SHIFT &= ~(1 << F74HC595_SHIFT);
	F74HC595_PORT_RESET |= (1 << F74HC595_RESET);
}		  

// Функция сброса регистра
void F74HC595_Reset(void) {
	F74HC595_PORT_RESET &= ~(1 << F74HC595_RESET);
	F74HC595_PORT_SHIFT |= (1 << F74HC595_SHIFT);
	F74HC595_PORT_SHIFT &= ~(1 << F74HC595_SHIFT);
	F74HC595_PORT_RESET |= (1 << F74HC595_RESET);
}

// Функция обработки данных передаваемых через микромонтроллер 
void Indication(unsigned char *data_, int segments_) { 
	for (int i = 0; i < segments_; i++) {
	    for (int j = 0; j <= 7; j++) {
		    F74HC595_PORT_SHIFT &= ~(1 << F74HC595_SHIFT);
		    if (bit_is_set(data_[i], 7)) {
		        F74HC595_PORT_CLK |= (1 << F74HC595_CLK);
	        }
	        else F74HC595_PORT_CLK &= ~(1 << F74HC595_CLK);
		    data_[i] = data_[i] << 1;
		    F74HC595_PORT_SHIFT |= (1 << F74HC595_SHIFT);
	    }    
	}
	F74HC595_PORT_DATA &= ~(1 << 2);
	F74HC595_PORT_DATA |= (1 << 2);	
}