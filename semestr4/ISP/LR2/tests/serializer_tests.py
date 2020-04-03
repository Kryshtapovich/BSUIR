from .test_objects import *
import unittest

import sys

sys.path.insert(0, '/Task/serializers')
from serializers import *


class SerializerTester(unittest.TestCase):

    def __init__(self, method):
        super().__init__(method)
        self.json_serializer = SerializerFactory.get_instance(SerializerType.Json)
        self.pickle_serializer = SerializerFactory.get_instance(SerializerType.Pickle)
        self.yaml_serializer = SerializerFactory.get_instance(SerializerType.Yaml)
        self.toml_serializer = SerializerFactory.get_instance(SerializerType.Toml)

    def test_list(self):
        json_obj = self.json_serializer.loads(self.json_serializer.dumps(lst1))
        pickle_obj = self.pickle_serializer.loads(self.pickle_serializer.dumps(lst1))
        yaml_obj = self.yaml_serializer.loads(self.yaml_serializer.dumps(lst1))
        # toml_obj = self.toml_serializer.loads(self.toml_serializer.dumps(lst1))

        self.assertEqual(json_obj, lst1)
        self.assertEqual(pickle_obj, lst1)
        self.assertEqual(yaml_obj, lst1)
        # self.assertEqual(toml_obj, lst1)

    def test_simple_dicts(self):
        json_obj = self.json_serializer.loads(self.json_serializer.dumps(dict1))
        pickle_obj = self.pickle_serializer.loads(self.pickle_serializer.dumps(dict1))
        yaml_obj = self.yaml_serializer.loads(self.yaml_serializer.dumps(dict1))
        toml_obj = self.toml_serializer.loads(self.toml_serializer.dumps(dict1))
        # print(toml_obj.a)
        # print(toml_obj.b)
        # print(toml_obj)

        self.assertEqual(json_obj, exp_dict)
        self.assertEqual(pickle_obj, exp_dict)
        self.assertEqual(yaml_obj, exp_dict)
        self.assertEqual(toml_obj, exp_dict)

    def test_simple_object(self):
        json_obj = self.json_serializer.loads(self.json_serializer.dumps(obj1))
        pickle_obj = self.pickle_serializer.loads(self.pickle_serializer.dumps(obj1))
        yaml_obj = self.yaml_serializer.loads(self.yaml_serializer.dumps(obj1))
        toml_obj = self.toml_serializer.loads(self.toml_serializer.dumps(obj1))

        self.assertEqual(json_obj, exp_obj1)
        self.assertEqual(pickle_obj, exp_obj1)
        self.assertEqual(yaml_obj, exp_obj1)
        self.assertEqual(toml_obj, exp_obj1)

    def test_complex_object(self):
        json_obj = self.json_serializer.loads(self.json_serializer.dumps(obj2))
        pickle_obj = self.pickle_serializer.loads(self.pickle_serializer.dumps(obj2))
        yaml_obj = self.yaml_serializer.loads(self.yaml_serializer.dumps(obj2))
        toml_obj = self.toml_serializer.loads(self.toml_serializer.dumps(obj2))

        self.assertEqual(json_obj, exp_obj2)
        self.assertEqual(pickle_obj, exp_obj2)
        self.assertEqual(yaml_obj, exp_obj2)
        self.assertEqual(toml_obj, exp_obj2)

    def test_object_list(self):
        json_obj = self.json_serializer.loads(self.json_serializer.dumps(obj_lst))
        pickle_obj = self.pickle_serializer.loads(self.pickle_serializer.dumps(obj_lst))
        yaml_obj = self.yaml_serializer.loads(self.yaml_serializer.dumps(obj_lst))

        self.assertEqual(json_obj, exp_obj_lst)
        self.assertEqual(pickle_obj, exp_obj_lst)
        self.assertEqual(yaml_obj, exp_obj_lst)

    def test_object_dictionary(self):
        json_obj = self.json_serializer.loads(self.json_serializer.dumps(obj_dict))
        pickle_obj = self.pickle_serializer.loads(self.pickle_serializer.dumps(obj_dict))
        yaml_obj = self.yaml_serializer.loads(self.yaml_serializer.dumps(obj_dict))
        toml_obj = self.toml_serializer.loads(self.toml_serializer.dumps(obj_dict))

        self.assertEqual(json_obj, exp_obj_dict)
        self.assertEqual(pickle_obj, exp_obj_dict)
        self.assertEqual(yaml_obj, exp_obj_dict)
        self.assertEqual(toml_obj, exp_obj_dict)

    def test_simple_function(self):
        json_obj = self.json_serializer.loads(self.json_serializer.dumps(hello))
        pickle_obj = self.pickle_serializer.loads(self.pickle_serializer.dumps(hello))
        yaml_obj = self.yaml_serializer.loads(self.yaml_serializer.dumps(hello))
        # toml_obj = self.toml_serializer.loads(self.toml_serializer.dumps(hello))

        self.assertEqual(json_obj(), exp_hello)
        self.assertEqual(pickle_obj(), exp_hello)
        self.assertEqual(yaml_obj(), exp_hello)

    def test_functions_with_global_variable(self):
        json_obj = self.json_serializer.loads(self.json_serializer.dumps(say_hello))
        pickle_obj = self.pickle_serializer.loads(self.pickle_serializer.dumps(say_hello))
        yaml_obj = self.yaml_serializer.loads(self.yaml_serializer.dumps(say_hello))

        self.assertEqual(json_obj(), exp_say_hello)
        self.assertEqual(pickle_obj(), exp_say_hello)
        self.assertEqual(yaml_obj(), exp_say_hello)

    def test_function_with_parameters(self):
        json_obj = self.json_serializer.loads(self.json_serializer.dumps(add))
        pickle_obj = self.pickle_serializer.loads(self.pickle_serializer.dumps(add))
        yaml_obj = self.yaml_serializer.loads(self.yaml_serializer.dumps(add))
        toml_obj = self.toml_serializer.loads(self.toml_serializer.dumps(add))

        self.assertEqual(json_obj(2, 3), exp_add)
        self.assertEqual(pickle_obj(2, 3), exp_add)
        self.assertEqual(yaml_obj(2, 3), exp_add)
        self.assertEqual(toml_obj(2, 3), exp_add)

    def test_file_io(self):
        self.json_serializer.dump(add, json_file)
        self.pickle_serializer.dump(add, pickle_file)
        json_obj = self.json_serializer.load(json_file)
        pickle_obj = self.pickle_serializer.load(pickle_file)

        self.assertEqual(json_obj(2, 3), exp_add)
        self.assertEqual(pickle_obj(2, 3), exp_add)

    def test_recursive_function(self):
        json_obj = self.json_serializer.loads(self.json_serializer.dumps(factorial))
        pickle_obj = self.pickle_serializer.loads(self.pickle_serializer.dumps(factorial))
        yaml_obj = self.yaml_serializer.loads(self.yaml_serializer.dumps(factorial))
        toml_obj = self.toml_serializer.loads(self.toml_serializer.dumps(factorial))

        self.assertEqual(json_obj(5), exp_factorial)
        self.assertEqual(pickle_obj(5), exp_factorial)
        self.assertEqual(yaml_obj(5), exp_factorial)
        self.assertEqual(toml_obj(5), exp_factorial)

    def test_lambda(self):
        json_obj = self.json_serializer.loads(self.json_serializer.dumps(power))
        pickle_obj = self.pickle_serializer.loads(self.pickle_serializer.dumps(power))
        yaml_obj = self.yaml_serializer.loads(self.yaml_serializer.dumps(power))
        toml_obj = self.toml_serializer.loads(self.toml_serializer.dumps(power))

        self.assertEqual(json_obj(2, 3), exp_power)
        self.assertEqual(pickle_obj(2, 3), exp_power)
        self.assertEqual(yaml_obj(2, 3), exp_power)
        self.assertEqual(toml_obj(2, 3), exp_power)
