#include "board.h"
#include <sys/socket.h>
#include <unistd.h>

// Constructor that sets up board from user
Board::Board() : boats({5, 4, 3, 3, 2})
{
    int curr_boat;
    Board::print_board();
    while (!boats.empty())
    {
        cout << "Please pick which boat to place, general: [ ";
        for (int boat : boats)
        {
            cout << boat << " ";
        }
        cout << "]: ";

        cin >> curr_boat;
        if (!contains(curr_boat))
        {
            cout << "There are no boats of that size! Ur geekin! Try again lol." << endl;
            continue;
        }

        int x, y;
        cout << "What are the x-coords: ";
        cin >> y;
        cout << "What are the y-coords: ";
        cin >> x;

        vector<pair<int, int>> pp = valid_positions(curr_boat, x, y);
        if (pp.empty())
        {
            cout << "There are no possible positions to place that boat!" << endl;
            continue;
        }

        cout << "Possible tail positions for the boat starting at (" << y << "," << x << "): ";
        for (auto &p : pp)
        {
            cout << "(" << p.second << ", " << p.first << ") ";
        }
        cout << endl;

        int tail_x, tail_y;
        cout << "Enter the tail x coordinates from the list above: ";
        cin >> tail_y;
        cout << "Enter the tail y coordinates from the list above: ";
        cin >> tail_x;
        cout << endl << endl;
        if (find(pp.begin(), pp.end(), make_pair(tail_x, tail_y)) != pp.end())
        {
            place_boat(x, y, tail_x, tail_y, curr_boat);
            auto it = find(boats.begin(), boats.end(), curr_boat);
            boats.erase(it);
        }
        else
        {
            cout << "Blud how. Please select a valid position from the list." << endl;
            continue;
        }

        Board::print_board();
    }
}

bool Board::contains(int size)
{
    for (auto x : boats)
    {
        if (x == size)
            return true;
    }
    return false;
}

bool Board::lose() {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if(my_board[i][j] == 1) {
                return false;
            }
        }
    }
    return true;
}

void Board::print_board()
{
    cout << "YOUR BOARD" << endl << endl;
    cout << "   ";
    for (int k = 0; k < 10; ++k) {
        cout << k << " ";
    }
    cout << endl << endl;
    for (int i = 0; i < 10; ++i)
    {
        cout << i << "  ";
        for (int j = 0; j < 10; ++j)
        {
            if(my_board[i][j] == 0) {
                cout << ". ";
                continue;
            }
            if(my_board[i][j] == 1) {
                cout << "@ ";
                continue;
            }
            if(my_board[i][j] == 2) {
                cout << "X ";
                continue;
            }
        }
        cout << endl;
        }
    cout << endl;
}

void Board::print_theirs() {
    cout << "THEIR BOARD" << endl
         << endl;
    cout << "   ";
    for (int k = 0; k < 10; ++k)
    {
        cout << k << " ";
    }
    cout << endl
         << endl;
    for (int i = 0; i < 10; ++i)
    {
        cout << i << "  ";
        for (int j = 0; j < 10; ++j)
        {
            if (their_board[i][j] == 0)
            {
                cout << ". ";
                continue;
            }
            if (their_board[i][j] == 1)
            {
                cout << "% ";
                continue;
            }
            if (their_board[i][j] == 2)
            {
                cout << "X ";
                continue;
            }
        }
        cout << endl;
    }
    cout << endl;
}

