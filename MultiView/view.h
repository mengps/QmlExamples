#ifndef VIEW_H
#define VIEW_H

#include <QObject>

class ViewPrivate;
class QQuickImageProvider;
class View : public QObject
{
    Q_OBJECT

public:
    View();

    QQuickImageProvider* multiView() const;
    QQuickImageProvider* multiSource() const;

    Q_INVOKABLE void startSource();
    Q_INVOKABLE void resumeSource(int source);
    Q_INVOKABLE void stopSource();
    Q_INVOKABLE void pauseSource(int source);

signals:
    void viewNeedUpdate(int index);
    void sourceNeedUpdate(int source);

private:
    ViewPrivate *d = nullptr;
};

#endif // VIEW_H
