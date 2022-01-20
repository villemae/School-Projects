#ifndef MAINMENU_HH
#define MAINMENU_HH

#include <QDialog>

namespace Ui {
class MainMenu;
}

namespace StudentSide {

class MainMenu : public QDialog
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

signals:
    void startGame(int min);

private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_startButton_clicked();

private:
    Ui::MainMenu *ui;
    int time_;
};

}
#endif // MAINMENU_HH
