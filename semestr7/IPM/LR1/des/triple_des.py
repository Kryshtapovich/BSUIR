from .base import BaseDes
from .single_des import Des

class TripleDes(BaseDes):
    def __init__(self, key, pad=None):
        BaseDes.__init__(self, pad)
        self.key_size = 24
        self.set_key(key)

    def set_key(self, key):
        if len(key) != self.key_size:
            raise ValueError("Invalid triple DES key size. Key must be 24 bytes long")

        self.__key1 = Des(key[:8], self._padding)
        self.__key2 = Des(key[8:16], self._padding)
        self.__key3 = Des(key[16:], self._padding)

        BaseDes.set_key(self, key)

    def set_padding(self, pad):
        BaseDes.set_padding(self, pad)
        for key in (self.__key1, self.__key2, self.__key3):
            key.set_padding(pad)

    def encrypt(self, data, pad=None):
        ENCRYPT = Des.ENCRYPT
        DECRYPT = Des.DECRYPT
        data = self.must_be_bytes(data)
        if pad is not None:
            pad = self.must_be_bytes(pad)
        # Pad the data accordingly.
        data = self.pad_data(data, pad)
        data = self.__key1.crypt(data, ENCRYPT)
        data = self.__key2.crypt(data, DECRYPT)
        return self.__key3.crypt(data, ENCRYPT)

    def decrypt(self, data, pad=None):
        ENCRYPT = Des.ENCRYPT
        DECRYPT = Des.DECRYPT
        data = self.must_be_bytes(data)
        if pad is not None:
            pad = self.must_be_bytes(pad)
        data = self.__key3.crypt(data, DECRYPT)
        data = self.__key2.crypt(data, ENCRYPT)
        data = self.__key1.crypt(data, DECRYPT)
        return self.unpad_data(data, pad)