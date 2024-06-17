#include <QPainter>
#include <WebView.h>

WebView::WebView(size_t w, size_t h) : m_width(w), m_height(h), m_pixelwidth(3)
{
    m_bitmap = new uchar[m_width * m_height * 3];
    m_page = new Page(m_bitmap, m_width, m_height, m_pixelwidth);
}

WebView::~WebView()
{
    delete[] m_bitmap;
    delete m_page;
}

void WebView::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setClipRect(event->rect());
    m_page->render();

    QImage q_image(m_bitmap, m_width, m_height, QImage::Format_RGB888);
    painter.drawImage(QPoint(0, 0), q_image);
}

