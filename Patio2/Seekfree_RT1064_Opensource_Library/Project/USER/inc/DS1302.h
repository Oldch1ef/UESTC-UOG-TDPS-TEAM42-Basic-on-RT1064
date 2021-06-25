#ifndef CLOCK_L4_DS1302_H
#define CLOCK_L4_DS1302_H

#include "zf_gpio.h"

#define DEF_true  1
#define DEF_false 0


#define kRamSize 31

typedef struct
{
    PIN_enum DS1302_SCL_Pin;
		PIN_enum DS1302_SDA_Pin;
    PIN_enum DS1302_CE_Pin;
}DS1302;

typedef enum
{
    kSecondReg       = 0,
    kMinuteReg       = 1,
    kHourReg         = 2,
    kDateReg         = 3,
    kMonthReg        = 4,
    kDayReg          = 5,
    kYearReg         = 6,
    kWriteProtectReg = 7,
    kChargeReg		 = 8,

    // The RAM register space follows the clock register space.
    kRamAddress0     = 32
} DS1302_Register;

typedef enum
{
    kClockBurstRead  = 0xBF,
    kClockBurstWrite = 0xBE,
    kRamBurstRead    = 0xFF,
    kRamBurstWrite   = 0xFE
} DS1302_Command;

typedef enum
{
    kSunday    = 1,
    kMonday    = 2,
    kTuesday   = 3,
    kWednesday = 4,
    kThursday  = 5,
    kFriday    = 6,
    kSaturday  = 7
} DS1302_Day;

typedef struct
{
    int year;
    int month;
    int date;
    int hour;
    int minute;
    int second;
    int day;
} DS1302_Time;

//Top layer function
void DS1302_timeRead(DS1302* ds1302, DS1302_Time* time) ;
void DS1302_timeWrite(DS1302* ds1302, DS1302_Time* time) ;


#endif //CLOCK_L4_DS1302_H
