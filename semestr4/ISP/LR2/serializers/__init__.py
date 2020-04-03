from .pickle_serializer import PickleSerializer
from .json_serializer import JsonSerializer
from .toml_serializer import TomlSerializer
from .yaml_serializer import YamlSerializer
from .converter import *


class SerializerType:
    Pickle = 1,
    Json = 2,
    Yaml = 3,
    Toml = 4


class SerializerFactory:
    @staticmethod
    def get_instance(serializer_type):
        if serializer_type == SerializerType.Pickle:
            return PickleSerializer()
        elif serializer_type == SerializerType.Json:
            return JsonSerializer()
        elif serializer_type == SerializerType.Toml:
            return TomlSerializer()
        elif serializer_type == SerializerType.Yaml:
            return YamlSerializer()
        else:
            raise Exception('Incorrect serializer type')
