#include "window.h"
#include "quicksort.h"

Window::Window() {
  student_array_ = nullptr;
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
            font-size: 14px;
            background-color: #f9f9f9;
            color: #000000;
            border: 2px solid #000000; /* Черная рамка */
            border-radius: 5px; /* Немного закругленные углы */
        )";
  QString text_birth_edit_style = R"(
            font-size: 12px;
            background-color: #f9f9f9;
            color: #000000;
            border: 2px solid #000000; /* Черная рамка */
            border-radius: 5px; /* Немного закругленные углы */
        )";

  auto* open_button = new QPushButton("Открыть текстовый файл", this);
  open_button->setFixedSize(width, heigth);
  open_button->setStyleSheet(button_style);
  connect(open_button, &QPushButton::clicked, this, &Window::fileOpen);

  auto* add_student_button = new QPushButton("Добавить студента", this);
  add_student_button->setFixedSize(width, heigth);
  add_student_button->setStyleSheet(button_style);
  connect(add_student_button, &QPushButton::clicked, this, &Window::addStudent);

  auto* change_student_button = new QPushButton("Изменить студента", this);
  change_student_button->setFixedSize(width, heigth);
  change_student_button->setStyleSheet(button_style);
  connect(change_student_button, &QPushButton::clicked, this,
          &Window::editStudent);

  auto* delete_student_button = new QPushButton("Удалить студента", this);
  delete_student_button->setFixedSize(width, heigth);
  delete_student_button->setStyleSheet(button_style);
  connect(delete_student_button, &QPushButton::clicked, this,
          &Window::deleteStudent);

  auto* sort_all_button = new QPushButton("Сортировать всех", this);
  sort_all_button->setFixedSize(width, heigth);
  sort_all_button->setStyleSheet(button_style);
  connect(sort_all_button, &QPushButton::clicked, this,
          &Window::sortAllStudents);

  auto* sort_group_button = new QPushButton("Сортировать группу", this);
  sort_group_button->setFixedSize(width, heigth);
  sort_group_button->setStyleSheet(button_style);
  connect(sort_group_button, &QPushButton::clicked, this,
          &Window::sortGroupStudents);

  auto* find_studen_button = new QPushButton("Найти студента", this);
  find_studen_button->setFixedSize(width, heigth);
  find_studen_button->setStyleSheet(button_style);
  connect(find_studen_button, &QPushButton::clicked, this,
          &Window::findStudent);

  auto* clear_button = new QPushButton("Сбросить файл", this);
  clear_button->setFixedSize(width, heigth);
  clear_button->setStyleSheet(button_style);
  connect(clear_button, &QPushButton::clicked, this, &Window::clearFile);

  auto* good_student_button =
      new QPushButton("Показать успевающих студентов", this);
  good_student_button->setFixedSize(width, heigth);
  good_student_button->setStyleSheet(button_style);
  connect(good_student_button, &QPushButton::clicked, this,
          &Window::showGoodStudents);

  textEdit1_ = new QTextEdit(this);
  textEdit1_->setReadOnly(true);
  textEdit1_->setStyleSheet(text_edit_style);
  textEdit1_->setFixedSize(width, fieldSize);

  auto* layout = new QGridLayout();
  layout->addWidget(open_button, 0, 0);
  layout->addWidget(add_student_button, 0, 1);
  layout->addWidget(change_student_button, 0, 2);
  layout->addWidget(delete_student_button, 0, 3);
  layout->addWidget(good_student_button, 0, 4);
  layout->addWidget(clear_button, 1, 0);
  layout->addWidget(sort_all_button, 1, 1);
  layout->addWidget(sort_group_button, 1, 2);
  layout->addWidget(find_studen_button, 1, 3);
  layout->addWidget(textEdit1_, 2, 0);
  layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
  layout->setContentsMargins(margin, margin, margin, margin);
  setLayout(layout);
}

Window::~Window() {
  // Освобождение памяти
  for (int i = 0; i < StudentsNumber_; i++) {
    delete student_array_[i];
  }
  delete[] student_array_;
}

