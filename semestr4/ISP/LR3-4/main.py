from aiogram.utils import executor

from handlers.text_messages_handler import *


if __name__ == '__main__':
    executor.start_polling(dispatcher)
