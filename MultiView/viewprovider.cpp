#include "viewprovider.h"

ViewProvider::ViewProvider()
    : QQuickImageProvider(QQuickImageProvider::Image)
{

}

void ViewProvider::updateView(int index, const QImage &view)
{
    m_views[index] = view;
}

QImage ViewProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    //这里可以id.left(1);
    int index = id.left(id.indexOf("###")).toInt();
    QImage view = m_views[index];

    if (!view.isNull()) {
        view.scaled(requestedSize);

        if (size) *size = requestedSize;
    }

    return view;
}
