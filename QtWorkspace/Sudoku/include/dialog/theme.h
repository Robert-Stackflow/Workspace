#ifndef THEME_H
#define THEME_H

#include <QDialog>

namespace Ui {
class Theme;
}

class Theme : public QDialog
{
    Q_OBJECT

public:
    Ui::Theme *ui;
    explicit Theme(QWidget *parent = nullptr);
    ~Theme();

private slots:
    QColor colorDialog();

};

#endif // THEME_H
