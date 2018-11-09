#ifndef MYTITLEBAR_H
#define MYTITLEBAR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTimer>

enum ButtonType
{
    MIN_BUTTON = 0,			// ×îÐ¡»¯ºÍ¹Ø±Õ°´Å¥;
    MIN_MAX_BUTTON ,		// ×îÐ¡»¯¡¢×î´ó»¯ºÍ¹Ø±Õ°´Å¥;
    ONLY_CLOSE_BUTTON		// Ö»ÓÐ¹Ø±Õ°´Å¥;
};

class MyTitleBar : public QWidget
{
    Q_OBJECT

public:
    MyTitleBar(QWidget *parent = NULL);
    ~MyTitleBar();

    // ÉèÖÃ±êÌâÀ¸±³¾°É«;
    void setBackgroundColor(int r, int g, int b , bool isTransparent = false);
    // ÉèÖÃ±êÌâÀ¸Í¼±ê;
    void setTitleIcon(QString filePath);
    // ÉèÖÃ±êÌâÄÚÈÝ;
    void setTitleContent(QString titleContent , int titleFontSize = 9);
    // ÉèÖÃ±êÌâÀ¸³¤¶È;
    void setTitleWidth(int width);
    // ÉèÖÃ±êÌâÀ¸ÉÏ°´Å¥ÀàÐÍ;
    void setButtonType(ButtonType buttonType);
    // ÉèÖÃ±êÌâÀ¸ÖÐµÄ±êÌâÊÇ·ñ»á¹ö¶¯;¾ßÌå¿ÉÒÔ¿´Ð§¹û;
    void setTitleRoll();
    // ÉèÖÃ´°¿Ú±ß¿ò¿í¶È;
    void setWindowBorderWidth(int borderWidth);

    // ±£´æ/»ñÈ¡ ×î´ó»¯Ç°´°¿ÚµÄÎ»ÖÃ¼°´óÐ¡;
    void saveRestoreInfo(const QPoint point, const QSize size);
    void getRestoreInfo(QPoint& point, QSize& size);

private:
    void paintEvent(QPaintEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    // ³õÊ¼»¯¿Ø¼þ;
    void initControl();
    // ÐÅºÅ²ÛµÄ°ó¶¨;
    void initConnections();
    // ¼ÓÔØÑùÊ½ÎÄ¼þ;
    void loadStyleSheet(const QString &sheetName);

signals:
    // °´Å¥´¥·¢µÄÐÅºÅ;
    void signalButtonMinClicked();
    void signalButtonRestoreClicked();
    void signalButtonMaxClicked();
    void signalButtonCloseClicked();

private slots:
    // °´Å¥´¥·¢µÄ²Û;
    void onButtonMinClicked();
    void onButtonRestoreClicked();
    void onButtonMaxClicked();
    void onButtonCloseClicked();
    void onRollTitle();

private:
    QLabel* m_pIcon;					// ±êÌâÀ¸Í¼±ê;
    QLabel* m_pTitleContent;			// ±êÌâÀ¸ÄÚÈÝ;
    QPushButton* m_pButtonMin;			// ×îÐ¡»¯°´Å¥;
    QPushButton* m_pButtonRestore;		// ×î´ó»¯»¹Ô­°´Å¥;
    QPushButton* m_pButtonMax;			// ×î´ó»¯°´Å¥;
    QPushButton* m_pButtonClose;		// ¹Ø±Õ°´Å¥;

    // ±êÌâÀ¸±³¾°É«;
    int m_colorR;
    int m_colorG;
    int m_colorB;

    // ×î´ó»¯£¬×îÐ¡»¯±äÁ¿;
    QPoint m_restorePos;
    QSize m_restoreSize;
    // ÒÆ¶¯´°¿ÚµÄ±äÁ¿;
    bool m_isPressed;
    QPoint m_startMovePos;
    // ±êÌâÀ¸ÅÜÂíµÆÐ§¹ûÊ±ÖÓ;
    QTimer m_titleRollTimer;
    // ±êÌâÀ¸ÄÚÈÝ;
    QString m_titleContent;
    // °´Å¥ÀàÐÍ;
    ButtonType m_buttonType;
    // ´°¿Ú±ß¿ò¿í¶È;
    int m_windowBorderWidth;
    // ±êÌâÀ¸ÊÇ·ñÍ¸Ã÷;
    bool m_isTransparent;
};

#endif // MYTITLEBAR_H
