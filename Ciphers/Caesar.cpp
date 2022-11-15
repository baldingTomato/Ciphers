//Tomasz Kłuba, 275542

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

    //std::cout << text << std::endl;

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

    //std::cout << text << std::endl;

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

    //std::cout << text << std::endl;

    std::fstream file;
    file.open("crypto.txt", std::fstream::out);
    file << text;
    file.close();

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

    std::cout << "a' value equals: " << a_inverse << std::endl;

    std::fstream file;
    file.open("decrypt.txt", std::fstream::out);
    file << text;
    file.close();
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

    //std::cout << odszyfrowane << std::endl;

    std::fstream file;
    file.open("plain.txt", std::fstream::out);
    file << odszyfrowane;
    file.close();

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

            std::fstream file;
            file.open("key_found.txt", std::fstream::out);
            file << key << "\n" << odszyfrowane;
            file.close();
            
            //std::cout << "Key: " << key << " decrypted text: " << odszyfrowane << '\n';
            break;
        }

    }

}

int NWD(int x, int y) {

    while (x != y) {

        if (x > y) {

            x -= y;

        }
        else {

            y -= x;

        }

    }

    return x;
}

void CryptanalysisAffineWithHelp(std::string text, std::string help) {

    std::string odszyfrowane = "";

    int a_inverse = 0;
    int temp = 0;
    
    for(int a = 1; a < 26; a++){

        if(NWD(a, 26) == 1){

            for(int b = 0; b < 26; b++){

                for(int i = 0; i < 26; i++){

                    temp = (a * i) % 26;

                    if (temp == 1) {

                        a_inverse = i;

                    }

                }

                odszyfrowane = "";

                for(int i = 0; i < text.length(); i++) {

                    if(text[i] >= 'A' && text[i] <= 'Z'){

                        char Cchar = (char)(((a_inverse * ((text[i] + 'A' - b)) % 26)) + 'A');
                        odszyfrowane.push_back(Cchar);

                    }else if(text[i] >= 'a' && text[i] <= 'z'){

                        char Cchar = (char)(((a_inverse * ((text[i] + 'a' - b)) % 26)) + 'a');
                        odszyfrowane.push_back(Cchar);

                    }else{

                        odszyfrowane.push_back(text[i]);;

                    }

                }

                if(odszyfrowane.find(help) != std::string::npos){

                    std::fstream file;
                    file.open("key_found.txt", std::fstream::out);
                    file << "a: " << a << " b: " << " text: " << odszyfrowane << "\n";

                }

            }
        }
    }

}

void CryptanalysisAffine(std::string text) {

    std::string odszyfrowane = "";
    char space = '\n';

    int a_inverse = 0;
    int temp = 0;

    for (int a = 1; a < 26; a++) {

        if (NWD(a, 26) == 1) {

            for (int b = 0; b < 26; b++) {

                for (int i = 0; i < 26; i++) {

                    temp = (a * i) % 26;

                    if (temp == 1) {

                        a_inverse = i;

                    }

                }

                odszyfrowane = "";

                for (int i = 0; i < text.length(); i++) {

                    if (text[i] >= 'A' && text[i] <= 'Z') {

                        char Cchar = (char)(((a_inverse * ((text[i] + 'A' - b)) % 26)) + 'A');
                        odszyfrowane.push_back(Cchar);

                    }
                    else if (text[i] >= 'a' && text[i] <= 'z') {

                        char Cchar = (char)(((a_inverse * ((text[i] + 'a' - b)) % 26)) + 'a');
                        odszyfrowane.push_back(Cchar);

                    }
                    else {

                        odszyfrowane.push_back(text[i]);

                    }

                }

                odszyfrowane.push_back('\n');

                std::fstream file;
                file.open("plain.txt", std::fstream::out);
                file <<  odszyfrowane;

            }

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

    if (opt1 == "-c") {

        if (opt2 == "-e") {

            std::ifstream ifs("plain.txt");
            std::string content((std::istreambuf_iterator<char>(ifs)),
                (std::istreambuf_iterator<char>()));

            std::fstream myfile("key.txt", std::ios_base::in);

            int key = 0;
            myfile >> key;

            if (key < 1 || key > 25) {
                std::cout << "Error, wrong key for Caesar cipher!" << std::endl;
                return 1;
            }

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

            if (key < 1 || key > 25) {
                std::cout << "Error, wrong key for Caesar cipher!" << std::endl;
                return 1;
            }

            //std::string text = "defg";
            DecryptCaesar(content, key);

        }
        else if (opt2 == "-j") {

            //kryptoanaliza cezara z tekstem jawnym
            std::ifstream cipher("crypto.txt");
            std::string content((std::istreambuf_iterator<char>(cipher)),
                (std::istreambuf_iterator<char>()));
            //std::string text = "Dod pd nrwdC";

            std::ifstream ifs("extra.txt");
            std::string help((std::istreambuf_iterator<char>(ifs)),
                (std::istreambuf_iterator<char>()));
            //std::string help = "kotaZ";

            CryptanalysisCaesarWithHelp(content, help);

        }
        else if (opt2 == "-k") {

            //kryptoanaliza cezara
            
            std::ifstream ifs("crypto.txt");
            std::string content((std::istreambuf_iterator<char>(ifs)),
                (std::istreambuf_iterator<char>()));
            //std::string text = "Ala ma kotaZ";

            CryptanalysisCaesar(content);

        }
        else {

            std::cout << "There is no such option for Caesar cipher!" << std::endl;
            return 1;

        }

    }

    if (opt1 == "-a") {

        if (opt2 == "-e") {

            std::ifstream ifs("plain.txt");
            std::string content((std::istreambuf_iterator<char>(ifs)),
                (std::istreambuf_iterator<char>()));

            //std::string text = "AB";

            std::fstream myfile("key.txt", std::ios_base::in);

            int a = 0;
            int b = 0;
            myfile >> a;
            myfile >> b;

            EncryptAffine(content, a, b);

        }
        else if (opt2 == "-d") {

            std::ifstream ifs("crypto.txt");
            std::string content((std::istreambuf_iterator<char>(ifs)),
                (std::istreambuf_iterator<char>()));
            //std::string text = "GJ";

            std::fstream myfile("key.txt", std::ios_base::in);

            int a = 0;
            int b = 0;
            myfile >> a;
            myfile >> b;

            DecryptAffine(content, a, b);

        }
        else if (opt2 == "-j") {

            //kryptoanaliza afinicznego z tekstem jawnym
            std::ifstream cipher("crypto.txt");
            std::string content((std::istreambuf_iterator<char>(cipher)),
                (std::istreambuf_iterator<char>()));
            //std::string text = "Dod pd nrwdC";

            std::ifstream ifs("extra.txt");
            std::string help((std::istreambuf_iterator<char>(ifs)),
                (std::istreambuf_iterator<char>()));
            //std::string help = "kotaZ";

            CryptanalysisAffineWithHelp(content, help);

        }
        else if (opt2 == "-k") {

            //kryptoanaliza afinicznego z tekstem jawnym
            std::ifstream cipher("crypto.txt");
            std::string content((std::istreambuf_iterator<char>(cipher)),
                (std::istreambuf_iterator<char>()));

            CryptanalysisAffine(content);

        }
        else {

            std::cout << "There is no such option for Affine cipher!" << std::endl;
            return 1;

        }

    }

    //std::cout << odszyfrowane << std::endl;

    return 0;
}
