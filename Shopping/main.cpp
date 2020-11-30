/* Shopping:
 *
 * Desc:
 * This program reads the product selection data of different chain stores from
 * a file at startup, stores them in a suitable data structure,
 * and gives the user the opportunity to search the data structure in question.
 * */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iomanip>
#include <algorithm>

struct Product {
    std::string product_name;
    double price;
};

bool sortNames(const Product& a, const Product& b)
// Sorts names alphabetically
{
    // Smallest value comes first
    return a.product_name < b.product_name;
}

std::map<std::string, std::map<std::string, std::vector<Product>>> chains;
std::set<std::string> all_products;
std::set<std::string> all_priced_products;
std::set<std::string> all_chains;
std::set<std::string> all_stores;


void collectData(std::vector<std::string> splitted_row)
// Collects all data from the vector that contains splitted words
// Stores the data to data structure (map)
{
    std::vector<Product> listed_items;
    Product item = {splitted_row[2], stod(splitted_row[3])};
    std::map<std::string, std::vector<Product>> stores;

    all_products.insert(splitted_row[2]);
    // If price is defined, adds the product also to priced_products vector
    if(stod(splitted_row[3]) > 0) {
        all_priced_products.insert(splitted_row[2]);
    }
    all_chains.insert(splitted_row[0]);
    all_stores.insert(splitted_row[1]);

    listed_items.push_back(item);
    stores.insert({splitted_row[1], listed_items});
    // If no chain is found
    if(chains.find(splitted_row[0]) == chains.end()) {
        chains.insert({splitted_row[0], stores});
    // If there is already chain in the data structure
    // a new map will be created which includes the store and the products.
    } else {
        std::map<std::string, std::vector<Product>> new_stores =
                                                     chains.at(splitted_row[0]);
        // if no store is found
        if(new_stores.find(splitted_row[1]) == new_stores.end()) {
            new_stores.insert({splitted_row[1], listed_items});
            // Old map will be deleted and then add new store
            chains.erase(splitted_row[0]);
            chains.insert({splitted_row[0], new_stores});
        // If there is already store in the data structure
        } else {
            // Old products will be copied
            std::vector<Product> new_listed_items =
                                chains.at(splitted_row[0]).at(splitted_row[1]);

            // Check if the product is already listed
            // If the product is in the list, old item will be replaced
            int i = 0;
            std::string item_replaced = "no";
            for(auto item : new_listed_items) {
                if(item.product_name == splitted_row[2]) {
                    Product new_item = {splitted_row[2], stod(splitted_row[3])};
                    new_listed_items.at(i) = new_item;
                    item_replaced = "yes";
                }
                i++;
            }
            // If the item has replaced
            // the new product will no longer be added a second time
            if(item_replaced == "no") {
                new_listed_items.push_back(item);
            }
            new_stores.erase(splitted_row[1]);
            new_stores.insert({splitted_row[1], new_listed_items});
            chains.erase(splitted_row[0]);
            chains.insert({splitted_row[0], new_stores});
        }
    }
}


std::vector<std::string> split(const std::string& s, const char delimiter,
                               bool ignore_empty = false)
// Splits a line into separate sentences and returns a vector,
// which have splitted row
{
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos) {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty())) {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty())) {
        result.push_back(tmp);
    }
    return result;
}


bool checkFile(std::string input_file)
// Checks whether the input file meets the definition.
// four parts, no empty parts, the last part should be double or "out-of-stock"
// If the input file can't be opened, an error message will be printed.
{
    std::ifstream open_file(input_file);
    if(not open_file) {
        std::cout << "Error: the input file cannot be opened" << std::endl;
        return false;
    } else {
        std::string row;
        while(getline(open_file, row)) {
            std::vector<std::string> splitted_row = split(row, ';', true);
            int length = splitted_row.size();
            // The number of parts must be 4
            if(length != 4) {
                std::cout << "Error: the input file has an erroneous line" <<
                             std::endl;
                return false;
            }
            long unsigned int is_double = splitted_row[3].find(".");
            // If the last part isn't double or "out-of-stock", prints error
            if(is_double == std::string::npos and (splitted_row[3] !=
                                                   "out-of-stock")) {
                std::cout << "Error: the input file has an erroneous line" <<
                             std::endl;
                return false;
            }
            for(auto word : splitted_row) {
                long unsigned int empty = word.find(" ");
                // If some part is empty
                if(word == "" or (not (empty == std::string::npos))) {
                    std::cout << "Error: the input file has an erroneous line"
                              << std::endl;
                    return false;
                }
            }
            // If price is "out-of-stock", change it to 0.0
            if(splitted_row[3] == "out-of-stock") {
                splitted_row[3] = "0.0";
            }
            collectData(splitted_row);
        }
    }
    return true;
}

