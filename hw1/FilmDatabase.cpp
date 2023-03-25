#include "FilmDatabase.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
FilmDatabase::FilmDatabase(std::string name_path, std::string prin_path,
                           std::string akas_path, std::string basic_path)
        : name_path_(std::move(name_path)), prin_path_(std::move(prin_path)), akas_path_(std::move(akas_path)), basic_path_(std::move(basic_path))
{
}
static void fileOpen(const std::string &name_file){
    std::ifstream basic_file(name_file);
    if (!basic_file.is_open()) {
        std::cout << "Не удалось открыть файл " << name_file << std::endl;
    }
}

void FilmDatabase::search(const std::string &word) {
    std::ifstream name_file(name_path_);
    fileOpen(name_path_);

    std::string id_t;
    std::string line;

    while (std::getline(name_file, line)) {
        size_t pos = line.find(word);
        if (pos != std::string::npos) {
            size_t space_pos = line.find('\t');
            if (space_pos != std::string::npos) {
                id_t = line.substr(0, space_pos);
                break;
            }
        }
    }
    name_file.close();

    std::vector<std::string> film_list = getActorFilms(id_t);
    std::vector<std::string> ru_film_list = getRussianFilms(film_list);
    std::vector<std::string> not_ru_film_list = getNonRussianFilms(film_list);

    if (ru_film_list.empty() and not_ru_film_list.empty()) {
        std::cout << "Актёр нигде не снимался " << std::endl;
    } else {
        std::cout << "ID актера: " << id_t << std::endl;
        std::cout << "Фильмы, в которых он снимался: " << std::endl;
        for (auto &film: film_list) {
            std::cout << " - " << film << std::endl;
        }

        std::cout << "Русские названия этих фильмов: " << std::endl;
        for (auto &film: ru_film_list) {
            std::cout << " - " << film << std::endl;
        }
        std::cout << "Оригинальные названия не русских фильмов: " << std::endl;
        for (auto &film: not_ru_film_list) {
            std::cout << " - " << film << std::endl;
        }

        std::cout << std::endl;
    }
}

std::vector<std::string> FilmDatabase::getActorFilms(const std::string &id) {
    std::ifstream prin_file(prin_path_);
    fileOpen(prin_path_);

    std::vector<std::string> film_list;
    std::string line;
    while (std::getline(prin_file, line)) {

        size_t pos = line.find(id);

        if ((pos != std::string::npos) and line.find("actor") != std::string::npos) {
            std::stringstream ss(line);
            std::string id_film;
            ss >> id_film;
            film_list.push_back(id_film);
        }
    }
    prin_file.close();

    return film_list;
}

std::vector<std::string> FilmDatabase::getRussianFilms(const std::vector<std::string> &film_list) {

    std::vector<std::string> ru_film_list;
    for (const auto &i : film_list) {

        std::ifstream akas_file(akas_path_);
        std::string id_film;
        fileOpen(akas_path_);

        std::string line;
        akas_file.seekg(0);
        while (std::getline(akas_file, line)) {

            auto pos = line.find(i);
            if (pos != std::string::npos) {
                if (line.find("RU") != std::string::npos) {
                    std::stringstream ss(line);
                    ss.ignore(200, '\t');
                    ss.ignore(200, '\t');
                    std::getline(ss, id_film, '\t');
                    ru_film_list.push_back(id_film);
                    id_film.clear();
                }
            }

        }
        akas_file.close();
    }

    return ru_film_list;
}

std::vector<std::string> FilmDatabase::getNonRussianFilms(std::vector<std::string> &film_list) {

    std::vector<std::string> not_ru_film_list;
    std::string line;
    std::string primary_name;


    for (auto &i: film_list) {

        std::ifstream basic_file(basic_path_);
        fileOpen(basic_path_);

        while (std::getline(basic_file, line)) {
            size_t pos = line.find(i);
            if (pos != std::string::npos) {
                std::stringstream ss(line);
                ss.ignore(200, '\t');
                ss.ignore(200, '\t');
                std::getline(ss, primary_name, '\t');
                not_ru_film_list.push_back(primary_name);
            }
        }
        basic_file.close();
    }


    return not_ru_film_list;
}