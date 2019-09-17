#include "../../utils/loso_utils.c"

#define INVALID_DATE -1

static char nonLeapYears[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static char leapYears[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static char *daytab[] = {nonLeapYears, leapYears};

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
    char _day = *(*(daytab + isLeap) + month);
    if (_day < day)
    {
        return INVALID_DATE;
    }

    for (uint32 monthIndex = 1; monthIndex < month; ++monthIndex)
    {
        day += *(*(daytab + isLeap) + monthIndex);
    }

    return day;
}

void MonthDay(uint32 year, uint32 yearDay, int32* pMonth, int32 *pDay)
{
    uint32 monthIndex = 0;
    int32 isLeap = IsLeapYear(year);

    if (yearDay == 0 || isLeap && yearDay > 366 || !isLeap && yearDay > 365)
    {
        *pMonth = *pDay = INVALID_DATE;
        return;
    }

    for (monthIndex = 1; yearDay > *(*(daytab + isLeap) + monthIndex); ++monthIndex)
    {
        yearDay -= *(*(daytab + isLeap) + monthIndex);
    }

    *pMonth = monthIndex;
    *pDay = yearDay;
}

int main()
{
    assert(DayOfYear(1988, 3, 1) == 61);
    assert(DayOfYear(1989, 3, 1) == 60);
    assert(DayOfYear(1988, 3, 32) == INVALID_DATE);
    assert(DayOfYear(1988, -3, -29) == INVALID_DATE);

    int32 pDay, pMonth;
    MonthDay(1988, 61, &pMonth, &pDay);
    assert(pMonth == 3 && pDay == 1);

    MonthDay(1989, 60, &pMonth, &pDay);
    assert(pMonth == 3 && pDay == 1);

    MonthDay(1989, 366, &pMonth, &pDay);
    assert(pMonth == INVALID_DATE && pDay == INVALID_DATE);
    
    MonthDay(1989, 366, &pMonth, &pDay);
    assert(pMonth == INVALID_DATE && pDay == INVALID_DATE);

    MonthDay(1988, 366, &pMonth, &pDay);
    assert(pMonth == 12 && pDay == 31);
}