#include "mytitlebar.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QFile>
#include <QMouseEvent>
#include <QDebug>

#define BUTTON_HEIGHT 30		// °´Å¥¸ß¶È;
#define BUTTON_WIDTH 30			// °´Å¥¿í¶È;
#define TITLE_HEIGHT 30			// ±êÌâÀ¸¸ß¶È;

MyTitleBar::MyTitleBar(QWidget *parent)
    : QWidget(parent)
    , m_colorR(153)
    , m_colorG(153)
    , m_colorB(153)
    , m_isPressed(false)
    , m_buttonType(MIN_MAX_BUTTON)
    , m_windowBorderWidth(0)
    , m_isTransparent(false)
{
    // ³õÊ¼»¯;
    initControl();
    initConnections();
    loadStyleSheet("MyTitle");
}

MyTitleBar::~MyTitleBar()
{

}

// ³õÊ¼»¯¿Ø¼þ;
void MyTitleBar::initControl()
{
    m_pIcon = new QLabel;
    m_pTitleContent = new QLabel;

    m_pButtonMin = new QPushButton;
    m_pButtonRestore = new QPushButton;
    m_pButtonMax = new QPushButton;
    m_pButtonClose = new QPushButton;

    m_pButtonMin->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
    m_pButtonRestore->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
    m_pButtonMax->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
    m_pButtonClose->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));

    m_pTitleContent->setObjectName("TitleContent");
    m_pButtonMin->setObjectName("ButtonMin");
    m_pButtonRestore->setObjectName("ButtonRestore");
    m_pButtonMax->setObjectName("ButtonMax");
    m_pButtonClose->setObjectName("ButtonClose");

    QHBoxLayout* mylayout = new QHBoxLayout(this);
    mylayout->addWidget(m_pIcon);
    mylayout->addWidget(m_pTitleContent);

    mylayout->addWidget(m_pButtonMin);
    mylayout->addWidget(m_pButtonRestore);
    mylayout->addWidget(m_pButtonMax);
    mylayout->addWidget(m_pButtonClose);

    mylayout->setContentsMargins(5, 0, 0, 0);
    mylayout->setSpacing(0);

    m_pTitleContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->setFixedHeight(TITLE_HEIGHT);
    this->setWindowFlags(Qt::FramelessWindowHint);
}

// ÐÅºÅ²ÛµÄ°ó¶¨;
void MyTitleBar::initConnections()
{
    connect(m_pButtonMin, SIGNAL(clicked()), this, SLOT(onButtonMinClicked()));
    connect(m_pButtonRestore, SIGNAL(clicked()), this, SLOT(onButtonRestoreClicked()));
    connect(m_pButtonMax, SIGNAL(clicked()), this, SLOT(onButtonMaxClicked()));
    connect(m_pButtonClose, SIGNAL(clicked()), this, SLOT(onButtonCloseClicked()));
}

// ÉèÖÃ±êÌâÀ¸±³¾°É«,ÔÚpaintEventÊÂ¼þÖÐ½øÐÐ»æÖÆ±êÌâÀ¸±³¾°É«;
//ÔÚ¹¹Ôìº¯ÊýÖÐ¸øÁËÄ¬ÈÏÖµ£¬¿ÉÒÔÍâ²¿ÉèÖÃÑÕÉ«Öµ¸Ä±ä±êÌâÀ¸±³¾°É«;
void MyTitleBar::setBackgroundColor(int r, int g, int b, bool isTransparent)
{
    m_colorR = r;
    m_colorG = g;
    m_colorB = b;
    m_isTransparent = isTransparent;
    // ÖØÐÂ»æÖÆ£¨µ÷ÓÃpaintEventÊÂ¼þ£©;
    update();
}

// ÉèÖÃ±êÌâÀ¸Í¼±ê;
void MyTitleBar::setTitleIcon(QString filePath)
{
    QPixmap titleIcon(filePath);
    m_pIcon->setPixmap(titleIcon.scaled(25 , 25));
}

// ÉèÖÃ±êÌâÄÚÈÝ;
void MyTitleBar::setTitleContent(QString titleContent, int titleFontSize)
{
    // ÉèÖÃ±êÌâ×ÖÌå´óÐ¡;
    QFont font = m_pTitleContent->font();
    font.setPointSize(titleFontSize);
    m_pTitleContent->setFont(font);
    // ÉèÖÃ±êÌâÄÚÈÝ;
    m_pTitleContent->setText(titleContent);
    m_titleContent = titleContent;
}

