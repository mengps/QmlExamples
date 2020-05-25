#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QTranslator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_translator = new QTranslator(this);

    QCoreApplication::instance()->installTranslator(m_translator);

    m_changeBtn = new QPushButton(this);
    m_changeBtn->setText(tr("Change Language"));
    m_changeBtn->setGeometry(40, 100, 120, 40);

    connect(m_changeBtn, &QPushButton::clicked, this, [this]() {
        if (m_language == Language::English) {
            setLanguage(Language::Chinese);
        } else {
            setLanguage(Language::English);
        }
    });
    connect(ui->actionChinese, &QAction::triggered, this, [this]() {
        setLanguage(Language::Chinese);
    });
    connect(ui->actionEnglish, &QAction::triggered, this, [this]() {
        setLanguage(Language::English);
    });

    emit ui->actionEnglish->triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setLanguage(MainWindow::Language lang)
{
    switch (lang) {
    case Language::Chinese:
        if (m_translator->load("./language/Translator_widget_zh_CN.qm")) {
            ui->actionChinese->setChecked(true);
            ui->actionEnglish->setChecked(false);
            m_language = Language::Chinese;
            statusBar()->showMessage(tr("--- Language changed to Chinese"), 1000);
        }
        break;
    case Language::English:
        m_translator->load("");
        ui->actionChinese->setChecked(false);
        ui->actionEnglish->setChecked(true);
        m_language = Language::English;
        statusBar()->showMessage(tr("--- Language changed to English"), 1000);
        break;
    }

    retranslateUi();
}

void MainWindow::retranslateUi()
{
    ui->retranslateUi(this);
    m_changeBtn->setText(QCoreApplication::translate("MainWindow", "Change Language", nullptr));
}
