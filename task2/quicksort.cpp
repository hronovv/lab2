#include "quicksort.h"

void quickSort(Student** students, int left, int right) {
  int i = left;
  int j = right;
  double pivot = students[(left + right) / 2]->getAverageGrade();
  while (i <= j) {
    while (students[i]->getAverageGrade() > pivot) {
      i++;
    }
    while (students[j]->getAverageGrade() < pivot) {
      j--;
    }
    if (i <= j) {
      std::swap(students[i], students[j]);
      i++;
      j--;
    }
  }
  if (left < j) {
    quickSort(students, left, j);
  }
  if (i < right) {
    quickSort(students, i, right);
  }
}
