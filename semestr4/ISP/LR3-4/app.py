import logging
import pyowm
from aiogram import Bot, Dispatcher, executor
from aiogram.types import Message, CallbackQuery, Update
from aiogram.dispatcher import FSMContext
from aiogram.contrib.fsm_storage.memory import MemoryStorage
from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from configuration.configurator import Configurator

app = Flask(__name__)

configuration = Configurator.get_configuration('./configuration/config.json')
app.config['SQLALCHEMY_DATABASE_URI'] = configuration['connection_string']
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = True

log_config = configuration['logger']
logger = logging.getLogger(__name__)
logging.basicConfig(filename=log_config['file'], level=log_config['level'], format=log_config['format'])

db = SQLAlchemy(app)

bot = Bot(configuration['token'])

dispatcher = Dispatcher(bot, storage=MemoryStorage())

owm = pyowm.OWM(configuration['api_key'])
