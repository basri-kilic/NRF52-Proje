#include <stdbool.h>
#include <stdint.h>
#include "nrf.h"
#include "nrf_drv_timer.h"
#include "bsp.h"
#include "app_error.h"
#include "nrf_delay.h"


static nrf_drv_timer_t timer_0 = NRF_DRV_TIMER_INSTANCE(0);

void timer_event(nrf_timer_event_handler_t event_type, void * p_context)
{
  
}



int main(void)
{
    uint32_t err_code = NRF_SUCCESS;
    bsp_board_init(BSP_INIT_LEDS);

    nrf_drv_timer_config_t timer_cfg = NRF_DRV_TIMER_DEFAULT_CONFIG;

    timer_cfg.mode = NRF_TIMER_MODE_COUNTER;


    err_code = nrf_drv_timer_init(&timer_0, &timer_cfg, &timer_event);
    APP_ERROR_CHECK(err_code);

    uint32_t timValue = 0;

    nrf_drv_timer_enable(&timer_0);
      
    while (1)
    {
        nrfx_timer_increment(&timer_0);

        timValue = nrfx_timer_capture(&timer_0, NRF_TIMER_CC_CHANNEL0);

        printf("Timer Deger: %d /r/n", timValue);

        nrf_delay_ms(1000);


        
    }
}
