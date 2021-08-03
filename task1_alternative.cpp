#include <iostream>
#include <vector>
#include <assert.h>
#include <string>
#include <ctime>
#include <iomanip>

class Track
{
    std::tm releaseDate{};
    int duration = 0;
    std::string title = "";

public:

    void setTitle(std::string inTitle)
    {
        title = inTitle;
    }

    std::string getTitle()
    {
        return title;
    }

    void setDuration(int inDuration)
    {
        if (inDuration < 5)
        {
            inDuration = 5;
        }
    }

    void setReleaseDate(std::tm inDate)
    {
        releaseDate = inDate;
    }

    int getDuration()
    {
        return duration;
    }

    std::tm getReleaseDate()
    {
        return releaseDate;
    }

    void showInfo()
    {
        int minutes = duration / 60;
        int seconds = duration % 60;
        std::cout << title << " " << std::asctime(&releaseDate) << " "
                  << minutes << ":" << seconds << std::endl;
    }
};

class Player
{
private:

    std::vector<Track*> tracks;
    Track* currentTrack = nullptr;
    bool isPlaying = false;
    bool isPaused = false;

public:

    void addTrack(Track* track)
    {
        assert(track != nullptr);
        tracks.push_back(track);
        std::cout << "Added track: ";
        track->showInfo();
    }

    void play()
    {
        if (isPlaying) return;
        if (currentTrack == nullptr)
        {
            assert(tracks.size());
            currentTrack = tracks[std::rand() % tracks.size()];
        }
        isPlaying = true;
        std::cout << "Playing: ";
        currentTrack->showInfo();
    }

    void pause()
    {
        if (!isPlaying) return;
        if (isPaused) return;
        assert(currentTrack != nullptr);
        isPaused = true;
        std::cout << "Pausing: ";
        currentTrack->showInfo();
    }

    void stop()
    {
        if (!isPlaying) return;
        assert(currentTrack != nullptr);
        isPlaying = false;
        isPaused = false;
        std::cout << "Stopped: ";
        currentTrack->showInfo();
        currentTrack = nullptr;
    }

    void next()
    {
        currentTrack = tracks[std::rand() % tracks.size()];
        std::cout << "Moving next: ";
        currentTrack->showInfo();
        if (isPlaying)
        {
            std::cout << "Playing: ";
            currentTrack->showInfo();
        }
    }
};

int main()
{
    Player* player = new Player();
    while (true)
    {
        std::string title;
        std::tm date{};
        int duration;

        std::cout << "Track info:";
        std::cin >> title;
        if (title == "None") break;
        std::cin >> std::get_time(&date, "%d/%m/%Y");
        std::cin >> duration;

        Track* track = new Track;
        track->setTitle(title);
        track->setReleaseDate(date);
        track->setDuration(duration);

        player->addTrack(track);
    }

    while (true)
    {
        std::string command;
        std::cout << "Command:";
        std::cin >> command;
        if (command == "play")
        {
            player->play();
        }
        else if (command == "pause")
        {
            player->pause();
        }
        else if (command == "stop")
        {
            player->stop();
        }
        else if (command == "next")
        {
            player->next();
        }
        else if (command == "exit")
        {
            return 0;
        }
    }
}