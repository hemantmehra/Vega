#include <QPainter>
#include "WebView.h"

WebView::WebView(size_t w, size_t h) : m_width(w), m_height(h), m_pixelwidth(3)
{
    m_bitmap = new uchar[m_width * m_height * 3];
    m_page_client = new PageClient(m_bitmap, m_width, m_height, m_pixelwidth);
}

WebView::~WebView()
{
    delete[] m_bitmap;
    delete m_page_client;
}

void WebView::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setClipRect(event->rect());
    // paint();
    m_page_client->paint();

    QImage q_image(m_bitmap, m_width, m_height, QImage::Format_RGB888);
    painter.drawImage(QPoint(0, 0), q_image);
}

void WebView::paint()
{
    for (size_t x=0; x<m_width; x++)
    {
        for (size_t y=0; y<m_height; y++)
        {
            size_t where = (y*m_width + x) * m_pixelwidth;
            m_bitmap[where] = 100;
            m_bitmap[where + 1] = 200;
            m_bitmap[where + 2] = 50;
        }
    }
}
