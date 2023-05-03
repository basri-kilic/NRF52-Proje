/**

 */

#include <stdbool.h>
#include <stdint.h>
#include "nrf.h"
#include "app_error.h"
#include "bsp.h"
#include "nrf_delay.h"
#include "app_pwm.h"




APP_PWM_INSTANCE(m_pwm, 1);


#define FREQ_IN_US  100


#define led 31
#define Motor_Pin   7  
#define M_Dir_Pin1  6 
#define M_Dir_Pin2  8 


static volatile bool ready_flag;

float deger;

void pwm_ready_handler(uint32_t pwm_id)
{
    ready_flag = true; 
}






int main(void)
{
    
    nrf_gpio_cfg_output(M_Dir_Pin1); 
    nrf_gpio_cfg_output(M_Dir_Pin2); 
    nrf_gpio_cfg_output(led);

  
    nrf_gpio_pin_set(M_Dir_Pin1); 
    nrf_gpio_pin_clear(M_Dir_Pin2); 

    ret_code_t err_code; 

	
    app_pwm_config_t pwm_config = APP_PWM_DEFAULT_CONFIG_1CH(FREQ_IN_US, Motor_Pin);

	
    pwm_config.pin_polarity[1] = APP_PWM_POLARITY_ACTIVE_HIGH;


	
    err_code = app_pwm_init(&m_pwm, &pwm_config, pwm_ready_handler);
    APP_ERROR_CHECK(err_code);
    app_pwm_enable(&m_pwm); 
    app_pwm_channel_duty_set(&m_pwm, 0, 50) == NRF_ERROR_BUSY;
    
    
    bsp_board_init(BSP_INIT_LEDS);
    uint8_t duty_cycle;
    nrf_gpio_pin_set(M_Dir_Pin1); 
    nrf_gpio_pin_clear(M_Dir_Pin2);
    



    while (true)
    {
      
      printf("duty cycle :%d \r\n", app_pwm_channel_duty_get(&m_pwm, 0)); 
                                                                                         		
      nrf_gpio_pin_set(led);
      
    }

}

