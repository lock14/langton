#include <utility>

#include <utility>

//
// Created by brian on 4/7/2019.
//

#include <iostream>
#include "Menu.hpp"

std::size_t menu::prompt_option(const std::string& prompt, const std::vector<std::string>& options, std::size_t indent_val) {
    std::size_t choice;
    std::string indent(indent_val, ' ');
    std::cout << indent << prompt << " (" << 1 << ":" << options[0];
    for (std::size_t i = 1; i < options.size(); i++) {
        std::cout << ", " << (i + 1) << ":" << options[i];
    }
    std::cout << ")? ";
    while (!(std::cin >> choice) || !(0 < choice && choice <= options.size())) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << indent << "invalid input" << std::endl;
        std::cout << indent << prompt << " (" << 1 << ":" << options[0];
        for (std::size_t i = 1; i < options.size(); i++) {
            std::cout << ", " << (i + 1) << ":" << options[i];
        }
        std::cout << ")? ";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return choice;
}


bool menu::MenuItem::run() {
    return f();
}

const std::string& menu::MenuItem::getText() const {
    return text;
}

const std::function<bool()>& menu::MenuItem::getFunc() const {
    return f;
}

menu::MenuItem::MenuItem(std::string text, std::function<bool()> f): text(std::move(text)), f(std::move(f)) {}

menu::Menu::Menu(std::size_t indent): indent(indent), items() {}

std::size_t menu::Menu::getIndent() {
    return indent;
}

void menu::Menu::addItem(const MenuItem& item) {
    items.push_back(item);
}

bool menu::Menu::run() {
    std::string indent_str(indent, ' ');
    for (std::size_t i = 0; i < items.size(); i++) {
        std::cout << indent_str << (i + 1) << ". " << items[i].getText() << std::endl;
    }
    std::size_t choice = prompt_range("your choice", 1ul, items.size(), indent);
    return items[choice - 1].getFunc()();
}
