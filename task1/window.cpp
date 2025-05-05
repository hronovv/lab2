#include "window.h"

Window::Window() {
  date_array_ = nullptr;
  QString button_style = R"(
        QPushButton {
            background-color: #ffffff; /* Белый фон */
            border: 2px solid #000000; /* Черная рамка */
            color: #000000; /* Черный текст */
            padding: 10px 20px; /* Отступы */
            font-size: 13px; /* Размер шрифта */
            margin: 5px; /* Отступы между кнопками */
            border-radius: 5px; /* Немного закругленные углы */
        }
        QPushButton:hover {
            background-color: #f0f0f0; /* Цвет фона при наведении */
        }
        QPushButton:pressed {
            background-color: #d0d0d0; /* Цвет фона при нажатии */
            color: #333333; /* Темный текст при нажатии */
        }
    )";
  QString text_edit_style = R"(
            font-size: 15px;
            background-color: #f9f9f9;
            color: #000000;
            border: 2px solid #000000; /* Черная рамка */
            border-radius: 5px; /*  закругленные углы */
        )";
  QString text_birth_edit_style = R"(
            font-size: 12px;
            background-color: #f9f9f9;
            color: #000000;
            border: 2px solid #000000; /* Черная рамка */
            border-radius: 5px; /*  закругленные углы */
        )";

  auto* open_button = new QPushButton("Открыть текстовый файл", this);
  open_button->setFixedSize(width, heigth);
  open_button->setStyleSheet(button_style);
  connect(open_button, &QPushButton::clicked, this, &Window::fileOpen);

  auto* next_day_button = new QPushButton("Вычислить следующий день", this);
  next_day_button->setFixedSize(width, heigth);
  next_day_button->setStyleSheet(button_style);
  connect(next_day_button, &QPushButton::clicked, this, &Window::outputNextDay);

  auto* previous_day_button = new QPushButton("Вычислить пред. день", this);
  previous_day_button->setFixedSize(width, heigth);
  previous_day_button->setStyleSheet(button_style);
  connect(previous_day_button, &QPushButton::clicked, this,
          &Window::outputPreviousDay);

  auto* diff_day_button = new QPushButton("Вычислить разницу", this);
  diff_day_button->setFixedSize(width, heigth);
  diff_day_button->setStyleSheet(button_style);
  connect(diff_day_button, &QPushButton::clicked, this, &Window::outputDiffDay);

  auto* week_button = new QPushButton("Показать № недели", this);
  week_button->setFixedSize(width, heigth);
  week_button->setStyleSheet(button_style);
  connect(week_button, &QPushButton::clicked, this, &Window::outputWeekDay);

  auto* edit_button = new QPushButton("Изменить даты", this);
  edit_button->setFixedSize(width, heigth);
  edit_button->setStyleSheet(button_style);
  connect(edit_button, &QPushButton::clicked, this, &Window::editDates);

  auto* save_button = new QPushButton("Сохранить изменения", this);
  save_button->setFixedSize(width, heigth);
  save_button->setStyleSheet(button_style);
  connect(save_button, &QPushButton::clicked, this, &Window::saveChanges);

  auto* clear_button = new QPushButton("Сбросить файл", this);
  clear_button->setFixedSize(width, heigth);
  clear_button->setStyleSheet(button_style);
  connect(clear_button, &QPushButton::clicked, this, &Window::clearFile);

  auto* add_date_button = new QPushButton("Добавить дату", this);
  add_date_button->setFixedSize(width, heigth);
  add_date_button->setStyleSheet(button_style);
  connect(add_date_button, &QPushButton::clicked, this, &Window::onAddDate);

  auto* change_date_button = new QPushButton("Изменить дату", this);
  change_date_button->setFixedSize(width, heigth);
  change_date_button->setStyleSheet(button_style);
  connect(change_date_button, &QPushButton::clicked, this,
          &Window::onChangeDate);

  auto* diff_to_birthday_button = new QPushButton("Разница до ДР", this);
  diff_to_birthday_button->setFixedSize(width, heigth);
  diff_to_birthday_button->setStyleSheet(button_style);
  connect(diff_to_birthday_button, &QPushButton::clicked, this,
          &Window::outputDiffToBirthday);

  birthdayInput_ = new QLineEdit(this);
  birthdayInput_->setPlaceholderText("Введите дату рождения (дд.мм.гггг)");
  birthdayInput_->setFixedSize(width, birthday_heigth);
  birthdayInput_->setStyleSheet(text_birth_edit_style);

  auto* set_birthday_button = new QPushButton("Установить дату рождения", this);
  set_birthday_button->setFixedSize(width, heigth);
  set_birthday_button->setStyleSheet(button_style);
  connect(set_birthday_button, &QPushButton::clicked, this,
          &Window::setBirthday);

  textEdit1_ = new QTextEdit(this);
  textEdit1_->setReadOnly(true);
  textEdit1_->setStyleSheet(text_edit_style);
  textEdit1_->setFixedSize(width, field_heigth);

  textEdit2_ = new QTextEdit(this);
  textEdit2_->setReadOnly(true);
  textEdit2_->setStyleSheet(text_edit_style);
  textEdit2_->setFixedSize(width, field_heigth);

  textEdit3_ = new QTextEdit(this);
  textEdit3_->setReadOnly(true);
  textEdit3_->setStyleSheet(text_edit_style);
  textEdit3_->setFixedSize(width, field_heigth);

  textEdit4_ = new QTextEdit(this);
  textEdit4_->setReadOnly(true);
  textEdit4_->setStyleSheet(text_edit_style);
  textEdit4_->setFixedSize(width, field_heigth);

  textEdit5_ = new QTextEdit(this);
  textEdit5_->setReadOnly(true);
  textEdit5_->setStyleSheet(text_edit_style);
  textEdit5_->setFixedSize(width, field_heigth);

  textEdit6_ = new QTextEdit(this);
  textEdit6_->setReadOnly(true);
  textEdit6_->setStyleSheet(text_edit_style);
  textEdit6_->setFixedSize(width, field_heigth);

  auto* layout = new QGridLayout();
  layout->addWidget(open_button, 0, 0);
  layout->addWidget(next_day_button, 0, 1);
  layout->addWidget(diff_day_button, 0, 2);
  layout->addWidget(previous_day_button, 0, 3);
  layout->addWidget(week_button, 0, 4);
  layout->addWidget(edit_button, 2, 0);
  layout->addWidget(save_button, 3, 0);
  layout->addWidget(clear_button, 4, 0);
  layout->addWidget(add_date_button, 4 + 1, 0);
  layout->addWidget(change_date_button, 4 + 2, 0);
  layout->addWidget(week_button, 0, 4);
  layout->addWidget(textEdit1_, 1, 0);
  layout->addWidget(textEdit2_, 1, 1);
  layout->addWidget(textEdit3_, 1, 2);
  layout->addWidget(textEdit4_, 1, 3);
  layout->addWidget(textEdit5_, 1, 4);
  layout->addWidget(textEdit6_, 1, 4 + 1);
  layout->addWidget(birthdayInput_, 2, 1);
  layout->addWidget(set_birthday_button, 3, 1);
  layout->addWidget(diff_to_birthday_button, 0, 4 + 1);
  layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
  layout->setContentsMargins(margin, margin, margin, margin);
  setLayout(layout);
}

