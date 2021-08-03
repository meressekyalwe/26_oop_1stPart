/*Задание 1. Реализация имитации аудиоплеера
Что нужно сделать
С помощью классов реализуйте программу имитации работы аудиоплеера. В плеере находится
несколько аудиозаписей, доступных для воспроизведения. Для них вы должны создать отдельный
класс Track. Полями этого класса должны быть: название, дата создания (здесь вы можете
использовать тип std::tm) и продолжительность записи в секундах.

Сам плеер тоже реализуйте с помощью класса. Внутри он должен содержать список доступных
записей и нужные для логики работы плеера поля.

Пользователь взаимодействует с программой с помощью команд:

*Команда play запрашивает у пользователя название записи для воспроизведения и начинает
её воспроизведение. Воспроизведение симулируется с помощью вывода в консоль всей
информации о записи. Если произведение какой-то записи уже начато, ничего не
происходит.
*Команда pause. Ставит запись на паузу, о чём выводит соответствующее сообщение в
консоль. Если запись уже на паузе или не воспроизводится вовсе, ничего не происходит.
*Команда next переходит к следующей записи для воспроизведения. Запись при этом
выбирается случайно, как будто плеер работает в режиме shuffle.
*Команда stop прекращает воспроизведение текущей записи, если таковая имеется. Об этом
выводится сообщение в консоль. Два раза остановить воспроизведение невозможно, так что
команда должна срабатывать только в первом случае.
*Команда exit — выход из программы.

Советы и рекомендации
Забудьте про отдельные глобальные функции и используйте возможности классов и методов по максимуму.
*/
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <ctime>

class Track{
    std::string title = "Untitled";
    std::tm creationDate = {};
    int duration = 0;
public:
    void set_title(std::string inTitle){
        title = inTitle;
    }
    void set_creationDate(std::tm inCreationDate){
        creationDate = inCreationDate;
    }
    void set_duration(int inDuration){
        if (inDuration < 0){
            inDuration = 1;
        }
        duration = inDuration;
    }
    std::string get_title(){
        return title;
    }
    std::tm get_creationDate(){
        return creationDate;
    }
    int get_Duration(){
        return duration;
    }
    void showInfos(){
        std::cout << title << " " << std::put_time(&creationDate, "%d-%m-%Y") << " " << duration << std::endl;
    }
};

class Player{
    std::vector<Track>Playlist;
    Track currentTrack;
    bool isPlaying = false;
    bool isPaused = false;
public:
    void addTrack(Track track){
        Playlist.push_back(track);
    }
    void play(std::string title){ // title for playing
        if (isPlaying == false && Playlist.size() > 0){ 
            for (auto& track : Playlist){
                if (title == track.get_title()) {
                    isPlaying = true;
                    std::cout << "Playing : "; 
                    memcpy(&currentTrack, &track, sizeof(track));
                    currentTrack.showInfos();
                }
            }
        } 
        std::cout << (Playlist.size() == 0 ? "Empty Playlist" : "");
    }
    void pause(){
        if (isPaused == false && isPlaying == true){
            isPaused = true;
            std::cout << "Pausing : ";
            currentTrack.showInfos();
        }
    }
    void stop(){
        if (isPaused == true || isPlaying == true){
            isPlaying = false;
            isPaused = false;
            currentTrack = Track{};
            std::cout << "Stopped : ";
            currentTrack.showInfos();
        }
    }
    void next(size_t i){
        isPlaying = true;
        memcpy(&currentTrack, &Playlist[i], sizeof(Playlist[i]));
        std::cout << "Next :";
        currentTrack.showInfos();
    }
    void exit(){
        isPaused = false;
        isPlaying = false;
        currentTrack = Track{};
        std::cout << "Exit" << std::endl;
    }
    size_t numberTracks(){
        return Playlist.size();
    }
};

int main(){
    std:srand(std::time(nullptr));

    std::string title = "Untitled";
    std::tm creationDate;
    int duration;

    Track* track = new Track;
    Player* player = new Player;

    while(true){
        std::cout << "Title :";
        std::cin >> title;
        if (title == "finish") break;
        std::cout << "Date of creation :";
        std::cin >> std::get_time(&creationDate, "%d-%m-%Y");
        std::cout << "Duration :";
        std::cin >> duration;

        (*track).set_title(title); // = track->set_title(title);
        (*track).set_creationDate(creationDate);
        (*track).set_duration(duration);

        (*player).addTrack(*track);
    }

    std::string command;

    do{
        std::cout << "Command :";
        std::cin >> command;
        if (command == "play"){
            std::cout << "Title of track you want to play : ";
            std::cin >> title;
            (*player).play(title);
        }
        else if (command == "pause"){
            (*player).pause();
        }
        else if (command == "stop"){
            (*player).stop();
        }
        else if (command == "next"){
            size_t random = rand() % (*player).numberTracks();
            (*player).next(random);
        }
        else if (command == "exit"){
            (*player).exit();
        }
    }while(command != "exit");

    delete track;
    track = nullptr;
    delete player;
    player = nullptr;
}