bool checkParameters(std::vector<std::string> parts,
                     long unsigned int parameters)
// If the command is given the wrong number of parameters,
// an error message is printed
{
    if(parts.size() != parameters) {
        std::string command = parts.at(0);
        std::cout << "Error: error in command " << command << std::endl;
        return false;
    }
    return true;
}

void commandStores(std::vector<std::string> parts)
// Prints in alphabetical order one below the other,
// all the stores of the given chain
{
    if(all_chains.find(parts[1]) == all_chains.end()) {
        std::cout << "Error: unknown chain name" << std::endl;
    }
    for(auto name : chains) {
        if(name.first == parts[1]) {
            for(auto shop : name.second) {
                std::cout << shop.first << std::endl;
            }
        }
    }
}

void commandSelection(std::vector<std::string> parts)
// Prints all the products and their prices in the selection of the given chain
// and its store arranged alphabetically by the product name
{
    if(all_chains.find(parts[1]) == all_chains.end()) {
        std::cout << "Error: unknown chain name" << std::endl;
    } else if(all_stores.find(parts[2]) == all_stores.end()) {
        std::cout << "Error: unknown store" << std::endl;
    }
    for(auto name : chains) {
        if(name.first == parts[1]) {
            for(auto shop : name.second) {
                if(shop.first == parts[2]) {
                    sort(shop.second.begin(), shop.second.end(), sortNames);
                    for(auto item : shop.second) {
                        if(item.price == 0.0) {
                            std::string price = "out of stock";
                            std::cout << std::setprecision(2) << std::fixed <<
                                item.product_name << " " << price << std::endl;
                        } else {
                            std::cout << std::setprecision(2) << std::fixed <<
                            item.product_name << " " << item.price << std::endl;
                        }
                    }
                }
            }
        }
    }
}

void cheapestStores(std::vector<double> prices, std::vector<std::string> parts)
// Prints out the stores selling the product at the lowest price
{
    for(auto name : chains) {
        for(auto shop : name.second) {
            for(auto item : shop.second) {
                if(parts[1] == item.product_name) {
                    if(item.price == prices.at(0)) {
                        std::cout << name.first << " " << shop.first <<
                                     std::endl;
                    }
                }
            }
        }
    }
}

void commandCheapest(std::vector<std::string> parts)
// Checks whether the product specified in the command is for sale
// Finds the lowest price at which the product is on sale.
// Uses this price as part of another function that prints stores.
{
    std::vector<double> prices;
    if(all_products.find(parts[1]) == all_products.end()) {
        std::cout << "The product is not part of product selection" <<
                     std::endl;
    } else if(all_priced_products.find(parts[1]) == all_priced_products.end()) {
        std::cout << "The product is temporarily out of stock everywhere" <<
                     std::endl;
    } else {
        for(auto name : chains) {
            for(auto shop : name.second) {
                for(auto item : shop.second) {
                    if(parts[1] == item.product_name) {
                        if(item.price != 0.0) {
                            prices.push_back(item.price);
                        }
                    }
                }
            }
        }
        sort(prices.begin(), prices.end());
        std::cout << std::setprecision(2) << std::fixed << prices.at(0) <<
                     " euros" << std::endl;
        cheapestStores(prices, parts);
    }
}




int main()
{
    std::string input_file = "";
    std::cout << "Input file: ";
    getline(std::cin, input_file);
    long unsigned int parameters;

    if(not checkFile(input_file)) {
        return 1;
    }

    while(true) {
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);
        std::string command = parts.at(0);

        if(command == "quit") {
            parameters = 1;
            if(checkParameters(parts, parameters)) {
                return EXIT_SUCCESS;
            }
        } else if(command == "chains") {
            // Prints all the known grocery store chains in alphabetical order
            parameters = 1;
            if(checkParameters(parts, parameters)) {
                for(auto name : chains) {
                    std::cout << name.first << std::endl;
                }
            }
        } else if(command == "stores") {
            parameters = 2;
            if(checkParameters(parts, parameters)) {
                commandStores(parts);
            }
        } else if(command == "selection") {
            parameters = 3;
            if(checkParameters(parts, parameters)) {
                commandSelection(parts);
            }
        } else if(command == "cheapest") {
            parameters = 2;
            if(checkParameters(parts, parameters)) {
                commandCheapest(parts);
                }
        } else if(command == "products") {
            parameters = 1;
            if(checkParameters(parts, parameters)) {
                for(auto name : all_products) {
                    std::cout << name << std::endl;
                }
            }
        } else {
            std::cout << "Error: unknown command: " << command << std::endl;
        }
    }
    return 0;
}
