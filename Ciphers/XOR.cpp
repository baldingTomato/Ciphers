#include <iostream>
#include <string.h>
#include <fstream>

#define LETTERS 64

void PrepareText(std::string orig) {

    int counter = 0;
    int i = 0;
    std::string whitespace = " ";

    std::fstream file;
    file.open("plain.txt", std::fstream::out);

    while (counter < orig.length()) {

        for (i = 0; i < LETTERS; i++) {

            if (counter == orig.length()) {
                break;
            }

            if (orig.at(counter) < 65 || (orig.at(counter) > 90 && orig.at(counter) < 97) || orig.at(counter) > 122) {

                orig.replace(counter, 1, whitespace); // replace only one char at 'counter' index with text in 'whitespace' string
                file << orig.at(counter);
                counter++;

            }
            else {

                file << orig.at(counter);
                counter++;

            }

        }

        if (counter == orig.length()) {
            break;
        }

        file << "\n";

    }

    i = LETTERS - i;

    while (i > 0) {

        file << " ";
        i--;

    }

    file.close();

}

void EncryptXOR(std::string plain, std::string key) {

    std::string cipher = "";
    int counter = 0;

    std::fstream file;
    file.open("crypto.txt", std::fstream::out);

    while (counter < plain.length()) {

        for (int i = 0; i < LETTERS; i++) {

            file << (char)(plain[counter] ^ key[i]);
            counter++;

        }

        if (counter == plain.length()) {
            break;
        }

        file << '\n';

    }


    file.close();

}

int main(int argc, char* argv[]) {

    if (argc != 2) {

        std::cout << "Error, wrong number of parameters!" << std::endl;
        return 1;

    }

    std::string opt = argv[1];

        if (opt == "-p") {

            std::ifstream ifs("orig.txt");
            std::string content((std::istreambuf_iterator<char>(ifs)),
                (std::istreambuf_iterator<char>()));

            PrepareText(content);

        }
        else if (opt == "-e") {

            std::ifstream ifs("plain.txt");
            std::string content((std::istreambuf_iterator<char>(ifs)),
                (std::istreambuf_iterator<char>()));

            std::fstream myfile("key.txt", std::ios_base::in);
            std::string key((std::istreambuf_iterator<char>(myfile)),
                (std::istreambuf_iterator<char>()));

            EncryptXOR(content, key);

        }
        else if (opt == "-k") {

            //kryptoanaliza cezara z tekstem jawnym
            std::string text = "Dod pd nrwdC";
            std::string help = "kotaZ";

            //CryptanalysisCaesarWithHelp(text, help);

        }

    //std::cout << odszyfrowane << std::endl;

    return 0;
}
