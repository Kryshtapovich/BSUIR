class ECC(object):

    def __init__(self, a, b, p, base_point):
        self.curve = (a,b,p)
        self.base_point = base_point
        self.double_base_point = self.double_point(base_point)

    def xgcd(self, b, n):
        x0, x1, y0, y1 = 1, 0, 0, 1
        while n != 0:
            q, b, n = b // n, n, b % n
            x0, x1 = x1, x0 - q * x1
            y0, y1 = y1, y0 - q * y1
        return b, x0, y0

    def inverse(self, b):
        g, x, _ = self.xgcd(b, self.curve[2])
        if g == 1:
            return x % self.curve[2]

    def add_points(self, p, q):
        delta = 0

        if p == None or q == None:
            return p if q == None else q
        elif p[0] == q[0] and p[1] == q[1]:
            delta = (3 * p[0]**2 + self.curve[0]) * \
                    self.inverse(2 * p[1]) % self.curve[2]
        else:
            delta = (p[1] - q[1]) * self.inverse((p[0] - q[0])) % self.curve[2]

        x = (delta * delta - p[0] - q[0]) % self.curve[2]
        y = (delta * (p[0] - x) - p[1]) % self.curve[2]

        return (x,y)

    def double_point(self, p, k = 1):
        Q = p
        for i in range(0,k):
            Q = self.add_points(Q,Q)
        return Q

    def base_point_mult(self, k):
        Q = None
        for i in [1 if digit == '1' else 0 for digit in bin(k)[2:]]:
            Q = self.double_point(Q)
            if i == 1:
                Q = self.add_points(Q, self.base_point)

        return Q

class DiffieHellman(object):

    def __init__(self, elliptic_curve, point_g):
        self.elliptic_curve = elliptic_curve
        self.point_g = point_g

    def generate_public_key(self, private_key):
        if private_key < 0:
            raise ValueError
        return self.elliptic_curve.double_point(self.point_g, private_key)

    def secret_key(self, private_key, public_key):
        return self.elliptic_curve.double_point(public_key, private_key)[0]

point_g = (
    0x188da80eb03090f67cbf20eb43a18800f4ff0afd82ff1012, # Gx
    0x07192b95ffc8da78631011ed6b24cdd573f977a11e794811) # Gy

curve = ECC(
    -3, # a
    0x64210519e59c80e70fa7e9ab72243049feb8deecc146b9b1, # b
    6277101735386680763835789423207666416083908700390324961279, # p
    point_g)

dh = DiffieHellman(curve, point_g)

private_key1 = 7919
public_key1 = dh.generate_public_key(private_key1)

private_key2 = 8387
public_key2 = dh.generate_public_key(private_key2)

private_key3 = 10657
public_key3 = dh.generate_public_key(private_key3)

print("private_key1: {} \npublic_key1 {}\n \nprivate_key2: {} \npublic_key2: {}\n \nprivate_key3: {} \npublic_key3: {}\n"
    .format(private_key1, public_key1, private_key2, public_key2, private_key3, public_key3))
print("dh.secret_key(private_key1, public_key2) {}".format(dh.secret_key(private_key1, public_key2)))
print("dh.secret_key(private_key2, public_key1) {}".format(dh.secret_key(private_key2, public_key1)))