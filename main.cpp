
#include <iostream>
#include <Windows.h>
#include "menu.hpp"
#include "progressbar.hpp"
#include "time_conversion.hpp"
#include <thread>

#define POMODORO_TIME 1500 // 25 mins
#define BREAK_TIME 300     // 5 mins

int startTime = POMODORO_TIME;
int counter = 0;
bool isEnd = false;

bool isPaused = false;
bool isBreak = false;

int pomodoros = 0;
int breaks = 0;

Progressbar pbar = Progressbar(0, startTime);

void drawProgressbar();

void printStats();
bool isWindowOnFocus();
HWND myWindow = GetForegroundWindow();

int main()
{

    printMenu();

    pbar.setColor(91);
    pbar.setLength(20);

    DWORD myThreadID;

    const auto thread = CreateThread(
        nullptr,
        0,
        reinterpret_cast<LPTHREAD_START_ROUTINE>(drawProgressbar),
        &myThreadID,
        0,
        nullptr);

    if (thread)
        CloseHandle(thread);

    while (!GetAsyncKeyState(VK_END))
    {
        Sleep(1);
        if ((GetAsyncKeyState(VK_SPACE) & 1) && isWindowOnFocus())
        {
            isPaused = !isPaused;
        }
    }
    isEnd = true;
    printStats();
}

void printStats()
{
    system("cls");
    std::cout
        << "\033[91mPomodoros: " << pomodoros << "\n";
    std::cout << "\033[94mBreaks: " << breaks << "\033[0m\n";
    std::cout << "\nThank you!\n";
    std::cin.get();
}

void drawProgressbar()
{
    int color;

    if (isBreak)
        color = 94;
    else
        color = 91;

    pbar.setColor(color);

    while (pbar.getProgress() < 100)
    {
        if (isEnd)
        {
            break;
        }
        if (isPaused)
            continue;
        counter += 1;
        pbar.update(counter);
        system("cls");
        std::cout << "\n\033[" << color << "mPOMODORO ";
        if (isBreak)
            std::cout << "BREAK";

        std::cout << "\n\n\033[0m";
        pbar.print();
        std::cout << "Time Left: " << getTime(startTime - counter) << "\n";
        std::cout << "\n\033[2mPress END key to Finish";
        std::cout << "\nPress SPACE key to Pause\033[0m\n";
        Sleep(1000);
    }

    counter = 0;
    pbar.update(counter);

    std::cout << "\a";
    Sleep(1000);
    std::cout << "\a";
    Sleep(1000);
    std::cout << "\a";
    Sleep(1000);
    std::cout << "\nPress INTRO to continue...";
    while (!isWindowOnFocus())
    {
        Sleep(1000);
    }
    std::cin.get();

    if (isBreak)
    {
        isBreak = false;
        breaks++;
        startTime = POMODORO_TIME;
        pbar.setMax(POMODORO_TIME);
    }
    else
    {
        isBreak = true;
        pomodoros++;
        startTime = BREAK_TIME;
        pbar.setMax(BREAK_TIME);
    }

    drawProgressbar();
}

bool isWindowOnFocus()
{
    if (myWindow == GetForegroundWindow())
        return true;
    return false;
}