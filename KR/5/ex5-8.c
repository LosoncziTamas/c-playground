#include "../../utils/loso_utils.c"

#define INVALID_DATE -1

static char daytab[2][13] =
{
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

static inline uint32 IsLeapYear(uint32 year)
{
    return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}

int32 DayOfYear(uint32 year, uint32 month, uint32 day)
{
    if (year == 0 || month == 0 || month > 12)
    {
        return INVALID_DATE;
    }

    uint32 isLeap = IsLeapYear(year);
    if (daytab[isLeap][month] < day)
    {
        return INVALID_DATE;
    }

    for (uint32 monthIndex = 1; monthIndex < month; ++monthIndex)
    {
        day += daytab[isLeap][monthIndex];
    }

    return day;
}

void MonthDay(uint32 year, uint32 yearDay, int* pMonth, int *pDay)
{
    uint32 monthIndex = 0;
    int32 isLeap = IsLeapYear(year);

    if (isLeap && yearDay > 366 || !isLeap && year > 365)
    {
        *pMonth = *pDay = INVALID_DATE;
    }

    for (monthIndex = 1; yearDay > daytab[isLeap][monthIndex]; ++monthIndex)
    {
        yearDay -= daytab[isLeap][monthIndex];
    }

    *pMonth = monthIndex;
    *pDay = yearDay;
}

int main()
{
    assert(DayOfYear(1988, 3, 1) == 61);
    assert(DayOfYear(1988, 3, 32) == INVALID_DATE);
    // TODO: signed or unsigned
    assert(DayOfYear(1988, -3, -29) == INVALID_DATE);
    // TODO: test MonthDay

}