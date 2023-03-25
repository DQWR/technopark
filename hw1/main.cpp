#include <iostream>
#include <string>
#include <algorithm>
#include "FilmDatabase.h"

//first - name.basics.tsv, second - title.principals.tsv, third - title.akas.tsv, fourth - title.basics.tsv
int main(int argc, char *argv[]) {


    FilmDatabase db(argv[1], argv[2],
                    argv[3], argv[4]);


    // actor
    db.search(argv[5]);

    return 0;

}
