#include "DS1302.h"
#include "zf_systick.h"

// Returns the decoded decimal value from a binary-coded decimal (BCD) byte.
// Assumes 'bcd' is coded with 4-bits per digit, with the tens place digit in
// the upper 4 MSBs.
uint8_t bcdToDec(const uint8_t bcd)
{
    return (10 * ((bcd & 0xF0) >> 4) + (bcd & 0x0F));
}

// Returns the binary-coded decimal of 'dec'. Inverse of bcdToDec.
uint8_t decToBcd(const uint8_t dec)
{
    uint8_t tens, ones;

    tens = dec / 10;
    ones = dec % 10;
    return (tens << 4) | ones;
}

// Returns the hour in 24-hour format from the hour register value.
uint8_t hourFromRegisterValue(const uint8_t value) {
    uint8_t adj;
    if (value & 128)  // 12-hour mode
        adj = 12 * ((value & 32) >> 5);
    else           // 24-hour mode
        adj = 10 * ((value & (32 + 16)) >> 4);
    return (value & 15) + adj;
}

void DS1302_writeOut(DS1302* ds1302, const uint8_t value, uint8_t readAfter)
{
    gpio_init(ds1302->DS1302_SDA_Pin, GPO, 0, GPIO_PIN_CONFIG);

    for (int i = 0; i < 8; i++) {
        //digitalWrite(io_pin_, (value >> i) & 1);
        if( (value >> i) & 1 ) {
            gpio_set(ds1302->DS1302_SDA_Pin, 1);
        } else {
            gpio_set(ds1302->DS1302_SDA_Pin, 0);
        }
        //systick_delay_ms(1);
        gpio_set(ds1302->DS1302_SCL_Pin, 0);    //digitalWrite(sclk_pin_, HIGH);
        systick_delay_ms(2);

        if (readAfter && i == 7) {
            // We're about to read data -- ensure the pin is back in input mode
            // before the clock is lowered.
            //pinMode(io_pin_, INPUT);
            gpio_set(ds1302->DS1302_SCL_Pin, 1);
            systick_delay_ms(1);
            gpio_set(ds1302->DS1302_SDA_Pin, 0);
            gpio_init(ds1302->DS1302_SDA_Pin, GPI, 0, GPIO_PIN_CONFIG);
            //systick_delay_ms(1);
        } else {
            gpio_set(ds1302->DS1302_SCL_Pin, 1);  //digitalWrite(sclk_pin_, LOW);
            systick_delay_ms(2);                                                                //delayMicroseconds(1);
        }
    }
}

uint8_t DS1302_readIn(DS1302* ds1302)
{
    uint8_t input_value;
    uint8_t bit;
    uint32_t i;

    input_value = 0;
    bit = 0;

		gpio_init(ds1302->DS1302_SDA_Pin, GPI, 0, GPIO_PIN_CONFIG);
	
    

    // Bits from the DS1302 are output on the falling edge of the clock
    // cycle. This is called after readIn (which will leave the clock low) or
    // writeOut(..., true) (which will leave it high).
    for (i = 0; i < 8; i++) {

        gpio_set(ds1302->DS1302_SCL_Pin, 1);    //digitalWrite(sclk_pin_, HIGH);
        systick_delay_ms(2);                                                                //delayMicroseconds(1);
        gpio_set(ds1302->DS1302_SCL_Pin, 0);  //digitalWrite(sclk_pin_, LOW);
        systick_delay_ms(1);                                                                //delayMicroseconds(1);
        bit = gpio_get(ds1302->DS1302_SDA_Pin);                  //bit = digitalRead(io_pin_);
        systick_delay_ms(1);
        input_value |= (bit << i);  // Bits are read LSB first.
    }

    return input_value;
}

uint8_t DS1302_readRegister(DS1302* ds1302, const uint8_t reg)
{
    //const SPISession s(ce_pin_, io_pin_, sclk_pin_);

    uint8_t cmd_byte;
    uint8_t result;

    gpio_set(ds1302->DS1302_CE_Pin, 1);

    cmd_byte = (0x81 | (reg << 1));
    DS1302_writeOut(ds1302, cmd_byte, DEF_true);
    result = DS1302_readIn(ds1302);

    systick_delay_ms(1);
    gpio_set(ds1302->DS1302_CE_Pin, 0);

    return result;
}

void DS1302_writeRegister(DS1302* ds1302, const uint8_t reg, const uint8_t value)
{
    uint8_t cmd_byte;

    gpio_set(ds1302->DS1302_CE_Pin, 1);

    cmd_byte = (0x80 | (reg << 1));
    DS1302_writeOut(ds1302, cmd_byte, DEF_false);
    DS1302_writeOut(ds1302, value, DEF_false);

    gpio_set(ds1302->DS1302_SCL_Pin, 0);
    gpio_set(ds1302->DS1302_CE_Pin, 0);
}

void DS1302_writeProtect(DS1302* ds1302, const uint8_t enable)
{
    gpio_set(ds1302->DS1302_CE_Pin, 1);
    DS1302_writeRegister(ds1302, kWriteProtectReg, (enable << 7));
    gpio_set(ds1302->DS1302_CE_Pin, 0);
}

void DS1302_halt(DS1302* ds1302, const uint8_t enable)
{
    uint8_t sec;
    gpio_set(ds1302->DS1302_CE_Pin, 1);
    sec = DS1302_readRegister(ds1302, kSecondReg);
    sec &= ~(1 << 7);
    sec |= (enable << 7);
    DS1302_writeRegister(ds1302, kSecondReg, sec);
    gpio_set(ds1302->DS1302_CE_Pin, 0);
}


