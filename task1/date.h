#ifndef DATE_H
#define DATE_H

#include <bits/stdc++.h>
#include <ctime>
typedef unsigned short ushort;
typedef unsigned int uint;
constexpr ushort kMonthNumber = 12;
constexpr ushort kFebruaryLeapDay = 29;
constexpr ushort kFebruaryNotLeapDay = 28;
constexpr ushort kLastLongMonthDayNumber = 31;
constexpr ushort kLastDefaultMonthDayNumber = 30;
constexpr ushort kLastMonthNumber = 12;
constexpr ushort kDivisibleBy100 = 100;
constexpr ushort kDivisibleBy400 = 400;
constexpr ushort kDefaultYear = 365;
constexpr ushort kLongYear = 366;
constexpr ushort kWeekDaysNumber = 7;
using namespace std;

class Date {
  ushort day_, month_, year_;
  ushort GetDayInMonth(ushort month_number);

 public:
  static constexpr ushort kDaysInMonth[12] = {31, 28, 31, 30, 31, 30,
                                              31, 31, 30, 31, 30, 31};

  Date(ushort day, ushort month, ushort year);

  Date();

  void setDay(ushort day_to_save);

  void setMonth(ushort month_to_save);

  void setYear(ushort year_to_save);

  ushort getDay();

  ushort getMonth();

  ushort getYear();

  bool IsLeap();

  Date NextDay();

  Date PreviousDay();

  Date ThisDay();

  ushort WeekNumber();

  ushort DaysTillYourBirthday(Date birthday_date);

  uint Duration(Date date);
};
#endif  //DATE_H
