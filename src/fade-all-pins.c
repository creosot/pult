/*
 * fade-all-pins
 *
 * This example shows how to fade an LED on all PWM-capable pins
 * using the analogWrite() function. (Derived from 01.Basics/Fade)
 *
 * This example code is in the public domain.
 */
#include <Arduino.h>
#include <string.h>

uint8_t pre_cmd[] = { 0x23, 0x09, 0x23, 0x0D, 0x0A };
uint8_t menu_cmd[] = { 0x21, 0x09, 0x3F, 0x09, 0x4E, 0x0D, 0x0A };
uint8_t powr_on_after_install_door_open_cmd[] = { 0x21, 0x09, 0x3F, 0x09, 0x4C, 0x0D, 0x0A, 0x57, 0x0D, 0x0A };
uint8_t powr_on_after_install_door_close_cmd[] = { 0x21, 0x09, 0x3F, 0x09, 0x4C, 0x0D, 0x0A, 0x55, 0x0D, 0x0A };
uint8_t door_open_cmd[] = { 0x21, 0x09, 0x3F, 0x09, 0x4C, 0x0D, 0x0A, 0x57, 0x0D, 0x0A };
uint8_t Menu_plus_to_UpmotorMenu_cmd[] = { 0x3F, 0x09, 0x44, 0x09, 0x52, 0x0D, 0x0A };
uint8_t UpmotorMenu_enter_to_Upmotor_cmd[] = { 0x3F, 0x0D, 0x0A, 0x44, 0x0D, 0x0A };
uint8_t Upmotor_enter_to_UpmotorMenu_cmd[] = { 0x3F, 0x0D, 0x0A, 0x44, 0x0D, 0x0A, 0x52, 0x0D, 0x0A };
uint8_t Bottommotor_enter_to_BottommotorMenu_cmd[] = { 0x3F, 0x0D, 0x0A, 0x45, 0x0D, 0x0A, 0x52, 0x0D, 0x0A };
uint8_t BottommotorMenu_enter_to_Bottommotor_cmd[] = { 0x3F, 0x0D, 0x0A, 0x45, 0x0D, 0x0A };
uint8_t UpmotorMenu_plus_to_BottommotorMenu_cmd[] = { 0x3F, 0x09, 0x45, 0x09, 0x52, 0x0D, 0x0A };
uint8_t BottommotorMenu_plus_to_BothmotorsMenu_cmd[] = { 0x3F, 0x09, 0x4B, 0x09, 0x52, 0x0D, 0x0A };
uint8_t BothmotorsMenu_enter_to_Bothmotors_cmd[] = { 0x3F, 0x0D, 0x0A, 0x4B, 0x0D, 0x0A };
uint8_t Bothmotors_enter_to_BothmotorsMenu_cmd[] = { 0x3F, 0x0D, 0x0A, 0x4B, 0x0D, 0x0A, 0x52, 0x0D, 0x0A };
uint8_t Back_to_MainMenu_cmd[] = { 0x23, 0x09, 0x23, 0x0D, 0x0A, 0x21, 0x09, 0x3F, 0x09, 0x4E, 0x0D, 0x0A };
uint8_t BothmotorsMenu_plus_to_ScrethingMenu_cmd[] = { 0x3F, 0x09, 0x53, 0x09, 0x52, 0x0D, 0x0A };
uint8_t ScrethingMenu_plus_to_InstallMenu_cmd[] = { 0x3F, 0x09, 0x48, 0x09, 0x52, 0x0D, 0x0A };
uint8_t InstallMenu_plus_to_StoptimeMenu_cmd[] = { 0x3F, 0x09, 0x52, 0x09, 0x5A, 0x0D, 0x0A };
uint8_t Scrething_enter_cmd[] = { 0x3F, 0x09, 0x53, 0x09, 0x52, 0x0D, 0x0A };
uint8_t InstallMenu_enter_to_DoorOpen_SensorOff_cmd[] = { 0x3F, 0x09, 0x48, 0x0D, 0x0A, 0x21, 0x09, 0x3F, 0x09, 0x4C, 0x0D, 0x0A, 0x57, 0x0D, 0x0A };
uint8_t DoorOpen_enter_3sec_to_MainMenu_cmd[] = { 0x23, 0x09, 0x23, 0x0D, 0x0A, 0x21, 0x09, 0x3F, 0x09, 0x4E, 0x0D, 0x0A };
uint8_t DoorOpen_enter_s_on_to_scrolling_cmd[] = { 0x3F, 0x09, 0x48, 0x0D, 0x0A };
uint8_t InstallMenu_enter_to_Stopped_SensorOn_cmd[] = { 0x3F, 0x09, 0x48, 0x0D, 0x0A, 0x21, 0x09, 0x3F, 0x09, 0x4C, 0x0D, 0x0A, 0x55, 0x0D, 0x0A };
uint8_t InstallMode[] = { 0x21, 0x09, 0x3F, 0x09, 0x4C, 0x0D, 0x0A };
uint8_t DoorClose[] = { 0x55, 0x0D, 0x0A };
uint8_t DoorOpen[] = { 0x57, 0x0D, 0x0A };
uint8_t InstallMenu_enter_to[] = { 0x3F, 0x09, 0x48, 0x0D, 0x0A, 0x21, 0x09, 0x3F, 0x09, 0x4C, 0x0D, 0x0A };
uint8_t Enter_Return[] = { 0x21, 0x09, 0x3F, 0x09, 0x4C, 0x0D, 0x0A };

