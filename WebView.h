#pragma once

#include <QWidget>
#include <QPaintEvent>
#include <LibGfx/Painter.h>
#include <Page.h>

class WebView : public QWidget
{
public:
    WebView(size_t w, size_t h);
    ~WebView();

protected:
    virtual void paintEvent(QPaintEvent*) override;

private:
    size_t m_width;
    size_t m_height;
    size_t m_pixelwidth;
    uchar *m_bitmap;
    Page* m_page;
};