void Window::fileOpen() {
  QString file_name = QFileDialog::getOpenFileName(
      this, "Откройте текстовый файл", "", "Text Files (*.txt)");
  if (!file_name.isEmpty()) {
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

    // Allocate memory for students
    delete[] student_array_;
    StudentsNumber_ = line_count / kFieldNumber;
    student_array_ = new Student*[StudentsNumber_];
    for (int i = 0; i < StudentsNumber_; i++) {
      student_array_[i] = new Student();
    }

    if (file.open(QFile::ReadOnly)) {
      QTextStream fstream(&file);
      for (int i = 0; i < StudentsNumber_; i++) {
        QString name, speciality, group_number;
        ushort grades[kMarkNumber] = {0};  // Initialize grades array

        // Read name
        name = fstream.readLine().trimmed();
        // Read speciality
        speciality = fstream.readLine().trimmed();
        // Read group number
        group_number = fstream.readLine().trimmed();
        // Read grades
        QString grades_line = fstream.readLine().trimmed();
        std::stringstream grades_stream(grades_line.toStdString());
        for (int j = 0; j < kMarkNumber; j++) {
          if (!(grades_stream >> grades[j])) {
            // Handle the case where there are not enough grades
            grades[j] = 0;  // Default to 0 if reading fails
          }
        }

        // Populate Student data
        student_array_[i]->setName(name.toStdString());
        student_array_[i]->setSpeciality(speciality.toStdString());
        student_array_[i]->setGroupNumber(group_number.toStdString());
        student_array_[i]->setGrades(grades, kMarkNumber);
        student_array_[i]->setAverageGrade(
            student_array_[i]->findAverageGrade());
      }
      file.close();
      dataLoaded_ = true;
    }

    // Clear previous text edits and display new data
    textEdit1_->clear();
    for (int i = 0; i < StudentsNumber_; i++) {
      QStringList grades_list;
      for (int j = 0; j < kMarkNumber; j++) {
        grades_list << QString::number(student_array_[i]->getGrade(
            j));  // Предполагается, что grades — это массив в классе Student.
      }
      QString date_info =
          QString(
              "%1:\nСпециальность - %2\n№ гр. - %3\nОценки - %4\nСр. балл - %5")
              .arg(QString::fromStdString(student_array_[i]->getName()))
              .arg(QString::fromStdString(student_array_[i]->getSpeciality()))
              .arg(QString::fromStdString(student_array_[i]->getGroupNumber()))
              .arg(QString::fromStdString(grades_list.join(", ").toStdString()))
              .arg(student_array_[i]->getAverageGrade());
      textEdit1_->append(date_info);
    }
  }
}

