#include <iostream>
#include <cstring>
#include <tgbot/tgbot.h>
#include <cstdlib>
#include <sstream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

#define BOOST_BIND_GLOBAL_PLACEHOLDERS

// функция для отправки текста в llama и получение ответа
std::string queryLlama(const std::string &input);

// функция для обработки данных, полученных из потока
size_t write_callback(void *contents, size_t size, size_t nmemb, std::string *output);

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
        // Логируем событие для отладки
        if (message->text == "/start") {
            return;
        }

        if (message->text.empty()) {
            std::cout << "Сообщение пустое" << std::endl;
            return;
        }
        
        try {
            std::string response = queryLlama(message->text);

            if (response.empty()) {
                response = "Ответа от модели не последовало.";
            }
            else if (response.size() > 4096) {
                response = "Ответ слишком длинный для отправки.";
            }

            bot.getApi().sendMessage(message->chat->id, response);
        }
        catch (const std::exception &e) {
            bot.getApi().sendMessage(message->chat->id, "Произошла ошибка при обработке сообщения.");
            std::cerr << "Ошибка в обработке сообщения: " << e.what() << std::endl;
        }
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

size_t write_callback(void *contents, size_t size, size_t nmemb, std::string *output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);

    return totalSize;
}

std::string queryLlama(const std::string &input) {
    // URL
    const std::string url = "http://localhost:11434/api/generate";

    // переменная для ответа модели
    std::string result;

    CURL *curl;
    CURLcode res;

    std::string responseBuffer; // буффер для хранения данных

    if (input.empty()) {
        throw std::invalid_argument("queryLlama: Пустая строка недопустима.");
    }

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // настраиваем URL
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // указываем, что запрос будет POST
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        // создаем тело запроса
        std::string postData = R"({ "model": "llama3.2", "prompt": ")" + input + R"(" })";

        // устанавливаем тело запроса
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());

        // устанавливаем функцию обратного вызова для обработки данных
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        // передаем указатель на строку для записи данных
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseBuffer);

        // выполняем запрос
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "Ошибка при выполнении запроса: " << curl_easy_strerror(res) << std::endl;
        }
        else {
            // обработка ответа
            long httpCode = 0;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
            std::cout << "HTTP-код ответа: " << httpCode << std::endl;

            // используем stringstream для разделения ответа на строки
            std::stringstream responseStream(responseBuffer);
            std::string line;

            // Считываем каждую строку
            while (std::getline(responseStream, line)) {
                try {
                    // Парсим строку как JSON
                    auto jsonLine = nlohmann::json::parse(line);

                    // Проверяем, содержит ли объект ключ "response"
                    if (jsonLine.contains("response")) {
                        result += jsonLine["response"].get<std::string>();
                    }
                } catch (const nlohmann::json::parse_error &e) {
                    std::cerr << "Ошибка парсинга JSON в строке: " << line << std::endl;
                    std::cerr << "Ошибка: " << e.what() << std::endl;
                }
            }
        }

        // освобождение ресурсов
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return result;
}