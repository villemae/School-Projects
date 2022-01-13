#include "mainwindow.hh"
#include "ui_mainwindow.h"

const QGraphicsRectItem* EMPTY = nullptr;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    game_timer_(new QTimer(this)),
    seconds_(0),
    minutes_(0)
{
    ui->setupUi(this);

    // A graphics scene in which to draw rectangles.
    scene_ = new QGraphicsScene(this);

    int left_margin = 100; // x coordinate
    int top_margin = 150; // y coordinate

    // The width of the graphicsView is BORDER_RIGHT added by 2,
    // since the borders take one pixel on each side
    // (1 on the left, and 1 on the right).
    // Similarly, the height of the graphicsView is BORDER_DOWN added by 2.
    ui->graphicsView->setGeometry(left_margin, top_margin,
                                  BORDER_RIGHT + 2, BORDER_DOWN + 2);
    ui->graphicsView->setScene(scene_);

    // The width of the scene_ is BORDER_RIGHT decreased by 1 and
    // the height of it is BORDER_DOWN decreased by 1, because
    // each square of a tetromino is considered to be inside the sceneRect,
    // if its upper left corner is inside the sceneRect.
    scene_->setSceneRect(0, 0, BORDER_RIGHT - 1, BORDER_DOWN - 1);

    // Setting random engine ready for the first real call.
    int seed = time(0);
    randomEng.seed(seed);
    distr = std::uniform_int_distribution<int>(0, NUMBER_OF_TETROMINOS - 1);
    distr(randomEng);

    // A non-singleshot timer fires every interval milliseconds,
    // which makes tetrominoMove function to be called,
    // until the timer is stopped
    timer_.setSingleShot(false);
    connect(&timer_, &QTimer::timeout, this, &MainWindow::tetrominoMove);

    //game grid where every slot has pointer to one RectItem, nullptr if empty
    for (int i = 0; i < COLUMNS; ++i) {
        std::vector<QGraphicsRectItem*> temp;
        for (int j = 0; j < ROWS; ++j) {
            temp.push_back(nullptr);
        }
        grid_.push_back(temp);
    }

    //game timer settings initialized
    connect(game_timer_, SIGNAL(timeout()), this, SLOT(secondsPassed()));
    ui->secondsTimer->setStyleSheet("background-color: grey");
    ui->minutesTimer->setStyleSheet("background-color: grey");

    //push buttons colors changed
    ui->startButton->setStyleSheet("background-color: green");
    ui->closeButton->setStyleSheet("background-color: red");
    ui->pauseButton->setStyleSheet("background-color: yellow");

    ui->pauseButton->setDisabled(true);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    if (paused_) {
        return;
    }
    if (event->key() == Qt::Key_A) {
        //if falling tetromino is on the far left side of the scene or there is
        // already tetromino on the left move not possible
        for (auto s : falling_tetromino_) {
            if (s->x() == BORDER_LEFT or
                    isTaken(s->x()-SQUARE_SIDE, s->y())) {
                return;
            }
        }
        //else tetromino moved one step left
        for (auto s : falling_tetromino_) {
            s->moveBy(-SQUARE_SIDE, 0);
        }
        return;
    }

    if (event->key() == Qt::Key_D) {
        //if falling tetromino is far right or there is already
        //tetromino on the right move not possible
        for (auto s : falling_tetromino_) {
            if (s->x()+SQUARE_SIDE == BORDER_RIGHT or
                    isTaken(s->x()+SQUARE_SIDE, s->y())) {
                return;
            }
        }
        //else all squares of tetromino moved one step right
        for (auto s : falling_tetromino_) {
            s->moveBy(SQUARE_SIDE, 0);
        }
        return;

    }
    if (event->key() == Qt::Key_S) {
        //if the tetromino is on the bottom or there is tetromino below move
        //not possible
        for (auto s : falling_tetromino_) {
            if(s->y() + SQUARE_SIDE == BORDER_DOWN or
                    isTaken(s->x(), s->y() + SQUARE_SIDE)) {
                return;
            }
        }
        //else all squares of the tetromino moved one step down
        for (auto s : falling_tetromino_) {
            s->moveBy(0, SQUARE_SIDE);
        }
        return;
    }

    if (event->key() == Qt::Key_W and shape_ != SQUARE) {
        rotate();
    }
}

