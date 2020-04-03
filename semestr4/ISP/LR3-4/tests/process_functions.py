from app import bot


def get_message_handler(message):
    for handler in bot.message_handlers:
        if bot._test_message_handler(handler, message):
            return handler
    return None


def get_callback_handler(message):
    for handler in bot.callback_query_handlers:
        if bot._test_message_handler(handler, message):
            return handler
    return None


def process_message(message):
    handler = get_message_handler(message)
    try:
        handler['function'](message)
    except:
        pass
    return handler['function']


def process_callback(callback):
    handler = get_callback_handler(callback)
    try:
        handler['function'](callback)
    except:
        pass
    return handler['function']
