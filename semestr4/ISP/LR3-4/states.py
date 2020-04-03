from aiogram.dispatcher.filters.state import State, StatesGroup


class CityAddition(StatesGroup):
    start = State()
    add = State()


class Registration(StatesGroup):
    password = State()
    success = State()


class Alertion(StatesGroup):
    start = State()
    set_alert = State()
