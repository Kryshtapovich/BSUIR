import pytest
from telebot import types

from models import *
from .tests_constants import *


@pytest.fixture()
def model_user():
    user = User(MODEL_USER_ID, MODEL_USER_NAME, MODEL_USER_PASSWORD)
    db.session.add(user)
    db.session.commit()
    yield user
    db.session.delete(user)
    db.session.commit()


@pytest.fixture()
def model_city():
    city = City(MODEL_CITY_NAME)
    db.session.add(city)
    db.session.commit()
    yield city
    db.session.delete(city)
    db.session.commit()


@pytest.fixture()
def telegram_user():
    return types.User(TELEGRAM_USER_ID, False, TELEGRAM_USER_NAME)


@pytest.fixture()
def telegram_chat():
    return types.Chat(CHAT_ID, 'private')


@pytest.fixture()
def telegram_message(telegram_user, telegram_chat):
    return types.Message(MESSAGE_ID, telegram_user, 0, telegram_chat, 'text', [], 'null')


@pytest.fixture()
def telegram_callback(telegram_message, telegram_user, telegram_chat):
    return types.CallbackQuery(MESSAGE_ID, telegram_user, 1, telegram_chat, telegram_message)



