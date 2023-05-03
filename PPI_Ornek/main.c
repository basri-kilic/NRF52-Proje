#include <stdbool.h>
#include <stdint.h>
#include "nrf.h"
#include "nrf_gpiote.h"
#include "nrf_gpio.h"
#include "boards.h"
#include "nrf_drv_ppi.h"
#include "nrf_drv_timer.h"
#include "nrf_drv_gpiote.h"
#include "app_error.h"


#define led 17
#define buton 13


static nrf_ppi_channel_t ppi_channel;


void interrupt_pin_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
    //boş
}

static void gpiote_pin_init(void)
{
  uint32_t error_code = NRF_SUCCESS;
  error_code = nrf_drv_gpiote_init();
  APP_ERROR_CHECK(error_code);

  nrf_drv_gpiote_in_config_t in_config = GPIOTE_CONFIG_IN_SENSE_HITOLO(true);
  in_config.pull = NRF_GPIO_PIN_PULLUP;

  error_code = nrf_drv_gpiote_in_init(buton, &in_config, interrupt_pin_handler);
  APP_ERROR_CHECK(error_code);

  nrf_drv_gpiote_out_config_t out_config = GPIOTE_CONFIG_OUT_TASK_TOGGLE(true);
  error_code = nrf_drv_gpiote_out_init(led, &out_config);
  APP_ERROR_CHECK(error_code);

  nrf_drv_gpiote_out_task_enable(led);

  nrf_drv_gpiote_in_event_enable(buton, true);

}

static void ppi_init(void)
{
    uint32_t err_code = NRF_SUCCESS;
    uint32_t btn_evt_addr;
    uint32_t led_task_addr;

    err_code = nrf_drv_ppi_init();
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_ppi_channel_alloc(&ppi_channel);
    APP_ERROR_CHECK(err_code);

    btn_evt_addr = nrf_drv_gpiote_in_event_addr_get(buton);
    led_task_addr = nrf_drv_gpiote_out_task_addr_get(led);

    err_code = nrf_drv_ppi_channel_assign(ppi_channel, btn_evt_addr, led_task_addr);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_ppi_channel_enable(ppi_channel);
    APP_ERROR_CHECK(err_code);

}

int main(void)
{
    gpiote_pin_init();
    ppi_init();


    while (true)
    {
        // Do Nothing - GPIO can be toggled without software intervention.
    }
}
