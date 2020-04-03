from os import urandom
from hashlib import sha1
from codecs import getdecoder
from codecs import getencoder


_hexdecoder = getdecoder("hex")
_hexencoder = getencoder("hex")

def hexdec(data):
    return _hexdecoder(data)[0]

def hexenc(data):
    return _hexencoder(data)[0].decode("ascii")


def modinvert(a, n):
    if a < 0:
        return n - modinvert(-a, n)
    t, newt = 0, 1
    r, newr = n, a
    while newr != 0:
        quotinent = r // newr
        t, newt = newt, t - quotinent * newt
        r, newr = newr, r - quotinent * newr
    if r > 1:
        return -1
    if t < 0:
        t = t + n
    return t

def bytes2long(raw):
    return int(hexenc(raw), 16)


def long2bytes(n, size=32):
    res = hex(int(n))[2:].rstrip("L")
    if len(res) % 2 != 0:
        res = "0" + res
    s = hexdec(res)
    if len(s) != size:
        s = (size - len(s)) * b"\x00" + s
    return s

class GOST3410Curve(object):
    def __init__(self, p, q, a, b, x, y, e=None, d=None):
        self.p = p
        self.q = q
        self.a = a
        self.b = b
        self.x = x
        self.y = y
        self.e = e
        self.d = d
        r1 = self.y * self.y % self.p
        r2 = ((self.x * self.x + self.a) * self.x + self.b) % self.p
        if r1 != self.pos(r2):
            raise ValueError("Invalid parameters")
        self._st = None

    def pos(self, v):
        if v < 0:
            return v + self.p
        return v

    def _add(self, p1x, p1y, p2x, p2y):
        if p1x == p2x and p1y == p2y:
            t = ((3 * p1x * p1x + self.a) * modinvert(2 * p1y, self.p)) % self.p
        else:
            tx = self.pos(p2x - p1x) % self.p
            ty = self.pos(p2y - p1y) % self.p
            t = (ty * modinvert(tx, self.p)) % self.p
        tx = self.pos(t * t - p1x - p2x) % self.p
        ty = self.pos(t * (p1x - tx) - p1y) % self.p
        return tx, ty

    def exp(self, degree, x=None, y=None):
        x = x or self.x
        y = y or self.y
        tx = x
        ty = y
        if degree == 0:
            raise ValueError("Bad degree value")
        degree -= 1
        while degree != 0:
            if degree & 1 == 1:
                tx, ty = self._add(tx, ty, x, y)
            degree = degree >> 1
            x, y = self._add(x, y, x, y)
        return tx, ty

    def st(self):
        """Compute s/t parameters for twisted Edwards curve points conversion
        """
        if self.e is None or self.d is None:
            raise ValueError("non twisted Edwards curve")
        if self._st is not None:
            return self._st
        self._st = (
            self.pos(self.e - self.d) * modinvert(4, self.p) % self.p,
            (self.e + self.d) * modinvert(6, self.p) % self.p,
        )
        return self._st

def public_key(curve, prv):
    """ Generate public key from the private one"""
    return curve.exp(prv)


def sign(curve, prv, digest):
    """ Calculate signature for provided digest"""
    size = 64
    q = curve.q
    e = bytes2long(digest) % q
    if e == 0:
        e = 1
    while True:
        k = bytes2long(urandom(size)) % q
        if k == 0:
            continue
        r, _ = curve.exp(k)
        r %= q
        if r == 0:
            continue
        d = prv * r
        k *= e
        s = (d + k) % q
        if s == 0:
            continue
        break
    return long2bytes(s, size) + long2bytes(r, size)


def verify(curve, pub, digest, signature):
    """ Verify provided digest with the signature"""
    size = 64
    if len(signature) != size * 2:
        raise ValueError("Invalid signature length")
    q = curve.q
    p = curve.p
    s = bytes2long(signature[:size])
    r = bytes2long(signature[size:])
    if r <= 0 or r >= q or s <= 0 or s >= q:
        return False
    e = bytes2long(digest) % curve.q
    if e == 0:
        e = 1
    v = modinvert(e, q)
    z1 = s * v % q
    z2 = q - r * v % q
    p1x, p1y = curve.exp(z1)
    q1x, q1y = curve.exp(z2, pub[0], pub[1])
    lm = q1x - p1x
    if lm < 0:
        lm += p
    lm = modinvert(lm, p)
    z1 = q1y - p1y
    lm = lm * z1 % p
    lm = lm * lm % p
    lm = lm - p1x - q1x
    lm = lm % p
    if lm < 0:
        lm += p
    lm %= q
    # This is not constant time comparison!
    return lm == r


def prv_unmarshal(prv):
    """Unmarshal private key"""
    return bytes2long(prv[::-1])


def pub_marshal(pub):
    """Marshal public key"""
    size = 32
    return (long2bytes(pub[1], size) + long2bytes(pub[0], size))[::-1]


def pub_unmarshal(pub):
    """Unmarshal public key"""
    size = 32
    pub = pub[::-1]
    return (bytes2long(pub[size:]), bytes2long(pub[:size]))


def uv2xy(curve, u, v):
    """Convert twisted Edwards curve U,V coordinates to Weierstrass X,Y"""
    s, t = curve.st()
    k1 = (s * (1 + v)) % curve.p
    k2 = curve.pos(1 - v)
    x = t + k1 * modinvert(k2, curve.p)
    y = k1 * modinvert(u * k2, curve.p)
    return x % curve.p, y % curve.p


def xy2uv(curve, x, y):
    """Convert Weierstrass X,Y coordinates to twisted Edwards curve U,V"""
    s, t = curve.st()
    xmt = curve.pos(x - t)
    u = xmt * modinvert(y, curve.p)
    v = curve.pos(xmt - s) * modinvert(xmt + s, curve.p)
    return u % curve.p, v % curve.p

curve = GOST3410Curve(
        p=bytes2long(hexdec("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD97")),
        q=bytes2long(hexdec("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF6C611070995AD10045841B09B761B893")),
        a=bytes2long(hexdec("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD94")),
        b=bytes2long(hexdec("00000000000000000000000000000000000000000000000000000000000000a6")),
        x=bytes2long(hexdec("0000000000000000000000000000000000000000000000000000000000000001")),
        y=bytes2long(hexdec("8D91E471E0989CDA27DF505A453F2B7635294F2DDF23E3B122ACC99C9E9F1E14")),
)
prv_raw = urandom(32)
prv = prv_unmarshal(prv_raw)
pub = public_key(curve, prv)
print("Public key: %r" % hexenc(pub_marshal(pub)))
data_for_signing = b"some data"
dgst = sha1(data_for_signing).digest()
signature = sign(curve, prv, dgst)
verify(curve, pub, dgst, signature)