void MainWindow::newTetromino() {
    falling_tetromino_.clear();

    if (shape_ == HORIZONTAL) {
        newHorizontal();
    }

    else if (shape_ == LEFT_CORNER) {
        newLeftCorner();
    }

    else if (shape_ == RIGHT_CORNER) {
        newRightCorner();
    }

    else if (shape_ == SQUARE) {
        newSquare();
    }

    else if (shape_ == STEP_UP_RIGHT) {
        newStepUpRight();
    }

    else if (shape_ == STEP_UP_LEFT) {
        newStepUpLeft();
    }

    else if (shape_ == PYRAMID) {
        newPyramid();
    }
}

void MainWindow::tetrominoMove() {
    for (auto s : falling_tetromino_) {
        //if there is no more room below, currently falling tetromino stops,
        // a new tetromino will be added on board and points will be updated
        if (s->y() + SQUARE_SIDE == BORDER_DOWN or
                isTaken(s->x(), s->y()+SQUARE_SIDE)) {
            timer_.stop();
            addToGrid();
            ui->pointsLabel->setText(QString::number(points_));
            shape_ = distr(randomEng);
            //check if there is still room for a new tetromino
            if (isGameOver()) {
                gameOver();
                return;
            }
            newTetromino();
            return;
        }
    }
    for (auto s : falling_tetromino_) {
        s->moveBy(0, SQUARE_SIDE);
    }
}

void MainWindow::rotate() {

    int origin_x = falling_tetromino_.at(2)->x();
    int origin_y = falling_tetromino_.at(2)->y();

    //coordinates after rotation
    int new_x;
    int new_y;

    //vectors to store the new coordinates after the rotation
    std::vector<qreal> new_x_coordinates = {};
    std::vector<qreal> new_y_coordinates = {};

    // algorithm that sets new coordinates for squares to rotate the tetromino
    for (auto s : falling_tetromino_) {
        new_x = s->x()-origin_x;
        new_y = s->y()-origin_y;

        int temp_x = new_x * -1;
        int temp_y = new_y * -1;

        new_x = -temp_y;
        new_y = temp_x;

        new_x *= -1;
        new_y *= -1;

        new_x += origin_x;
        new_y += origin_y;

        //if new coordinate is out of bounds rotation not possible
        if (new_x >= BORDER_RIGHT or new_y >= BORDER_DOWN or
                new_x < BORDER_LEFT or new_y < BORDER_UP or
                isTaken(new_x, new_y)) {
            return;
        }
        new_x_coordinates.push_back(new_x);
        new_y_coordinates.push_back(new_y);
    }

    //if all of the new coordinates are valid rotates the tetromino
    for (int i = 0; i < 4; ++i) {
        falling_tetromino_.at(i)->setPos(new_x_coordinates.at(i),
                                         new_y_coordinates.at(i));
    }
}

void MainWindow::addToGrid() {
    int x;
    int y;
    std::vector<int> rows_to_delete = {};
    for (auto s : falling_tetromino_) {
        x = s->x() / SQUARE_SIDE;
        y = s->y() / SQUARE_SIDE;
        grid_.at(x).at(y) = s;
        if (isRowFull(y)) {
            rows_to_delete.push_back(y);
        }
    }
    if (rows_to_delete.size() > 0) {
        int combo = rows_to_delete.size();
        for (auto row : rows_to_delete) {
            points_ += combo*50;
            deleteRow(row);

        }
    }
    else {
        points_ += 10;
    }
}

bool MainWindow::isRowFull(int y) {
    for (int x = 0; x < COLUMNS; ++x) {
        if (grid_.at(x).at(y) == EMPTY) {
            return false;
        }
    }
    return true;
}

