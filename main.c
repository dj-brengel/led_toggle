#include<stdint.h>

//Peripheral address
#define PERIPH_BASE 		0x40000000UL

//AHB1PERIPHERAL bus address
#define AHB1PERIPH_OFFSET	0x00020000UL
#define AHB1PERIPH_BASE 	PERIPH_BASE + AHB1PERIPH_OFFSET

//GPIOA address
#define GPIOA_OFFSET		0x00000000UL
#define GPIOA_BASE			AHB1PERIPH_BASE + GPIOA_OFFSET

//GPIOA peripheral registers (mode register used to configure
//as an output pin, output data register used to store data
//written to pin)
#define GPIOX_MODER_OFFSET 	0x00000000UL


#define GPIOX_ODR_OFFSET 	0x00000014UL


//RCC address
#define RCC_OFFSET 			0x00003800UL
#define RCC_BASE 			AHB1PERIPH_BASE + RCC_OFFSET

//RCC peripheral registers
#define RCC_AHB1ENR_OFFSET	0x00000030UL


//RCC bits
#define GPIOAEN 			(1U<<0)

//Output bits
#define PIN5				(1U<<5)
#define LED_PIN 			(PIN5)


typedef struct
{
	volatile uint32_t MODER;
	volatile uint32_t DUMMY[4];
	volatile uint32_t ODR;
}GPIO_TypeDef;

typedef struct
{
	volatile uint32_t DUMMY[12];
	volatile uint32_t AHB1ENR;
}RCC_TypeDef;

#define RCC 		((RCC_TypeDef*) RCC_BASE)
#define GPIOA		((GPIO_TypeDef*) GPIOA_BASE)




int main(void)
{
	//1. Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;


	//2. Set PA5 as output pin
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~(1U<<11);



	while(1)
	{
		//3. Toggle PA5 high
		GPIOA->ODR ^= LED_PIN;
		for(int i=0;i<1000000;i++) {}

	}

}







