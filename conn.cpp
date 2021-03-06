﻿#include "conn.h"
#include <QDateTime>
#include <random>

Conn::Conn(QObject *parent) : QObject(parent) {
}

const int db[10][9][9] = {
        {
                { 9, 0, 5, 4, 3, 1, 6, 2, 7, },
                { 6, 0, 3, 0, 0, 9, 1, 5, 4, },
                { 1, 4, 2, 6, 5, 0, 3, 8, 9, },
                { 3, 6, 4, 5, 9, 2, 0, 1, 0, },
                { 0, 2, 1, 3, 8, 6, 9, 4, 0, },
                { 5, 9, 8, 1, 7, 0, 2, 3, 6, },
                { 4, 3, 7, 2, 6, 8, 0, 9, 0, },
                { 2, 1, 9, 7, 4, 5, 8, 0, 3, },
                { 8, 5, 6, 9, 0, 3, 4, 0, 2, },
        },
        {
                { 0, 4, 0, 8, 9, 5, 3, 2, 1, },
                { 1, 0, 8, 2, 3, 4, 7, 6, 5, },
                { 0, 0, 5, 1, 0, 7, 8, 4, 9, },
                { 5, 1, 0, 9, 2, 3, 6, 8, 7, },
                { 8, 7, 0, 0, 0, 6, 0, 0, 0, },
                { 6, 3, 9, 7, 4, 8, 5, 1, 2, },
                { 0, 0, 7, 4, 8, 9, 0, 5, 3, },
                { 4, 5, 3, 6, 7, 1, 2, 0, 8, },
                { 9, 8, 0, 3, 5, 2, 0, 7, 0, },
        },
        {
                { 9, 0, 1, 5, 2, 0, 7, 0, 4, },
                { 5, 6, 0, 0, 0, 0, 9, 8, 2, },
                { 2, 4, 3, 0, 7, 9, 0, 6, 5, },
                { 4, 5, 6, 7, 9, 0, 0, 1, 3, },
                { 1, 9, 8, 0, 3, 2, 4, 0, 7, },
                { 7, 3, 2, 4, 5, 1, 0, 9, 6, },
                { 8, 0, 5, 9, 6, 7, 0, 4, 0, },
                { 0, 1, 9, 2, 0, 3, 5, 0, 8, },
                { 3, 0, 0, 0, 8, 0, 6, 2, 0, },
        },
        {
                { 1, 6, 3, 0, 0, 9, 0, 8, 0, },
                { 0, 8, 9, 5, 0, 2, 0, 0, 3, },
                { 0, 4, 0, 3, 0, 0, 0, 7, 9, },
                { 8, 2, 6, 0, 0, 0, 0, 1, 4, },
                { 9, 0, 1, 0, 0, 6, 8, 3, 5, },
                { 4, 3, 5, 0, 1, 0, 7, 2, 6, },
                { 6, 5, 7, 1, 2, 0, 4, 9, 8, },
                { 0, 9, 4, 8, 5, 7, 2, 0, 1, },
                { 2, 0, 0, 6, 9, 0, 3, 0, 0, },
        },
        {
                { 9, 4, 0, 8, 1, 2, 6, 0, 0, },
                { 1, 0, 0, 7, 6, 5, 0, 0, 3, },
                { 0, 0, 0, 0, 3, 0, 0, 0, 8, },
                { 8, 0, 4, 1, 0, 0, 0, 5, 0, },
                { 3, 0, 0, 0, 0, 9, 7, 8, 4, },
                { 2, 0, 7, 4, 0, 3, 9, 0, 1, },
                { 0, 0, 9, 6, 2, 0, 8, 4, 7, },
                { 7, 6, 1, 0, 0, 8, 0, 0, 0, },
                { 4, 8, 0, 5, 9, 7, 1, 3, 6, },
        },
        {
                { 1, 9, 3, 0, 0, 5, 0, 4, 8, },
                { 6, 0, 8, 9, 2, 4, 0, 0, 1, },
                { 2, 0, 5, 0, 0, 8, 0, 0, 0, },
                { 9, 5, 4, 2, 0, 0, 0, 1, 3, },
                { 7, 0, 0, 0, 0, 9, 8, 2, 0, },
                { 0, 2, 0, 0, 1, 0, 4, 0, 0, },
                { 0, 0, 2, 7, 0, 1, 5, 8, 4, },
                { 0, 0, 0, 4, 0, 3, 0, 7, 0, },
                { 4, 0, 7, 0, 0, 2, 0, 3, 0, },
        },
        {
                { 0, 2, 0, 7, 5, 6, 9, 4, 0, },
                { 7, 0, 0, 0, 8, 0, 0, 0, 0, },
                { 0, 6, 1, 0, 2, 4, 0, 8, 0, },
                { 0, 0, 0, 4, 3, 8, 2, 0, 9, },
                { 0, 8, 0, 9, 0, 0, 4, 0, 0, },
                { 4, 0, 9, 0, 0, 0, 7, 0, 0, },
                { 0, 0, 7, 2, 0, 1, 8, 0, 0, },
                { 0, 0, 0, 0, 0, 0, 1, 0, 4, },
                { 6, 1, 4, 0, 0, 7, 3, 0, 5, },
        },
        {
                { 0, 9, 4, 7, 0, 0, 0, 5, 0, },
                { 0, 0, 8, 0, 0, 2, 0, 0, 6, },
                { 0, 0, 0, 0, 6, 1, 0, 0, 0, },
                { 0, 0, 0, 0, 4, 0, 0, 1, 0, },
                { 0, 6, 0, 8, 1, 9, 0, 3, 7, },
                { 9, 0, 0, 3, 0, 7, 0, 4, 5, },
                { 0, 3, 7, 0, 9, 4, 0, 0, 1, },
                { 0, 4, 0, 0, 0, 8, 0, 6, 0, },
                { 0, 0, 0, 0, 0, 0, 0, 0, 4, },
        },
        {
                { 7, 0, 0, 4, 0, 0, 6, 3, 0, },
                { 0, 0, 0, 0, 0, 1, 0, 2, 0, },
                { 0, 0, 0, 0, 0, 2, 4, 0, 0, },
                { 0, 9, 0, 0, 5, 0, 3, 0, 1, },
                { 0, 6, 0, 0, 0, 0, 8, 0, 0, },
                { 0, 1, 0, 0, 8, 3, 5, 0, 0, },
                { 0, 0, 4, 7, 0, 0, 0, 6, 0, },
                { 0, 0, 2, 9, 0, 0, 0, 0, 3, },
                { 0, 0, 3, 0, 0, 0, 0, 5, 0, },
        },
        {
                { 8, 0, 0, 0, 0, 0, 0, 0, 0, },
                { 0, 0, 0, 0, 2, 1, 0, 0, 7, },
                { 0, 5, 9, 0, 0, 3, 0, 0, 0, },
                { 0, 0, 4, 0, 0, 7, 0, 1, 0, },
                { 1, 0, 0, 0, 0, 9, 0, 4, 2, },
                { 7, 0, 0, 0, 0, 0, 0, 0, 0, },
                { 0, 6, 0, 0, 0, 0, 9, 0, 0, },
                { 0, 7, 0, 8, 4, 0, 0, 0, 0, },
                { 0, 0, 5, 0, 0, 0, 0, 0, 1, },
        },
};

