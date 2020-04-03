import socket
from threading import Thread
from des import Des

import const_kerberos


class KerberosServer:
    def __init__(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.bind((
            const_kerberos.KERBEROS_IP,
            const_kerberos.KERBEROS_PORT))

        self.sock.listen()

    def listening_client(self, connection, address):
        print(f'\nConnection address: {address}')

        data = connection.recv(const_kerberos.BUFFER_SIZE)
        ip, sock_number = address

        print(f'\nSender: {address}\nMessage: {data.decode("UTF-8")}')

        sendto_msg = str(self.step_2_generate_key(sock_number)).encode('UTF-8')
        connection.send(sendto_msg)
        print(f'\nSend to: {address}\nMessage: {sendto_msg.decode("UTF-8")}')

        data = connection.recv(const_kerberos.BUFFER_SIZE)
        print(f'\nSender: {address}\nMessage: {data.decode("UTF-8")}')

        sendto_msg = str(self.step_4_generate_key(
            data.decode("UTF-8"))).encode('UTF-8')
        connection.send(sendto_msg)
        print(f'\nSend to: {address}\nMessage: {sendto_msg.decode("UTF-8")}')

        connection.close()
        print(f'\nStop connection: {address}')

    def step_2_generate_key(self, sock_number):
        return Des.encrypt(
            Des.encrypt(
                int(const_kerberos.TGT.encode('UTF-8').hex(), 16),
                int(str(sock_number).encode('UTF-8').hex(), 16)
            ), int(const_kerberos.KC.encode('UTF-8').hex(), 16))

    def step_4_generate_key(self, value):
        return Des.encrypt(
            int(value),
            int(const_kerberos.KC_TGS.encode('UTF-8').hex(), 16))

    def new_connection(self):
        while True:
            connection, address = self.sock.accept()

            if connection:
                new_client_thread = Thread(
                    target=self.listening_client,
                    args=(connection, address)
                    )
                new_client_thread.start()

    def start(self):
        parent_thread = Thread(target=self.new_connection)
        parent_thread.start()


if __name__ == '__main__':
    server = KerberosServer()
    server.start()
