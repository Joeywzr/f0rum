#include "basewindow.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QPainter>
#include <QFile>
#include <QStyleOption>

BaseWindow::BaseWindow(QWidget *parent)
    : QDialog(parent)
{
    // FramelessWindowHintÊôÐÔÉèÖÃ´°¿ÚÈ¥³ý±ß¿ò;
    // WindowMinimizeButtonHint ÊôÐÔÉèÖÃÔÚ´°¿Ú×îÐ¡»¯Ê±£¬µã»÷ÈÎÎñÀ¸´°¿Ú¿ÉÒÔÏÔÊ¾³öÔ­´°¿Ú;
    //Qt::WindowFlags flag = this->windowFlags();
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    // ÉèÖÃ´°¿Ú±³¾°Í¸Ã÷;
    setAttribute(Qt::WA_TranslucentBackground);
    // ¹Ø±Õ´°¿ÚÊ±ÊÍ·Å×ÊÔ´;
    //setAttribute(Qt::WA_DeleteOnClose);
    // ³õÊ¼»¯±êÌâÀ¸;
    initTitleBar();
}

BaseWindow::~BaseWindow()
{

}

void BaseWindow::initTitleBar()
{
    m_titleBar = new MyTitleBar(this);
    m_titleBar->move(0, 0);

    connect(m_titleBar, SIGNAL(signalButtonMinClicked()), this, SLOT(onButtonMinClicked()));
    connect(m_titleBar, SIGNAL(signalButtonRestoreClicked()), this, SLOT(onButtonRestoreClicked()));
    connect(m_titleBar, SIGNAL(signalButtonMaxClicked()), this, SLOT(onButtonMaxClicked()));
    connect(m_titleBar, SIGNAL(signalButtonCloseClicked()), this, SLOT(onButtonCloseClicked()));

}

void BaseWindow::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    //ÉèÖÃ±³¾°É«;

    QPainterPath pathBack;
    pathBack.setFillRule(Qt::WindingFill);
    pathBack.addRoundedRect(QRect(0, 0, this->width(), this->height()), 3, 3);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.fillPath(pathBack, QBrush(QColor(236, 241, 245)));

//	return QWidget::paintEvent(event);
}

void BaseWindow::loadStyleSheet(const QString &sheetName)
{
    QFile file(sheetName);
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString styleSheet = this->styleSheet();
        styleSheet += QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
    }
}

void BaseWindow::onButtonMinClicked()
{
    if (Qt::Tool == (windowFlags() & Qt::Tool))
    {
        hide();    //ÉèÖÃÁËQt::Tool Èç¹ûµ÷ÓÃshowMinimized()Ôò´°¿Ú¾ÍÏú»ÙÁË£¿£¿£¿
    }
    else
    {
        showMinimized();
    }
}

void BaseWindow::onButtonRestoreClicked()
{
    QPoint windowPos;
    QSize windowSize;
    m_titleBar->getRestoreInfo(windowPos, windowSize);
    this->setGeometry(QRect(windowPos, windowSize));
}

void BaseWindow::onButtonMaxClicked()
{
    m_titleBar->saveRestoreInfo(this->pos(), QSize(this->width(), this->height()));
    QRect desktopRect = QApplication::desktop()->availableGeometry();
    QRect FactRect = QRect(desktopRect.x() - 3, desktopRect.y() - 3, desktopRect.width() + 6, desktopRect.height() + 6);
    setGeometry(FactRect);
}

void BaseWindow::onButtonCloseClicked()
{
    // ×¢Òâ £¡£¡£¡;
    // Èç¹ûÉèÖÃÁËQt::Tool ÇÒµ±Ç°´°¿ÚÎªÖ÷´°¿Úµ÷ÓÃclose()·½·¨Ö»ÊÇ¹Ø±ÕÁËµ±Ç°´°¿Ú£¬²¢Ã»ÓÐ½áÊøÕû¸ö³ÌÐò½ø³Ì;
    // Èç¹ûÖ»ÓÐÒ»¸ö´°¿ÚÇé¿öÏÂ,ÐèÒªµ÷ÓÃqApp->quit();À´½áÊø½ø³Ì;
    // Èç¹ûÉèÖÃÁËQt::ToolµÄ´°¿ÚÊÇ×Ó´°¿Ú£¬ÔòÖ»ÐèÒªµ÷ÓÃclose()·½·¨¹Ø±Õ¼´¿É;
    // 	if (Qt::Tool == (windowFlags() & Qt::Tool))
    // 	{
    // 		qApp->quit();
    // 	}
    // 	else
    {
        close();
    }
}