const int shuffleTimes = 20000;

void Conn::requestPuzzle(int level) {
    std::mt19937 ran(QDateTime::currentMSecsSinceEpoch());

    QString rv = "";

    int board[9][9];
    bool fixed[9][9];

    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j) {
            board[i][j] = db[level][i][j];
        }

    // shuffle
    for (int _ = 0; _ < shuffleTimes; ++_) {
        switch (ran() % 3) {
            int a, b, c;
        case 0:  // exchange numbers
            a = ran() % 9;
            b = (a + ran() % 8) % 9;
            ++a;
            ++b;

            for (int i = 0; i < 9; ++i)
                for (int j = 0; j < 9; ++j)
                    if (board[i][j] == a)
                        board[i][j] = b;
                    else if (board[i][j] == b)
                        board[i][j] = a;

            break;

        case 1: // exchange rows
            a = ran() % 3;
            b = (a + ran() % 2) % 3;
            c = ran() % 3;
            a += c * 3; b += c * 3;

            for (int i = 0; i < 9; ++i)
                for (int j = 0; j < 9; ++j) std::swap(board[a][i], board[b][i]);

            break;

        case 2: // exchange columns
            a = ran() % 3;
            b = (a + ran() % 2) % 3;
            c = ran() % 3;
            a += c * 3; b += c * 3;

            for (int i = 0; i < 9; ++i)
                for (int j = 0; j < 9; ++j) std::swap(board[i][a], board[i][b]);

            break;
        }
    }

    // dig
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j) fixed[i][j] = (bool)board[i][j];

    rv += "{ \"board\": [\n";
    for (int i = 0; i < 9; ++i) {
        rv += "[";

        for (int j = 0; j < 9; ++j) rv += QString::number(board[i][j]) + ((j < 8) ? "," : "]");
        rv += (i < 8) ? ",\n" : "],\n";
    }

    rv += "\"fixed\":[\n";
    for (int i = 0; i < 9; ++i) {
        rv += "[";

        for (int j = 0; j < 9; ++j) rv += QString(fixed[i][j] ? "true" : "false") + ((j < 8) ? "," : "]");
        rv += (i < 8) ? ",\n" : "]}\n";
    }

    emit sendPuzzle(rv);
}
