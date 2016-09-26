#include "ketchupmain.h"
#include <QAction>
#include <QDebug>

KetchupMain::KetchupMain(QWidget *parent)
    : QWidget(parent),
      settingsWidget(new SettingsWidget()),
      trayIcon(new QSystemTrayIcon(QIcon(":/tray.ico"), this)),
      trayMenu(new QMenu(this)),
      workTimer(new QTimer(this)),
      breakTimer(new QTimer(this))
{
    QSettings settings(this);
    connect(settingsWidget, &SettingsWidget::workTimeChanged, this, &KetchupMain::setWorkTime);
    connect(settingsWidget, &SettingsWidget::breakTimeChanged, this, &KetchupMain::setBreakTime);
    //trayMenu->setStyleSheet("QMenu::indicator { display: none; }");
    QAction *showAction = trayMenu->addAction("Settings");
    connect(showAction, &QAction::triggered, settingsWidget, &SettingsWidget::show);
    QAction *quitAction = trayMenu->addAction("Quit");
    connect(quitAction, &QAction::triggered, this, &KetchupMain::quit);
    connect(trayIcon, &QSystemTrayIcon::activated, this, &KetchupMain::activated);
    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();

    connect(workTimer, &QTimer::timeout, this, &KetchupMain::workTimeout);
    workTimer->setTimerType(Qt::VeryCoarseTimer);
    workTimer->setSingleShot(true);
    workTimer->setInterval(settings.value("worktime").toUInt()*60*1000);
    connect(breakTimer, &QTimer::timeout, this, &KetchupMain::breakTimeout);
    breakTimer->setTimerType(Qt::VeryCoarseTimer);
    breakTimer->setSingleShot(true);
    breakTimer->setInterval(settings.value("breaktime").toUInt()*60*1000);
}

KetchupMain::~KetchupMain()
{

}

void KetchupMain::activated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Unknown:
        break;
    case QSystemTrayIcon::Context:
        break;
    case QSystemTrayIcon::DoubleClick:
        break;
    case QSystemTrayIcon::Trigger:
        if (!workTimer->isActive()) {
            if (breakTimer->isActive()) {
                breakTimer->stop();
                trayIcon->showMessage("Ketchup", "Stopped", QSystemTrayIcon::NoIcon);
            } else {
                workTimer->start();
                trayIcon->showMessage("Ketchup", "Started", QSystemTrayIcon::NoIcon);
            }
        } else {
            workTimer->stop();
            trayIcon->showMessage("Ketchup", "Stopped", QSystemTrayIcon::NoIcon);
        }
        break;
    case QSystemTrayIcon::MiddleClick:
        break;
    }
    qDebug() << reason;
}

void KetchupMain::workTimeout()
{
    trayIcon->showMessage("Ketchup", "work timeout!", QSystemTrayIcon::NoIcon);
    breakTimer->start();
}

void KetchupMain::breakTimeout()
{
    trayIcon->showMessage("Ketchup", "break timeout!", QSystemTrayIcon::NoIcon);
    workTimer->start();
}

void KetchupMain::setWorkTime(int newTime)
{
    workTimer->setInterval(newTime*60*1000);
}

void KetchupMain::setBreakTime(int newTime)
{
    breakTimer->setInterval(newTime*60*1000);
}
