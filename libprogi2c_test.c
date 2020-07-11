#include <stdio.h>
#include <string.h>
#include "libprogi2c.h"

#define SCL 0
#define SDA 1
#define IMPULSE 100

#define SAME 255

int t = 0;
uint8_t bus[1000][2];

void write_bus(uint8_t port, uint8_t value) {
    bus[t][port] = value;
}

uint8_t always_one(uint8_t port) {
    return 1;
}

void increment_time(uint8_t ms) {
    t += (2 * ms) / IMPULSE;
}

int main() {
    memset(bus, SAME, 1000*2);

    i2c_impulse_ms = IMPULSE;
    i2c_scl_port = SCL;
    i2c_sda_port = SDA;
    i2c_write_port = write_bus;
    i2c_read_port = always_one;
    i2c_delay_ms = increment_time;

    i2c_start(0b0111000, WRITE);
    printf(i2c_write(0b10011001) ? "write successful\n" : "write failed\n");
    i2c_stop();

    int cycle = 0;
    printf("CYCLE\tSCL\tSDA\n");
    for (int i=1; i < t; i++) {
        if (bus[i][0] == SAME)
            bus[i][0] = bus[i-1][0];        
        if (bus[i][1] == SAME)
            bus[i][1] = bus[i-1][1];
        
        if (bus[i][0] - bus[i-1][0] == 1 || bus[i][0] - bus[i-1][0] == (1 - SAME)) {
            cycle++;
            printf("%d\t%d\t%d\n", cycle, bus[i][0], bus[i][1]);
        } else
            printf("\t%d\t%d\n", bus[i][0], bus[i][1]);
    }

    return 0;
}