void Window::addStudent() {
  if (!currentFileName_.isEmpty()) {
    bool ok;
    QString full_name = QInputDialog::getText(
        this, "Добавить студента", "Введите ФИО:", QLineEdit::Normal, "", &ok);
    if (!ok || full_name.isEmpty()) {
      QMessageBox::warning(this, "Ошибка", "ФИО не может быть пустым.",
                           QMessageBox::Ok);
      return;
    }

    // Запрашиваем специальность
    QString speciality = QInputDialog::getText(
        this, "Добавить студента", "Введите специальность:", QLineEdit::Normal,
        "", &ok);
    if (!ok || speciality.isEmpty()) {
      QMessageBox::warning(this, "Ошибка",
                           "Специальность не может быть пустой.",
                           QMessageBox::Ok);
      return;
    }

    // Запрашиваем номер группы
    QString group_number = QInputDialog::getText(
        this, "Добавить студента", "Введите номер группы:", QLineEdit::Normal,
        "", &ok);
    if (!ok || group_number.isEmpty()) {
      QMessageBox::warning(this, "Ошибка", "Номер группы не может быть пустым.",
                           QMessageBox::Ok);
      return;
    }

    // Запрашиваем оценки
    QString grades_line = QInputDialog::getText(
        this, "Добавить студента",
        "Введите оценки (через пробел):", QLineEdit::Normal, "", &ok);
    if (!ok || grades_line.isEmpty()) {
      QMessageBox::warning(this, "Ошибка", "Оценки не могут быть пустыми.",
                           QMessageBox::Ok);
      return;
    }

    // Обработка оценок
    QStringList grades_list = grades_line.split(" ", Qt::SkipEmptyParts);
    ushort grades[kMarkNumber] = {0};
    if (grades_list.size() != kMarkNumber) {
      QMessageBox::warning(
          this, "Ошибка",
          QString("Неправильное количество оценок! Ожидается %1.")
              .arg(kMarkNumber),
          QMessageBox::Ok);
      return;
    }

    // Ввод оценок и проверка на корректность
    for (int i = 0; i < kMarkNumber; ++i) {
      bool grade_ok;
      grades[i] = grades_list[i].toUShort(&grade_ok);
      if (!grade_ok || grades[i] < 0 ||
          grades[i] > max_grade) {  // Предположим, что максимальная оценка 10
        QMessageBox::warning(this, "Ошибка",
                             QString("Оценка должна быть числом от 0 до 10!"),
                             QMessageBox::Ok);
        return;
      }
    }

    Student new_student = Student();
    new_student.setName(full_name.toStdString());
    new_student.setSpeciality(speciality.toStdString());
    new_student.setGroupNumber(group_number.toStdString());
    new_student.setGrades(grades, kMarkNumber);
    new_student.setAverageGrade(new_student.findAverageGrade());
    addStudentToArray(new_student);
    textEdit1_->append(
        QString(
            "%1:\nСпециальность - %2\n№ гр. - %3\nОценки - %4\nСр. балл - %5")
            .arg(QString::fromStdString(
                student_array_[StudentsNumber_ - 1]->getName()))
            .arg(QString::fromStdString(
                student_array_[StudentsNumber_ - 1]->getSpeciality()))
            .arg(QString::fromStdString(
                student_array_[StudentsNumber_ - 1]->getGroupNumber()))
            .arg(grades_list.join(", "))
            .arg(student_array_[StudentsNumber_ - 1]->getAverageGrade()));
    addStudentToFile();
    QMessageBox::information(this, "Успех", "Студент успешно добавлен.",
                             QMessageBox::Ok);
  } else {
    QMessageBox::warning(this, "Ошибка",
                         "Ошибка. Выберите файл для добавления студента.",
                         QMessageBox::Ok);
  }
}

void Window::addStudentToArray(const Student& newStudent) {
  auto** new_date_array = new Student*[StudentsNumber_ + 1];
  for (int i = 0; i < StudentsNumber_; i++) {
    new_date_array[i] = student_array_[i];
  }
  new_date_array[StudentsNumber_] = new Student(newStudent);
  delete[] student_array_;
  student_array_ = new_date_array;
  StudentsNumber_++;
}

void Window::saveChanges() {
  if (!currentFileName_.isEmpty()) {
    QFile file(currentFileName_);
    if (file.open(QFile::WriteOnly | QFile::Text)) {
      QTextStream out(&file);
      for (int i = 0; i < StudentsNumber_; i++) {
        out << QString::fromStdString(student_array_[i]->getName()) + "\n"
            << QString::fromStdString(student_array_[i]->getSpeciality()) + "\n"
            << QString::fromStdString(student_array_[i]->getGroupNumber()) +
                   "\n";

        QStringList grades_list;
        for (int j = 0; j < kMarkNumber; ++j) {
          grades_list << QString::number(student_array_[i]->getGrade(j));
        }
        out << grades_list.join(" ") << "\n";
      }
      file.close();
    }
  }
}