void DS1302_writeRam(DS1302* ds1302, const uint8_t address, const uint8_t value)
{
    if (address >= kRamSize) {
        return;
    }

    DS1302_writeRegister(ds1302, kRamAddress0 + address, value);
}

uint8_t DS1302_readRam(DS1302* ds1302, const uint8_t address)
{
    if (address >= kRamSize) {
        return 0;
    }

    return DS1302_readRegister(ds1302, kRamAddress0 + address);
}

void DS1302_writeRamBulk(DS1302* ds1302, const uint8_t* const data, int len)
{
    if (len <= 0) {
        return;
    }
    if (len > kRamSize) {
        len = kRamSize;
    }

    DS1302_writeOut(ds1302, kRamBurstWrite, DEF_false);
    for (int i = 0; i < len; ++i) {
        DS1302_writeOut(ds1302, data[i], DEF_false);
    }
}

void DS1302_readRamBulk(DS1302* ds1302, uint8_t* const data, int len)
{
    if (len <= 0) {
        return;
    }
    if (len > kRamSize) {
        len = kRamSize;
    }

    DS1302_writeOut(ds1302, kRamBurstRead, DEF_true);
    for (int i = 0; i < len; ++i) {
        data[i] = DS1302_readIn(ds1302);
    }
}

void DS1302_timeRead(DS1302* ds1302, DS1302_Time* time)
{
    uint8_t time_buf_reg[8];
    
    gpio_set(ds1302->DS1302_CE_Pin, 1);

    time_buf_reg[7] = DS1302_readRegister(ds1302, kSecondReg)& 0x7F;  //sec
    time_buf_reg[6] = DS1302_readRegister(ds1302, kMinuteReg);  //min
    time_buf_reg[5] = DS1302_readRegister(ds1302, kHourReg);    //hr
    time_buf_reg[4] = DS1302_readRegister(ds1302, kDateReg);    //date
    time_buf_reg[3] = DS1302_readRegister(ds1302, kMonthReg);    //mon
    time_buf_reg[2] = DS1302_readRegister(ds1302, kDayReg);      //day
    time_buf_reg[1] = DS1302_readRegister(ds1302, kYearReg);    //yr
    /*
    time_buf_reg[7] = DS1302_readIn() & 0x7F;  //sec
    time_buf_reg[6] = DS1302_readIn();          //min
    time_buf_reg[5] = DS1302_readIn();          //hr
    time_buf_reg[4] = DS1302_readIn();          //date
    time_buf_reg[3] = DS1302_readIn();          //mon
    time_buf_reg[2] = DS1302_readIn();          //day
    time_buf_reg[1] = DS1302_readIn();          //yr
    */

    time->year  = 2000 + bcdToDec(time_buf_reg[1]);
    time->day   = bcdToDec(time_buf_reg[2]);
    time->month = bcdToDec(time_buf_reg[3]);
    time->date  = bcdToDec(time_buf_reg[4]);
    time->hour  = hourFromRegisterValue(time_buf_reg[5]);
    time->minute = bcdToDec(time_buf_reg[6]);
    time->second = bcdToDec(time_buf_reg[7]);

    gpio_set(ds1302->DS1302_SCL_Pin, 0);
    gpio_set(ds1302->DS1302_CE_Pin, 0);
}

void DS1302_timeWrite(DS1302* ds1302, DS1302_Time* time)
{

    // We want to maintain the Clock Halt flag if it is set.
    uint8_t ch_value;

    gpio_set(ds1302->DS1302_CE_Pin, 1);

    ch_value = DS1302_readRegister(ds1302, kSecondReg) & 0x80;

    //DS1302_writeRegister(kSecondReg, decToBcd(b_second));      
    DS1302_writeRegister(ds1302, kSecondReg,ch_value | decToBcd(time->second));
    DS1302_writeRegister(ds1302, kMinuteReg,decToBcd(time->minute));
    DS1302_writeRegister(ds1302, kHourReg,decToBcd(time->hour));
    DS1302_writeRegister(ds1302, kDateReg,decToBcd(time->date));
    DS1302_writeRegister(ds1302, kMonthReg,decToBcd(time->month));
    DS1302_writeRegister(ds1302, kDayReg ,decToBcd(time->day));
    DS1302_writeRegister(ds1302, kYearReg,decToBcd(time->year - 2000));
    /*
    DS1302_writeOut(kClockBurstWrite, DEF_false);
    DS1302_writeOut(ch_value | decToBcd(b_second), DEF_false);
    DS1302_writeOut(decToBcd(b_minute), DEF_false);
    DS1302_writeOut(decToBcd(b_hour), DEF_false);
    DS1302_writeOut(decToBcd(b_date), DEF_false);
    DS1302_writeOut(decToBcd(b_month), DEF_false);
    DS1302_writeOut(decToBcd(b_day), DEF_false);
    DS1302_writeOut(decToBcd(b_year - 2000), DEF_false);
    // All clock registers *and* the WP register have to be written for the time
    // to be set.
    DS1302_writeOut(0, DEF_false);  // Write protection register.
    DS1302_writeOut(0, DEF_false);  // Trickle Charge register.
    */

    gpio_set(ds1302->DS1302_SCL_Pin, 0);
    gpio_set(ds1302->DS1302_CE_Pin, 0);
}