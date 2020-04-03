from aiogram.types import InlineKeyboardButton, InlineKeyboardMarkup
from models import User
from text_literals.command_messages import *
from text_literals.commands import *
from .authorization_handlers import *
from .services.database_service import user_is_banned


@dispatcher.message_handler(commands=[START_COMMAND], state='*')
async def start_command_handler(message: Message):
    chat_id = message.chat.id
    user_id = message.from_user.id
    user = User.query.get(user_id)
    markup = None
    text = ''
    if user is None:
        markup = InlineKeyboardMarkup(row_width=1)
        button = InlineKeyboardButton(text=AUTHORIZE, callback_data=AUTHORIZE)
        markup.add(button)
        text = START_MESSAGE
        if message.chat.username is None:
            text += f'\n\n{NO_USERNAME_MESSAGE}'
    else:
        if not user_is_banned(chat_id, user_id):
            text = AUTHORIZED_ENTER_MESSAGE
    await bot.send_message(chat_id=chat_id, text=text, reply_markup=markup)


@dispatcher.message_handler(commands=[HELP_COMMAND], state='*')
async def help_command_handler(message: Message):
    await bot.send_message(message.chat.id, HELP_MESSAGE)
