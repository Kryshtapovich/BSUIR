from app import bot, owm, dispatcher, CallbackQuery
from handlers.services.database_service import user_is_banned
from text_literals.callback_prefixes import GET_WEATHER


@dispatcher.callback_query_handler(lambda call: call.data.startswith(GET_WEATHER), state='*')
async def get_forecasts_in_city(callback: CallbackQuery):
    chat_id = callback.message.chat.id
    if user_is_banned(chat_id, callback.from_user.id):
        return
    city = callback.data[11:-1]
    await send_weather(chat_id, city)


async def send_weather(chat_id, city):
    weather = owm.weather_manager().weather_at_place(city).weather
    temperature = weather.temperature('celsius')
    wind_speed = weather.wnd['speed']
    visibility_distance = weather.visibility_distance
    status = weather.detailed_status
    icon = switch_icon(weather.weather_code, weather.weather_icon_name)
    message = f'Now in {city}\n\n' \
              f'Weather: {status} {icon}\n' \
              f"Temperature: {temperature['temp']} ℃\n" \
              f"Feels like: {temperature['feels_like']} ℃\n" \
              f'Wind speed: {wind_speed} m/s\n' \
              f'Visibility: {visibility_distance} m'
    await bot.send_message(chat_id, message)


def switch_icon(code, icon):
    if code <= 232:
        return "⛈"
    elif 300 <= code <= 321 or 500 <= code <= 504 or 520 <= code <= 531:
        return "🌧️"
    elif code == 511 or 600 <= code <= 622:
        return "❄"
    elif 701 <= code <= 781:
        return "🌫"
    elif code == 800:
        return "🌑" if icon.endswith('n') else "☀"
    elif 801 <= code <= 804:
        return "☁"