#define BUTTON_GPIO_PORT  (GPIOB)
#define BUTTON_GPIO_PINS  (GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1 | GPIO_PIN_0)
#define LED_GPIO_PORT  (GPIOC)
#define LED_GPIO_PINS  (GPIO_PIN_2 | GPIO_PIN_1)
#define OUT_GPIO_PORT  (GPIOD)
#define OUT_GPIO_PINS  (GPIO_PIN_7 | GPIO_PIN_4 | GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_0)
#define OUT_START_PIN (GPIO_PIN_0)
#define OUT_NUSE_PIN (GPIO_PIN_2)
#define OUT_PLUS_PIN (GPIO_PIN_3)
#define OUT_MINUS_PIN (GPIO_PIN_4)
#define OUT_ENTER_PIN (GPIO_PIN_7)
#define BUTTON_COUNT	4
#define DEBOUNCE_ms 50
#define GERKON_GPIO_PORT (GPIOC)
#define GERKON_PIN (GPIO_PIN_4)
#define LED_UP_PIN (GPIO_PIN_1)
#define LED_DOWN_PIN (GPIO_PIN_2)
#define BUT_MODE 0
#define BUT_MINUS 1
#define BUT_PLUS 2
#define BUT_ENTER 3
#define SIZE_BUFFER 100

typedef enum FLASH_MODE{
	FLASH_UP = 1,
	FLASH_DOWN,
	FLASH_BOTH,
	FLASH_NONE,
} Flash_mode;

typedef enum MODE{
	MODE_UP = 1,
	MODE_DOWN,
	MODE_BOTH,
	OVER,
} Mode;

typedef enum MENU{
	MENU_MENUE = 0,
	MENU_UP,
	MENU_DOWN,
	MENU_BOTH,
	MENU_STRETCHING,
	MENU_INSTALL
} Menu;

typedef struct CONTROL{
	Mode current_mode;
	Menu current_menu;
} Control;

//Control ctrl = {MODE_UP, MENU_MENUE};

static void CLK_Config(void);
static void GPIO_Config();
static void IWDG_Config();  //1.02s
static void EEPROM_Config();
void getButtonState(uint8_t but);
void loop_check_button();
void *memmem(const void *haystack, size_t hlen, const void *needle, size_t nlen);
bool select_mode(Control* ctrl);
void flash_led(Flash_mode flash);
void iwdg_reset();
void check_reset_flag();
void switch_menu_press_plus(Control* ctrl);

