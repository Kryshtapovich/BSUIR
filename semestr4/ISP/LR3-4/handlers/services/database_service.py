import pyowm
from app import app, bot, owm, dispatcher, Message, CallbackQuery
from handlers.services.markup_service import set_inline_markup
from models import *
from states import CityAddition
from text_literals.authorization_messages import USER_BANNED_MESSAGE
from text_literals.callback_prefixes import REMOVE_CITY
from text_literals.command_messages import ADMIN
from text_literals.main_functions_messages import *
from .deletion_service import delete_by_callback


def get_users_by_attr(attr=None, value=None):
    if attr is None and value is None:
        return User.query.all()
    else:
        return User.query.filter(User.user_name != ADMIN[1:], attr == value).all()


def user_is_banned(chat_id, user_id):
    user = User.query.get(user_id)
    if user.is_banned:
        bot.send_message(chat_id, USER_BANNED_MESSAGE)
    return user.is_banned


def change_ban_status(user_name, status):
    user = get_users_by_attr(User.user_name, user_name)[0]
    with app.app_context():
        user.is_banned = status
        db.session.commit()


def get_cities(user_id):
    return City.query.join(user_to_city).join(User).filter(user_to_city.c.user_id == user_id).all()


def register_user(user_id, user_name, password):
    user = User(user_id, user_name, password)
    db.session.add(user)
    db.session.commit()


@dispatcher.message_handler(state=CityAddition.add)
async def register_city(message: Message):
    text = ''
    try:
        city = City.query.filter_by(city_name=message.text).first()
        if city is None:
            owm.weather_manager().weather_at_place(message.text)
            city = City(message.text)
        user = User.query.get(message.from_user.id)
        city.users.append(user)
        db.session.commit()
        text = f'{CITY_ADDED_MESSAGE}'
    except pyowm.commons.exceptions.NotFoundError or pyowm.commons.exceptions.TimeoutError:
        text = INVALID_CITY_MESSAGE
    finally:
        await CityAddition.start.set()
        await message.reply(text)


@dispatcher.callback_query_handler(lambda call: call.data.startswith(REMOVE_CITY), state='*')
async def delete_city(callback: CallbackQuery):
    user = User.query.get(callback.from_user.id)
    if user_is_banned(callback.message.chat.id, user.user_id):
        return
    text = callback.data[11:-1]
    city = City.query.filter_by(city_name=text).first()
    city.users.remove(user)
    db.session.commit()
    cites = get_cities(user.user_id)
    markup = set_inline_markup(cites, 'city_name', REMOVE_CITY)
    await delete_by_callback(callback, cites, text, markup, CITY_DELETED_MESSAGE)
