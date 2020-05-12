// #include <stdio.h>
// #include <winsock2.h>

//  #pragma comment(lib,"ws2_32.lib") //Winsock Library

// #define PORT 3000

// int main(int argc, char *argv[])
// {
//     WSADATA wsa;
//     SOCKET s;
//     struct sockaddr_in server;
//     char *message, server_reply[2000];
//     int recv_size;

//     printf("\nInitialising Winsock...");
//     if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
//     {
//         printf("Failed. Error Code : %d", WSAGetLastError());
//         return 1;
//     }

//     printf("Initialised.\n");

//     if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
//     {
//         printf("Error in creating the socket : %d", WSAGetLastError());
//     }

//     printf("Succeful Socket creation. \n");

//     server.sin_addr.s_addr = inet_addr("94.142.241.111");
//     server.sin_family = AF_INET;
//     server.sin_port = htons(23);
//     printf("server size %d\n", sizeof(server));

//     int rc = 0;
//     if ((rc = connect(s, (struct sockaddr *)&server, sizeof(server))) < 0)
//     {
//         puts("connect error");
//         printf("error code %d\n", rc);
//         return 1;
//     }
//     puts("Connected");

//     message = "Hello";
//     if (send(s, message, strlen(message), 0) < 0)
//     {
//         puts("Send failed");
//         return 1;
//     }

//     puts("Data sent");

//     if ((recv_size = recv(s, server_reply, 2000, 0)) == SOCKET_ERROR)
//     {
//         puts("recv failed");
//     }

//     puts("received\n");

//   //  server_reply[recv_size] = '/0';
//     puts(server_reply);
//     closesocket(s);
//     WSACleanup();

//     return 0;
// }