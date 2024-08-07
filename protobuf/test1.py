import socket
import message_pb2

def main():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('127.0.0.1', 1708))  
    server_socket.listen(1)
    print('esperando msgs da porta 1708.')

    client_socket, addr = server_socket.accept()
    print(f'erro: {addr}')

    while True:
        data = client_socket.recv(4096)
        if not data:
            break

        message = message_pb2.MyMessage()
        message.ParseFromString(data)

        print(f'ID: {message.id}')
        print(f'content: {message.content}')

    client_socket.close()
    server_socket.close()

if __name__ == '__main__':
    main()