uint8_t buttonMask[BUTTON_COUNT] = { GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3 };
uint8_t buttonOnLevel[BUTTON_COUNT] = { GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3 };
volatile uint8_t buttonCurrentState[BUTTON_COUNT] = { 0, 0, 0, 0 };
volatile uint32_t lastDebounceTime[BUTTON_COUNT] = { 0, 0, 0, 0 };
volatile uint8_t buttonStateOFF[BUTTON_COUNT] = { 0, 0, 0, 0 };
volatile uint8_t buttonStateON[BUTTON_COUNT] = { 0, 0, 0, 0 };
volatile uint8_t buttonStateChange[BUTTON_COUNT] = { 0 };
volatile uint8_t button_plus = 0;
volatile uint8_t button_minus = 0;
volatile uint8_t button_enter = 0;
volatile uint8_t button_mode = 0;

uint8_t cur_menu = 0; //MENU_MENUE;
uint8_t to_menu = 0; //MENU_MENUE;

int incomingByte = 0;
uint8_t buf[SIZE_BUFFER];
uint8_t buf_index = 0;
bool wait_connect_pult = 0;
uint8_t power_on = 0;
uint8_t menu = 0;
uint8_t menue = 0;
uint8_t upmotor_menu = 0;
uint8_t bottommotor_menu = 0;
uint8_t upmotor = 0;
uint8_t downmotor = 0;
uint8_t bothmotors_menu = 0;
uint8_t bothmotors = 0;
uint8_t scretching_menu = 0;
uint8_t install_door_open = 0;
uint8_t install_door_close = 0;
uint8_t stoptime_menu = 0;
uint8_t door_open = 0;
uint8_t start_loop_impuls_enter_press = 0;

const uint8_t led1 = 23;
const uint8_t led2 = 24;
// int brightness = 0;    // how bright the LED is
// int fadeAmount = 5;    // how many points to fade the LED by
// char i;

void setup()  {
	CLK_Config();
	IWDG_Config();
  	GPIO_Config();
	IWDG_ReloadCounter();  
	EEPROM_Config();
	IWDG_ReloadCounter();
  	//UART2_Init();
  	Serial_begin(9600);
  	wait_connect_pult = true;
  	FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);
} 

