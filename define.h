#include <chrono>
#include <locale>
#include <iostream>
#include <codecvt>
#include <thread>
#include <map>
#include <vector>
#include <array>
#include <functional>
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