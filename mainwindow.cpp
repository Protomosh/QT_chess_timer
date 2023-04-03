#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pQtimer = new QTimer(this);
    pQtimer->setInterval(1000);

    connect(pQtimer,SIGNAL(timeout()),
            this,SLOT(updateProgressBar()));

    connect(ui->select_120s_btn,SIGNAL(clicked()),
            this,SLOT(change_Game_Time()));

    connect(ui->select_5min_btn,SIGNAL(clicked()),
            this,SLOT(change_Game_Time()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

// function for game time settings
void MainWindow::change_Game_Time()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());    // set clicked button to btn variable

    QPushButton *another_btn = (btn == ui->select_120s_btn) ? ui->select_5min_btn : ui->select_120s_btn ;
    another_btn->setChecked(false); // set not clicked button state to false
    btn->setChecked(true);          // set set clicked button state to true.

    // set time to gametime depending on which button is checked
    this->gameTime = (btn == ui->select_120s_btn) ? 120 : 300 ;
    qDebug()<<this->gameTime;
    player1Time = gameTime;
    player2Time = gameTime;
}

// function for progress bar update. (core game logic)
void MainWindow::updateProgressBar()
{
    QProgressBar *progBar = (player_turn == 1) ? ui->player1_progbar : ui->player2_progbar ;
    short player_time = (player_turn == 1) ? player1Time-- : player2Time-- ;

    if (progBar->value() >0){   // check if time left
        progBar->setValue(player_time);
        setGameInfoText(0,ONGOING);
    }

    if (progBar->value() == 0){ // check for timeout
        short opponent = (player_turn==1) ? 2:1;
        setGameInfoText(opponent,VICTORY);
    }
}

void MainWindow::setProgressBars()
{
    player1Time = gameTime;
    player2Time = gameTime;

    ui->player1_progbar->setRange(0,player1Time);
    ui->player2_progbar->setRange(0,player2Time);
    ui->player1_progbar->setValue(player1Time);
    ui->player2_progbar->setValue(player2Time);

}

void MainWindow::setGameInfoText(short player_number,short state)
{
    QString msg;

    switch(state){
    case READY:
        msg = "Ready to play";
        break;

    case ONGOING:
        msg = "Game ongoing";
        ui->select_120s_btn->setDisabled(true);
        ui->select_5min_btn->setDisabled(true);
        ui->start_game_btn->setDisabled(true);
        break;

    case VICTORY:
        msg = QString("Player %1 WON!").arg(player_number);
        ui->select_120s_btn->setDisabled(false);
        ui->select_5min_btn->setDisabled(false);
        ui->start_game_btn->setDisabled(false);

        break;

    case NEWGAME:
        msg = "New game via start button";
        ui->select_120s_btn->setDisabled(false);
        ui->select_5min_btn->setDisabled(false);

        break;
    }
    ui->game_state_text->setText(msg);
}

void MainWindow::on_start_game_btn_clicked()
{
    //Set progress bars to default start state
    setProgressBars();
    pQtimer->start();
    ui->switch_player1_btn->setDisabled(false);

}


void MainWindow::on_stop_game_btn_clicked()
{
    //Stop timer,set game state text and set
    // progress bars to default values
    pQtimer->stop();
    setGameInfoText(0,NEWGAME);
    setProgressBars();

    //Disable buttons
    ui->switch_player1_btn->setDisabled(true);
    ui->switch_player2_btn->setDisabled(true);
    this->player_turn = 1;

}

void MainWindow::on_switch_player1_btn_clicked()
{
    this->player_turn = 2;
    qDebug()<<"player turn changed"<<player_turn;
    ui->switch_player1_btn->setDisabled(true);
    ui->switch_player2_btn->setDisabled(false);
}

void MainWindow::on_switch_player2_btn_clicked()
{
    this->player_turn = 1;
    qDebug()<<"player turn changed"<<player_turn;
    ui->switch_player2_btn->setDisabled(true);
    ui->switch_player1_btn->setDisabled(false);
}

