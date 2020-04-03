import socket
from threading import Thread
from des import Des

import const_tcp
import const_kerberos


class Client:
    def __init__(self):
        self.sock_kerberos = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock_kerberos.connect((
            const_kerberos.KERBEROS_IP,
            const_kerberos.KERBEROS_PORT))

        self.step_1_send_authentication_key()

        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect((
            const_tcp.TCP_IP,
            const_tcp.TCP_PORT))

    def sending(self):
        while True:
            self.sock.send(input().encode('UTF-8'))

    def receiving_kerberos(self):
        data = self.sock_kerberos.recv(const_kerberos.BUFFER_SIZE)
        key_2 = data.decode('UTF-8')
        print(f'Get key from kerberos server: {key_2}')

        self.sock_kerberos.send(
            str(self.step_3_generate_key(key_2)).encode('UTF-8'))

        key_4 = self.sock_kerberos.recv(
            const_kerberos.BUFFER_SIZE).decode('UTF-8')
        print(f'Get key from kerberos server: {key_4}\n')

        self.sock.send(key_4.encode('UTF-8'))
        self.sock.send(str(self.step_5_generate_key()).encode('UTF-8'))

        data = self.sock.recv(const_tcp.BUFFER_SIZE)
        print(data.decode('UTF-8'))

    def start(self):
        send_thread = Thread(target=self.sending)
        receive_thread = Thread(target=self.receiving_kerberos)
        send_thread.start()
        receive_thread.start()

    def step_1_send_authentication_key(self):
        print('Connection with kerberos server')
        _, address = self.sock_kerberos.getsockname()
        self.sock_kerberos.send(str(address).encode('UTF-8'))

    def step_3_generate_key(self, key_tgs):
        return Des.encrypt(
            int(key_tgs),
            int(const_kerberos.AUT.encode('UTF-8').hex(), 16))

    def step_5_generate_key(self):
        return Des.encrypt(
            int(const_kerberos.KC.encode('UTF-8').hex(), 16),
            int(const_kerberos.KC_TGS.encode('UTF-8').hex(), 16))


if __name__ == '__main__':
    new_client = Client()
    new_client.start()
