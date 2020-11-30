#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <random>
#include <QTimer>
#include <vector>
#include <fstream>
#include <map>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent* event) override;
    QTimer* game_time_;
    QWidget *wdg = new QWidget;

private slots:

    void on_start_button_clicked();
    void on_pause_button_clicked();
    void on_reset_button_clicked();
    void on_leaderboard_push_button_clicked();
    void on_close_push_button_clicked();
    void on_player_name_line_edit_editingFinished();
    void on_player_name_button_clicked();
    void on_easy_level_button_clicked();
    void on_normal_level_button_clicked();
    void on_hard_level_button_clicked();

private:

    Ui::MainWindow *ui;

    QGraphicsScene* scene_;

    // Single small square which the tetrominos consist
    QGraphicsRectItem* square_;

    // Tetromino vectors which are used in the game
    std::vector<QGraphicsRectItem*> horizontal_tetromino_;
    std::vector<QGraphicsRectItem*> left_corner_tetromino_;
    std::vector<QGraphicsRectItem*> right_corner_tetromino_;
    std::vector<QGraphicsRectItem*> square_tetromino_;
    std::vector<QGraphicsRectItem*> step_up_right_tetromino_;
    std::vector<QGraphicsRectItem*> pyramid_tetromino_;
    std::vector<QGraphicsRectItem*> step_up_left_tetromino_;
    std::vector<QGraphicsRectItem*> tetromino_; // Empty tetromino, utilized in moving
    std::vector<QGraphicsRectItem*> played_squares_; // Include all played squares

    QTimer timer_;
    QString player_name_;

    // Initialize values
    int min_ = 0;
    int sec_ = 0;
    int player_score_ = 0;
    int level_ = 1;
    int y_line_ = 0;
    int drop_time_ = 300;

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
    
    bool tetromino_stopped_ = false;
    bool game_ended_ = false;

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

    /**
     * @brief checks if it is possible move tetromino down, right or left
     * @return true if it is possible, false otherwise
     */
    bool check_y_direction();
    bool check_right_direction();
    bool check_left_direction();

    /**
     * @brief checks if the game board includes full lines
     * @return true if there is not any full lines, false otherwise
     */
    bool check_full_lines();

    /**
     * @brief places tetromino in the middle of the top
     * @param tetromino vector
     */
    void place_tetromino(std::vector<QGraphicsRectItem*>);

    /**
     * @brief update game time and display it
     */
    void update_game_time();

    /**
     * @brief moves tetrominos to down and give two seconds delay
     */
    void tetromino_move();

    /**
     * @brief create all 7 tetrominos in their own methods
     */
    void horizontal();
    void left_corner();
    void right_corner();
    void square();
    void step_up_right();
    void pyramid();
    void step_up_left();

    /**
     * @brief reads saved scores from leaderboard file and display it on screen
     */
    void read_leaderboard();

    /**
     * @brief saves player's name and score to leaderboard file when game ends
     */
    void save_leaderboard();

    /**
     * @brief hides some elements which are not needed when game start
     */
    void hide_elements();

    /**
     * @brief create new grid to game board
     */
    void create_grid();

    /**
     * @brief if the game includes full line, it will be deleted
     */
    void remove_full_line();

    /**
     * @brief move lines down always when full line has been deleted
     */
    void move_lines_down();

    /**
     * @brief when tetromino stops, the squares of the tetromino
     * will be added to played squares vector
     */
    void tetromino_stop();

    /**
     * @brief if the top line of the game is used, the game ends
     */
    void game_end();

    /**
     * @brief set all level buttons disabled or enabled
     */
    void change_level_buttons(bool);

};

#endif // MAINWINDOW_HH