void MainWindow::deleteRow(int y) {
    //first hides the row from user's view
    for (int x = 0; x < COLUMNS; ++x) {
        scene_->removeItem(grid_.at(x).at(y));
    }
    //then moves every block one step down both in the grid and in the scene
    for (int j = y; j > 0; --j) {
        for (int i = 0; i < COLUMNS; ++i) {
            if (grid_.at(i).at(j-1) == EMPTY) {
                grid_.at(i).at(j) = nullptr;
            }
            else {
                grid_.at(i).at(j-1)->moveBy(0, SQUARE_SIDE);
                grid_.at(i).at(j) = grid_.at(i).at(j-1);

            }
        }
    }
}

bool MainWindow::isTaken(qreal qx, qreal qy) {
    int x = qx / SQUARE_SIDE;
    int y = qy / SQUARE_SIDE;
    if (grid_.at(x).at(y) != EMPTY) {
        return true;
    }
    return false;
}

bool MainWindow::isGameOver() {
    for (int x = 4; x < 8; ++x) {
        for (int y = 0; y < 2; ++y) {
            if (grid_.at(x).at(y) != EMPTY) {
                return true;
            }
        }
    }
    return false;
}

void MainWindow::gameOver() {
    ui->gameOverLabel->setText("Game Over!");
    game_timer_->stop();
    ui->pauseButton->setDisabled(true);
}


void MainWindow::on_startButton_clicked() {
    scene_->clear();

    //resets the game grid
    for (int i = 0; i < COLUMNS; ++i) {
        for (int j = 0; j < ROWS; ++j) {
            grid_.at(i).at(j) = nullptr;
        }
    }

    ui->gameOverLabel->clear();

    ui->pauseButton->setDisabled(false);
    ui->pauseButton->setText("Pause");
    paused_= false;

    points_ = 0;
    ui->pointsLabel->setText(QString::number(points_));

    resetTimer();
    game_timer_->start(1000);

    interval_ = 1000;

    shape_ = distr(randomEng);
    newTetromino();
}

void MainWindow::secondsPassed() {
    ++seconds_;

    if (seconds_==60) {
        ++minutes_;
        seconds_ = 0;
        interval_ -= 50;
    }
    ui->secondsTimer->display(seconds_);
    ui->minutesTimer->display(minutes_);

}

void MainWindow::resetTimer() {
    minutes_ = 0;
    seconds_ = 0;
    ui->secondsTimer->display(seconds_);
    ui->minutesTimer->display(minutes_);
}

void MainWindow::newHorizontal() {
    QBrush cyan_brush(Qt::cyan);
    QPen black_pen(Qt::black);
    black_pen.setWidth(2);
    for (int i = 0; i < 4*SQUARE_SIDE; i += SQUARE_SIDE) {
        square_ = scene_->addRect(0, 0, SQUARE_SIDE, SQUARE_SIDE, black_pen, cyan_brush);
        square_->setPos(4*SQUARE_SIDE+i,0);
        falling_tetromino_.push_back(square_);
    }
    timer_.start(interval_);
}

void MainWindow::newLeftCorner() {
    QBrush red_brush(Qt::red);
    QPen black_pen(Qt::black);
    black_pen.setWidth(2);
    square_ = scene_->addRect(0, 0, SQUARE_SIDE, SQUARE_SIDE, black_pen, red_brush);
    square_->setPos(4*SQUARE_SIDE,0);
    falling_tetromino_.push_back(square_);
    for (int i = 0; i < 3*SQUARE_SIDE; i+= SQUARE_SIDE) {
        square_ = scene_->addRect(0, 0, SQUARE_SIDE, SQUARE_SIDE, black_pen, red_brush);
        square_->setPos(4*SQUARE_SIDE+i, SQUARE_SIDE);
        falling_tetromino_.push_back(square_);
    }
    timer_.start(interval_);
}

void MainWindow::newRightCorner() {
    QBrush green_brush(Qt::green);
    QPen black_pen(Qt::black);
    black_pen.setWidth(2);
    square_ = scene_->addRect(0, 0, SQUARE_SIDE, SQUARE_SIDE, black_pen, green_brush);
    square_->setPos(6*SQUARE_SIDE, 0);
    falling_tetromino_.push_back(square_);
    for (int i = 0; i < 3*SQUARE_SIDE; i+= SQUARE_SIDE) {
        square_ = scene_->addRect(0, 0, SQUARE_SIDE, SQUARE_SIDE, black_pen, green_brush);
        square_->setPos(4*SQUARE_SIDE+i, SQUARE_SIDE);
        falling_tetromino_.push_back(square_);
    }
    timer_.start(interval_);
}

