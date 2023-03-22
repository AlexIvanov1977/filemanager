// filemanager.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <filesystem>
#include <string>
#include <cstdlib>
#include <climits>
#include <fstream>
#include <system_error>
namespace  fs = std::filesystem;

class filemanager
{
public:
    filemanager() = default;
    fs::path getcp() const
    {
        return cp;
    }
    void setcp(fs::path const& ncp)
    {
        if (fs::exists(ncp))
        {
            cp = ncp;
        }
        else
        {
            std::cerr << "Path not found\n";
        }
    }

public:
    fs::path cp{ fs::current_path().generic_string() };
};

int main()
{
    setlocale(LC_ALL, "rus");
    filemanager fm;
    std::string str;
    std::error_code ec;
    int opt{ -1 };
    while (opt != 0)
    {
        system("cls");
        std::cout << fm.getcp() << "\n"
            "1 Смена текущего каталога (путь к текущему каталогу должен всегда отображаться на экране)\n"
            "2 Отображение всех подкаталогов текущего каталога\n"
            "3 Отображение всех файлов текущего каталога\n"
            "4 Создание нового каталога в текущем каталоге\n"
            "5 Удаление уже существующего каталога(если каталог не пустой – то необходимо удалить все его содержимое, для этого Вам необходимо использовать рекурсию)\n"
            "6 Создание нового файла в текущем каталоге\n"
            "7 Удаление файла из текущего каталога\n"
            "8 Переименование файла в текущем каталоге\n"
            "9 Перемещение файла из текущего каталога в указанный пользователем каталог\n"
            "10 Вывод содержимого указанного пользователем файла из текущего каталога на экран\n"
            "0 Выход\n";
        std::cin >> opt;
        switch (opt)
        {
        case 1:
        {
            std::cin.ignore(INT_MAX, '\n');
            std::getline(std::cin, str);
            fm.setcp(str);
        }
        break;
        case 2:
        {
            for (auto const& de : fs::directory_iterator{ fm.getcp() })
            {
                if (de.is_directory())
                    std::cout << de.path() << "\n";
            }
        }
        break;
        case 3:
        {
            for (auto const& de : fs::directory_iterator{ fm.getcp() })
            {
                if (de.is_regular_file())
                    std::cout << de.path() << "\n";
            }
        }
        break;
        case 4:
        {

            std::cin.ignore(INT_MAX, '\n');
            std::getline(std::cin, str);
            fs::create_directory(fm.getcp() / str, ec);
            if (ec.value())
            {
                std::cout << "create_directory() failed: " << ec.message() << "\n";
            }
        }
        break;
        case 5:
        {
            std::cin.ignore(INT_MAX, '\n');
            std::getline(std::cin, str);
            auto n = fs::remove_all(fm.getcp() / str, ec);
            if (ec.value())
            {
                std::cout << "remove_all() failed: " << ec.message() << "\n";
            }
        }
        break;
        case 6:
        {
            std::cin.ignore(INT_MAX, '\n');
            std::getline(std::cin, str);
            std::ofstream ofs{ str };
            if (!ofs.is_open())
            {
                std::cerr << "create file failed\n";
            }
            ofs.close();
        }
        break;
        case 7:
        {
            std::cin.ignore(INT_MAX, '\n');
            std::getline(std::cin, str);
            fs::remove(fm.getcp() / str, ec);
            if (ec.value())
            {
                std::cout << "remove() failed: " << ec.message() << "\n";
            }
        }
        break;
        case 8:
        {
            std::cin.ignore(INT_MAX, '\n');
            std::getline(std::cin, str);
            std::string newname;
            std::getline(std::cin, newname);
            fs::rename(fm.getcp() / str, fm.getcp() / newname, ec);
            if (ec.value())
            {
                std::cout << "rename() failed: " << ec.message() << "\n";
            }
        }
        break;
        case 9:
        {
            std::cin.ignore(INT_MAX, '\n');
            std::getline(std::cin, str); // имя файла
            std::string newfolder;
            std::getline(std::cin, newfolder); // путь к новому каталогу
            fs::rename(fm.getcp() / str, fs::path{ newfolder } / str, ec);
            if (ec.value())
            {
                std::cout << "move() failed: " << ec.message() << "\n";
            }
        }
        break;
        case 10:
        {
            std::cin.ignore(INT_MAX, '\n');
            std::getline(std::cin, str);
            std::ifstream ifs{ str };
            if (!ifs.is_open())
            {
                std::cerr << "ifs.is_open() failed\n";
            }
            else
            {
                std::cout << ifs.rdbuf() << "\n";
                ifs.close();
            }
        }
        break;
        }
        system("pause");
    }

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