void Window::addStudentToFile() {
  if (!currentFileName_.isEmpty()) {  // Проверяем, что файл открыт
    QFile file(currentFileName_);
    if (file.open(QFile::Append | QFile::Text)) {
      QTextStream out(&file);
      out << QString::fromStdString(
                 student_array_[StudentsNumber_ - 1]->getName()) +
                 "\n"
          << QString::fromStdString(
                 student_array_[StudentsNumber_ - 1]->getSpeciality()) +
                 "\n"
          << QString::fromStdString(
                 student_array_[StudentsNumber_ - 1]->getGroupNumber()) +
                 "\n";

      QStringList grades_list;
      for (int i = 0; i < kMarkNumber; ++i) {
        grades_list << QString::number(
            student_array_[StudentsNumber_ - 1]->getGrade(i));
      }
      out << grades_list.join(" ");  // Оценки через пробел
      file.close();
    }
  }
}

void Window::sortGroupStudents() {
  if (!currentFileName_.isEmpty()) {
    bool ok;
    QString group_number = QInputDialog::getText(
        this, "Сортировать группу", "Введите номер группы:", QLineEdit::Normal,
        "", &ok);
    if (!ok || group_number.isEmpty()) {
      QMessageBox::warning(this, "Ошибка", "Номер группы не может быть пустым.",
                           QMessageBox::Ok);
      return;
    }
    std::vector<Student*> group_students;
    for (int i = 0; i < StudentsNumber_; i++) {
      if (QString::fromStdString(student_array_[i]->getGroupNumber()) ==
          group_number) {
        group_students.push_back(student_array_[i]);
      }
    }
    if (group_students.empty()) {
      QMessageBox::warning(this, "Ошибка", "Нет студентов в данной группе.",
                           QMessageBox::Ok);
      return;
    }
    quickSort(group_students.data(), 0, group_students.size() - 1);
    int index = 0;
    for (int i = 0; i < StudentsNumber_; i++) {
      if (QString::fromStdString(student_array_[i]->getGroupNumber()) ==
          group_number) {
        student_array_[i] = group_students[index++];
      }
    }
    displayStudents();
    saveChanges();
    QMessageBox::information(this, "Сортировка",
                             "Студенты в группе успешно отсортированы.",
                             QMessageBox::Ok);
  } else {
    QMessageBox::warning(
        this, "Ошибка",
        "Ошибка. Выберите файл для сортировки студентов группы.",
        QMessageBox::Ok);
  }
}

void Window::deleteStudent() {
  if (!currentFileName_.isEmpty()) {
    bool ok;
    QString full_name = QInputDialog::getText(
        this, "Удалить студента",
        "Введите ФИО студента для удаления:", QLineEdit::Normal, "", &ok);

    if (ok && !full_name.isEmpty()) {
      int student_index = -1;

      // Поиск студента по ФИО
      for (int i = 0; i < StudentsNumber_; i++) {
        if (QString::fromStdString(student_array_[i]->getName()) == full_name) {
          student_index = i;
          break;
        }
      }

      if (student_index == -1) {
        QMessageBox::warning(this, "Не найдено",
                             "Студент с таким ФИО не найден.", QMessageBox::Ok);
        return;
      }

      // Удаление студента из массива
      auto** new_student_array = new Student*[StudentsNumber_ - 1];
      for (int i = 0, j = 0; i < StudentsNumber_; i++) {
        if (i != student_index) {
          new_student_array[j++] = student_array_[i];
        } else {
          delete student_array_[i];  // Освобождаем память
        }
      }
      delete[] student_array_;
      student_array_ = new_student_array;
      StudentsNumber_--;  // меньше на 1

      //выводим и сохраняем
      displayStudents();
      saveChanges();

      QMessageBox::information(this, "Успех", "Студент успешно удален.",
                               QMessageBox::Ok);
    } else {
      QMessageBox::warning(this, "Ошибка", "Ошибка. Введите не пустое ФИО.",
                           QMessageBox::Ok);
    }
  } else {
    QMessageBox::warning(this, "Ошибка",
                         "Ошибка. Выберите файл для удаления студента.",
                         QMessageBox::Ok);
  }
}

