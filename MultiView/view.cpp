#include "view.h"
#include "viewprovider.h"

#include <QGuiApplication>
#include <QMovie>
#include <QPixmap>
#include <QScreen>
#include <QTimer>
#include <QDebug>

class ViewPrivate
{
public:
    ViewPrivate() {
        m_multiView = new ViewProvider;
        m_multiSource = new ViewProvider;
    }

    ViewProvider *m_multiView = nullptr;
    ViewProvider *m_multiSource = nullptr;
    QTimer *m_generator = nullptr;
    QMovie *m_sources[4] = { nullptr };
};

View::View()
{
    d = new ViewPrivate;

    //多视图图像生成器
    d->m_generator = new QTimer(this);
    connect(d->m_generator, &QTimer::timeout, this, [this]() {
        static int index = 0;
        QImage image = QGuiApplication::primaryScreen()->grabWindow(0).toImage();
        d->m_multiView->updateView(index, image);
        emit viewNeedUpdate(index);

        if (++index == 9) index = 0;
    });
    d->m_generator->start(1000 / 9);

    /**
     * @note 多图像源
     * @source[0-4] gif[0-4]
     */
    for (int i = 0;  i < 4; i++) {
        d->m_sources[i] =  new QMovie(":/" + QString::number(i) + ".gif", "GIF", this);
        qDebug() << d->m_sources[i]->fileName() << d->m_sources[i]->isValid();
        connect(d->m_sources[i], &QMovie::frameChanged, this, [i, this](int) {
            d->m_multiSource->updateView(i, d->m_sources[i]->currentImage());
            emit sourceNeedUpdate(i);
        });
    }
}

QQuickImageProvider* View::multiView() const
{
    return d->m_multiView;
}

QQuickImageProvider* View::multiSource() const
{
    return d->m_multiSource;
}

void View::startSource()
{
    if (d->m_generator) d->m_generator->stop();

    for (auto it : d->m_sources) {
        if (it) it->start();
    }
}

void View::resumeSource(int source)
{
    if (d->m_sources[source]) d->m_sources[source]->setPaused(false);
}

void View::stopSource()
{
    if (d->m_generator) d->m_generator->start(1000 / 9);

    for (auto it : d->m_sources) {
        if (it) it->stop();
    }
}

void View::pauseSource(int source)
{
    if (d->m_sources[source]) d->m_sources[source]->setPaused(true);
}