void loop()  {
	Control ctrl = {MODE_UP, MENU_MENUE};
	while (wait_connect_pult)
	{
		IWDG_ReloadCounter();
		loop_check_button();
		if (button_mode)
		{
			button_mode = 0;
			//check_reset_flag();
			if (select_mode(&ctrl))
			{
				flash_led(FLASH_NONE);
				flash_led(ctrl.current_mode);
				wait_connect_pult = false;
				break;
			}
			else
			{
				GPIO_WriteHigh(LED_GPIO_PORT, LED_GPIO_PINS);
			}
		}
	}
	uint32_t time_delay;
	GPIO_WriteLow(OUT_GPIO_PORT, OUT_START_PIN);
	time_delay = millis() + 372;
	while (time_delay > millis())
	{
		IWDG_ReloadCounter();
		flash_led(ctrl.current_mode);
	}
  	GPIO_WriteHigh(OUT_GPIO_PORT, OUT_START_PIN);
	time_delay = millis() + 120;
	while (time_delay > millis())
	{
		IWDG_ReloadCounter();
		flash_led(ctrl.current_mode);
	}
  	GPIO_WriteLow(OUT_GPIO_PORT, OUT_START_PIN);
	time_delay = millis() + 199;
	while (time_delay > millis())
	{
		IWDG_ReloadCounter();
		flash_led(ctrl.current_mode);
	}
  	GPIO_WriteHigh(OUT_GPIO_PORT, OUT_START_PIN);
	time_delay = millis() + 2128;
	while (time_delay > millis())
	{
		IWDG_ReloadCounter();
		flash_led(ctrl.current_mode);
	}
	Serial_flush();
	Serial_write(0x23);
	Serial_write(0x0D);
	Serial_write(0x0A); 

	uint32_t time_loop = 15000 + millis();
	power_on = 1;

	while (true)
	{
		while (power_on)
		{
			IWDG_ReloadCounter();
			flash_led(ctrl.current_mode);
			if (Serial_available() > 0) 
			{
				incomingByte = Serial_read(); // get the character
				buf[buf_index++] = (uint8_t)incomingByte;
				if (incomingByte == '\n') 
				{
					if (memmem(buf, buf_index, pre_cmd, 5) != NULL)
					{
						buf_index = 0;
						time_loop = 15000 + millis();
						delay(500);
						Serial_write(0x23);
						Serial_write(0x0D);
						Serial_write(0x0A);
						Serial_flush();
					}
					else if (memmem(buf, buf_index, menu_cmd, 7) != NULL)
					{
						buf_index = 0; // Serial.println(F("MENUE PLUS NEXT"));
						Serial_flush();
						ctrl.current_menu = MENU_MENUE;
						power_on = 0;
						// menue = 1;
						menu = 1;
						break;
					}
					// else if (memmem(buf, buf_index, InstallMode, 7) != NULL)
					// {
					// 	buf_index = 0;
					// 	// Serial.println(F("INSTALL MODE"));
					// 	Serial_flush();
					// 	cur_menu = MENU_INSTALL;
					// 	// led_install_flash();
					// 	power_on = 0;
					// 	install_door_open = 1;
					// 	break;
					// }
				}
				if (buf_index == SIZE_BUFFER)
				{ // Serial.println(F("Buffer full"));
					iwdg_reset();
				}
			}
			if (millis() > time_loop)
			{ // Serial.println(F("Time read end. Restart"));
				iwdg_reset();
			}
		}
		while (menu)
		{
			IWDG_ReloadCounter();
			flash_led(ctrl.current_mode);
			if (Serial_available() > 0)
			{
				incomingByte = Serial_read(); // get the character
				buf[buf_index++] = (uint8_t)incomingByte;
				if (buf_index == SIZE_BUFFER)
				{ //Serial.println(F("Buffer full"));
					iwdg_reset();
				}
				if (incomingByte == '\n') 
				{
					if (memmem(buf, buf_index, menu_cmd, 7) != NULL)
					{
						buf_index = 0; //Serial.println(F("MENUE PLUS NEXT"));
						Serial_flush();
						ctrl.current_menu = MENU_MENUE;
						//stop_enter_press_loop();
						//loop_check_menu();
					}
					else if (memmem(buf, buf_index, Menu_plus_to_UpmotorMenu_cmd, 7) != NULL)
					{
						buf_index = 0; //Serial.println(F("UPMOTOR WITH ENTER RETURN or PLUS NEXT"));
						Serial_flush();
						ctrl.current_menu = MENU_UP;
						while (true)
						{
							IWDG_ReloadCounter();
							flash_led(ctrl.current_mode);
						}
						
						//stop_enter_press_loop();
						//loop_check_menu();
					}
					// else if (memmem(buf, buf_index, Upmotor_enter_to_UpmotorMenu_cmd, 9) != NULL)
					// {
					// 	buf_index = 0; //Serial.println(F("UPMOTOR WITH ENTER RETURN or PLUS NEXT"));
					// 	Serial_flush();
					// 	control.current_menu = MENU_UP;
					// 	//stop_enter_press_loop();
					// 	//loop_check_menu();
					// }
					// else if (memmem(buf, buf_index, UpmotorMenu_plus_to_BottommotorMenu_cmd, 7) != NULL)
					// {
					// 	buf_index = 0; //Serial.println(F("DOWNMOTOR WITH ENTER RETURN or PLUS NEXT"));
					// 	Serial_flush();
					// 	control.current_menu = MENU_DOWN;
					// 	//stop_enter_press_loop();
					// 	//loop_check_menu();
					// }
					// else if (memmem(buf, buf_index, Bottommotor_enter_to_BottommotorMenu_cmd, 9) != NULL)
					// {
					// 	buf_index = 0;
					// 	Serial.println(F("DOWNMOTOR WITH ENTER RETURN or PLUS NEXT"));
					// 	Serial1.flush();
					// 	cur_menu = MENU_DOWN;
					// 	stop_enter_press_loop();
					// 	loop_check_menu();
					// }
					// else if (memmem(buf, buf_index, BottommotorMenu_plus_to_BothmotorsMenu_cmd, 7) != NULL)
					// {
					// 	buf_index = 0;
					// 	Serial.println(F("BOTHMOTOR WITH ENTER RETURN or PLUS NEXT"));
					// 	Serial1.flush();
					// 	cur_menu = MENU_BOTH;
					// 	stop_enter_press_loop();
					// 	loop_check_menu();
					// }
					// else if (memmem(buf, buf_index, Bothmotors_enter_to_BothmotorsMenu_cmd, 9) != NULL)
					// {
					// 	buf_index = 0;
					// 	Serial.println(F("BOTHMOTOR WITH ENTER RETURN or PLUS NEXT"));
					// 	Serial1.flush();
					// 	cur_menu = MENU_BOTH;
					// 	stop_enter_press_loop();
					// 	loop_check_menu();
					// }
					// else if (memmem(buf, buf_index, ScrethingMenu_plus_to_InstallMenu_cmd, 7) != NULL)
					// {
					// 	buf_index = 0;
					// 	Serial.println(F("INSTALL WITH ENTER RETURN or PLUS NEXT"));
					// 	Serial1.flush();
					// 	cur_menu = MENU_INSTALL;
					// 	stop_enter_press_loop();
					// 	loop_check_menu();
					// }
					// else if (memmem(buf, buf_index, InstallMenu_enter_to, 12) != NULL)
					// {
					// 	buf_index = 0;
					// 	Serial.println(F("INSTALL"));
					// 	Serial1.flush();
					// 	cur_menu = MENU_INSTALL;
					// 	stop_enter_press_loop();
					// 	menu = 0;
					// 	install_door_open = 1;
					// 	break;
					// }
				}
			}

			switch_menu_press_plus(&ctrl);

			//loop_enter_emulate_press();
			
// 			switch (ctrl.current_menu)
// 			{
// 			case MENU_MENUE:
// 				if (ctrl.current_menu == MENU_MENUE) 
// 				{
// 					menu = 0;
// 					menue = 1;
// 				}
// 				break;
// 			case MENU_UP:
// 				if (to_menu == MENU_UP) 
// 				{
// 					start_enter_press_loop();
// 					menu = 0;
// 					upmotor = 1;
// 				}
// 				break;
// 			case MENU_DOWN:
// 				if (to_menu == MENU_DOWN) 
// 				{
// 					start_enter_press_loop();
// 					menu = 0;
// 					downmotor = 1;
// 				}
// 				break;
// 			case MENU_BOTH:
// 				if (to_menu == MENU_BOTH) 
// 				{
// 					start_enter_press_loop();
// 					menu = 0;
// 					bothmotors = 1;
// 				}
// 				break;
// 			case MENU_INSTALL:
// 				if (to_menu == MENU_INSTALL) 
// 				{
// 					start_enter_press_loop();
// //					menu = 0;
// //					install = 1;
// 				}
// 				break;
// 			default:
// 				break;
// 			}
		}
		// while (menue)
		// {
		// 	IWDG_ReloadCounter();
		// 	GPIO_WriteLow(LED_GPIO_PORT, LED_GPIO_PINS);
	// 		led_main_cont();
	// 		loop_check_button();
	// 		if (wait_enter_press())
	// 		{
	// 			loop_check_menu();
	// 			menue = 0;
	// 			menu = 1;
	// 		}
	// 		if (button_plus && button_minus)
	// 		{
	// 			led_all_off();
	// 			to_menu = MENU_INSTALL;
	// 			led_install_flash();
	// 			loop_check_menu();
	// 			menue = 0;
	// 			menu = 1;
	// 		}
		// }
	}
}