Window::~Window() {
  // Освобождение памяти
  for (int i = 0; i < kDateNumber_; i++) {
    delete date_array_[i];
  }
  delete[] date_array_;
}

void Window::fileOpen() {
  QString file_name = QFileDialog::getOpenFileName(
      this, "Откройте текстовый файл", "", "Text Files (*.txt)");
  if (!file_name.isEmpty()) {
    try {
      currentFileName_ = file_name;
      QTextStream stream;
      QFile file(file_name);
      int line_count = 0;
      if (file.open(QFile::ReadOnly | QFile::Text)) {
        stream.setDevice(&file);
        while (!stream.atEnd()) {
          stream.readLine();
          line_count++;
        }
        file.close();
      }
      delete[] date_array_;
      kDateNumber_ = line_count;
      date_array_ = new Date*[kDateNumber_];
      for (int i = 0; i < kDateNumber_; i++) {
        date_array_[i] = new Date();
      }
      if (file.open(QFile::ReadOnly)) {
        QTextStream fstream(&file);
        for (int i = 0; i < kDateNumber_; i++) {
          QString line = fstream.readLine();
          line.replace('.', ' ');  // Заменяем '.' на пробел
          std::stringstream new_line(line.toStdString());
          unsigned short day, month, year;
          new_line >> day >> month >> year;  // Читаем день, месяц, год
          date_array_[i]->setDay(day);
          date_array_[i]->setMonth(month);
          date_array_[i]->setYear(year);
        }
        file.close();
        dataLoaded_ = true;
      }
      textEdit1_->clear();
      textEdit2_->clear();
      textEdit3_->clear();
      textEdit4_->clear();
      textEdit5_->clear();
      textEdit6_->clear();
      for (int i = 0; i < kDateNumber_; i++) {
        QString date_info =
            QString("%1.%2.%3")
                .arg(date_array_[i]->getDay(), 2, base_of_number,
                     QLatin1Char('0'))  // День с нулём
                .arg(date_array_[i]->getMonth(), 2, base_of_number,
                     QLatin1Char('0'))  // Месяц с нулём
                .arg(date_array_[i]->getYear(), 4, base_of_number,
                     QLatin1Char('0'));  // Год с нулём
        textEdit1_->append(date_info);
      }
    } catch (const std::exception& e) {
      QMessageBox::warning(this, "Ошибка", e.what(), QMessageBox::Ok);
    }
  }
}

