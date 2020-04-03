from const_des import BLOCK_SIZE, KEY_SIZE, IP, IP_INV, PC1, PC2, E, S_BOXES, P


class Des:
    @staticmethod
    def encrypt(msg, key, decrypt=False):
        key = Des.permutation_by_table(key, BLOCK_SIZE, PC1)

        C0 = key >> 28
        D0 = key & (2**28-1)
        round_keys = Des.generate_round_keys(C0, D0)

        msg_block = Des.permutation_by_table(msg, BLOCK_SIZE, IP)
        L0 = msg_block >> 32
        R0 = msg_block & (2**32-1)

        L_last = L0
        R_last = R0
        for i in range(1, 17):
            if decrypt:
                i = 17-i
            key = Des.round_function(R_last, round_keys[i])
            L_round = R_last
            R_round = L_last ^ key
            L_last = L_round
            R_last = R_round

        cipher_block = (R_round << 32) + L_round
        cipher_block = Des.permutation_by_table(
            cipher_block,
            BLOCK_SIZE,
            IP_INV)

        return cipher_block

    @staticmethod
    def round_function(Ri, Ki):
        Ri = Des.permutation_by_table(Ri, 32, E)
        Ri ^= Ki
        Ri_blocks = [
            ((Ri & (0b111111 << shift_val)) >> shift_val)
            for shift_val in (42, 36, 30, 24, 18, 12, 6, 0)]

        for i, block in enumerate(Ri_blocks):
            row = ((0b100000 & block) >> 4) + (0b1 & block)
            col = (0b011110 & block) >> 1
            Ri_blocks[i] = S_BOXES[i][16*row+col]

        Ri_blocks = zip(Ri_blocks, (28, 24, 20, 16, 12, 8, 4, 0))
        Ri = 0
        for block, lshift_val in Ri_blocks:
            Ri += (block << lshift_val)
        Ri = Des.permutation_by_table(Ri, 32, P)

        return Ri

    @staticmethod
    def permutation_by_table(block, block_len, table):
        block_str = bin(block)[2:].zfill(block_len)
        perm = []
        for pos in range(len(table)):
            perm.append(block_str[table[pos]-1])
        return int(''.join(perm), 2)

    @staticmethod
    def lrot(val, r_bits, max_bits):
        return (val << r_bits % max_bits) & (2**max_bits-1) | \
            ((val & (2**max_bits-1)) >> (max_bits-(r_bits % max_bits)))

    @staticmethod
    def generate_round_keys(C0, D0):
        round_keys = dict.fromkeys(range(0, 17))
        lrot_values = (1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1)

        C0 = Des.lrot(C0, 0, 28)
        D0 = Des.lrot(D0, 0, 28)
        round_keys[0] = (C0, D0)

        for i, rot_val in enumerate(lrot_values):
            i += 1
            Ci = Des.lrot(round_keys[i-1][0], rot_val, 28)
            Di = Des.lrot(round_keys[i-1][1], rot_val, 28)
            round_keys[i] = (Ci, Di)

        del round_keys[0]

        for i, (Ci, Di) in round_keys.items():
            Ki = (Ci << 28) + Di
            round_keys[i] = Des.permutation_by_table(Ki, KEY_SIZE, PC2)

        return round_keys
