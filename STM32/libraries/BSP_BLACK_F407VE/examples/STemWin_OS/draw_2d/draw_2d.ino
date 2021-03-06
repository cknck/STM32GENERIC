#include "BSP_BLACK_F407VE.h"
#include "FreeRTOS.h"
#include "MW_STemWin.h"
#include "display2d.h"
#define LED  LED_BUILTIN
#define LED1 LED_BUILTIN1

extern "C"  void GUI_X_ErrorOut(const char * s);

static void myTask1(void  __attribute__ ((unused)) *argument)
{
  /*Task setup*/
  pinMode(LED, OUTPUT);
  uint32_t i = 0;
  /* USER CODE BEGIN Task1 */
  /* Infinite loop */
  for (;;)
  {
    digitalToggle(LED);    // turn the LED off by making the voltage LOW
    vTaskDelay(950);              // wait for a second
  }
  /* USER CODE END Task1 */
}

static void myTask2(void __attribute__ ((unused)) *argument)
{
  /*Task setup*/
  pinMode(LED1, OUTPUT);
  /* USER CODE BEGIN Task2 */
  /* Infinite loop */
  for (;;)
  {
    digitalToggle(LED1);    // turn the LED off by making the voltage LOW
    vTaskDelay(200);              // wait for a second
  }
  /* USER CODE END Task2 */
}

extern "C"  void MainTask (void __attribute__ ((unused)) *argument)
{

  TFTLCD_Init();
  /*Task setup*/
  GUI_Init();
  GUI_Clear();
  for (;;)
  {
	GUI_Clear();
    GUI_SetFont(&GUI_Font20_1);
    GUI_DispStringAt("Draw2D demo...", (LCD_GetXSize() - 100) / 2, (LCD_GetYSize() - 20) / 2);
    vTaskDelay(2000);              // wait for a second
    display_2d();
  }
  /* USER CODE END Task2 */
}

// the setup function runs once when you press reset or power the board.
void setup() {
  Serial.begin(115200);
  //  osThreadDef(task1Name, myTask1, osPriorityNormal, 0, 128);
  //  myTask1Handle=osThreadCreate(osThread(task1Name), NULL);
  xTaskCreate(myTask1,
              NULL,
              configMINIMAL_STACK_SIZE,
              NULL,
              3,
              NULL);
  xTaskCreate(myTask2,
              NULL,
              configMINIMAL_STACK_SIZE,
              NULL,
              3,
              NULL);
  xTaskCreate(MainTask,
              NULL,
              configMINIMAL_STACK_SIZE,
              NULL,
              3,
              NULL);
  vTaskStartScheduler();
}

// the loop function runs over and over again forever
void loop() {
  /*
    !!! this no runed in freertos  !!!
  */
}
