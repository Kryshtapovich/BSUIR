from .command_messages import ADMIN

AUTHORIZED_ENTER_MESSAGE = "You're already authorized"
PASSWORD_MESSAGE = 'Enter password\n\n' \
                   'Requirements: from 8 to 15 symbols, must contain at least one digit and letters'

INVALID_PASSWORD_MESSAGE = 'Invalid password, try again'
NO_USERNAME_MESSAGE = "You can't authorize without username. Set username and try again"
SUCCESS_REGISTRATION_MESSAGE = "You're authorized"
UNAUTHORIZED_USER_MESSAGE = 'Authorize before using my functions'
USER_BANNED_MESSAGE = "Sorry, you can't use my functions.\n" \
                      f'Write {ADMIN} to fix'
