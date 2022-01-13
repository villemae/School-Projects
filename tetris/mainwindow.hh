#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QDebug>
#include <random>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void keyPressEvent(QKeyEvent* event) override;


private slots:
    //initializes the game
    void on_startButton_clicked();

    //adds seconds to game timer
    void secondsPassed();

    void resetTimer();

    //pauses the game
    void on_pauseButton_clicked();

private:
    Ui::MainWindow *ui;

    QGraphicsScene* scene_;

    // Constants describing scene coordinates
    // Copied from moving circle example and modified a bit
    const int BORDER_UP = 0;
    const int BORDER_DOWN = 480; // 260; (in moving circle)
    const int BORDER_LEFT = 0;
    const int BORDER_RIGHT = 240; // 680; (in moving circle)

    // Size of a tetromino component
    const int SQUARE_SIDE = 20;
    // Number of horizontal cells (places for tetromino components)
    const int COLUMNS = BORDER_RIGHT / SQUARE_SIDE;
    // Number of vertical cells (places for tetromino components)
    const int ROWS = BORDER_DOWN / SQUARE_SIDE;


    // Constants for different tetrominos and the number of them
    enum Tetromino_kind {HORIZONTAL,
                         LEFT_CORNER,
                         RIGHT_CORNER,
                         SQUARE,
                         STEP_UP_RIGHT,
                         PYRAMID,
                         STEP_UP_LEFT,
                         NUMBER_OF_TETROMINOS};
    // From the enum values above, only the last one is needed in this template.
    // Recall from enum type that the value of the first enumerated value is 0,
    // the second is 1, and so on.
    // Therefore the value of the last one is 7 at the moment.
    // Remove those tetromino kinds above that you do not implement,
    // whereupon the value of NUMBER_OF_TETROMINOS changes, too.
    // You can also remove all the other values, if you do not need them,
    // but most probably you need a constant value for NUMBER_OF_TETROMINOS.


    // For randomly selecting the next dropping tetromino
    std::default_random_engine randomEng;
    std::uniform_int_distribution<int> distr;

    //rectItem that moves in the scene
    QGraphicsRectItem* square_ = nullptr;

    //currently falling tetromino
    std::vector<QGraphicsRectItem*> falling_tetromino_;

    //timer which controls the falling pace of tetrominos
    QTimer timer_;


    //game grid which has the information of stopped tetrominos on board
    std::vector<std::vector<QGraphicsRectItem*>> grid_;

    //shape of the tetromino to fall next
    int shape_;

    //points of current game
    int points_;

    //minutes and seconds passed during the game
    QTimer* game_timer_;
    int seconds_;
    int minutes_;

    //interval for timer, is reduced every minute
    int interval_ = 1000;

    //tells if the game is currently paused or not
    bool paused_ = true;

    //calls one of the tetromino building methods based on value of shape_
    void newTetromino();

    //moves tetromino one step down and calls newTetromino and
    //gameOver methods when needed
    void tetrominoMove();

    //rotates the tetromino clockwise if possible
    void rotate();
    
    //when tetromino stops adds the rectItems to grid and calls the isRowFull
    //method
    void addToGrid();

    //chekcs if the row where the latest rectItem was added is full
    bool isRowFull(int y);

    //if the row is full deletes it and moves all stopped tetrominos above
    //one step down
    void deleteRow(int y);

    //checks if the slot in the desireable direction is already taken
    bool isTaken(qreal qx, qreal qy);

    //chekcs if any of the slots in the 2x4 area where new tetrominos are added
    //is taken
    bool isGameOver();

    //tells the user that game is over and basically ends the game
    void gameOver();

    //methods for building different tetrominos
    void newHorizontal();
    void newLeftCorner();
    void newRightCorner();
    void newSquare();
    void newStepUpRight();
    void newStepUpLeft();
    void newPyramid();
};

#endif // MAINWINDOW_HH