void Window::findStudent() {
  if (!currentFileName_.isEmpty()) {
    bool ok;
    QString full_name = QInputDialog::getText(
        this, "Найти студента", "Введите ФИО:", QLineEdit::Normal, "", &ok);

    if (ok && !full_name.isEmpty()) {
      QString student_info;
      bool found = false;

      // Ищем студента
      for (int i = 0; i < StudentsNumber_; i++) {
        if (QString::fromStdString(student_array_[i]->getName()) == full_name) {
          found = true;
          QStringList grades_list;
          for (int j = 0; j < kMarkNumber; j++) {
            grades_list << QString::number(student_array_[i]->getGrade(j));
          }
          // Формируем строку с информацией о студенте
          student_info =
              QString(
                  "ФИО: %1\nСпециальность: %2\n№ гр.: %3\nОценки: %4\nСр. "
                  "балл: %5")
                  .arg(QString::fromStdString(student_array_[i]->getName()))
                  .arg(QString::fromStdString(
                      student_array_[i]->getSpeciality()))
                  .arg(QString::fromStdString(
                      student_array_[i]->getGroupNumber()))
                  .arg(grades_list.join(", "))
                  .arg(student_array_[i]->getAverageGrade());
          break;  // выход из цикла, если студент найден
        }
      }

      if (found) {
        // Показываем информацию о студенте
        QMessageBox::information(this, "Информация о студенте", student_info);
      } else {
        // Если студент не найден
        QMessageBox::warning(this, "Не найдено",
                             "Студент с таким ФИО не найден.");
      }
    } else {
      QMessageBox::warning(this, "Ошибка", "Ошибка. Введите не пустое ФИО.",
                           QMessageBox::Ok);
    }
  } else {
    QMessageBox::warning(this, "Ошибка",
                         "Ошибка. Выберите файл для поиска студента.",
                         QMessageBox::Ok);
  }
}

void Window::showGoodStudents() {
  if (!currentFileName_.isEmpty()) {
    QStringList good_students;

    // Проходим по всем студентам и собираем тех, кто успевающий
    for (int i = 0; i < StudentsNumber_; i++) {
      bool is_good_student = true;
      for (int j = 0; j < kMarkNumber; j++) {
        if (student_array_[i]->getGrade(j) < 4) {
          is_good_student =
              false;  // Если хоть одна оценка ниже 4, студент не успевающий
          break;
        }
      }

      // Если студент успевающий, добавляем его в список
      if (is_good_student) {
        good_students << QString::fromStdString(student_array_[i]->getName());
      }
    }

    // Проверяем, есть ли успевающие студенты и выводим их в QMessageBox
    if (!good_students.isEmpty()) {
      QMessageBox::information(this, "Успевающие студенты",
                               good_students.join("\n"));
    } else {
      QMessageBox::information(this, "Успевающие студенты",
                               "Нет успевающих студентов.");
    }
  } else {
    QMessageBox::warning(
        this, "Ошибка",
        "Ошибка. Выберите файл для поиска успевающих студентов.",
        QMessageBox::Ok);
  }
}

void Window::sortAllStudents() {
  if (!currentFileName_.isEmpty()) {
    quickSort(student_array_, 0, StudentsNumber_ - 1);
    displayStudents();
    saveChanges();
    QMessageBox::information(this, "Сортировка",
                             "Студенты отсортированы по среднему баллу.",
                             QMessageBox::Ok);
  } else {
    QMessageBox::warning(this, "Сортировка",
                         "Выберите файл для сортировки студентов",
                         QMessageBox::Ok);
  }
}

void Window::displayStudents() {
  textEdit1_->clear();
  for (int i = 0; i < StudentsNumber_; i++) {
    QStringList grades_list;
    for (int j = 0; j < kMarkNumber; j++) {
      grades_list << QString::number(student_array_[i]->getGrade(j));
    }
    QString student_info =
        QString(
            "%1:\nСпециальность - %2\n№ гр. - %3\nОценки - %4\nСр. балл - %5")
            .arg(QString::fromStdString(student_array_[i]->getName()))
            .arg(QString::fromStdString(student_array_[i]->getSpeciality()))
            .arg(QString::fromStdString(student_array_[i]->getGroupNumber()))
            .arg(grades_list.join(", "))
            .arg(student_array_[i]->getAverageGrade());
    textEdit1_->append(student_info);
  }
}

