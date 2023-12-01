#ifndef MUSICPLAYER_HPP
#define MUSICPLAYER_HPP

#include <dpp/dpp.h>

#include <iostream>

class MusicPlayer {
   public:
    MusicPlayer();
    ~MusicPlayer();
    
    bool isInVoiceChannel(const dpp::slashcommand_t &event);

    void playSong(const std::string &songName, const dpp::slashcommand_t &event);
    void joinChannel(const dpp::slashcommand_t &event, bool reply);    
};

#endif  // MUSICPLAYER_HPP