// ÉèÖÃ±êÌâÀ¸³¤¶È;
void MyTitleBar::setTitleWidth(int width)
{
    this->setFixedWidth(width);
}

// ÉèÖÃ±êÌâÀ¸ÉÏ°´Å¥ÀàÐÍ;
// ÓÉÓÚ²»Í¬´°¿Ú±êÌâÀ¸ÉÏµÄ°´Å¥¶¼²»Ò»Ñù£¬ËùÒÔ¿ÉÒÔ×Ô¶¨Òå±êÌâÀ¸ÖÐµÄ°´Å¥;
// ÕâÀïÌá¹©ÁËËÄ¸ö°´Å¥£¬·Ö±ðÎª×îÐ¡»¯¡¢»¹Ô­¡¢×î´ó»¯¡¢¹Ø±Õ°´Å¥£¬Èç¹ûÐèÒªÆäËû°´Å¥¿É×ÔÐÐÌí¼ÓÉèÖÃ;
void MyTitleBar::setButtonType(ButtonType buttonType)
{
    m_buttonType = buttonType;

    switch (buttonType)
    {
    case MIN_BUTTON:
        {
            m_pButtonRestore->setVisible(false);
            m_pButtonMax->setVisible(false);
        }
        break;
    case MIN_MAX_BUTTON:
        {
            m_pButtonRestore->setVisible(false);
        }
        break;
    case ONLY_CLOSE_BUTTON:
        {
            m_pButtonMin->setVisible(false);
            m_pButtonRestore->setVisible(false);
            m_pButtonMax->setVisible(false);
        }
        break;
    default:
        break;
    }
}

// ÉèÖÃ±êÌâÀ¸ÖÐµÄ±êÌâÊÇ·ñ»á×Ô¶¯¹ö¶¯£¬ÅÜÂíµÆµÄÐ§¹û;
// Ò»°ãÇé¿öÏÂ±êÌâÀ¸ÖÐµÄ±êÌâÄÚÈÝÊÇ²»¹ö¶¯µÄ£¬µ«ÊÇ¼ÈÈ»×Ô¶¨Òå¾Í¿´×Ô¼ºÐèÒªÂï£¬ÏëÔõÃ´Éè¼Æ¾ÍÔõÃ´¸ãO(¡É_¡É)O£¡
void MyTitleBar::setTitleRoll()
{
    connect(&m_titleRollTimer, SIGNAL(timeout()), this, SLOT(onRollTitle()));
    m_titleRollTimer.start(200);
}

void MyTitleBar::setWindowBorderWidth(int borderWidth)
{
    m_windowBorderWidth = borderWidth;
}

// ±£´æ´°¿Ú×î´ó»¯Ç°´°¿ÚµÄÎ»ÖÃÒÔ¼°´óÐ¡;
void MyTitleBar::saveRestoreInfo(const QPoint point, const QSize size)
{
    m_restorePos = point;
    m_restoreSize = size;
}

// »ñÈ¡´°¿Ú×î´ó»¯Ç°´°¿ÚµÄÎ»ÖÃÒÔ¼°´óÐ¡;
void MyTitleBar::getRestoreInfo(QPoint& point, QSize& size)
{
    point = m_restorePos;
    size = m_restoreSize;
}

// »æÖÆ±êÌâÀ¸±³¾°É«;
void MyTitleBar::paintEvent(QPaintEvent *event)
{
    if (!m_isTransparent)
    {
        //ÉèÖÃ±³¾°É«;
        QPainter painter(this);
        QPainterPath pathBack;
        pathBack.setFillRule(Qt::WindingFill);
        pathBack.addRoundedRect(QRect(0, 0, this->width(), this->height()), 3, 3);
        painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
        painter.fillPath(pathBack, QBrush(QColor(m_colorR, m_colorG, m_colorB)));
    }

    // µ±´°¿Ú×î´ó»¯»òÕß»¹Ô­ºó£¬´°¿Ú³¤¶È±äÁË£¬±êÌâÀ¸µÄ³¤¶ÈÓ¦µ±Ò»Æð¸Ä±ä;
    if (this->width() != (this->parentWidget()->width() - m_windowBorderWidth))
    {
        this->setFixedWidth(this->parentWidget()->width() - m_windowBorderWidth);
    }
    QWidget::paintEvent(event);
}

