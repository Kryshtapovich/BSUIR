class BaseDes(object):
    def __init__(self, pad=None):
        if pad:
            pad = self.must_be_bytes(pad)
        self.block_size = 8

        self._padding = pad

    def get_key(self):
        return self.__key

    def set_key(self, key):
        key = self.must_be_bytes(key)
        self.__key = key

    def get_padding(self):
        return self._padding

    def set_padding(self, pad):
        if pad is not None:
            pad = self.must_be_bytes(pad)
        self._padding = pad

    def pad_data(self, data, pad):

        if len(data) % self.block_size == 0:
            return data
        if not pad:
            pad = self.get_padding()
        if not pad:
            raise ValueError(
                "Data must be a multiple of " + str(self.block_size) + " bytes in length. Set the pad character.")
        data += (self.block_size - (len(data) % self.block_size)) * pad

        return data

    def unpad_data(self, data, pad):

        if not data:
            return data

        if not pad:
            pad = self.get_padding()
        if pad:
            data = data[:-self.block_size] + \
                   data[-self.block_size:].rstrip(pad)

        return data

    def must_be_bytes(self, data):

        if isinstance(data, str):

            try:
                return data.encode('ascii')
            except UnicodeEncodeError:
                pass
            raise ValueError("This program can only work with encoded strings, not Unicode.")
        return data