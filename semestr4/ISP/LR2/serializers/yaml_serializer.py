import yaml
from .serializer import Serializer


class YamlSerializer(Serializer):

    def dumps(self, obj):
        return yaml.dump(super().dumps(obj))

    def loads(self, yaml_string):
        return super().loads(yaml.unsafe_load(yaml_string))
