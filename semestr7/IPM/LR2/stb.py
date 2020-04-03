from constants import *

class STB:
    def __init__(self, key, mode=COUNTER):
        count = self.get_key_chunks_counts(key)
        self.tmp_keys = []

        for i in range(count):
            self.tmp_keys.append(key & 0xFFFF)
            key >>= 32

        if count == 4:
            self.tmp_keys.extend(self.tmp_keys[:])
        elif count == 6:
            self.tmp_keys.extend([
                self.tmp_keys[0] ^ self.tmp_keys[1] ^ self.tmp_keys[2],
                self.tmp_keys[3] ^ self.tmp_keys[4] ^ self.tmp_keys[5]
            ])

        self.K = []
        for _ in range(8):
            self.K.extend(self.tmp_keys[:])

        self.mode = mode

    def get_key_chunks_counts(self, key):
        l = len(bin(key)[2:])
        l &= (1 << 256) - 1
        if 256 >= l > 192:
            return 8
        elif 192 >= l > 128:
            return 6
        elif l <= 128:
            return 4

    def rot_hi(self, u):
        if u < 1 << 31:
            return (2 * u) % (1 << 32)
        else:
            return (2 * u + 1) % (1 << 32)

    def rot_hi_r(self, u, r):
        result = u
        for i in range(r):
            result = self.rot_hi(result)
        return result

    def square_plus(self, u, v):
        return (u + v) % (1 << 32)

    def square_minus(self, u, v):
        return (u - v) % (1 << 32)

    def L(self, X, Y):
        l = len(bin(X)) - 2
        res = int(bin(Y)[2:l+2], base=2)
        return Y

    def G(self, r, word):
        mask = (1 << 8) - 1
        final = 0
        for i in range(4):
            part = word & mask
            word >>= 8
            r = part & 0x0F
            l = (part & 0xF0) >> 4
            result = H[l][r]
            result <<= 8 * i
            final += result
        return self.rot_hi_r(final, r)

    def encrypt_block(self, X):
        if self.get_key_chunks_counts(X) != 4:
            raise ValueError()
        d = X & 0xFFFFFFFF
        X >>= 32
        c = X & 0xFFFFFFFF
        X >>= 32
        b = X & 0xFFFFFFFF
        X >>= 32
        a = X

        for i in range(1, 9):
            b = b ^ self.G(5, self.square_plus(a, self.K[7*i - 7]))
            c = c ^ self.G(21, self.square_plus(d, self.K[7*i - 6]))
            a = self.square_minus(a, self.G(13, self.square_plus(b, self.K[7*i - 5])))
            e = self.G(21, self.square_plus(self.square_plus(b, c), self.K[7*i - 4] )) ^ (i % (2 ** 32))
            b = self.square_plus(b, e)
            c = self.square_minus(c, e)
            d = self.square_plus(d, self.G(13,self.square_plus(c, self.K[7*i - 3])))
            b = b ^ self.G(21, self.square_plus(a, self.K[7*i - 2]))
            c = c ^ self.G(5, self.square_plus(d, self.K[7*i - 1]))
            a, b = b, a
            c, d = d, c
            b, c = c, b

        return (b << 96) + (d << 64) + (a << 32) + c

    def decrypt_block(self, X):
        if self.get_key_chunks_counts(X) != 4:
            raise ValueError()
        d = X & 0xFFFFFFFF
        X >>= 32
        c = X & 0xFFFFFFFF
        X >>= 32
        b = X & 0xFFFFFFFF
        X >>= 32
        a = X

        for i in range(8, 0, -1):
            b = b ^ self.G(5, self.square_plus(a, self.K[7*i - 1]))
            c = c ^ self.G(21, self.square_plus(d, self.K[7*i - 2]))
            a = self.square_minus(a, self.G(13, self.square_plus(b, self.K[7*i - 3])))
            e = self.G(21, self.square_plus(self.square_plus(b, c), self.K[7*i - 4] )) ^ (i % (2 ** 32))
            b = self.square_plus(b, e)
            c = self.square_minus(c, e)
            d = self.square_plus(d, self.G(13,self.square_plus(c, self.K[7*i - 5])))
            b = b ^ self.G(21, self.square_plus(a, self.K[7*i - 6]))
            c = c ^ self.G(5, self.square_plus(d, self.K[7*i - 7]))
            a, b = b, a
            c, d = d, c
            a, d = d, a

        return (c << 96) + (a << 64) + (d << 32) + b

    def split_message(self, message):
        chunks = []
        chunk = 0
        while message:
            chunk = message & 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            chunks.append(chunk)
            message >>= 128
        return chunks

    def join_message(self, chunks):
        answer = 0
        for chunk in chunks:
            answer <<= 128
            answer += chunk
        return answer

    def encrypt_block_plain(self, chunks):
        results = []

        for X in chunks:
            Y = self.encrypt_block(X)
            results.append(Y)

        return results

    def decrypt_block_plain(self, chunks):
        results = []

        for X in chunks:
            Y = self.decrypt_block(X)
            results.append(Y)

        return results

    def encrypt_block_coupled(self, chunks, S):
        results = []

        for X in chunks:
            Y = self.encrypt_block(X ^ S)
            results.append(Y)
            S = Y

        return results

    def decrypt_block_coupled(self, chunks, S):
        results = []

        for X in chunks:
            Y = self.decrypt_block(X) ^ S
            results.append(Y)
            S = X

        return results

    def encrypt_block_gamming(self, chunks, S):
        results = []

        for X in chunks:
            Y = X ^ self.L(X, self.encrypt_block(S))
            results.append(Y)
            S = Y

        return results

    def decrypt_block_gamming(self, chunks, S):
        results = []

        for X in chunks:
            Y = X ^ self.L(X, self.encrypt_block(S))
            results.append(Y)
            S = X

        return results

    def encrypt_counter(self, chunks, S):
        results = []

        s = self.encrypt_block(S)
        for X in chunks:
            s = self.square_plus(s, 1)
            Y = X ^ self.L(X, self.encrypt_block(s))
            results.append(Y)

        return results

    def decrypt_counter(self, chunks, S):
        return self.encrypt_counter(chunks, S)

    def encrypt(self, message: str, **kwargs):
        plain_msg = int.from_bytes(message.encode(), 'big')
        chunks = self.split_message(plain_msg)

        synchro = kwargs['S']

        if self.mode == BLOCK:
            results = self.encrypt_block_coupled(chunks, synchro)
        elif self.mode == PLAIN:
            results = self.encrypt_block_plain(chunks)
        elif self.mode == GAMMING:
            results = self.encrypt_block_gamming(chunks, synchro)
        elif self.mode == COUNTER:
            results = self.encrypt_counter(chunks, synchro)

        answer = self.join_message(results)

        return answer.to_bytes((answer.bit_length() + 7) // 8, 'big')

    def decrypt(self, message: bytes, **kwargs):
        plain_msg = int.from_bytes(message, 'big')
        chunks = reversed(self.split_message(plain_msg))

        synchro = kwargs['S']

        if self.mode == BLOCK:
            results = self.decrypt_block_coupled(chunks, synchro)
        elif self.mode == PLAIN:
            results = self.decrypt_block_plain(chunks)
        elif self.mode == GAMMING:
            results = self.decrypt_block_gamming(chunks, synchro)
        elif self.mode == COUNTER:
            results = self.decrypt_counter(chunks, synchro)

        answer = self.join_message(reversed(results))
        return answer.to_bytes((answer.bit_length() + 7) // 8, 'big').decode()