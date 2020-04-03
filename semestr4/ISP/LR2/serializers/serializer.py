from .converter import Converter
import inspect


class Serializer:

    def __init__(self):
        self.__converter = Converter()

    def dump(self, obj, file_path):
        with open(file_path, 'w') as file:
            file.write(self.dumps(obj))

    def dumps(self, obj):
        if inspect.isfunction(obj):
            return self.__converter.function_to_dict(obj)
        else:
            return self.__converter.object_to_dict(obj)

    def load(self, file_path):
        with open(file_path, 'r') as file:
            python_object = self.loads(file.read())

        return python_object

    def loads(self, obj_dict):
        if 'code' in obj_dict:
            return self.__converter.dict_to_function(obj_dict)
        else:
            return self.__converter.dict_to_object(obj_dict)
