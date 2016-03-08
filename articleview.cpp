#include "articleview.h"

ArticleView::ArticleView( QWidget * parent ):
    QWebView( parent )
{}

ArticleView::~ArticleView()
{}

void ArticleView::mouseDoubleClickEvent(QMouseEvent *event){
    emit doubleClicked();
}
