#include <dpp/dpp.h>

#include <fstream>
#include <iostream>
#include <string>

#include "musicPlayer.hpp"

std::string readTokenFromFile(const std::string &filePath) {
    std::ifstream file(filePath);
    std::string token;
    if (file.is_open()) {
        if (std::getline(file, token)) {
            file.close();
            return token;
        }
    }
    return "";  // Return an empty string if the file cannot be read or is empty
}

const std::string BOT_TOKEN = readTokenFromFile("/home/elegadro/bashrcBot/TOKEN.txt");
MusicPlayer musicPlayer;

int main() {
    dpp::cluster bot(BOT_TOKEN, dpp::i_default_intents);

    bot.on_log(dpp::utility::cout_logger());

    bot.on_ready([&bot](const dpp::ready_t &event) {
        bot.set_presence(dpp::presence(dpp::ps_online, dpp::at_listening, "your commands"));

        if (dpp::run_once<struct register_bot_commands>()) {
            bot.global_command_create(dpp::slashcommand("ping", "Ping pong!", bot.me.id));

            dpp::slashcommand playCommand("play", "Play a song", bot.me.id);
            playCommand.add_option(
                dpp::command_option(dpp::co_string, "song", "The song name or song link to play", true));

            dpp::slashcommand joinCommand("join", "Join your voice channel", bot.me.id);

            bot.guild_command_create(playCommand, 1164573819369951242);
            bot.guild_command_create(joinCommand, 1164573819369951242);
        }
    });

    bot.on_slashcommand([](const dpp::slashcommand_t &event) {
        std::cout << "[" << dpp::utility::current_date_time() << "]"
                  << " COMMAND: " << event.command.get_command_name() << " by "
                  << event.command.member.get_user()->username.c_str() << "#"
                  << event.command.member.get_user()->id.str() << std::endl;

        if (event.command.get_command_name() == "ping") {
            event.reply("Pong!");
        }

        if (event.command.get_command_name() == "play") {
            std::string songName = std::get<std::string>(event.get_parameter("song"));
            musicPlayer.playSong(songName, event);
        }

        if (event.command.get_command_name() == "join") {
            musicPlayer.joinChannel(event, true);
        }
    });

    bot.start(dpp::st_wait);

    return 0;
}
