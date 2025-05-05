#ifndef WINDOW_H
#define WINDOW_H
#include <QApplication>
#include <QFileDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QTextEdit>
#include <sstream>
#include "QComboBox"
#include "QInputDialog"
#include "QMessageBox"
#include "student.h"
#define width 265
#define heigth 55
#define margin 10
#define max_grade 10
#define windowSize 1600
#define fieldSize 400

class Window : public QWidget {
  Q_OBJECT

 public:
  Window();
  ~Window() override;
 public slots:

  void fileOpen();  //открытие файла

  void addStudent();  //форма добавления студента

  void addStudentToArray(const Student& newStudent);  // в массив

  void saveChanges();  // сохранение любых изменений

  void addStudentToFile();  // добавление студента в файл без перезаписи

  void sortGroupStudents();  //сортировка студентов в группе

  void deleteStudent();  // удаление студента

  void findStudent();  //функция поиска студента

  void showGoodStudents();  // вывод студентов с оценками >=4

  void sortAllStudents();  // сортировка всех студентов

  void displayStudents();  // вывод всех студентов в форму

  void editStudent();  // изменение студента

  void clearFile();  // сброс файла

 private:
  QTextEdit* textEdit1_;
  QTextEdit* textEdit2_;
  QTextEdit* textEdit3_;
  QTextEdit* textEdit4_;
  QTextEdit* textEdit5_;
  QTextEdit* textEdit6_;
  Student** student_array_;
  Student* birthday_date_;
  uint StudentsNumber_{0};
  bool dataLoaded_{false};
  QString currentFileName_{""};
};

#endif  //WINDOW_H