void Window::outputNextDay() {
  if (!currentFileName_.isEmpty()) {
    textEdit2_->clear();
    if (dataLoaded_) {
      for (int i = 0; i < kDateNumber_; i++) {
        Date date_next_day = date_array_[i]->NextDay();
        QString date_info =
            QString("%1.%2.%3")
                .arg(date_next_day.getDay(), 2, base_of_number,
                     QLatin1Char('0'))  // День с нулём
                .arg(date_next_day.getMonth(), 2, base_of_number,
                     QLatin1Char('0'))  // Месяц с нулём
                .arg(date_next_day.getYear(), 4, base_of_number,
                     QLatin1Char('0'));
        textEdit2_->append(date_info);
      }
    }
  } else {
    QMessageBox::warning(this, "Ошибка", "Ошибка. Выберите файл.",
                         QMessageBox::Ok);
  }
}

void Window::outputPreviousDay() {
  if (!currentFileName_.isEmpty()) {
    textEdit4_->clear();
    if (dataLoaded_) {
      for (int i = 0; i < kDateNumber_; i++) {
        Date date_previous_day = date_array_[i]->PreviousDay();
        QString date_info = QString("%1.%2.%3")
                                .arg(date_previous_day.getDay(), 2,
                                     base_of_number, QLatin1Char('0'))
                                .arg(date_previous_day.getMonth(), 2,
                                     base_of_number, QLatin1Char('0'))
                                .arg(date_previous_day.getYear(), 4,
                                     base_of_number, QLatin1Char('0'));
        textEdit4_->append(date_info);
      }
    }
  } else {
    QMessageBox::warning(this, "Ошибка", "Ошибка. Выберите файл.",
                         QMessageBox::Ok);
  }
}

void Window::outputDiffDay() {
  if (!currentFileName_.isEmpty()) {
    textEdit3_->clear();
    if (dataLoaded_) {
      for (int i = 0; i < kDateNumber_ - 1; i++) {
        QString date_info =
            QString("%1").arg(date_array_[i]->Duration(*date_array_[i + 1]));
        textEdit3_->append(date_info);
      }
    }
  } else {
    QMessageBox::warning(this, "Ошибка", "Ошибка. Выберите файл.",
                         QMessageBox::Ok);
  }
}

void Window::outputWeekDay() {
  if (!currentFileName_.isEmpty()) {
    textEdit5_->clear();
    if (dataLoaded_) {
      for (int i = 0; i < kDateNumber_; i++) {
        QString date_info = QString("%1").arg(date_array_[i]->WeekNumber());
        textEdit5_->append(date_info);
      }
    }
  } else {
    QMessageBox::warning(this, "Ошибка", "Ошибка. Выберите файл.",
                         QMessageBox::Ok);
  }
}

