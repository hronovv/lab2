#include "student.h"

Student::Student() = default;

void Student::setName(const std::string& name_to_save) {
  name_ = name_to_save;
}

std::string Student::getName() {
  return name_;
}

void Student::setSpeciality(const std::string& speciality_to_save) {
  speciality_ = speciality_to_save;
}

std::string Student::getSpeciality() {
  return speciality_;
}

void Student::setGroupNumber(const std::string& group_number_to_save) {
  group_number_ = group_number_to_save;
}

std::string Student::getGroupNumber() {
  return group_number_;
}

void Student::setGrades(const ushort* gradesArray, size_t size) {
  for (size_t i = 0; i < size && i < kMarkNumber; ++i) {
    grades_[i] = gradesArray[i];
  }
}

ushort Student::getGrade(ushort grade_number) {
  return grades_[grade_number];
}

void Student::setAverageGrade(double average_grade_to_save) {
  average_grade_ = average_grade_to_save;
}

double Student::getAverageGrade() {
  return average_grade_;
}

double Student::findAverageGrade() {
  double average = 0.0;
  for (uint grade : grades_) {
    average += grade;
  }
  average /= kMarkNumber;
  return average;
}
