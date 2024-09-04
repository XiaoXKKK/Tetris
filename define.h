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

using namespace std::chrono_literals;

// multiplatform getch
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#endif

#define KEY_Q 'q'
#define KEY_W 'w'
#define KEY_S 's'
#define KEY_A 'a'
#define KEY_D 'd'
#define KEY_SPACE ' '

using Matrix = std::vector<std::vector<int>>;
using Tetromino = std::array<std::array<std::pair<int,int>, 4>, 4>;
using std::ranges::views::iota;

#define PREVIEW 5