void Window::editDates() {
  if (!currentFileName_.isEmpty()) {
    bool is_read_only = textEdit1_->isReadOnly();
    textEdit1_->setReadOnly(!is_read_only);  // Изменяем состояние
    if (!is_read_only) {
      textEdit1_->setFocus();  // Устанавливаем фокус на текстовое поле
    }
  } else {
    QMessageBox::warning(this, "Ошибка",
                         "Ошибка. Выберите файл для редактирования.",
                         QMessageBox::Ok);
  }
}

void Window::saveChanges() {
  if (!currentFileName_.isEmpty() && !textEdit1_->isReadOnly()) {

    try {
      QFile file(currentFileName_);

      if (file.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream out(&file);
        out << textEdit1_
                   ->toPlainText();  // Сохранить текст из первого текстового поля
        file.close();                // Закрыть файл после записи
      }

      clearFields();
      textEdit1_->setReadOnly(true);

      if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        int line_count = 0;

        while (!stream.atEnd()) {
          stream.readLine();
          line_count++;
        }

        delete[] date_array_;

        kDateNumber_ = line_count;
        date_array_ = new Date*[kDateNumber_];

        file.seek(0);

        for (int i = 0; i < kDateNumber_; i++) {
          QString line = stream.readLine();
          line.replace('.', ' ');  // Заменяем '.' на пробел
          std::stringstream new_line(line.toStdString());
          unsigned short day, month, year;
          if (new_line >> day >> month >> year) {  // Чтение дня, месяца, года
            date_array_[i] = new Date(day, month, year);
          }
        }

        file.close();
      }
    } catch (const std::exception& e) {
      QMessageBox::warning(this, "Ошибка", e.what(), QMessageBox::Ok);
    }
  }
}

void Window::clearFile() {
  currentFileName_ = "";
  textEdit1_->clear();
  textEdit2_->clear();
  textEdit3_->clear();
  textEdit4_->clear();
  textEdit5_->clear();
  textEdit6_->clear();
  textEdit1_->setReadOnly(true);
}

void Window::clearFields() {
  textEdit2_->clear();
  textEdit3_->clear();
  textEdit4_->clear();
  textEdit5_->clear();
  textEdit6_->clear();
}

void Window::onAddDate() {
  if (!currentFileName_.isEmpty()) {
    bool ok;
    QString new_date = QInputDialog::getText(
        this, "Добавить дату", "Введите дату (дд.мм.гггг):", QLineEdit::Normal,
        "", &ok);
    if (ok && !new_date.isEmpty()) {
      QStringList date_parts = new_date.split('.');
      if (date_parts.size() == 3) {
        bool day_ok, month_ok, year_ok;
        int day = date_parts[0].toInt(&day_ok);
        int month = date_parts[1].toInt(&month_ok);
        int year = date_parts[2].toInt(&year_ok);
        if (day_ok && month_ok && year_ok) {
          if (month < 1 || month > kMonthNumber) {
            QMessageBox::warning(this, "Ошибка",
                                 "Месяц должен быть от 1 до 12.",
                                 QMessageBox::Ok);
            return;
          }
          if (year < 0) {
            QMessageBox::warning(this, "Ошибка",
                                 "Год должен быть положительным.",
                                 QMessageBox::Ok);
            return;
          }
          if (day < 1 || day > GetDayInMonthChecker(year, month)) {
            QMessageBox::warning(
                this, "Ошибка",
                "День вне допустимого диапазона для указанного месяца.",
                QMessageBox::Ok);
            return;
          }

          Date new_date(day, month, year);
          addDate(new_date);
          addDateToFile();        // Сохраняем изменения
          loadDatesToTextEdit();  // Обновляем текстовое поле
        } else {
          QMessageBox::warning(this, "Ошибка", "Введите корректную дату.",
                               QMessageBox::Ok);
        }
      } else {
        QMessageBox::warning(this, "Ошибка",
                             "Введите дату в формате дд.мм.гггг.",
                             QMessageBox::Ok);
      }
    }
  } else {
    QMessageBox::warning(this, "Ошибка",
                         "Ошибка. Выберите файл для добавления даты.",
                         QMessageBox::Ok);
  }
}

