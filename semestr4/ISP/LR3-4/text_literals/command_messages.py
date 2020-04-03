from app import configuration

ADMIN = configuration['admin']

HELP_MESSAGE = 'What can i do:\n' \
               "1. Add / remove cities you're interested in\n" \
               '2. Send current weather in your cities\n' \
               '3. Notify with forecast in set time\n\n' \
               f'For any questions write to {ADMIN}'

START_MESSAGE = HELP_MESSAGE + '\n\nTo use my functions you need to authorize'
