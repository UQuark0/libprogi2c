#include "libprogi2c.h"

i2c_write_port_t i2c_write_port;
i2c_read_port_t i2c_read_port;
i2c_delay_ms_t i2c_delay_ms;
uint8_t i2c_impulse_ms;
uint8_t i2c_scl_port;
uint8_t i2c_sda_port;

void i2c_write_bit(uint8_t bit) {
    // half delay
    i2c_delay_ms(i2c_impulse_ms / 2);

    // write sda
    i2c_write_port(i2c_sda_port, bit);

    // half delay
    i2c_delay_ms(i2c_impulse_ms / 2);
    
    // scl high
    i2c_write_port(i2c_scl_port, 1);

    // delay
    i2c_delay_ms(i2c_impulse_ms);

    // scl low
    i2c_write_port(i2c_scl_port, 0);
}

uint8_t i2c_read_bit() {
    // delay
    i2c_delay_ms(i2c_impulse_ms);
    
    // scl high
    i2c_write_port(i2c_scl_port, 1);

    // read sda
    uint8_t bit = i2c_read_port(i2c_sda_port);
    
    // delay
    i2c_delay_ms(i2c_impulse_ms);

    // scl low
    i2c_write_port(i2c_scl_port, 0);

    return bit;
}

uint8_t i2c_write(uint8_t data) {

    for (uint8_t i = 0; i < 8; i++) {
        i2c_write_bit( (data & 0b10000000) > 0 );
        data <<= 1;
    }
    return i2c_read_bit();
}

uint8_t i2c_read() {
    uint8_t data = 0;
    for (uint8_t i = 0; i < 8; i++) {
        if (i2c_read_bit())
            data++;
        if (i != 7)
            data <<= 1;
    }
    i2c_write_bit(1);
    return data;
}

void i2c_start(uint8_t address, uint8_t mode) {
    // delay
    i2c_delay_ms(i2c_impulse_ms);
    
    // sda high
    i2c_write_port(i2c_sda_port, 1);

    // scl high
    i2c_write_port(i2c_scl_port, 1);

    // half delay
    i2c_delay_ms(i2c_impulse_ms / 2);

    // sda low
    i2c_write_port(i2c_sda_port, 0);

    // half delay
    i2c_delay_ms(i2c_impulse_ms / 2);

    // scl low
    i2c_write_port(i2c_scl_port, 0);

    i2c_write((address << 1) | mode);
}

void i2c_stop() {
    // delay
    i2c_delay_ms(i2c_impulse_ms);
    
    // sda high
    i2c_write_port(i2c_sda_port, 0);

    // scl high
    i2c_write_port(i2c_scl_port, 1);

    // half delay
    i2c_delay_ms(i2c_impulse_ms / 2);

    // sda low
    i2c_write_port(i2c_sda_port, 1);

    // half delay
    i2c_delay_ms(i2c_impulse_ms / 2);

    // scl low
    i2c_write_port(i2c_scl_port, 0);
}