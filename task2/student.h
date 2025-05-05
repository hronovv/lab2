#ifndef STUDENT_H
#define STUDENT_H
#include <bits/stdc++.h>
typedef unsigned short ushort;
typedef unsigned int uint;
constexpr ushort kFebruaryLeapDay = 29;
constexpr ushort kFebruaryNotLeapDay = 28;
constexpr ushort kMarkNumber = 5;
constexpr ushort kFieldNumber = 4;
using namespace std;

class Student {
  std::string name_, speciality_, group_number_;
  ushort grades_[kMarkNumber]{};
  double average_grade_{0};

 public:
  Student();
  void setName(const std::string& name_to_save);

  std::string getName();

  void setSpeciality(const std::string& speciality_to_save);

  std::string getSpeciality();

  void setGroupNumber(const std::string& group_number_to_save);

  std::string getGroupNumber();

  void setGrades(const ushort* gradesArray, size_t size);

  ushort getGrade(ushort grade_number);

  void setAverageGrade(double average_grade_to_save);

  double getAverageGrade();

  double findAverageGrade();
};

#endif  //STUDENT_H
