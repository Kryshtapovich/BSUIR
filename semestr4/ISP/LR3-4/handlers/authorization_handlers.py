from app import bot, dispatcher, Message, CallbackQuery
from handlers.services.database_service import register_user
from states import Registration
from text_literals.authorization_messages import *
import re
from handlers.services.markup_service import set_reply_markup
from text_literals.callback_prefixes import AUTHORIZE
from text_literals.reply_keyboard_buttons import GET_USERS, BAN_USERS, UNBAN_USERS

check_password = lambda password: re.match(r'^(?=.*[A-Za-z])(?=.*\d)[A-Za-z\d]{8,15}$', password)


@dispatcher.callback_query_handler(lambda call: call.data == AUTHORIZE)
async def authorize(callback: CallbackQuery):
    await bot.edit_message_reply_markup(chat_id=callback.message.chat.id,
                                        message_id=callback.message.message_id, reply_markup=None)
    await bot.send_message(callback.message.chat.id, PASSWORD_MESSAGE)
    await Registration.password.set()


@dispatcher.message_handler(lambda message: not check_password(message.text), state=Registration.password)
async def invalid_password(message: Message):
    await message.reply(INVALID_PASSWORD_MESSAGE)


@dispatcher.message_handler(lambda message: check_password(message.text), state=Registration.password)
async def register(message: Message):
    password = message.text
    chat_id = message.chat.id
    user_id = message.from_user.id
    user_name = message.chat.username
    register_user(user_id, user_name, password)
    markup = set_reply_markup()
    if user_name == ADMIN[1:]:
        markup.add(GET_USERS)
        markup.row(BAN_USERS, UNBAN_USERS)
    await bot.send_message(chat_id=chat_id, text=SUCCESS_REGISTRATION_MESSAGE, reply_markup=markup)
    await Registration.success.set()
