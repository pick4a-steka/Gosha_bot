#include <iostream>
#include <cstring>
#include <tgbot/tgbot.h>

#define BOOST_BIND_GLOBAL_PLACEHOLDERS

int main() {
    // получаем значение токена сохраненное в системной переменной
    const char *TOKEN = getenv("GOSHA_BOT_TOKEN");
    if (TOKEN == nullptr) {
        std::cout << "Переменная не задана" << std::endl;
    } 
    // инициализация бота
    TgBot::Bot bot(TOKEN);

    // обработка команды /start
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Привет! Я ваш бот - Гоша.");
    });

    // обработка любых сообщений
    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        if (StringTools::startsWith(message->text, "/start")) {
            return;
        }
        bot.getApi().sendMessage(message->chat->id, "Вы написали: " + message->text);
    });

    try {
        std::cout << "Бот запущен. Нажмите Ctrl+C для остановки." << std::endl;
        // запуск бота
        TgBot::TgLongPoll longPoll(bot); // отвечает за получение новых событий (например, сообщений)
        while (true) {
            longPoll.start();
        }
    } catch (const std::exception &e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
