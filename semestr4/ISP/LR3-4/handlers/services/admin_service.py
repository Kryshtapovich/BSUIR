from app import dispatcher
from handlers.services.database_service import get_users_by_attr, change_ban_status
from handlers.services.deletion_service import delete_by_callback
from handlers.services.markup_service import set_inline_markup
from models import User
from text_literals.admin_messages import *
from text_literals.callback_prefixes import BAN, UNBAN


@dispatcher.callback_query_handler(lambda call: call.data.startswith(BAN), state='*')
async def ban(callback):
    await manipulate(callback, 3, -1, True, False, BAN, BAN_USER_MESSAGE)


@dispatcher.callback_query_handler(lambda call: call.data.startswith(UNBAN), state='*')
async def unban(callback):
    await manipulate(callback, 5, -1, False, True, UNBAN, UNBAN_USER_MESSAGE)


async def manipulate(callback, start, end, status, is_banned, flag, message):
    user_name = callback.data[start: end]
    change_ban_status(user_name, status)
    users = get_users_by_attr(User.is_banned, is_banned)
    markup = set_inline_markup(users, 'user_name', flag)
    await delete_by_callback(callback, users, user_name, markup, message)