void switch_menu_press_plus(Control* ctrl)
{
	static uint32_t press_on = 0;
	static uint32_t loop_press = 0;
	if (ctrl->current_menu != ctrl->current_mode)
	{	
		if (millis() > loop_press)
		{
			GPIO_WriteLow(OUT_GPIO_PORT, OUT_PLUS_PIN); //digitalWrite(BUT_PLUS, HIGH);
			press_on = millis() + 300;
			loop_press = millis() + 550;
		}
		if (millis() > press_on)
		{
			GPIO_WriteHigh(OUT_GPIO_PORT, OUT_PLUS_PIN); //digitalWrite(BUT_PLUS, LOW);
		}
	}
	else
	{
		GPIO_WriteHigh(OUT_GPIO_PORT, OUT_PLUS_PIN);
	}
}

void check_reset_flag()
{
	if (RST_GetFlagStatus (RST_FLAG_IWDGF))
  	{
		uint32_t t = millis() + 1000;
		uint32_t time_on = 0;
		while (millis() < t)
		{
			IWDG_ReloadCounter();
			if (millis() > time_on)
			{
				GPIO_WriteReverse(LED_GPIO_PORT, LED_GPIO_PINS);
				time_on = millis() + 60;
			}
		}
		RST_ClearFlag (RST_FLAG_IWDGF);
  	}
}

