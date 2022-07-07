#ifndef OPTION_H
#define OPTION_H

#include <QDialog>

namespace Ui {
class Option;
}

class Option : public QDialog
{
    Q_OBJECT

public:
    explicit Option(QWidget *parent = nullptr);
    ~Option();

public:
    Ui::Option *ui;
private slots:
    void level_changed(int);
    void type_changed(int);
    void candidate_changed(int);
    void threshold_changed(int);
    void load_changed();
    void longtime_changed();
    void timing_changed();
    void tips_changed();
    void yes_clicked();
    void cancel_clicked();

};

#endif // OPTION_H
