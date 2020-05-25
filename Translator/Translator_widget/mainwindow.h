#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QTranslator;
class QPushButton;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum class Language
    {
        English = 1,
        Chinese
    };

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setLanguage(Language lang);

private:
    void retranslateUi();

    Ui::MainWindow *ui;
    QTranslator *m_translator;
    QPushButton *m_changeBtn;
    Language m_language = Language::English;
};

#endif // MAINWINDOW_H