void MainWindow::newSquare() {
    QBrush yellow_brush(Qt::yellow);
    QPen black_pen(Qt::black);
    black_pen.setWidth(2);
    for (int i = 0; i < 2*SQUARE_SIDE; i += SQUARE_SIDE) {
        square_ = scene_->addRect(0, 0, SQUARE_SIDE, SQUARE_SIDE, black_pen, yellow_brush);
        square_->setPos(5*SQUARE_SIDE,i);
        falling_tetromino_.push_back(square_);
    }
    for (int i = 0; i < 2*SQUARE_SIDE; i += SQUARE_SIDE) {
        square_ = scene_->addRect(0, 0, SQUARE_SIDE, SQUARE_SIDE, black_pen, yellow_brush);
        square_->setPos(6*SQUARE_SIDE, i);
        falling_tetromino_.push_back(square_);
    }
    timer_.start(interval_);
}

void MainWindow::newStepUpRight() {
    QBrush lila_brush(Qt::darkMagenta);
    QPen black_pen(Qt::black);
    black_pen.setWidth(2);
    for (int i = 0; i < 2*SQUARE_SIDE; i += SQUARE_SIDE) {
        square_ = scene_->addRect(0, 0, SQUARE_SIDE, SQUARE_SIDE, black_pen, lila_brush);
        square_->setPos(5*SQUARE_SIDE+i, 0);
        falling_tetromino_.push_back(square_);
    }
    for (int i = SQUARE_SIDE; i > -1; i -= SQUARE_SIDE) {
        square_ = scene_->addRect(0, 0, SQUARE_SIDE, SQUARE_SIDE, black_pen, lila_brush);
        square_->setPos(4*SQUARE_SIDE+i, SQUARE_SIDE);
        falling_tetromino_.push_back(square_);
    }
    timer_.start(interval_);
}

void MainWindow::newStepUpLeft() {
    QBrush blue_brush(Qt::blue);
    QPen black_pen(Qt::black);
    black_pen.setWidth(2);
    for (int i = 0; i < 2*SQUARE_SIDE; i += SQUARE_SIDE) {
        square_ = scene_->addRect(0, 0, SQUARE_SIDE, SQUARE_SIDE, black_pen, blue_brush);
        square_->setPos(4*SQUARE_SIDE+i, 0);
        falling_tetromino_.push_back(square_);
    }
    for (int i = 0; i < 2*SQUARE_SIDE; i += SQUARE_SIDE) {
        square_ = scene_->addRect(0, 0, SQUARE_SIDE, SQUARE_SIDE, black_pen, blue_brush);
        square_->setPos(5*SQUARE_SIDE+i, SQUARE_SIDE);
        falling_tetromino_.push_back(square_);
    }
    timer_.start(interval_);
}

void MainWindow::newPyramid() {
    QBrush magenta_brush(Qt::magenta);
    QPen black_pen(Qt::black);
    black_pen.setWidth(2);
    square_ = scene_->addRect(0, 0, SQUARE_SIDE, SQUARE_SIDE, black_pen, magenta_brush);
    square_->setPos(5*SQUARE_SIDE, 0);
    falling_tetromino_.push_back(square_);
    for (int i = 0; i < 3*SQUARE_SIDE; i += SQUARE_SIDE) {
        square_ = scene_->addRect(0, 0, SQUARE_SIDE, SQUARE_SIDE, black_pen, magenta_brush);
        square_->setPos(4*SQUARE_SIDE+i, SQUARE_SIDE);
        falling_tetromino_.push_back(square_);
    }
    timer_.start(interval_);
}


void MainWindow::on_pauseButton_clicked() {
    if (not paused_) {
        paused_ = true;
        ui->pauseButton->setText("Continue");
        timer_.stop();
        game_timer_->stop();
    }
    else if (paused_) {
        paused_ = false;
        ui->pauseButton->setText("Pause");
        timer_.start(interval_);
        game_timer_->start(1000);
    }
}
