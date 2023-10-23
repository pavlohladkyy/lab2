#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

class MEDIA_LIBRARY {
public:
    MEDIA_LIBRARY(const string& title, const string& theme, const string& actors, double rating, int length, double playback_speed, const string& filename, const string& date) {
        title_ = title;
        theme_ = theme;
        actors_ = actors;
        rating_ = rating;
        length_ = length;
        playback_speed_ = playback_speed;
        filename_ = filename;
        date_ = date;
    }

    void show() const {
        cout << "заголовок: " << title_ << endl;
        cout << "тема: " << theme_ << endl;
        cout << "актори: " << actors_ << endl;
        cout << "оцінка: " << rating_ << endl;
        cout << "довжина: " << length_ << " хвилин" << endl;
        cout << "швидкість відтворення: " << playback_speed_ << "x" << endl;
        cout << "назва файлу: " << filename_ << endl;
        cout << "дата: " << date_ << endl;
    }

    const string& getTitle() const {
        return title_;
    }

    const string& getFilename() const {
        return filename_;
    }

private:
    string title_;
    string theme_;
    string actors_;
    double rating_;
    int length_;
    double playback_speed_;
    string filename_;
    string date_;
};

class PLAYER {
public:
    void addMedia(const MEDIA_LIBRARY& media) {
        media_library_.push_back(media);
    }

    void playMedia(const string& filename) {
        for (const MEDIA_LIBRARY& media : media_library_) {
            if (media.getFilename() == filename) {
                cout << "Відтворення медіа: " << filename << endl;
                return;
            }
        }
        cout << "фільм не знайдено в бібліотеці." << endl;
    }

    void showAllMedia() const {
        for (const MEDIA_LIBRARY& media : media_library_) {
            media.show();
            cout << "============================" << endl;
        }
    }

    const string& getFilenameByTitle(const string& title) const {
        for (const MEDIA_LIBRARY& media : media_library_) {
            if (media.getTitle() == title) {
                return media.getFilename();
            }
        }
        static const string not_found = "Файл не знайдено";
        return not_found;
    }

private:
    vector<MEDIA_LIBRARY> media_library_;
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    PLAYER player;

    MEDIA_LIBRARY media1("Гаррі Поттер", "Драма", "Деніел Редкліфф, Руперт Грінт, Емма Уотсон", 4.5, 152, 1.0, "Harry Potter.mp4", "01.01.2001");
    MEDIA_LIBRARY media2("Один вдома", "Комедія", "Кулкін Маколей", 3.8, 123, 1.2, "movie2.mp4", "10.10.1990");
    MEDIA_LIBRARY media3("Маска", "Комедія", "Джим Керрі", 3.8, 103, 1.2, "The Mask.mp4", "29.07.1994");

    player.addMedia(media1);
    player.addMedia(media2);
    player.addMedia(media3);

    int choice;
    string inputTitle;
    string filenameToPlay;

    while (true) {
        cout << "Оберіть опцію:" << endl;
        cout << "1. Пошук фільму за назвою" << endl;
        cout << "2. Відтворити фільм за назвою" << endl;
        cout << "3. Показати всі фільми" << endl;
        cout << "4. Вихід" << endl;

        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Введіть назву фільму для пошуку: ";
            cin.ignore();
            getline(cin, inputTitle);
            filenameToPlay = player.getFilenameByTitle(inputTitle);
            if (filenameToPlay != "Файл не знайдено") {
                cout << "Фільм знайдено. Назва файлу: " << filenameToPlay << endl;
            }
            else {
                cout << "Фільм не знайдено в бібліотеці." << endl;
            }
            break;
        case 2:
            cout << "Введіть назву фільму для відтворення: ";
            cin.ignore();
            getline(cin, inputTitle);
            filenameToPlay = player.getFilenameByTitle(inputTitle);
            if (filenameToPlay != "Файл не знайдено") {
                player.playMedia(filenameToPlay);
            }
            else {
                cout << "Фільм не знайдено в бібліотеці." << endl;
            }
            break;
        case 3:
            player.showAllMedia();
            break;
        case 4:
            return 0;
        default:
            cout << "Невірний вибір. Будь ласка, оберіть іншу опцію." << endl;
            break;
        }
    }

    return 0;
}