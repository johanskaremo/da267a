#include <stdio.h>
#include <stdint.h>
#include "I2C.h"
#include "esp_system.h"
#include "driver/i2c.h"

void initI2C(int sdapin, int sclpin)
{
    i2c_config_t config = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = sdapin,
        .scl_io_num = sclpin,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 100000 // Hz
    };
    ESP_ERROR_CHECK(i2c_param_config(I2C_NUM_0, &config));
    ESP_ERROR_CHECK(i2c_driver_install(I2C_NUM_0, config.mode, 0, 0, 0));
}
void writeI2C(uint8_t address, uint8_t reg, uint8_t data)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    esp_err_t err = i2c_master_start(cmd); // Start command
    ESP_ERROR_CHECK(err);
    err = i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_WRITE, 1);
    ESP_ERROR_CHECK(err);
    err = i2c_master_write_byte(cmd, reg, 1); // Write to register
    ESP_ERROR_CHECK(err);
    err = i2c_master_write_byte(cmd, data, 1); // Write data
    ESP_ERROR_CHECK(err);
    err = i2c_master_stop(cmd); // End command
    ESP_ERROR_CHECK(err);

    err = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    ESP_ERROR_CHECK(err);
    i2c_cmd_link_delete(cmd);
}
void readI2C(uint8_t address, uint8_t reg, uint8_t *buffer, int len)
{
    // read low register
    // send just the register number with no other data
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    esp_err_t res = i2c_master_start(cmd);
    ESP_ERROR_CHECK(res);
    res = i2c_master_write_byte(cmd, address << 1 | I2C_MASTER_WRITE, 1); // set address for i2c device
    ESP_ERROR_CHECK(res);
    res = i2c_master_write_byte(cmd, reg, 1); // set register for i2c device
    ESP_ERROR_CHECK(res);
    res = i2c_master_stop(cmd);
    ESP_ERROR_CHECK(res);
    res = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    ESP_ERROR_CHECK(res);
    i2c_cmd_link_delete(cmd);
    // might need to wait 1 ms.

    cmd = i2c_cmd_link_create();
    res = i2c_master_start(cmd);
    ESP_ERROR_CHECK(res);
    res = i2c_master_write_byte(cmd, address << 1 | I2C_MASTER_READ, 1); // READ bit set!
    ESP_ERROR_CHECK(res);
    res = i2c_master_read(cmd, buffer, len, I2C_MASTER_NACK);
    ESP_ERROR_CHECK(res);
    res = i2c_master_stop(cmd);
    ESP_ERROR_CHECK(res);
    res = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    ESP_ERROR_CHECK(res);
    i2c_cmd_link_delete(cmd);
}