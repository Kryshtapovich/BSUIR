import json


class Configurator:

    @staticmethod
    def get_configuration(file_path):
        with open(file_path, 'r') as file:
            configuration = json.load(file)
        return configuration
