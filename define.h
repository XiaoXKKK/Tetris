#include <chrono>
#include <locale>
#include <iostream>
#include <codecvt>
#include <thread>
#include <map>
#include <vector>
#include <array>
#include <functional>
#include <memory>
#include <string>
#include <cassert>
#include <ranges>
#include <sstream>
#include <ctime>
#include <queue>
#include <cmath>

using namespace std::chrono_literals;

// multiplatform getch
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#endif

#define KEY_QUIT 'q'
#define KEY_ROTATECW 'l'
#define KEY_ROTATECCW 'j'
#define KEY_ROTATE180 'k'
#define KEY_HOLD 'h'
#define KEY_SOFTDOWN 's'
#define KEY_LEFT 'a'
#define KEY_RIGHT 'd'
#define KEY_HARDDOWN ' '
#define KEY_HELP 'p'
#define KEY_RESET 'r'

using Matrix = std::vector<std::vector<int>>;
using Tetromino = std::vector<std::vector<std::pair<int, int>>>;
using Offset = std::vector<std::vector<std::pair<int,int>>>;
using std::ranges::views::iota;

#define PREVIEW 5