#include "musicPlayer.hpp"

MusicPlayer::MusicPlayer() { std::cout << "MusicPlayer constructor called" << std::endl; }

MusicPlayer::~MusicPlayer() { std::cout << "MusicPlayer destructor called" << std::endl; }

bool MusicPlayer::isInVoiceChannel(const dpp::slashcommand_t &event) {
    dpp::guild *g = dpp::find_guild(event.command.guild_id);

    auto current_vc = event.from->get_voice(event.command.guild_id);

    return current_vc;
}

void MusicPlayer::playSong(const std::string &songName, const dpp::slashcommand_t &event) {
    dpp::embed embed = dpp::embed().set_title("Now playing").set_description(songName).set_color(0x00ff00);

    bool isVoiceChannel = this->isInVoiceChannel(event);

    if (!isVoiceChannel) {
        this->joinChannel(event, false);
    }

    dpp::message msg(event.command.channel_id, embed);

    event.reply(msg);
}

void MusicPlayer::joinChannel(const dpp::slashcommand_t &event, bool reply) {
    dpp::guild *g = dpp::find_guild(event.command.guild_id);

    auto current_vc = event.from->get_voice(event.command.guild_id);

    bool join_vc = true;

    if (current_vc) {
        auto users_vc = g->voice_members.find(event.command.get_issuing_user().id);

        if (users_vc != g->voice_members.end() && current_vc->channel_id == users_vc->second.channel_id) {
            join_vc = false;

        } else {
            event.from->disconnect_voice(event.command.guild_id);

            join_vc = true;
        }
    }

    if (join_vc) {
        if (!g->connect_member_voice(event.command.get_issuing_user().id)) {
            event.reply("You don't seem to be in a voice channel");
            return;
        }

        if (reply) {
            event.reply("Joining your channel");
        }

    } else {
        event.reply("Don't need to join your channel as i'm already in it");
    }
}
