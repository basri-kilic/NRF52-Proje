#include "nrf.h"
#include "nrf_gpio.h"
#include "nrf_drv_rtc.h"
#include "nrf_drv_clock.h"
#include "boards.h"
#include "app_error.h"
#include <stdint.h>
#include <stdbool.h>
#include <nrfx.h>

#define led 17

const nrfx_rtc_t rtc = NRF_DRV_RTC_INSTANCE(2);

static void lfclk_config(void)
{
  
  ret_code_t err_code = nrf_drv_clock_init();
  APP_ERROR_CHECK(err_code);

  nrf_drv_clock_lfclk_request(NULL);

}

static void rtc_handler(nrfx_rtc_int_type_t int_type)
{
  if(int_type == NRFX_RTC_INT_TICK)
  {
    nrf_gpio_pin_toggle(led);
  }
}


static void rtc_config(void)
{
  uint32_t err_code; 
  
  nrfx_rtc_config_t rtc_cfg = NRFX_RTC_DEFAULT_CONFIG;

  rtc_cfg.prescaler = 4095;
  
  err_code = nrfx_rtc_init(&rtc, &rtc_cfg, rtc_handler);
  APP_ERROR_CHECK(err_code);

  nrfx_rtc_enable(&rtc);
  
}

int main(void)
{
  bsp_board_init(BSP_INIT_LEDS);

  lfclk_config();

  rtc_config();
    

    while (true)
    {
        __SEV();
        __WFE();
        __WFE();
    }
}