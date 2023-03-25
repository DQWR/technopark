#include <iostream>
#include <string>
#include <algorithm>
#include "FilmDatabase.h"

void requestPath(std::string & name_path, std::string & princip_path,
                 std::string & akas_path, std::string & basic_path){
    std::cout << "Введите путь до файла name.basics.tsv: ";
    std::cin >> name_path;

    std::cout << "Введите путь до файла title.principals.tsv: ";
    std::cin >> princip_path;

    std::cout << "Введите путь до файла title.akas.tsv: ";
    std::cin >> akas_path;

    std::cout << "Введите путь до файла title.basics.tsv: ";
    std::cin >> basic_path;
}

int main() {

    std::string search_word;

    std::string name_path, princip_path, akas_path, basic_path;
    requestPath(name_path, princip_path, akas_path, basic_path);

    FilmDatabase db(name_path, princip_path,
                    akas_path, basic_path);

    std::cout << "Введите слово для поиска: ";
    std::cin >> search_word;

    db.search(search_word);


    return 0;

}
