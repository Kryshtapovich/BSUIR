from des import Des, DoubleDes, TripleDes

file = open("sample.txt", "r")
data = file.read().encode()
print("Data: %r\n" % data)

k = Des(b"DESCRYPT", pad=b"\1")
d = k.encrypt(data)
print("DES")
print("Encrypted: %r" % d)
print("Decrypted: %r\n" % k.decrypt(d))
assert k.decrypt(d) == data

k = DoubleDes(b"DESCRYPTREALREAL", pad=b"\1")
d = k.encrypt(data)
print("Double DES")
print("Encrypted: %r" % d)
print("Decrypted: %r\n" % k.decrypt(d))
assert k.decrypt(d) == data

k = TripleDes(b"DESCRYPTREALREALHOOLHOOL", pad=b"\1")
d = k.encrypt(data)
print("Triple DES")
print("Encrypted: %r" % d)
print("Decrypted: %r\n" % k.decrypt(d))
assert k.decrypt(d) == data