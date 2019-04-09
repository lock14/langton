//
// Created by brian on 4/7/2019.
//

#ifndef LANGTON2_MENU_HPP
#define LANGTON2_MENU_HPP
#include <cstdint>
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <functional>

namespace menu {

    /**
     * continuously prompts the user to enter a value until they
     * enter a value that can be parsed into a value of type T.
     *
     * @tparam T the type to be returned
     * @param prompt the prompt to be displayed to the user
     * @param indent_val the amount of spaces the prompt should be indented
     * @return the value of type T entered by the user.
     */
    template<typename T>
    T prompt(const std::string& prompt, std::size_t indent_val = 0) {
        T choice;
        std::string indent(indent_val, ' ');
        std::cout << indent << prompt << "? ";
        while (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << indent << "invalid input" << std::endl;
            std::cout << indent << prompt << "? ";
        }
        std::cin.clear();
        std::numeric_limits<std::streamsize>::max();
        return choice;
    }

    /**
     * continuously prompts the user to enter a value until they
     * enter a value that can be parsed into a value of type T and
     * that the value is within the specified range.
     *
     * @tparam T the type to be returned
     * @param prompt the prompt to be displayed to the user
     * @param minValid the minimum accepted value (inclusive) of type T
     * @param maxValid the maximum accepted value (inclusive) of type T
     * @param indent_val the amount of spaces the prompt should be indented
     * @return the value of type T entered by the user that is within the specified range
     */
    template<typename T>
    T prompt_range(const std::string& prompt, const T& minValid, const T& maxValid, std::size_t indent_val = 0) {
        T choice;
        std::string indent(indent_val, ' ');
        std::cout << indent << prompt << " (" << minValid << ", " << maxValid << ")? ";
        while (!(std::cin >> choice) || !(minValid <= choice && choice <= maxValid )) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << indent << "invalid input" << std::endl;
            std::cout << indent << prompt << " (" << minValid << ", " << maxValid << ")? ";
        }
        std::cin.clear();
        std::numeric_limits<std::streamsize>::max();
        return choice;
    }

    /**
     * continuously prompts the user to enter a number until they enter a number
     * between 1 and options.size() (inclusive).
     *
     * @param prompt the prompt to be displayed to the user
     * @param options the options for which the user is to select from
     * @param indent_val the amount of spaces the prompt should be indented
     * @return the user's choice between 1 and options.size() (inclusive)
     */
    size_t prompt_option(const std::string& prompt, const std::vector<std::string>& options, std::size_t indent_val = 0);

    class MenuItem {
    private:
        std::string text;
        std::function<bool()> f;

    public:
        // default
        MenuItem() = default;
        // copy
        MenuItem(const MenuItem&) = default;
        // move
        MenuItem(MenuItem&&) = default;
        // assignment copy
        MenuItem& operator=(const MenuItem&) = default;
        // assignment move
        MenuItem& operator=(MenuItem&&) = default;
        // destructor
        virtual ~MenuItem() = default;

        /**
         * constructs a MenuItem with the given text and function.
         *
         * @param text the menu text to display to the user
         * @param f the function to be bound to this MenuItem's run() method
         */
        MenuItem(std::string text, std::function<bool()> f);

        /**
         * retrieves the menu text for this menu item.
         *
         * @return the text for this MenuItem
         */
        const std::string& getText() const;

        /**
         * retrieves the function bound to this menu item.
         *
         * @return the function bound to this MenuItem
         */
        const std::function<bool()>& getFunc() const;

        /**
         * executes this menu item.
         *
         * @return true if this MenuItem thinks the program should continue
         */
        bool run();
    };

    class Menu {
    private:
        std::size_t indent{};
        std::vector<MenuItem> items;

    public:
        // default
        Menu() = default;
        // copy
        Menu(const Menu&) = default;
        // move
        Menu(Menu&&) = default;
        // assignment copy
        Menu& operator=(const Menu&) = default;
        // assignment move
        Menu& operator=(Menu&&) = default;
        // destructor
        virtual ~Menu() = default;

        /**
         * constructs a Menu with the given indent
         *
         * @param indent the amount of spaces all items of this Menu should be
         *        indented by.
         */
        explicit Menu(std::size_t indent);

        /**
         * adds a menu item to this menu.
         *
         * @param item the MenuItem to add
         */
        void addItem(const MenuItem& item);

        /**
         * retrieves the amount of spaces this menu should be indented.
         *
         * @return the amount of spaces this Menu Should be indented
         */
        std::size_t getIndent();

        /*
         * run this menu. The menu will prompt the user with a list
         * of menu items indented by the indent amount of this menu.
         * once the user has selected a menu item, its corresponding
         * run() method will be executed.
         */
        bool run();
    };
}
#endif //LANGTON2_MENU_HPP
