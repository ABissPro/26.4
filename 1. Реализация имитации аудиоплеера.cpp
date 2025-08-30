#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <random>
#include <iomanip> //для std::put_time

class Track {
private:
    std::string title;
    std::tm creationDate;
    int duration; //в сек

public:
    Track(const std::string& title, const std::tm& date, int duration)
        : title(title), creationDate(date), duration(duration) {
    }

    std::string getTitle() const {
        return title;
    }

    std::tm getCreationDate() const {
        return creationDate;
    }

    int getDuration() const {
        return duration;
    }

    void displayInfo() const {
        std::cout << "Title: " << title << std::endl;
        std::cout << "Creation date: " << std::put_time(&creationDate, "%Y-%m-%d") << std::endl;
        std::cout << "Duration: " << duration / 60 << "m " << duration % 60 << "s" << std::endl;
    }
};

class Player {
private:
    std::vector<Track> tracks;
    Track* currentTrack;
    bool isPlaying;
    bool isPaused;
    std::default_random_engine randomEngine;

    Track* findTrackByName(const std::string& title) {
        for (Track& track : tracks) {
            if (track.getTitle() == title) {
                return &track;
            }
        }
        return nullptr;
    }

    Track* getRandomTrack() {
        if (tracks.empty()) {
            return nullptr;
        }

        if (!currentTrack) {
            std::uniform_int_distribution<int> randTrack(0, tracks.size() - 1);
            return &tracks[randTrack(randomEngine)];
        }

        std::vector<Track*> otherTracks;
        for (Track& track : tracks) {
            if (track.getTitle() != currentTrack->getTitle()) {
                otherTracks.push_back(&track);
            }
        }

        if (otherTracks.empty()) {
            return nullptr;
        }

        std::uniform_int_distribution<int> dist(0, otherTracks.size() - 1);
        return otherTracks[dist(randomEngine)];
    }

public:
    Player() : currentTrack(nullptr), isPlaying(false), isPaused(false) {
        std::random_device rd;
        randomEngine = std::default_random_engine(rd());
    }

    void addTrack(const Track& track) {
        tracks.push_back(track);
    }

    void play(const std::string& title = "") {
        if (isPlaying && !isPaused) {
            std::cout << "A track is already playing." << std::endl;
            return;
        }

        if (isPaused) {
            isPaused = false;
            std::cout << "Resumed playback: " << currentTrack->getTitle() << std::endl;
            return;
        }

        Track* trackToPlay = nullptr;

        if (!title.empty()) {
            trackToPlay = findTrackByName(title);
            if (!trackToPlay) {
                std::cout << "Track not found: " << title << std::endl;
                return;
            }
        }
        else {
            trackToPlay = getRandomTrack();
            if (!trackToPlay) {
                std::cout << "No tracks available." << std::endl;
                return;
            }
        }

        currentTrack = trackToPlay;
        isPlaying = true;
        isPaused = false;

        std::cout << "Now playing: " << std::endl;
        currentTrack->displayInfo();
    }

    void pause() {
        if (!isPlaying || isPaused) {
            std::cout << "No track is currently playing." << std::endl;
            return;
        }

        isPaused = true;
        std::cout << "Paused: " << currentTrack->getTitle() << std::endl;
    }

    void next() {
        Track* nextTrack = getRandomTrack();
        if (!nextTrack) {
            std::cout << "No tracks available." << std::endl;
            return;
        }

        currentTrack = nextTrack;
        isPlaying = true;
        isPaused = false;

        std::cout << "Playing next track: " << std::endl;
        currentTrack->displayInfo();
    }

    void stop() {
        if (!isPlaying) {
            std::cout << "No track is currently playing." << std::endl;
            return;
        }

        std::cout << "Stopped: " << currentTrack->getTitle() << std::endl;
        isPlaying = false;
        isPaused = false;
        currentTrack = nullptr;
    }

    bool isCurrentlyPlaying() const {
        return isPlaying && !isPaused;
    }
};

int main() {
    Player player;

    std::tm date1 = {};
    date1.tm_year = 120; //2020
    date1.tm_mon = 0;    //январь
    date1.tm_mday = 15;
    Track track1("Yesterday", date1, 125);
    player.addTrack(track1);

    std::tm date2 = {};
    date2.tm_year = 121;
    date2.tm_mon = 5;
    date2.tm_mday = 3;
    Track track2("Bohemian Rhapsody", date2, 355);
    player.addTrack(track2);

    std::tm date3 = {};
    date3.tm_year = 122;
    date3.tm_mon = 8;
    date3.tm_mday = 21;
    Track track3("Imagine", date3, 183);
    player.addTrack(track3);

    std::string command;
    while (true) {
        std::cout << "\nEnter command (play, pause, next, stop, exit): ";
        std::getline(std::cin, command);

        if (command == "play") {
            std::cout << "Enter track title (or press Enter for random track): ";
            std::string title;
            std::getline(std::cin, title);
            player.play(title);
        }
        else if (command == "pause") {
            player.pause();
        }
        else if (command == "next") {
            player.next();
        }
        else if (command == "stop") {
            player.stop();
        }
        else if (command == "exit") {
            break;
        }
        else {
            std::cout << "Unknown command. Available commands: play, pause, next, stop, exit." << std::endl;
        }
    }

    return 0;
}