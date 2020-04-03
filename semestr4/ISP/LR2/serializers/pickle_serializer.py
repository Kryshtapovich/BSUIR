import pickle
from .serializer import Serializer


class PickleSerializer(Serializer):

    def dump(self, obj, file_path):
        with open(file_path, 'wb') as file:
            pickle.dump(obj, file)

    def dumps(self, python_object):
        return pickle.dumps(super().dumps(python_object))

    def load(self, file_path):
        with open(file_path, 'rb') as file:
            obj = pickle.load(file)

        return obj

    def loads(self, pickle_string):
        return super().loads(pickle.loads(pickle_string))
