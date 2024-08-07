#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "message.pb.h"

void send_message(int sockfd) {
    MyMessage message;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> id_dist(1, 1000);
    std::uniform_int_distribution<> content_dist(1, 100);

    int random_id = id_dist(gen);
    std::string random_content = std::to_string(content_dist(gen));

    message.set_id(random_id);
    message.set_content(random_content);

    std::string serialized_message;
    message.SerializeToString(&serialized_message);

    send(sockfd, serialized_message.c_str(), serialized_message.size(), 0);

    std::cout << "ID: " << random_id << "\n Content: " << random_content << std::endl;
}

int main() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Socket creation failed." << std::endl;
        return 1;
    }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(1708); // Porta do servidor
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // IP do servidor

    if (connect(sockfd, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Connection failed." << std::endl;
        return 1;
    }

    while (true) {
        send_message(sockfd);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    close(sockfd);
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
