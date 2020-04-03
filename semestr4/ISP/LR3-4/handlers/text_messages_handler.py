from aiogram.types import ContentType

from text_literals.callback_prefixes import *
from text_literals.reply_keyboard_buttons import *
from .services.database_service import *
from .commands_handlers import *
from .services.admin_service import *
from .services.alert_service import *
from states import Alertion, CityAddition


@dispatcher.message_handler(state='*', content_types=ContentType.ANY)
async def text_message_handler(message: Message):
    user = User.query.get(message.from_user.id)
    txt = message.text
    markup = None
    if user is None:
        answer = UNAUTHORIZED_USER_MESSAGE
    elif not user.is_banned:
        cities = get_cities(user.user_id)
        if txt == ADD_CITY_BUTTON:
            answer = SET_CITY_MESSAGE
            await CityAddition.add.set()
        elif txt == GET_WEATHER_BUTTON or txt == REMOVE_CITY_BUTTON:
            if len(cities) == 0:
                answer = NO_CITIES_MESSAGE
            else:
                callback_data = GET_WEATHER if txt == GET_WEATHER_BUTTON else REMOVE_CITY
                markup = set_inline_markup(cities, 'city_name', callback_data)
                answer = USER_CITIES_MESSAGE
        elif txt == ADD_ALERT_BUTTON:
            if len(cities) == 0:
                answer = NO_CITIES_MESSAGE
            else:
                await Alertion.start.set()
                markup = set_inline_markup(cities, 'city_name', ADD_ALERT)
                answer = USER_CITIES_MESSAGE
        elif txt == STOP_ALERT_BUTTON:
            alert_cities = get_alert_cities()
            if len(alert_cities) == 0:
                answer = NO_ALERTS_MESSAGE
            else:
                markup = set_inline_markup(alert_cities, 'city_name', STOP_ALERT, 'time')
                answer = USER_CITIES_MESSAGE
        else:
            user_name = message.chat.username
            if user_name == ADMIN[1:]:
                users = get_users_by_attr()
                if txt == GET_USERS:
                    text = 'Bot users:\n'
                    for i in range(len(users)):
                        text += f'{i + 1}. {users[i].user_name}\n'
                    answer = text
                elif txt == BAN_USERS or txt == UNBAN_USERS:
                    value = False if txt == BAN_USERS else True
                    users = get_users_by_attr(User.is_banned, value)
                    no_text = ALL_BANNED_USERS if txt == BAN_USERS else ALL_UNBANNED_MESSAGE
                    if len(users) == 0:
                        answer = no_text
                    else:
                        flag = BAN if txt == BAN_USERS else UNBAN
                        markup = set_inline_markup(users, 'user_name', flag)
                        answer = USER_MESSAGE
                else:
                    answer = UNKNOWN_MESSAGE
            else:
                answer = UNKNOWN_MESSAGE
    else:
        answer = USER_BANNED_MESSAGE
    await bot.send_message(chat_id=message.chat.id, text=answer, reply_markup=markup)
