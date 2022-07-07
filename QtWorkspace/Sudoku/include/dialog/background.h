#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QDialog>

namespace Ui {
class BackGround;
}

class BackGround : public QDialog
{
    Q_OBJECT

public:
    explicit BackGround(QWidget *parent = nullptr);
    ~BackGround();

private:
    Ui::BackGround *ui;
};

#endif // BACKGROUND_H