// Ë«»÷ÏìÓ¦ÊÂ¼þ£¬Ö÷ÒªÊÇÊµÏÖË«»÷±êÌâÀ¸½øÐÐ×î´ó»¯ºÍ×îÐ¡»¯²Ù×÷;
void MyTitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    // Ö»ÓÐ´æÔÚ×î´ó»¯¡¢»¹Ô­°´Å¥Ê±Ë«»÷²ÅÓÐÐ§;
    if (m_buttonType == MIN_MAX_BUTTON)
    {
        // Í¨¹ý×î´ó»¯°´Å¥µÄ×´Ì¬ÅÐ¶Ïµ±Ç°´°¿ÚÊÇ´¦ÓÚ×î´ó»¯»¹ÊÇÔ­Ê¼´óÐ¡×´Ì¬;
        // »òÕßÍ¨¹ýµ¥¶ÀÉèÖÃ±äÁ¿À´±íÊ¾µ±Ç°´°¿Ú×´Ì¬;
        if (m_pButtonMax->isVisible())
        {
            onButtonMaxClicked();
        }
        else
        {
            onButtonRestoreClicked();
        }
    }

    return QWidget::mouseDoubleClickEvent(event);
}

// ÒÔÏÂÍ¨¹ýmousePressEvent¡¢mouseMoveEvent¡¢mouseReleaseEventÈý¸öÊÂ¼þÊµÏÖÁËÊó±êÍÏ¶¯±êÌâÀ¸ÒÆ¶¯´°¿ÚµÄÐ§¹û;
void MyTitleBar::mousePressEvent(QMouseEvent *event)
{
    if (m_buttonType == MIN_MAX_BUTTON)
    {
        // ÔÚ´°¿Ú×î´ó»¯Ê±½ûÖ¹ÍÏ¶¯´°¿Ú;
        if (m_pButtonMax->isVisible())
        {
            m_isPressed = true;
            m_startMovePos = event->globalPos();
        }
    }
    else
    {
        m_isPressed = true;
        m_startMovePos = event->globalPos();
    }

    return QWidget::mousePressEvent(event);
}

void MyTitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isPressed)
    {
        QPoint movePoint = event->globalPos() - m_startMovePos;
        QPoint widgetPos = this->parentWidget()->pos();
        m_startMovePos = event->globalPos();
        this->parentWidget()->move(widgetPos.x() + movePoint.x(), widgetPos.y() + movePoint.y());
    }
    return QWidget::mouseMoveEvent(event);
}

void MyTitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    m_isPressed = false;
    return QWidget::mouseReleaseEvent(event);
}

// ¼ÓÔØ±¾µØÑùÊ½ÎÄ¼þ;
// ¿ÉÒÔ½«ÑùÊ½Ö±½ÓÐ´ÔÚÎÄ¼þÖÐ£¬³ÌÐòÔËÐÐÊ±Ö±½Ó¼ÓÔØ½øÀ´;
void MyTitleBar::loadStyleSheet(const QString &sheetName)
{
    QFile file(":/Resources/" + sheetName + ".css");
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString styleSheet = this->styleSheet();
        styleSheet += QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
    }
}

// ÒÔÏÂÎª°´Å¥²Ù×÷ÏìÓ¦µÄ²Û;
void MyTitleBar::onButtonMinClicked()
{
    emit signalButtonMinClicked();
}

void MyTitleBar::onButtonRestoreClicked()
{
    m_pButtonRestore->setVisible(false);
    m_pButtonMax->setVisible(true);
    emit signalButtonRestoreClicked();
}

void MyTitleBar::onButtonMaxClicked()
{
    m_pButtonMax->setVisible(false);
    m_pButtonRestore->setVisible(true);
    emit signalButtonMaxClicked();
}

void MyTitleBar::onButtonCloseClicked()
{
    emit signalButtonCloseClicked();
}

// ¸Ã·½·¨Ö÷ÒªÊÇÈÃ±êÌâÀ¸ÖÐµÄ±êÌâÏÔÊ¾Îª¹ö¶¯µÄÐ§¹û;
void MyTitleBar::onRollTitle()
{
    static int nPos = 0;
    QString titleContent = m_titleContent;
    // µ±½ØÈ¡µÄÎ»ÖÃ±È×Ö·û´®³¤Ê±£¬´ÓÍ·¿ªÊ¼;
    if (nPos > titleContent.length())
        nPos = 0;

    m_pTitleContent->setText(titleContent.mid(nPos));
    nPos++;
}
