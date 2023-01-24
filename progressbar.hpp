#include <iostream>
#pragma once

class Progressbar
{
private:
    float progress;
    int length = 50;
    bool showPercentage = true;
    int color = 0;

    int getPercentage(int value) { return value * 100 / this->max; }
    int getDrawCharactersCount(int progress) { return getPercentage(progress) * this->length / 100; }

public:
    int min;
    int max;

    Progressbar(int min, int max)
    {
        this->min = min;
        this->max = max;
    }

    int getProgress() { return getPercentage(this->progress); }

    void setColor(int color) { this->color = color; }
    void setMax(int max) { this->max = max; }
    void setMin(int min) { this->min = min; }
    void setLength(int length) { this->length = length; }
    void update(int progress) { this->progress = progress; }

    void print()
    {
        std::cout << "[";
        std::cout << "\033[" << color << "m";
        int i;

        for (i = 0; i < getDrawCharactersCount(this->progress); i++)
        {
            std::cout << "#";
        }

        for (i = 0; i < ((this->length) - getDrawCharactersCount(this->progress)); i++)
        {
            std::cout << " ";
        }
        std::cout << "\033[0m";
        std::cout << "] ";

        if (showPercentage)
        {
            std::cout << getPercentage(this->progress) << "%\n";
        }
    }
};