// God awful function it was horrendous to code CS1400 vibes but like no other efficient way
vector<pair<int, int>> Board::valid_positions(int size, int x, int y)
{
    vector<pair<int, int>> ret;

    // Vertical placement
    if (x + size - 1 < 10) // Down
    {
        bool valid = true;
        for (int i = x; i < x + size; ++i)
        {
            if (my_board[i][y] != 0)
            {
                valid = false;
                break;
            }
        }
        if (valid && x + size - 1 != x)
            ret.push_back({x + size - 1, y});
    }

    if (x - size + 1 >= 0) // Up
    {
        bool valid = true;
        for (int i = x; i > x - size; --i)
        {
            if (my_board[i][y] != 0)
            {
                valid = false;
                break;
            }
        }
        if (valid && x - size + 1 != x)
            ret.push_back({x - size + 1, y});
    }

    // Horizontal placement
    if (y + size - 1 < 10) // Right
    {
        bool valid = true;
        for (int j = y; j < y + size; ++j)
        {
            if (my_board[x][j] != 0)
            {
                valid = false;
                break;
            }
        }
        if (valid && y + size - 1 != y)
            ret.push_back({x, y + size - 1});
    }

    if (y - size + 1 >= 0) // Left
    {
        bool valid = true;
        for (int j = y; j > y - size; --j)
        {
            if (my_board[x][j] != 0)
            {
                valid = false;
                break;
            }
        }
        if (valid && y - size + 1 != y)
            ret.push_back({x, y - size + 1});
    }

    return ret;
}

void Board::place_boat(int x, int y, int tail_x, int tail_y, int size)
{
    if (x == tail_x)
    { // Vertical placement
        int start = min(y, tail_y);
        int end = max(y, tail_y);
        for (int j = start; j <= end; j++)
        {
            my_board[x][j] = 1;
        }
    }
    else if (y == tail_y)
    { // Horizontal placement
        int start = min(x, tail_x);
        int end = max(x, tail_x);
        for (int i = start; i <= end; i++)
        {
            my_board[i][y] = 1;
        }
    }
}

    Attack Board::get_attack(int sock)
    {
        cout << "YOU ARE BEING ATTACKED THIS TURN" << endl;
        int buffer[2] = {0};
        recv(sock, buffer, sizeof(buffer), 0);
        Attack a{buffer[0], buffer[1]};
        return a;
    }

    int Board::send_attack(int sock)
    {
        cout << "ITS YOUR TURN TO ATTACK" << endl;
        int coords[2] = {0};
        cout << "Enter the x coordinate for your attack, boss: ";
        cin >> coords[0];
        cout << "Enter the y coordinate for your attack, general: ";
        cin >> coords[1];
        if (their_board[coords[1]][coords[0]] != 0) {
            cout << "You already did that, dumbo" << endl << endl;
            send_attack(sock);
        }
        send(sock, coords, sizeof(coords), 0);

        // Will receive confirmation
        char *msg = "No hit. Keep trying, my liege.";
        int buffer[1] = {0};
        recv(sock, buffer, sizeof(buffer), 0);
        if (buffer[0] == 2) {
            msg = "You hit their goddamn ship. Good shit, my leige";
        }
        if (buffer[0] == 3) {
            return -1;
        }
        their_board[coords[1]][coords[0]] = buffer[0];
        cout << msg << endl << endl;
        return 0;
    }

    void Board::send_confirmation(int sock, int hit) {
        int sent[1] = {0};
        sent[0] = hit;
        send(sock, sent, sizeof(sent), 0);
    }

void Board::play(int sock, int player_no) {
    while(!Board::lose()) {
        print_board();
        print_theirs();
        // Iteration case for attacker
        if (player_no == 0) {
            if (send_attack(sock)) {
                break;
            }
            player_no = 1;
        }
        // Iteration case for attacked one
        else {
            Attack a = get_attack(sock);
            int hit = 1;
            if (my_board[a.y][a.x] == 1)
            {
                cout << "YOU GOT HIT GGS" << endl;
                hit = 2;
                my_board[a.y][a.x] = 2;
            }

            send_confirmation(sock, hit);
            player_no = 0;
        }
    }

    if(lose()) {
        cout << "You lost, womp womp" << endl;
        send_confirmation(sock, 3);
    }
    else {
        cout << "WOOOOOHOOOOO U WON" << endl;
    }
}