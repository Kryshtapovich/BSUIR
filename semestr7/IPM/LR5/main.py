from hashlib import sha1

trans_5C = bytes((x ^ 0x5C) for x in range(256))
trans_36 = bytes((x ^ 0x36) for x in range(256))

digest_size = None

class HMAC:
    blocksize = 64

    def __init__(self, key, msg=None, digestmod=''):
        if not isinstance(key, (bytes, bytearray)):
            raise TypeError("key: expected bytes or bytearray, but got %r" % type(key).__name__)

        if not digestmod:
            raise TypeError("Missing required parameter 'digestmod'.")

        self.digest_cons = digestmod
        self.outer = self.digest_cons()
        self.inner = self.digest_cons()
        self.digest_size = self.inner.digest_size

        blocksize = self.inner.block_size

        self.block_size = blocksize

        if len(key) > blocksize:
            key = self.digest_cons(key).digest()

        key = key.ljust(blocksize, b'\0')
        self.outer.update(key.translate(trans_5C))
        self.inner.update(key.translate(trans_36))
        if msg is not None:
            self.update(msg)

    def update(self, msg):
        self.inner.update(msg)

    def _current(self):
        h = self.outer.copy()
        h.update(self.inner.digest())
        return h

    def digest(self):
        h = self._current()
        return h.digest()

    def hexdigest(self):
        h = self._current()
        return h.hexdigest()

def hmac(key, msg=None, digestmod=''):
    return HMAC(key, msg, digestmod)

text = b"Hello World!"
key = b"SECRET KEY"
print("Message: %r" % text)
print("Key: %r" % key)
hashed = hmac(key=key, msg=text, digestmod=sha1)
signature = hashed.hexdigest()
print("Result: %r" % signature)