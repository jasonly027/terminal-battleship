#pragma once
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

struct Attack
{
    int x;
    int y;
};

class Board
{
private:
    int my_board[10][10] = {0};
    int their_board[10][10] = {0};
    vector<int> boats;
    bool contains(int size);
    bool lose();
    void print_board();
    void print_theirs();
    vector<pair<int, int>> valid_positions(int size, int x, int y);
    void place_boat(int x, int y, int tail_x, int tail_y, int size);
    Attack get_attack(int sock);
    int send_attack(int sock);
    void send_confirmation(int sock, int hit);

public:
    Board();
    void play(int sock, int player_no);
};