void Window::editStudent() {
  if (!currentFileName_.isEmpty()) {
    bool ok;
    QString full_name = QInputDialog::getText(
        this, "Изменить студента",
        "Введите ФИО студента для редактирования:", QLineEdit::Normal, "", &ok);

    if (ok && !full_name.isEmpty()) {
      // Поиск студента
      int student_index = -1;
      for (int i = 0; i < StudentsNumber_; ++i) {
        if (QString::fromStdString(student_array_[i]->getName()) == full_name) {
          student_index = i;
          break;
        }
      }

      if (student_index == -1) {
        QMessageBox::warning(this, "Не найдено",
                             "Студент с таким ФИО не найден.", QMessageBox::Ok);
        return;
      }

      // Запрашиваем новую информацию
      QString new_speciality = QInputDialog::getText(
          this, "Изменить специальность",
          "Введите новую специальность:", QLineEdit::Normal,
          QString::fromStdString(
              student_array_[student_index]->getSpeciality()),
          &ok);
      if (!ok || new_speciality.isEmpty()) {
        QMessageBox::warning(this, "Ошибка",
                             "Специальность не может быть пустой.",
                             QMessageBox::Ok);
        return;
      }

      QString new_group_number = QInputDialog::getText(
          this, "Изменить номер группы",
          "Введите номер группы:", QLineEdit::Normal,
          QString::fromStdString(
              student_array_[student_index]->getGroupNumber()),
          &ok);
      if (!ok || new_group_number.isEmpty()) {
        QMessageBox::warning(this, "Ошибка",
                             "Номер группы не может быть пустым.",
                             QMessageBox::Ok);
        return;
      }

      // Запрашиваем новые оценки
      QString grades_line = QInputDialog::getText(
          this, "Изменить оценки",
          "Введите новые оценки (через пробел):", QLineEdit::Normal, "", &ok);
      if (!ok || grades_line.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Оценки не могут быть пустыми.",
                             QMessageBox::Ok);
        return;
      }

      // Обработка оценок
      QStringList grades_list = grades_line.split(" ", Qt::SkipEmptyParts);
      ushort grades[kMarkNumber] = {0};
      if (grades_list.size() != kMarkNumber) {
        QMessageBox::warning(
            this, "Ошибка",
            QString("Неправильное количество оценок! Ожидается %1.")
                .arg(kMarkNumber),
            QMessageBox::Ok);
        return;
      }

      for (int i = 0; i < kMarkNumber; ++i) {
        bool grade_ok;
        grades[i] = grades_list[i].toUShort(&grade_ok);
        if (!grade_ok || grades[i] < 0 || grades[i] > max_grade) {
          QMessageBox::warning(this, "Ошибка",
                               QString("Оценка должна быть числом от 0 до 10!"),
                               QMessageBox::Ok);
          return;
        }
      }

      // Обновление данных студента
      student_array_[student_index]->setSpeciality(
          new_speciality.toStdString());
      student_array_[student_index]->setGroupNumber(
          new_group_number.toStdString());
      student_array_[student_index]->setGrades(grades, kMarkNumber);
      student_array_[student_index]->setAverageGrade(
          student_array_[student_index]->findAverageGrade());

      // Обновление отображения и сохранение изменений в файл
      displayStudents();
      saveChanges();

      QMessageBox::information(this, "Успех",
                               "Информация о студенте успешно изменена.",
                               QMessageBox::Ok);
    } else {
      QMessageBox::warning(this, "Ошибка", "Ошибка. Введите не пустое ФИО.",
                           QMessageBox::Ok);
    }
  } else {
    QMessageBox::warning(this, "Ошибка",
                         "Ошибка. Выберите файл для изменения студента.",
                         QMessageBox::Ok);
  }
}

void Window::clearFile() {
  currentFileName_ = "";
  textEdit1_->clear();
}
