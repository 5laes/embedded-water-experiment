#include <stdio.h>
#include <string.h>

#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_adc/adc_continuous.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"

#define READ_LENGTH 512
#define BLINK_LED 33
#define EXAMPLE_ADC_GET_DATA(p_data)        ((p_data)->type1.data)

// vTaskDelay(1000 / portTICK_PERIOD_MS); pause for 1 sec

void app_main(void) {

    char *ourTaskName = pcTaskGetName(NULL);
    ESP_LOGI(ourTaskName, "Hello, starting up!\n");

    adc_continuous_handle_t handle = NULL;

    adc_continuous_handle_cfg_t adc_handle_cfg = {
        .max_store_buf_size = 1024,
        .conv_frame_size = 100,
    };
    ESP_ERROR_CHECK(adc_continuous_new_handle(&adc_handle_cfg, &handle));

    adc_digi_pattern_config_t adc_pattern_cfg = {
        .atten = ADC_ATTEN_DB_0,
        .channel = 4 & 0x7,
        .unit = ADC_UNIT_1,
        .bit_width = SOC_ADC_DIGI_MAX_BITWIDTH,
    };

    adc_continuous_config_t adc_cont_cfg = {
        .pattern_num = 1,
        .adc_pattern = &adc_pattern_cfg,
        .sample_freq_hz = 20 * 1000,
        .conv_mode = ADC_CONV_SINGLE_UNIT_1,
        .format = ADC_DIGI_OUTPUT_FORMAT_TYPE1,
    };

    ESP_ERROR_CHECK(adc_continuous_config(handle, &adc_cont_cfg));
    ESP_ERROR_CHECK(adc_continuous_start(handle));

    uint8_t result[READ_LENGTH] = {0};
    memset(result, 0xcc, READ_LENGTH);
    uint32_t ret_num = 0;

    gpio_reset_pin(BLINK_LED);
    gpio_set_direction(BLINK_LED, GPIO_MODE_OUTPUT);

    while (1)
    {
        ulTaskNotifyTake(pdTRUE, 50 / portTICK_PERIOD_MS);
        adc_continuous_read(handle, result, READ_LENGTH, &ret_num, 0);
        adc_digi_output_data_t *p = (adc_digi_output_data_t*)&result[0];
        uint32_t data = p->type1.data; // I receive data but it seems wrong, always maxed out at 4095
        ESP_LOGI(ourTaskName, "Moist level: %lu", data);
        if (data > 78) // Random number for the moment to test LED
        {
            gpio_set_level(BLINK_LED, 1);
        }
        else
        {
            gpio_set_level(BLINK_LED, 0);
        }
    }

    ESP_ERROR_CHECK(adc_continuous_stop(handle));
    ESP_ERROR_CHECK(adc_continuous_deinit(handle));
}
