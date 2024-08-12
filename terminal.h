#pragma once

namespace tc { // terminal control
    // Set the cursor position to row r and column c.
    void setCursor(int r, int c);

    // Set the foreground color to the 8-bit color code c.
    void setForeColor(int c);

    // Set the background color to the 8-bit color code c.
    void setBackColor(int c);

    // Reset the text color to the default.
    void resetColor();

    // Clear the screen.
    void clearScreen();

    // Set the cursor to be invisible.
    void hideCursor();

    // Set the cursor to be visible.
    void showCursor();

    // Check if a key has been pressed.
    bool kbhit();

    // Get the character of the key that has been pressed.
    char getch();
    
}