void Window::onChangeDate() {
  if (!currentFileName_.isEmpty() && dataLoaded_) {
    bool ok;
    int index = QInputDialog::getInt(this, "Изменить дату",
                                     "Введите индекс (начиная с 0):", 0, 0,
                                     kDateNumber_ - 1, 1, &ok);

    if (ok) {
      QString new_date = QInputDialog::getText(
          this, "Введите новую дату",
          "Введите дату (дд.мм.гггг):", QLineEdit::Normal, "", &ok);
      if (ok && !new_date.isEmpty()) {
        QStringList date_parts = new_date.split('.');
        if (date_parts.size() == 3) {
          bool day_ok, month_ok, year_ok;
          int day = date_parts[0].toInt(&day_ok);
          int month = date_parts[1].toInt(&month_ok);
          int year = date_parts[2].toInt(&year_ok);
          if (day_ok && month_ok && year_ok) {
            if (month < 1 || month > kMonthNumber) {
              QMessageBox::warning(this, "Ошибка",
                                   "Месяц должен быть от 1 до 12.",
                                   QMessageBox::Ok);
              return;
            }
            if (year < 0) {
              QMessageBox::warning(this, "Ошибка",
                                   "Год должен быть положительным.",
                                   QMessageBox::Ok);
              return;
            }
            if (day < 1 || day > GetDayInMonthChecker(year, month)) {
              QMessageBox::warning(
                  this, "Ошибка",
                  "День вне допустимого диапазона для указанного месяца.",
                  QMessageBox::Ok);
              return;
            }
            date_array_[index]->setDay(day);
            date_array_[index]->setMonth(month);
            date_array_[index]->setYear(year);
            changeDateInFile(index);
            loadDatesToTextEdit();
          } else {
            QMessageBox::warning(this, "Ошибка", "Введите корректную дату.",
                                 QMessageBox::Ok);
          }
        } else {
          QMessageBox::warning(this, "Ошибка",
                               "Введите дату в формате дд.мм.гггг.",
                               QMessageBox::Ok);
        }
      }
    }
  } else {
    QMessageBox::warning(this, "Ошибка",
                         "Ошибка. Выберите файл для изменения даты.",
                         QMessageBox::Ok);
  }
}

void Window::loadDatesToTextEdit() {
  textEdit1_->clear();
  clearFields();
  for (int i = 0; i < kDateNumber_; i++) {
    QString date_info =
        QString("%1.%2.%3")
            .arg(date_array_[i]->getDay(), 2, base_of_number, QLatin1Char('0'))
            .arg(date_array_[i]->getMonth(), 2, base_of_number,
                 QLatin1Char('0'))
            .arg(date_array_[i]->getYear(), 4, base_of_number,
                 QLatin1Char('0'));
    textEdit1_->append(date_info);
  }
}

void Window::changeDateInFile(int index) {
  if (!currentFileName_.isEmpty()) {
    QFile file(currentFileName_);
    if (file.open(QFile::ReadWrite | QFile::Text)) {
      QTextStream stream(&file);
      QString line = stream.readLine();  // Читаем первую строку
      int size = line.toUtf8().size();
      file.seek(index * (size + 1));
      QString date_info = QString("%1.%2.%3")
                              .arg(date_array_[index]->getDay(), 2,
                                   base_of_number, QLatin1Char('0'))
                              .arg(date_array_[index]->getMonth(), 2,
                                   base_of_number, QLatin1Char('0'))
                              .arg(date_array_[index]->getYear(), 4,
                                   base_of_number, QLatin1Char('0'));
      QTextStream out(&file);
      out << date_info;
    }
  }
}

ushort Window::GetDayInMonthChecker(ushort year, ushort month) {
  if (month < 1 || month > kMonthNumber) {
    return 0;
  }
  int days_in_month[] = {
      kLastLongMonthDayNumber,    kFebruaryNotLeapDay + (IsLeap(year) ? 1 : 0),
      kLastLongMonthDayNumber,    kLastDefaultMonthDayNumber,
      kLastLongMonthDayNumber,    kLastDefaultMonthDayNumber,
      kLastLongMonthDayNumber,    kLastLongMonthDayNumber,
      kLastDefaultMonthDayNumber, kLastLongMonthDayNumber,
      kLastDefaultMonthDayNumber, kLastLongMonthDayNumber};
  return days_in_month[month - 1];
}