bool select_mode(Control* ctrl){
	Mode mode = ctrl->current_mode;
	uint32_t time_end = millis() + 3000;
	while (true)
	{
		IWDG_ReloadCounter();
		switch (mode)
		{
		case MODE_UP:
			GPIO_WriteLow(LED_GPIO_PORT, LED_UP_PIN);
			GPIO_WriteHigh(LED_GPIO_PORT, LED_DOWN_PIN);
			break;
		case MODE_DOWN:
			GPIO_WriteLow(LED_GPIO_PORT, LED_DOWN_PIN);
			GPIO_WriteHigh(LED_GPIO_PORT, LED_UP_PIN);
			break;
		case MODE_BOTH:
			GPIO_WriteLow(LED_GPIO_PORT, LED_GPIO_PINS);
			break;
		case OVER:
			mode = MODE_UP;
			GPIO_WriteLow(LED_GPIO_PORT, LED_UP_PIN);
			GPIO_WriteHigh(LED_GPIO_PORT, LED_DOWN_PIN);
			break;
		default:
			break;
		}
		loop_check_button();
		if (button_enter)
		{
			button_enter = 0;
			ctrl->current_mode = mode;
			return true;
		}
		if (button_mode)
		{
			time_end = millis() + 3000;
			button_mode = 0;
			mode += 1;
		}
		if (millis() > time_end)
		{
			return false;
		}
	}
}

void iwdg_reset()
{
	uint32_t time_on = 0;
	GPIO_WriteHigh(LED_GPIO_PORT, LED_GPIO_PINS);
	while (true)
	{
		if (millis() > time_on)
		{
			GPIO_WriteReverse(LED_GPIO_PORT, LED_GPIO_PINS);
			time_on = millis() + 60;
		}
	}
}

void flash_led(Flash_mode flash)
{
	static uint32_t time_on = 0;
	if (millis() > time_on)
	{
		switch (flash)
		{
		case FLASH_UP:
			GPIO_WriteReverse(LED_GPIO_PORT, LED_UP_PIN);
			GPIO_WriteHigh(LED_GPIO_PORT, LED_DOWN_PIN);
			break;
		case FLASH_DOWN:
			GPIO_WriteReverse(LED_GPIO_PORT, LED_DOWN_PIN);
			GPIO_WriteHigh(LED_GPIO_PORT, LED_UP_PIN);
			break;
		case FLASH_BOTH:
			GPIO_WriteReverse(LED_GPIO_PORT, LED_GPIO_PINS);
			break;
		case FLASH_NONE:
			GPIO_WriteHigh(LED_GPIO_PORT, LED_GPIO_PINS);
		default:
			break;
		}
		time_on = millis() + 250;
	}
}

void *memmem(const void *haystack, size_t hlen, const void *needle, size_t nlen)
{
    int needle_first;
    const void *p = haystack;
    size_t plen = hlen;

    if (!nlen)
        return NULL;

    needle_first = *(unsigned char *)needle;

    while (plen >= nlen && (p = memchr(p, needle_first, plen - nlen + 1)))
    {
        if (!memcmp(p, needle, nlen))
            return (void *)p;

        p++;
        plen = hlen - (p - haystack);
    }

    return NULL;
}

