#include "window.h"
constexpr ushort kSizeWindow = 1600;

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  auto* window = new Window();
  window->setWindowTitle("File Manager");
  window->resize(kSizeWindow, kSizeWindow);  // Размеры окна
  window->show();
  return a.exec();
}

#include "main.moc"
