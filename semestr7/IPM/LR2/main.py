import sys
from constants import *
from stb import STB

file = open("sample.txt", "r")
data = file.read()
print("Data: %r\n" % data)

key = int.from_bytes('erpwkwekrokpdasdasda'.encode(), 'big')
synchro = 312312412412

s = STB(key, mode=PLAIN)
encrypted_text = s.encrypt(data, S=synchro)
print("Encrypted: %r" % encrypted_text)
decrypted_text = s.decrypt(encrypted_text, S=synchro)
print("Decrypted: %r\n" % decrypted_text)
