/**
 * Copyright (c) 2014 - 2021, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/** @file
 *
 * @defgroup ble_sdk_app_template_main main.c
 * @{
 * @ingroup ble_sdk_app_template
 * @brief Template project main file.
 *
 * This file contains a template for creating a new application. It has the code necessary to wakeup
 * from button, advertise, get a connection restart advertising on disconnect and if no new
 * connection created go back to system-off mode.
 * It can easily be used as a starting point for creating a new application, the comments identified
 * with 'YOUR_JOB' indicates where and how you can customize.
 */

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "nordic_common.h"
#include "nrf.h"
#include "app_error.h"
#include "ble.h"
#include "ble_hci.h"
#include "ble_srv_common.h"
#include "ble_advdata.h"
#include "ble_advertising.h"
#include "ble_conn_params.h"
#include "nrf_sdh.h"
#include "nrf_sdh_soc.h"
#include "nrf_sdh_ble.h"
#include "app_timer.h"
#include "fds.h"
#include "peer_manager.h"
#include "peer_manager_handler.h"
#include "bsp_btn_ble.h"
#include "sensorsim.h"
#include "ble_conn_state.h"
#include "nrf_ble_gatt.h"
#include "nrf_ble_qwr.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_drv_saadc.h"
#include "app_pwm.h"
#include "nrf_drv_pwm.h"
#include "nrfx_pwm.h"
#include "nrf_saadc.h"
#include "nrfx_saadc.h"
#include "nrf_drv_saadc.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "nrf_drv_timer.h"
#include "nrfx_timer.h"
#include "nrf_drv_ppi.h"
#include "nrfx_ppi.h"
#include "nrf_delay.h"


APP_PWM_INSTANCE(m_pwm, 1);

#define frekans 100
#define led 31
#define motor_pin 7
#define motor_drive_1 6
#define motor_drive_2 8





static volatile bool ready_flag; 

float adcDeger ;
float voltaj;




static uint8_t speed = 0;

void pwm_ready_handler(uint32_t pwm_id)
{
  ready_flag = true;
}

void saadc_callback_handler(nrf_drv_saadc_evt_t const * p_event)
{


}

void saadc_init(void)
{
    ret_code_t err_code;

    nrf_saadc_channel_config_t channel_config = NRFX_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN6);
    
    err_code = nrf_drv_saadc_init(NULL, saadc_callback_handler);
    APP_ERROR_CHECK(err_code);

    err_code = nrfx_saadc_channel_init(0, &channel_config);
    APP_ERROR_CHECK(err_code);




}


void motor_init(void)
{
  nrf_gpio_cfg_output(motor_drive_1);
  nrf_gpio_cfg_output(motor_drive_2);
  nrf_gpio_cfg_output(led);

  nrf_gpio_pin_set(motor_drive_1);
  nrf_gpio_pin_clear(motor_drive_2);

  ret_code_t err_code; 

  app_pwm_config_t pwm_config = APP_PWM_DEFAULT_CONFIG_1CH(frekans, motor_pin);
  pwm_config.pin_polarity[1] = APP_PWM_POLARITY_ACTIVE_HIGH;

  err_code = app_pwm_init(&m_pwm, &pwm_config, pwm_ready_handler);
  APP_ERROR_CHECK(err_code);

  app_pwm_enable(&m_pwm);
  
}

void change_speed(void){
    
     
      if(speed >1 && speed<10){

       app_pwm_channel_duty_set(&m_pwm, 0, 40) == NRF_ERROR_BUSY;
      }
      else if(speed >10 && speed<20){
      
       app_pwm_channel_duty_set(&m_pwm, 0, 30) == NRF_ERROR_BUSY; 
      }
      else if(speed >20 && speed<30){
        
        app_pwm_channel_duty_set(&m_pwm, 0, 20) == NRF_ERROR_BUSY;
      }
      else if(speed >30 && speed<40){
        
        app_pwm_channel_duty_set(&m_pwm, 0, 15) == NRF_ERROR_BUSY;
      }
      else if(speed >40  && speed<50){
        
        app_pwm_channel_duty_set(&m_pwm, 0, 10) == NRF_ERROR_BUSY;
      }
       else if(speed >50 && speed <60 ){
       
        app_pwm_channel_duty_set(&m_pwm,0, 5) == NRF_ERROR_BUSY;
      }

       else if (speed<1 ){
       app_pwm_channel_duty_set(&m_pwm, 0, 100) == NRF_ERROR_BUSY;
       }

}




int main(void)
{   
    saadc_init();
    motor_init();
    
   
   
    nrf_saadc_value_t adcDeger;
    while(true)
    {
     nrfx_saadc_sample_convert(0, &adcDeger);
     voltaj = adcDeger * 5/ 1024 ;
     speed = (adcDeger*3)/100;  
     //printf("duty cycle :%d \r\n", app_pwm_channel_duty_get(&m_pwm, 0));
     //printf("speed :%d \r\n", speed);
     //printf("voltaj :%d \r\n", voltaj);
     //printf("adcDeger :%d \r\n", adcDeger);
     change_speed();
     
 
     
    }
}


