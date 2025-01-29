#include <iostream>
#include <set>
#include <map>
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include<random>

#include "data.hpp"

// Глобальные переменные для размеров консоли
std::int32_t kColumns = 0;
std::int32_t kRows = 0;

void clear() {
    COORD topLeft = { 0, 0 };
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    FillConsoleOutputAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    SetConsoleCursorPosition(console, topLeft);
}

void show_text(const std::wstring& text) {
    clear();
    std::wcout << text << L"\n";
}

// Функция обработки событий
std::string process_event(const scu::Event& event) {
    std::wstring choices;
    std::map<std::uint32_t, std::string> choices_map;

    // Отладочный вывод: сколько вариантов выбора у события
    std::wcout << L"[DEBUG] Количество вариантов выбора: " << event.choices.size() << L"\n";

    if (event.choices.empty()) {
        std::wcout << L"[ОШИБКА] У события нет вариантов выбора!\n";
        system("pause");
        return "";
    }

    int choice_index = 1;
    for (const auto& choice : event.choices) {
        std::wcout << L"[DEBUG] Добавлен выбор: " << choice.second.description << L"\n";
        choices += std::to_wstring(choice_index) + L". " + choice.second.description + L"\n";
        choices_map[choice_index] = choice.first;
        choice_index++;
    }

    clear();
    show_text(event.description + L"\n\n" + choices);

    std::string temp;
    std::cin >> temp;

    int choice_number = std::stoi(temp);
    if (choices_map.find(choice_number) == choices_map.end()) {
        std::wcout << L"[ОШИБКА] Некорректный выбор! Попробуйте снова.\n";
        system("pause");
        return process_event(event);
    }

    return choices_map[choice_number];
}

int main() {
    setlocale(LC_ALL, "Russian");
    _setmode(_fileno(stdout), _O_U16TEXT);

    std::map<std::string, scu::Trait> traits = scu::Data::traits;
    int event_index = 0;
    bool is_died = false;

    while (!is_died) {
        std::string event_id = "E" + std::to_string(event_index);
        if (scu::Data::stages.at("S0").events.find(event_id) == scu::Data::stages.at("S0").events.end()) {
            break;
        }

        const scu::Event& event = scu::Data::stages.at("S0").events.at(event_id);
        std::wcout << L"[DEBUG] Загружено событие: " << event.description << L"\n";

        std::string choice_id = process_event(event);
        if (choice_id.empty()) continue;

        event_index++;
    }

    show_text(L"История завершена!");
    std::vector<std::wstring> endings = {
        L"Ви знехтували своїм здоров’ям протягом усього життя, що призвело до повного фізичного виснаження. Ваше тіло більше не змогло витримувати навантаження, і ви передчасно пішли з життя.",
        L"Ваше життя було сповнене смутку та розчарувань. Відсутність радості і позитивних емоцій зробили існування нестерпним, і ви втратили бажання жити.",
        L"Накопичений стрес та постійне напруження зруйнували вашу психіку. Ви не змогли впоратися з тиском і внутрішнім неспокоєм, що призвело до трагічних наслідків.",
        L"Ви завжди сумнівалися у власних силах і можливостях, що зрештою призвело до повної апатії і небажання жити.",
        L"Нездатність будувати стосунки та повна відсутність соціальних контактів зробили ваше життя самотнім і безнадійним.",
        L"Погане управління фінансами та відсутність стабільного доходу призвели до банкрутства і злиднів, які стали фатальними.",
        L"Відсутність прагнення до знань і розвитку зробили вас неготовим до життя в сучасному світі, що призвело до невдач та загибелі.",
        L"Відсутність творчого потенціалу і бажання самовиражатися зробило ваше життя безбарвним і порожнім.",
        L"Неправильні рішення та відсутність критичного мислення призвели до низки невиправних помилок, які коштували вам життя.",
        L"Ви не прагнули досягати цілей і змінювати своє життя на краще, що призвело до стагнації і деградації.",
        L"Ви прожили життя без віри, моралі та духовного спрямування, що призвело до внутрішнього краху.",
        L"Схильність до надмірного ризику і небезпечних авантюр зрештою призвела до трагічного фіналу вашого життя.",
        L"Ви прожили довге і насичене життя, сповнене досвіду, мудрості та цінних моментів. Ваші досягнення залишили слід в серцях близьких і суспільстві. Ви навчилися цінувати кожну мить і передавали свою мудрість наступним поколінням. Незважаючи на труднощі, ви змогли пройти шлях гідно і залишили цей світ з почуттям виконаного обов'язку.",
    };
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, endings.size() - 1);

    int random_index = distrib(gen);

    show_text(endings[random_index]);
}














