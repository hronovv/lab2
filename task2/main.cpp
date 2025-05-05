#include "window.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  auto* window = new Window();
  window->setWindowTitle("Student Manager");
  window->resize(windowSize, windowSize);  // Размеры окна
  window->show();
  return a.exec();
}

#include "main.moc"