void loop_check_button()
{
	for (uint8_t i = 0; i < BUTTON_COUNT; i++)
	{
		getButtonState(i); 
	}
	//plus
	if (buttonStateChange[BUT_PLUS])
	{
		buttonStateChange[BUT_PLUS] = 0;
		if (buttonStateON[BUT_PLUS])
		{
			// Serial.println(F("PLUS ON"));
			button_plus = 1;
		}
		if (buttonStateOFF[BUT_PLUS])
		{
			// Serial.println(F("PLUS OFF"));
			button_plus = 0;
		}
	}
	//minus
	if (buttonStateChange[BUT_MINUS])
	{
		buttonStateChange[BUT_MINUS] = 0;
		if (buttonStateON[BUT_MINUS])
		{
			// Serial.println(F("MINUS ON"));
			button_minus = 1;
		}
		if (buttonStateOFF[BUT_MINUS])
		{
			// Serial.println(F("MINUS OFF"));
			button_minus = 0;
		}
	}
  //mode
	if (buttonStateChange[BUT_MODE])
	{
		buttonStateChange[BUT_MODE] = 0;
		if (buttonStateON[BUT_MODE])
		{
			// Serial.println(F("MINUS ON"));
			button_mode = 1;
		}
		if (buttonStateOFF[BUT_MODE])
		{
			// Serial.println(F("MINUS OFF"));
			button_mode = 0;
		}
	}
	//enter
//	static unsigned long delay_3sec;
	if (buttonStateChange[BUT_ENTER])
	{
		buttonStateChange[BUT_ENTER] = 0;
		if (buttonStateON[BUT_ENTER])
		{
			// Serial.println(F("ENTER ON"));
			button_enter = 1;
		}
		if (buttonStateOFF[BUT_ENTER])
		{
			// Serial.println(F("ENTER OFF"));
			button_enter = 0;
//			delay_3sec = millis() + 3000;
		}
	}
	//up+down
	// if (buttonStateChange[UP] || buttonStateChange[DOWN])
	// {
	// 	//up
	// 	if (buttonStateChange[UP])
	// 	{
	// 		buttonStateChange[UP] = 0;
	// 		if (buttonStateON[UP]) mode_up_motor = 1;
	// 		if (buttonStateOFF[UP]) mode_up_motor = 0;
	// 	}
	// 	//down
	// 	if (buttonStateChange[DOWN])
	// 	{
	// 		buttonStateChange[DOWN] = 0;
	// 		if (buttonStateON[DOWN]) mode_down_motor = 1;
	// 		if (buttonStateOFF[DOWN]) mode_down_motor = 0;
	// 	}
	// 	//up+down
	// 	mode_both_motors = 0;
	// 	if (mode_up_motor && mode_down_motor)
	// 	{
	// 		Serial.println(F("BOTH"));
	// 		mode_both_motors = 1;
	// 	}
	// 	else if (mode_up_motor && !mode_down_motor)
	// 	{
	// 		Serial.println(F("UP"));
	// 	}
	// 	else if (!mode_up_motor && mode_down_motor)
	// 	{
	// 		Serial.println(F("DOWN"));
	// 	}
	// 	else
	// 	{
	// 		Serial.println(F("MAIN"));
	// 	}
	// }
}

void getButtonState(uint8_t but) {
	uint8_t state = GPIO_ReadInputData(GPIOB) & buttonMask[but];
	if (state ^ buttonCurrentState[but]) {
		//0^1 button press state=0;  1^0 button release state=1
		lastDebounceTime[but] = millis();
		buttonCurrentState[but] = state;
		return;
	}
	if ((millis() - lastDebounceTime[but] > DEBOUNCE_ms)) {
		if (buttonCurrentState[but] == buttonOnLevel[but]) {
			//1-button press or button release
			if (!buttonStateON[but]) 
			{
				buttonStateChange[but] = 1;
			}
			buttonStateON[but] = 1;
			buttonStateOFF[but] = 0;
		}
		else {
			if (buttonStateON[but])
			{
				buttonStateChange[but] = 1;
			}
			buttonStateON[but] = 0;
			buttonStateOFF[but] = 1;
		}
	}
}

static void IWDG_Config()
{
	IWDG_Enable(); //IWDG->KR =0xCC; // старт IWDG
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_256); //1.02s
	IWDG_SetReload(0xFF); //1.02s
	//IWDG_WriteAccessCmd(IWDG_WriteAccess_Disable);
	IWDG_ReloadCounter();
}

