#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTranslator>

#define q_invokalbe Q_INVOKABLE

class TranslateController : public QObject
{
    Q_OBJECT
    Q_ENUMS(Language)

public:
    enum class Language
    {
        English = 1,
        Chinese
    };

public:
    static TranslateController* instance(QQmlEngine *engine) {
        static TranslateController controller(engine);
        return &controller;
    }

    void retranslateUi() {
        m_engine->retranslate();
    }

    q_invokalbe void loadLanguage(Language lang) {
        switch (lang) {
        case Language::Chinese:
            if (m_translator->load("./language/Translator_qml_zh_CN.qm")) {
                emit message(tr("--- Language changed to Chinese"));
            }
            break;
        case Language::English:
            m_translator->load("");
            emit message(tr("--- Language changed to English"));
            break;
        }

        retranslateUi();
    }

signals:
    void message(const QString &msg);

private:
    TranslateController(QQmlEngine *engine) {
        m_engine = engine;
        m_translator = new QTranslator(this);
        QCoreApplication::installTranslator(m_translator);
    }

    QQmlEngine *m_engine = nullptr;
    QTranslator *m_translator = nullptr;
};

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterUncreatableType<TranslateController>("an.translate", 1, 0, "Language", "不能创建TranslateController对象");

    QQmlApplicationEngine engine;
    auto translateController = TranslateController::instance(&engine);
    engine.rootContext()->setContextProperty("controller", translateController);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

#include "main.moc"
