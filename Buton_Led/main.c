#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "nrf_gpio.h"

#define led 17
#define buton 15
int main(void)
{
  nrf_gpio_cfg_input(buton, NRF_GPIO_PIN_PULLUP);
  nrf_gpio_cfg_output(led);

  nrf_gpio_pin_set(led);

  while(1)
  {
    if(nrf_gpio_pin_read(buton == 0))
    {
      nrf_gpio_pin_clear(led);

      while(nrf_gpio_pin_read(buton == 0))

      nrf_gpio_pin_set(led);
    }

  }

}
