#pragma once

#include <QWidget>
#include <QPaintEvent>

class WebView : public QWidget
{
public:
    WebView(size_t w, size_t h);
    ~WebView();

protected:
    virtual void paintEvent(QPaintEvent*) override;

private:
    void paint();

    size_t m_width;
    size_t m_height;
    size_t m_pixelwidth;
    uchar *m_bitmap;
};
