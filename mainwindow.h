#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer *pQtimer;
    short player1Time;
    short player2Time;
    short currentPlayer;
    short gameTime = 120;
    short player_turn = 1;

    enum messages {
        READY,
        ONGOING,
        VICTORY,
        NEWGAME
    };


private slots:
    void updateProgressBar();
    void setProgressBars();
    void setGameInfoText(short player_number, short state);
    void change_Game_Time();

    void on_start_game_btn_clicked();
    void on_stop_game_btn_clicked();
    void on_switch_player1_btn_clicked();
    void on_switch_player2_btn_clicked();
};
#endif // MAINWINDOW_H
