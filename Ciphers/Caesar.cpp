#include <iostream>
#include <string.h>
#include <fstream>

void EncryptCaesar(std::string text, int key)
{
    //int key = 3;

    //encrypting
    for (int index = 0; index < text.size(); index++) {

        char c = text[index];

        if (c >= 'a' && c <= 'z') {

            c = c + key;

            if (c > 'z') {

                c = c - 'z' + 'a' - 1;

            }

            text[index] = c;

        }
        else if (c >= 'A' && c <= 'Z') {

            c = c + key;

            if (c > 'Z') {

                c = c - 'Z' + 'A' - 1;

            }

            text[index] = c;

        }

    }

    std::cout << text << std::endl;
    std::fstream file;
    file.open("crypto.txt", std::fstream::out);
    file << text;
    file.close();

}

void DecryptCaesar(std::string text, int key)
{
    //int key = 3;

    //decrypting
    for (int index = 0; index < text.size(); index++) {

        char c = text[index];

        if (c >= 'a' && c <= 'z') {

            c = c - key;

            if (c < 'a') {

                c = c + 'z' - 'a' + 1;

            }

            text[index] = c;

        }
        else if (c >= 'A' && c <= 'Z') {

            c = c - key;

            if (c < 'A') {

                c = c + 'Z' - 'A' + 1;

            }

            text[index] = c;

        }

    }

    std::cout << text << std::endl;

    std::fstream file;
    file.open("decrypt.txt", std::fstream::out);
    file << text;
    file.close();

}

void EncryptAffine(std::string text, int a, int b)
{

    //static int a = 3;
    //static int b = 6;

    for (int index = 0; index < text.length(); index++) {

        char c = text[index];

        if (c >= 'a' && c <= 'z') {

            c = (char)((((a * (text[index] - 'a')) + b) % 26) + 'a');

        }
        else if (c >= 'A' && c <= 'Z') {

            c = (char)((((a * (text[index] - 'A')) + b) % 26) + 'A');

        }

        text[index] = c;

    }

    std::cout << text << std::endl;
}

void DecryptAffine(std::string text, int a, int b)
{

    //static int a = 3;
    //static int b = 6;

    int a_inverse = 0;
    int flag = 0;

    for (int i = 0; i < 26; i++) {

        flag = (a * i) % 26;

        if (flag == 1) {

            a_inverse = i;

        }

    }

    for (int index = 0; index < text.length(); index++) {

        char c = text[index];

        if (c >= 'a' && c <= 'z') {

            c = (char)(((a_inverse * ((text[index] + 'a' - b)) % 26)) + 'a');

        }
        else if (c >= 'A' && c <= 'Z') {

            c = (char)(((a_inverse * ((text[index] + 'A' - b)) % 26)) + 'A');

        }

        text[index] = c;

    }

    std::cout << text << std::endl;
}

void CryptanalysisCaesar(std::string text) {

    std::string odszyfrowane = "";

    for (int key = 0; key < 26; key++) {

        for (int i = 0; i < text.length(); i++) {

            char c = text[i];

            if (c >= 'A' && c <= 'Z') {

                int Cchar = text[i] - key;

                if (Cchar < 65) {

                    Cchar += 26;

                }

                odszyfrowane += (char)(Cchar);

            }
            else if (c >= 'a' && c <= 'z') {

                int Cchar = text[i] - key;

                if (Cchar < 97) {

                    Cchar += 26;

                }

                odszyfrowane += (char)(Cchar);

            }
            else {

                odszyfrowane += text[i];

            }

        }

        odszyfrowane += "\n";

    }

    std::cout << odszyfrowane << std::endl;

}

void CryptanalysisCaesarWithHelp(std::string text, std::string help) {

    std::string odszyfrowane = "";

    for (int key = 0; key < 26; key++) {

        odszyfrowane = "";

        for (int i = 0; i < text.length(); i++) {

            char c = text[i];

            if (c >= 'A' && c <= 'Z') {

                int Cchar = text[i] - key;

                if (Cchar < 65) {

                    Cchar += 26;

                }

                odszyfrowane += (char)(Cchar);

            }
            else if (c >= 'a' && c <= 'z') {

                int Cchar = text[i] - key;

                if (Cchar < 97) {

                    Cchar += 26;

                }

                odszyfrowane += (char)(Cchar);

            }
            else {

                odszyfrowane += text[i];

            }

        }

        if (odszyfrowane.find(help) != std::string::npos) {
            std::cout << "Key: " << key << " decrypted text: " << odszyfrowane << '\n';
            break;
        }

    }

}


int main(int argc, char* argv[]) {

    if (argc != 3) {

        std::cout << "Error, wrong number of parameters!" << std::endl;
        return 1;

    }

    std::string opt1 = argv[1];
    std::string opt2 = argv[2];

    if(opt1 == "-c") {
        
        if (opt2 == "-e") {

            std::ifstream ifs("plain.txt");
            std::string content((std::istreambuf_iterator<char>(ifs)),
                (std::istreambuf_iterator<char>()));

            std::fstream myfile("key.txt", std::ios_base::in);

            int key = 0;
            myfile >> key;

            //std::string text = "abcd";
            EncryptCaesar(content, key);

        }
        else if (opt2 == "-d") {

            std::ifstream ifs("plain.txt");
            std::string content((std::istreambuf_iterator<char>(ifs)),
                (std::istreambuf_iterator<char>()));

            std::fstream myfile("key.txt", std::ios_base::in);

            int key = 0;
            myfile >> key;

            //std::string text = "defg";
            DecryptCaesar(content, key);

        }
        else if (opt2 == "-j") {

            //kryptoanaliza cezara z tekstem jawnym
            std::string text = "Dod pd nrwdC";
            std::string help = "kotaZ";

            CryptanalysisCaesarWithHelp(text, help);

        }
        else if (opt2 == "-k") {

            //kryptoanaliza cezara
            std::string text = "Ala ma kotaZ";

            CryptanalysisCaesar(text);

        }
        else {

            std::cout << "There is no such option for Caesar cipher!" << std::endl;
            return 1;

        }

    }

    if (opt1 == "-a") {

        if (opt2 == "-e") {

            std::string text = "AB";

            std::fstream myfile("key.txt", std::ios_base::in);

            int a = 0;
            int b = 0;
            myfile >> a;
            myfile >> b;

            EncryptAffine(text, a, b);

        }
        else if (opt2 == "-d") {

            std::string text = "GJ";

            std::fstream myfile("key.txt", std::ios_base::in);

            int a = 0;
            int b = 0;
            myfile >> a;
            myfile >> b;

            DecryptAffine(text, a, b);

        }
        else if (opt2 == "-j") {

            //kryptoanaliza afinicznego z tekstem jawnym
            std::string text = "Dod pd nrwdC";
            std::string help = "kotaZ";

            CryptanalysisCaesarWithHelp(text, help);

        }
        else if (opt2 == "-k") {

            //kryptoanaliza afinicznego
            std::string text = "Ala ma kotaZ";

            CryptanalysisCaesar(text);

        }
        else {

            std::cout << "There is no such option for Affine cipher!" << std::endl;
            return 1;

        }

    }


    //std::cout << odszyfrowane << std::endl;

    return 0;
}
