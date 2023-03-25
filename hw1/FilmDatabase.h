
#ifndef UNTITLED7_FILMDATABASE_H
#define UNTITLED7_FILMDATABASE_H

#pragma once

#include <string>
#include <vector>

class FilmDatabase {
public:
    FilmDatabase(std::string name_path, std::string prin_path,
                 std::string akas_path, std::string basic_path);

    static void fileOpen(const std::string &name_file) {};

    void search(const std::string &word);

private:
    std::string name_path_;
    std::string prin_path_;
    std::string akas_path_;
    std::string basic_path_;

    std::vector<std::string> getActorFilms(const std::string &id);

    std::vector<std::string> getRussianFilms(const std::vector<std::string> &film_list);

    std::vector<std::string> getNonRussianFilms(std::vector<std::string> &film_list);
};

#endif //UNTITLED7_FILMDATABASE_H
