from app import bot


async def delete_by_callback(callback, lst, text, markup, deletion_message):
    chat_id = callback.message.chat.id
    message_id = callback.message.message_id
    if len(lst) == 0:
        await bot.delete_message(chat_id, message_id)
    else:
        await bot.edit_message_reply_markup(chat_id=chat_id, message_id=message_id, reply_markup=markup)
    await bot.send_message(chat_id, f'{text} {deletion_message}')
