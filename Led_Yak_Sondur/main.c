#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "nrf_gpio.h"

#define led 31


int main(void)
{
  printf("uygulama basladi\r\n");
  nrf_gpio_cfg_output(led);
  
  while(1)
  {
    printf("led yandi \r\n");
    nrf_gpio_pin_set(led);
    nrf_delay_ms(500);
    printf("LED SONDU\r\n");
    nrf_gpio_pin_clear(led);
    nrf_delay_ms(500);

  }
}