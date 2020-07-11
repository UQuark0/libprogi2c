#pragma once
#include "stdint.h"

#define WRITE 0
#define READ 1

typedef void (*i2c_write_port_t) (uint8_t port, uint8_t value);
typedef uint8_t (*i2c_read_port_t) (uint8_t port);
typedef void (*i2c_delay_ms_t) (uint8_t ms);

extern i2c_write_port_t i2c_write_port;
extern i2c_read_port_t i2c_read_port;
extern i2c_delay_ms_t i2c_delay_ms;

extern uint8_t i2c_impulse_ms;
extern uint8_t i2c_scl_port;
extern uint8_t i2c_sda_port;

void i2c_start(uint8_t address, uint8_t mode);
uint8_t i2c_write(uint8_t data);
uint8_t i2c_read();
void i2c_stop();