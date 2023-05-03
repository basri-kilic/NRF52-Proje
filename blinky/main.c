#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "nrf_gpio.h"

#define led 31
int main(void)
{
  nrf_gpio_cfg_output(led);

  while(1)
  {
    nrf_gpio_pin_set(led);
    nrf_delay_ms(500);
    nrf_gpio_pin_clear(led);
    nrf_delay_ms(500);
  }
}
