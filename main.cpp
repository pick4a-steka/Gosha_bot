#include <iostream>
#include <tgbot/tgbot.h>

#define BOOST_BIND_GLOBAL_PLACEHOLDERS

int main() {
    TgBot::Bot bot("7566901438:AAF5eBnmz-9WplAMxfli6DUTwKdUhquGqd8");

    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Привет! Я ваш бот - Гоша.");
    });

    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        if (StringTools::startsWith(message->text, "/start")) {
            return;
        }
        bot.getApi().sendMessage(message->chat->id, "Вы написали: " + message->text);
    });

    try {
        std::cout << "Бот запущен. Нажмите Ctrl+C для остановки." << std::endl;
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            longPoll.start();
        }
    } catch (const std::exception &e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
