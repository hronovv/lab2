#include "date.h"

Date::Date(ushort day, ushort month, ushort year)
    : day_(day), month_(month), year_(year) {}  // перегрузка конструктора

Date::Date() : day_(1), month_(1), year_(1) {}

ushort Date::GetDayInMonth(ushort month_number) {
  return month_number == 2 && IsLeap() ? kFebruaryLeapDay
                                       : kDaysInMonth[month_number - 1];
}

void Date::setDay(ushort day_to_save) {
  day_ = day_to_save;
}

void Date::setMonth(ushort month_to_save) {
  month_ = month_to_save;
}

void Date::setYear(ushort year_to_save) {
  year_ = year_to_save;
}

ushort Date::getDay() {
  return day_;
}

ushort Date::getMonth() {
  return month_;
}

ushort Date::getYear() {
  return year_;
}

bool Date::IsLeap() {
  return year_ % 4 == 0 &&
         (year_ % kDivisibleBy100 != 0 || year_ % kDivisibleBy400 == 0);
}

Date Date::NextDay() {
  ushort current_days_in_month = GetDayInMonth(month_);
  if (day_ < current_days_in_month) {
    return Date(day_ + 1, month_, year_);
  } else {
    if (month_ == kLastMonthNumber) {
      return Date(1, 1, year_ + 1);  // Переход на 1 января следующего года
    } else {
      return Date(1, month_ + 1,
                  year_);  // Переход на 1 число следующего месяца
    }
  }
}

Date Date::ThisDay() {
  time_t now = time(nullptr);  //кол-во секунд с 1 янв 1970г
  tm* ltm = localtime(&now);   // в структуру tm со своими параметрами
  return Date(ltm->tm_mday, ltm->tm_mon, ltm->tm_year);
}

Date Date::PreviousDay() {
  ushort current_days_in_month = GetDayInMonth(month_);
  if (day_ > 1) {
    return Date(day_ - 1, month_, year_);
  } else {
    if (month_ == 1) {
      return Date(kLastLongMonthDayNumber, kLastMonthNumber, year_ - 1);
    } else {
      return Date(GetDayInMonth(month_ - 1), month_ - 1, year_);
    }
  }
}

ushort Date::WeekNumber() {
  int day_of_year = day_;
  for (int i = 0; i < month_ - 1; ++i) {
    day_of_year += GetDayInMonth(i + 1);
  }
  return ((day_of_year - 1) / kWeekDaysNumber) + 1;
}

ushort Date::DaysTillYourBirthday(Date birthday_date) {
  ushort days_count = 0;

  // Если день рождения еще в этом году
  if (birthday_date.getMonth() > month_ ||
      (birthday_date.getMonth() == month_ && birthday_date.getDay() > day_)) {
    // Если месяц одинаковый, просто вычисляем разницу в днях
    if (birthday_date.getMonth() == month_) {
      days_count = birthday_date.getDay() - day_;
    } else {
      // Остаток дней до конца текущего месяца
      days_count += GetDayInMonth(month_) - day_;

      // Полные месяцы между текущим и днем рождения
      for (ushort i = month_ + 1; i < birthday_date.getMonth(); ++i) {
        days_count += GetDayInMonth(i);
      }

      // Дни в месяце (день рождения)
      days_count += birthday_date.getDay();
    }
  } else {
    // Если день рождения уже прошел в этом году
    // Остаток дней до конца текущего месяца
    days_count += GetDayInMonth(month_) - day_;

    // Полные месяцы после текущего месяца
    for (ushort i = month_ + 1; i <= kLastMonthNumber; ++i) {
      days_count += GetDayInMonth(i);
    }

    // Считаем дни до дня рождения следующего года (январь до месяца дня рождения)
    for (ushort i = 1; i < birthday_date.getMonth(); ++i) {
      days_count += GetDayInMonth(i);
    }

    // Дни в месяце (день рождения)
    days_count += birthday_date.getDay();
  }

  return days_count;
}

uint Date::Duration(Date date) {
  // Сумма дней
  uint total_days = 0;

  // Начало и конец периода
  Date start = *this;
  Date end = date;

  // Убедимся, что start меньше или равен end
  if (start.year_ > end.year_ ||
      (start.year_ == end.year_ && start.month_ > end.month_) ||
      (start.year_ == end.year_ && start.month_ == end.month_ &&
       start.day_ > end.day_)) {
    // Меняем местами
    start = date;  // текущий объект
    end = *this;   // переданная дата
  }

  // Если обе даты в одном году
  if (start.year_ == end.year_) {
    if (start.month_ == end.month_) {
      return end.day_ - start.day_;  // Просто разница в днях
    } else {
      // Остаток дней в месяце старта
      total_days += start.GetDayInMonth(start.month_) - start.day_;
      // Считаем полные месяцы между
      for (ushort m = start.month_ + 1; m < end.month_; ++m) {
        total_days += start.GetDayInMonth(m);
      }
      // Добавляем дни в месяце конца
      total_days += end.day_;
    }
  } else {
    // Остаток дней в месяце старта
    total_days += start.GetDayInMonth(start.month_) - start.day_;
    // Считаем полные месяцы до конца года
    for (ushort m = start.month_ + 1; m <= kLastMonthNumber; ++m) {
      total_days += start.GetDayInMonth(m);
    }
    // Считаем полные годы между
    for (ushort y = start.year_ + 1; y < end.year_; ++y) {
      total_days += (Date(1, 1, y).IsLeap() ? kDefaultYear : kLongYear);
    }
    // Считаем дни в месяце конца
    for (ushort m = 1; m < end.month_; ++m) {
      total_days += end.GetDayInMonth(m);
    }
    // Добавляем дни в месяце конца
    total_days += end.day_;
  }

  return total_days;
}
