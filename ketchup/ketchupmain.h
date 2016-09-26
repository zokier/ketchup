#ifndef KETCHUPMAIN_H
#define KETCHUPMAIN_H

#include <QMenu>
#include <QSystemTrayIcon>
#include <QTimer>
#include <QWidget>

#include "settingswidget.h"

class KetchupMain : public QWidget
{
    Q_OBJECT

public:
    KetchupMain(QWidget *parent = 0);
    ~KetchupMain();

signals:
    void quit();

public slots:
    void activated(QSystemTrayIcon::ActivationReason reason);
    void workTimeout();
    void breakTimeout();
    void setWorkTime(int newTime);
    void setBreakTime(int newTime);

private:
    SettingsWidget *settingsWidget;
    QSystemTrayIcon *trayIcon;
    QMenu *trayMenu;
    QTimer *workTimer;
    QTimer *breakTimer;
};

#endif // KETCHUPMAIN_H
