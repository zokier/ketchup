#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QSettings>
#include <QSpinbox>
#include <QWidget>

class SettingsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsWidget(QWidget *parent = 0);

signals:
    void workTimeChanged(int newTime);
    void breakTimeChanged(int newTime);

public slots:

private:
    void setWorkTime(int newTime);
    void setBreakTime(int newTime);
    QSpinBox *workTimeSpinBox;
    QSpinBox *breakTimeSpinBox;
    QSettings *settings;
};

#endif // SETTINGSWIDGET_H