bool Window::IsLeap(ushort year) {
  return (year % 4 == 0 && year % kDivisibleBy100 != 0) ||
         (year % kDivisibleBy400 == 0);
}

void Window::addDate(const Date& newDate) {
  Date** new_date_array = new Date*[kDateNumber_ + 1];
  for (int i = 0; i < kDateNumber_; i++) {
    new_date_array[i] = date_array_[i];
  }
  new_date_array[kDateNumber_] = new Date(newDate);
  delete[] date_array_;
  date_array_ = new_date_array;
  kDateNumber_++;
}

void Window::addDateToFile() {
  if (!currentFileName_.isEmpty()) {  // Проверяем, что файл открыт
    QFile file(currentFileName_);
    if (file.open(QFile::Append | QFile::Text)) {
      QString date_info = QString("%1.%2.%3")
                              .arg(date_array_[kDateNumber_ - 1]->getDay(), 2,
                                   base_of_number, QLatin1Char('0'))
                              .arg(date_array_[kDateNumber_ - 1]->getMonth(), 2,
                                   base_of_number, QLatin1Char('0'))
                              .arg(date_array_[kDateNumber_ - 1]->getYear(), 4,
                                   base_of_number, QLatin1Char('0'));
      QTextStream out(&file);
      out << "\n" << date_info;
      file.close();
    }
  }
}

void Window::setBirthday() {
  bool ok;
  QString date_str = birthdayInput_->text();
  QStringList date_parts = date_str.split('.');

  if (date_parts.size() == 3) {
    bool day_ok, month_ok, year_ok;
    int day = date_parts[0].toInt(&day_ok);
    int month = date_parts[1].toInt(&month_ok);
    int year = date_parts[2].toInt(&year_ok);
    if (day_ok && month_ok && year_ok) {
      if (month < 1 || month > kMonthNumber) {
        QMessageBox::warning(this, "Ошибка", "Месяц должен быть от 1 до 12.",
                             QMessageBox::Ok);
        return;
      }
      if (year < 0) {
        QMessageBox::warning(this, "Ошибка", "Год должен быть положительным.",
                             QMessageBox::Ok);
        return;
      }
      if (day < 1 || day > GetDayInMonthChecker(year, month)) {
        QMessageBox::warning(
            this, "Ошибка",
            "День вне допустимого диапазона для указанного месяца.",
            QMessageBox::Ok);
        return;
      }

      // Сохранение даты рождения
      birthday_date_ = new Date(day, month, year);

      // Форматирование даты для вывода
      QString formatted_date =
          QString("%1.%2.%3")
              .arg(day, 2, base_of_number, QLatin1Char('0'))  // День с нулём
              .arg(month, 2, base_of_number,
                   QLatin1Char('0'))  // Месяц с нулём
              .arg(year, 4, base_of_number,
                   QLatin1Char('0'));  // Год с четырьмя цифрами

      QMessageBox::information(this, "Успех",
                               "Дата рождения установлена: " + formatted_date);
      birthdayInput_->clear();  // Очистка поля ввода после сохранения
    } else {
      QMessageBox::warning(this, "Ошибка", "Введите корректную дату.",
                           QMessageBox::Ok);
    }
  } else {
    QMessageBox::warning(this, "Ошибка", "Введите дату в формате дд.мм.гггг.",
                         QMessageBox::Ok);
  }
}

void Window::outputDiffToBirthday() {
  if ((birthday_date_ == nullptr) || currentFileName_.isEmpty()) {
    QMessageBox::warning(this, "Ошибка",
                         "Выберите файл и установите дату рождения.",
                         QMessageBox::Ok);
    return;
  }
  textEdit6_->clear();
  for (int i = 0; i < kDateNumber_; ++i) {
    ushort days_until_birthday =
        date_array_[i]->DaysTillYourBirthday(*birthday_date_);
    QString output = QString("%1").arg(days_until_birthday);
    textEdit6_->append(output);  // Добавляем строку в текстовое поле
  }
}
