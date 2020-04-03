import re
import aioschedule
from app import bot, dispatcher, Message, CallbackQuery
from handlers.services.deletion_service import delete_by_callback
from handlers.services.markup_service import set_inline_markup
from handlers.services.weather_service import send_weather
from models import City
from states import Alertion
from text_literals.callback_prefixes import ADD_ALERT, STOP_ALERT
from text_literals.main_functions_messages import *
from .database_service import user_is_banned
import asyncio

check_time = lambda time: re.match('^(([0,1][0-9])|(2[0-3])):[0-5][0-9]$', time)


def get_alert_cities():
    cities = list()
    for job in aioschedule.jobs:
        city = City(job.job_func.args[1])
        city.time = job.at_time.strftime('%H:%M')
        cities.append(city)
    return cities


@dispatcher.callback_query_handler(lambda call: call.data.startswith(ADD_ALERT), state=Alertion.start)
async def set_alert_city(callback: CallbackQuery):
    message = callback.message
    user_id = callback.from_user.id
    if user_is_banned(message.chat.id, user_id):
        return
    city = callback.data[9:-1]
    await bot.send_message(message.chat.id, SET_ALERT_TIME_MESSAGE)
    await Alertion.set_alert.set()
    Alertion.city = city


@dispatcher.message_handler(lambda message: not check_time(message.text), state=Alertion.set_alert)
async def invalid_time(message: Message):
    await Alertion.start.set()
    await message.reply(INVALID_TIME_MESSAGE)


@dispatcher.message_handler(lambda message: check_time(message.text), state=Alertion.set_alert)
async def set_alert_time(message: Message):
    await Alertion.start.set()
    city = Alertion.city
    time = message.text
    chat_id = message.chat.id
    for job in aioschedule.jobs:
        if time == job.at_time.strftime('%H:%M') and city == job.job_func.args[1]:
            await bot.send_message(chat_id, ALERT_EXISTS_MESSAGE)
            await Alertion.start.set()
            return
    await on_scheduling(chat_id, city, time)
    await bot.send_message(chat_id, f'{ALERT_PERIOD} {time} {ALERT_MESSAGE} {city}')


async def on_scheduling(chat_id, city, time):
    aioschedule.every().day.at(time).do(send_weather, chat_id, city).tag(f'{city} {time}')
    if len(aioschedule.jobs) == 1:
        asyncio.create_task(schedule())


async def schedule():
    while len(aioschedule.jobs) != 0:
        await aioschedule.run_pending()
        await asyncio.sleep(5)


@dispatcher.callback_query_handler(lambda call: call.data.startswith(STOP_ALERT), state='*')
async def delete_alert(callback: CallbackQuery):
    user_id = callback.from_user.id
    if user_is_banned(callback.message.chat.id, user_id):
        return
    text = callback.data[10:]
    aioschedule.clear(text)
    cities = get_alert_cities()
    markup = set_inline_markup(cities, 'city_name', STOP_ALERT, 'time')
    await delete_by_callback(callback, cities, text, markup, ALERT_DELETED_MESSAGE)
