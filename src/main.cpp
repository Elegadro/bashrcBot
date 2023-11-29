#include <dpp/dpp.h>
#include <iostream>
#include <fstream>
#include <string>

std::string readTokenFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    std::string token;
    if (file.is_open()) {
        if (std::getline(file, token)) {
            file.close();
            return token;
        }
    }
    return ""; // Return an empty string if the file cannot be read or is empty
}

const std::string BOT_TOKEN = readTokenFromFile("/home/elegadro/bashrcBot/TOKEN.txt");

int main() {
    std::cout << "Bot token: " << BOT_TOKEN << std::endl;
    dpp::cluster bot(BOT_TOKEN);
 
    bot.on_log(dpp::utility::cout_logger());
 
    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
        if (event.command.get_command_name() == "ping") {
            event.reply("Pong!");
        }
        if (event.command.get_command_name() == "emir") {
            event.reply("Sikimi kemir");
        }
    });
 
    bot.on_ready([&bot](const dpp::ready_t& event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            bot.global_command_create(dpp::slashcommand("ping", "Ping pong!", bot.me.id));
            bot.global_command_create(dpp::slashcommand("emir", "<3", bot.me.id));
        }
    });
 
    bot.start(dpp::st_wait);
}
