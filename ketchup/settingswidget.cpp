#include "settingswidget.h"

#include <QVBoxLayout>
#include <QLabel>

SettingsWidget::SettingsWidget(QWidget *parent) : QWidget(parent),
    settings(new QSettings(this)),
    workTimeSpinBox(new QSpinBox(this)),
    breakTimeSpinBox(new QSpinBox(this))
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    workTimeSpinBox->setValue(settings->value("worktime").toUInt());
    connect(workTimeSpinBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &SettingsWidget::setWorkTime);
    layout->addWidget(new QLabel(tr("Work time")));
    layout->addWidget(workTimeSpinBox);
    breakTimeSpinBox->setValue(settings->value("breaktime").toUInt());
    connect(breakTimeSpinBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &SettingsWidget::setBreakTime);
    layout->addWidget(new QLabel(tr("Break time")));
    layout->addWidget(breakTimeSpinBox);
    this->setLayout(layout);
}

void SettingsWidget::setWorkTime(int newTime)
{
    this->settings->setValue("worktime", QVariant(newTime));
    emit workTimeChanged(newTime);
}

void SettingsWidget::setBreakTime(int newTime)
{
    this->settings->setValue("breaktime", QVariant(newTime));
    emit breakTimeChanged(newTime);
}
