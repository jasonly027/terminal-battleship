#include "board.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

int create_server_sock(int port)
{
     int s_sock = socket(AF_INET, SOCK_STREAM, 0);

     sockaddr_in s_address;
     s_address.sin_family = AF_INET;
     s_address.sin_addr.s_addr = INADDR_ANY;
     s_address.sin_port = htons(port);

     ::bind(s_sock, (struct sockaddr *)&s_address, sizeof(s_address));

     return s_sock;
}

int connect_2_client(int s_sock)
{
     listen(s_sock, 5);
     cout << "Waiting for client to finish setup and connect!" << endl;
     int c_sock = accept(s_sock, NULL, NULL);
     cout << "Let's play battleships!" << endl<< endl;
     return c_sock;
}

int main()
{
     Board s_board;
     int s_sock = create_server_sock(64209);
     int c_sock = connect_2_client(s_sock);

     s_board.play(c_sock, 0);

     close(c_sock);
     close(s_sock);

     return 0;
}
