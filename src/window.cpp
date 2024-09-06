#include "window.h"
#include <iomanip>
#include "log.h"

namespace ui {
    void show_windows()
    {
        dw::window(1, 1, 9, 6, "Hold");
        dw::window(1, 10, 12, 22, "Tetriz");
        dw::window(7, 1, 9, 16, "Status");
        dw::window(19, 22, 8, 4, "Info");
        dw::window(1, 22, 8, 18, "Next");
    }
    void show_info()
    {
        tc::resetColor();
        //show fps
        tc::setCursor(10, 4);
        std::cout << std::left;
        std::cout << "FPS:   " << std::setw(6) << ut::fps();
        tc::setCursor(12, 4);
        std::cout << "Level: " << std::setw(6) << gm::level;
        tc::setCursor(13, 4);
        std::cout << "Score: " << std::setw(6) << gm::score;
        tc::setCursor(14, 4);
        std::cout << "Lines: " << std::setw(6) << gm::lines;

        if (gm::end) {
            dw::window(9, 13, 7, 3, "");
            tc::setCursor(10, ut::b2c(14));
            tc::setForeColor((int)Color::Red);
            std::cout << "Game Over!";
        }
        /*
        if (gm::helping) {
            tc::setCursor(7, ut::b2c(12));
            std::cout << "Rotate     [" << KEY_ROTATECW << "]    ";
            tc::setCursor(8, ut::b2c(12));
            std::cout << "Rotate_L   [" << KEY_ROTATECCW << "]    ";
            tc::setCursor(9, ut::b2c(12));
            std::cout << "Rotate_2   [" << KEY_ROTATE180 << "]    ";
            tc::setCursor(10, ut::b2c(12));
            std::cout << "Left       [" << KEY_LEFT << "]    ";
            tc::setCursor(11, ut::b2c(12));
            std::cout << "Right      [" << KEY_RIGHT <<"]    ";
            tc::setCursor(12, ut::b2c(12));
            std::cout << "Down       [" << KEY_SOFTDOWN << "]    ";
            tc::setCursor(13, ut::b2c(12));
            std::cout << "Drop       [space]";
            tc::setCursor(14, ut::b2c(12));
            std::cout << "Hold       [" << KEY_HOLD << "]    ";
            tc::setCursor(15, ut::b2c(12));
            std::cout << "Reset      [" << KEY_RESET << "]    ";
        }
        */
    }
    void show_game()
    {
        dw::frame(gm::frame, 2, 11);
        dw::next(gm::next_pieces, 2, 23);
        dw::hold(gm::hold_piece, 2, 2);
        std::cout << std::flush;
    }
    void show_exit()
    {
        tc::showCursor();
        tc::clearScreen();
        tc::setCursor(1, 1);
        std::cout << "Goodbye!" << std::endl;
    }
    void show_help()
    {
        tc::resetColor();
        tc::setCursor(21,ut::b2c(24));
        std::cout << "help [p]";
    }
    void show_clear(int count, int t_spin, int combo, int b2b)
    {
        tc::resetColor();
        std::string t_spin_str = t_spin == 1 ? "T-Spin" : t_spin == 2 ? "Mini T-Spin" : "";
        std::string clear_str = count == 1 ? "Single" : count == 2 ? "Double" : count == 3 ? "Triple" : count == 4 ? "Tetris": "";
        tc::setCursor(16, 4);
        tc::setForeColor((int)Color::Orange);
        std::cout << std::setw(12) << t_spin_str << std::flush;
        tc::setCursor(17, 4);
        tc::setForeColor((int)Color::Yellow);
        std::cout << std::setw(12) << clear_str << std::flush;
        tc::setCursor(18, 4);
        tc::setForeColor((int)Color::Green);
        if (combo > 1){
            std::cout << "Combo x " << combo << std::flush;
            lg::log("Combo x " + std::to_string(combo));
        }
        else 
            std::cout << std::setw(12) << "" << std::flush;
        tc::setCursor(19, 4);
        tc::setForeColor((int)Color::Cyan);
        if (b2b > 1)
            std::cout << "Back to Back" << std::flush;
        else 
            std::cout << std::setw(12) << "" << std::flush;
    }
}