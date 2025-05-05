#ifndef WINDOW_H
#define WINDOW_H
#include <QApplication>
#include <QFileDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QTextEdit>
#include <sstream>
#include "QInputDialog"
#include "QMessageBox"
#include "date.h"
#define width 235
#define heigth 55
#define field_heigth 300
#define birthday_heigth 45
#define base_of_number 10
#define margin 10
#endif  //WINDOW_H

class Window : public QWidget {
  Q_OBJECT

 public:
  Window();            // конструктор для отображения кнопок и прочего
  ~Window() override;  // деструктор с удалением массива классов
 public slots:
  void fileOpen();           // функция открытия файла
  void outputNextDay();      // функция вывода в поле следующего дня даты
  void outputPreviousDay();  // функция вывода в поле предыдущего дня даты
  void
  outputDiffDay();  // функция вывода в поле разницы со следующим элементом коллекции
  void outputWeekDay();  // аналогично с днем недели
  void
  editDates();  // функция редактирования дат внутри приложения с перезаписью
  void saveChanges();                // функция сохранения изменений
  void clearFile();                  // очистка полей и имени файла
  void clearFields();                // очистка при открытии другого файла
  void onAddDate();                  // добавление даты без перезаписи
  void onChangeDate();               // изменение даты без перезаписи
  void loadDatesToTextEdit();        // загрузка любых изменений в поле
  void changeDateInFile(int index);  // изменение без перезаписи
  ushort GetDayInMonthChecker(
      ushort year,
      ushort month);         // проверка даты при добавлении или изменении даты
  bool IsLeap(ushort year);  // проверка на високосный для проверки даты
  void addDate(const Date& newDate);  // добавление даты в массив
  void addDateToFile();               // добавление даты в файл без перезаписи
  void setBirthday();                 // функция установки дня рождения
  void outputDiffToBirthday();        // вывод разницы до др
 private:
  QTextEdit* textEdit1_;
  QTextEdit* textEdit2_;
  QTextEdit* textEdit3_;
  QTextEdit* textEdit4_;
  QTextEdit* textEdit5_;
  QTextEdit* textEdit6_;
  Date** date_array_;
  Date* birthday_date_;
  uint kDateNumber_{0};
  bool dataLoaded_{false};
  QString currentFileName_{""};
  QLineEdit* birthdayInput_;
};