static void GPIO_Config()
{
  	// pinMode(led1,OUTPUT);
  	// pinMode(led2,OUTPUT);
  	//button
  	GPIO_DeInit(GPIOB);
  	GPIO_Init(BUTTON_GPIO_PORT, (GPIO_Pin_TypeDef)BUTTON_GPIO_PINS, GPIO_MODE_IN_FL_NO_IT);
  	//led
  	GPIO_DeInit(GPIOC);
  	GPIO_Init(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS, GPIO_MODE_OUT_PP_LOW_FAST);
  	GPIO_WriteHigh(LED_GPIO_PORT, LED_GPIO_PINS);
  	//gerkon in
  	//GPIO_Init(GERKON_GPIO_PORT, (GPIO_Pin_TypeDef)GERKON_PIN, GPIO_MODE_IN_FL_NO_IT);
  	//out to block stiboard
  	GPIO_DeInit(GPIOD);
  	GPIO_Init(OUT_GPIO_PORT, (GPIO_Pin_TypeDef)OUT_GPIO_PINS, GPIO_MODE_OUT_PP_LOW_FAST);
  	GPIO_WriteHigh(OUT_GPIO_PORT, OUT_GPIO_PINS);
}

static void CLK_Config(void)
{
	CLK_LSICmd(ENABLE);
  	CLK_HSECmd(ENABLE);
  	while(CLK_GetFlagStatus(CLK_FLAG_HSERDY) == FALSE);
  	CLK_HSICmd(DISABLE);
  	CLK_ClockSwitchCmd(ENABLE);
  	CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);                             
  	CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSE, DISABLE, CLK_CURRENTCLOCKSTATE_DISABLE);
}

static void EEPROM_Config()
{
	FLASH_DeInit();
	FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);
	FLASH_Unlock(FLASH_MEMTYPE_DATA);
	while (FLASH_GetFlagStatus(FLASH_FLAG_DUL) == RESET); // Wait for unlock success
}

// void EEPROM_Write_byte(uint32_t Address, uint8_t Data)
// {
// 	assert_param(IS_FLASH_DATA_ADDRESS_OK(Address));  
// 	 //Unlock
// 	FLASH_Unlock(FLASH_MEMTYPE_DATA);
// 	FLASH_ProgramByte(Address, Data);
// 	// for( ; Len > 0; Len--)
// 	// {
// 	// 		 Refresh_WWDG_Window(); //feed the dog
// 	// 		*p++ = *pData++;
// 	// 		 / / Wait for the write to complete
// 	// 		while(!(FLASH_GetFlagStatus(FLASH_FLAG_EOP))); 
// 	// } 
// 	 //Lock
// 	FLASH_Lock(FLASH_MEMTYPE_DATA);
// }


// void Derive_EPWrite(u16 Adr, u8 *pData, u16 Len)
// {
// 	u8 *p;
// 	 //p pointer points to the corresponding unit of the EEPROM
// 	p = (u8*)0x4000 + Adr;   
// 	 //Unlock
// 	FLASH_Unlock(FLASH_MEMTYPE_DATA);
// 	 / / Write data
// 	for( ; Len > 0; Len--)
// 	{
// 			 Refresh_WWDG_Window(); //feed the dog
// 			*p++ = *pData++;
// 			 / / Wait for the write to complete
// 			while(!(FLASH_GetFlagStatus(FLASH_FLAG_EOP))); 
// 	} 
// 	 //Lock
// 	FLASH_Lock(FLASH_MEMTYPE_DATA);
// }
 
// /****************************************************************************************
// *  Function: Derive_EPRead                                                                         
//  * Object: Read EEPROM
//  * Input: Head address (0~2048) Data storage pointer Data length
//  * Output: None                                         
//  * Remarks: 2K EEPROM
// ****************************************************************************************/
// void Derive_EPRead(u16 Adr, u8 *pData, u16 Len)
// {
// 	u8 *p;
// 	 //p pointer points to the corresponding unit of the EEPROM
// 	p = (u8*)0x4000 + Adr; 
// 	 //Unlock
// 	FLASH_Unlock(FLASH_MEMTYPE_DATA);
// 	 / / Read data
// 	for( ; Len > 0; Len--)
// 	{
// 		*pData++ = *p++;
// 		 Refresh_WWDG_Window(); //feed the dog
// 	}
// 	 //Lock EEPROM
// 	FLASH_Lock(FLASH_MEMTYPE_DATA);


