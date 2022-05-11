#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 80
#define IP_ADDR "5.161.32.90"

int main()
{

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        std::cout << "[!Enable to create socket]";
        return -1;
    }

    sockaddr_in server = {'\0', AF_INET, htons(PORT), {inet_addr(IP_ADDR)}};

    int con = connect(sock, (sockaddr *)&server, sizeof(server));
    if (con < 0)
    {
        std::cout << "[!Enable to create socket]";
        return -1;
    }

    std::string req = "GET /twitter/latest/";
    std::string user_name;
    std::cout << "Enter twitter username : ";
    std::cin >> user_name;
    req = req + user_name + " HTTP/1.1\r\nHost:decapi.me\r\nUser-Agent:curl/7.35.0\r\n\r\n";

    send(sock, (char *)&req[0], 83, 0);

    int res_len = 20480;
    char res[res_len];
    recv(sock, res, res_len, 0);


    char end_word[8] = "preload";
    int count = 0, i = 0;

    while (i != 7)
    {
        if (res[count] == end_word[i])
            i++;
        else
            i = 0;

        count++;
    }

    while (res[count] != '0')
    {
        std::cout << res[count];
        count++;
    }
    std::cout << "\n";

    close(sock);
    return 0;
}