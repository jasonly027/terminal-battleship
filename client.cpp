#include "board.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

int create_client_sock(int port)
{
    int c_sock;

    sockaddr_in s_address;
    s_address.sin_family = AF_INET;
    s_address.sin_addr.s_addr = INADDR_ANY;
    s_address.sin_port = htons(port);

    while (true)
    {
        c_sock = socket(AF_INET, SOCK_STREAM, 0);
        if (connect(c_sock, (struct sockaddr *)&s_address, sizeof(s_address)) < 0)
        {
            cout << "Waiting on server, retrying in 5 seconds: " << endl;
            close(c_sock);
            sleep(5);
        }
        else
        {
            cout << "TIME TO PLAY BATTLESHIPS" << endl
                      << endl;
            break;
        }
    }
    return c_sock;
}

int main()
{
    Board c_board;
    int c_sock = create_client_sock(64209);

    c_board.play(c_sock, 1);

    close(c_sock);
    return 0;
}
