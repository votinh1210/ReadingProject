#ifndef ARTICLEVIEW_H
#define ARTICLEVIEW_H
#include <QWebView>

class ArticleView: public QWebView
{
    Q_OBJECT

public:

    ArticleView( QWidget * parent );
    ~ArticleView();

signals:

    void doubleClicked();

protected:

    void mouseDoubleClickEvent( QMouseEvent * event );

};

#endif // ARTICLEVIEW_H
