from handlers.commands_handlers import *
from handlers.services.alert_service import *
from handlers.services.weather_service import *
from handlers.text_messages_handler import *
from text_literals.callback_prefixes import *
from text_literals.commands import *
from text_literals.reply_keyboard_buttons import *
from .fixtures import *
from .process_functions import *


def test_commands(telegram_message):
    telegram_message.text = START_COMMAND
    handler = process_message(telegram_message)
    assert handler == start_command_handler

    telegram_message.text = HELP_COMMAND
    handler = process_message(telegram_message)
    assert handler == help_command_handler


def test_text_message_handler_(telegram_message, model_city, model_user):
    city = City(MODEL_CITY_NAME)

    telegram_message.text = ADD_CITY_BUTTON
    message_handler = process_message(telegram_message)
    model_city.users.append(model_user)
    db.session.commit()
    user_cities = get_cities(model_user.user_id)
    assert message_handler == text_message_handler
    assert len(user_cities) == 1
    assert city.city_name == user_cities[0].city_name

    telegram_message.text = GET_WEATHER_BUTTON
    message_handler = process_message(telegram_message)
    assert message_handler == text_message_handler

    telegram_message.text = REMOVE_CITY_BUTTON
    message_handler = process_message(telegram_message)
    model_city.users.remove(model_user)
    db.session.commit()
    assert message_handler == text_message_handler
    assert len(get_cities(model_user.user_id)) == 0

    telegram_message.text = STOP_ALERT_BUTTON
    message_handler = process_message(telegram_message)
    assert message_handler == text_message_handler

    if model_user.user_name == ADMIN[1:]:
        telegram_message.text = GET_USERS
        message_handler = process_message(telegram_message)
        assert message_handler == text_message_handler

        telegram_message.text = BAN_USERS
        message_handler = process_message(telegram_message)
        assert message_handler == text_message_handler

        telegram_message.text = UNBAN_USERS
        message_handler = process_message(telegram_message)
        assert message_handler == text_message_handler
    else:
        telegram_message.text = ''
        message_handler = process_message(telegram_message)
        assert message_handler == text_message_handler


def test_callback_handlers(telegram_callback, model_user):
    telegram_callback.data = AUTHORIZE
    handler = process_callback(telegram_callback)
    assert handler == authorize

    telegram_callback.data = GET_WEATHER
    callback_handler = process_callback(telegram_callback)
    assert callback_handler == get_forecasts_in_city

    telegram_callback.data = REMOVE_CITY
    callback_handler = process_callback(telegram_callback)
    assert callback_handler == delete_city

    telegram_callback.data = ADD_ALERT
    callback_handler = process_callback(telegram_callback)
    assert callback_handler == set_alert_city

    telegram_callback.data = STOP_ALERT
    callback_handler = process_callback(telegram_callback)
    assert callback_handler == delete_alert

    if model_user.user_name == ADMIN[1:]:
        telegram_callback.data = BAN
        callback_handler = process_callback(telegram_callback)
        assert callback_handler == ban

        telegram_callback.data = UNBAN
        callback_handler = process_callback(telegram_callback)
        assert callback_handler == unban
