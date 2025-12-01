#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <vector>

struct Player
{
    int Id;
    std::string name;
    int level;
    std::string character;
    int power;

    bool operator<(const Player& other) const {
        return Id < other.Id;
    }
};

void AddPlayer(std::set<Player>& players);
void OrganizeByCharacter(std::set<Player> &players);
void SearchByID(std::set<Player> &players);
void SearchByLevelBynariSearch(std::set<Player> &players);
void OrganizeByPower80(std::set<Player> &players);
void ShowTopThree(std::set<Player> &players);
int ShowMenu();

int main(){

    std::set<Player> players;

    int chooice = 0;

    while (chooice != 8)
    {
        chooice = ShowMenu();
    
        switch (chooice)
        {
        case 1:
            AddPlayer(players);
            break;
        case 2:
            OrganizeByCharacter(players);
            break;
        case 3:
            SearchByID(players);
            break;
        case 4:
            OrganizeByPower80(players);
            break;
        case 5:
            SearchByLevelBynariSearch(players);
            break;
        case 6:
            ShowTopThree(players);
            break;
        case 7:
            exit(0);
            break;
        default:
            break;
        }

    }
    

    return 0;
}

void SearchByLevelBynariSearch(std::set<Player> &players){

    int level;
    Player search_by_level = {};
    std::vector<Player> players_levels(players.begin(), players.end()); //Copiamos el set

    auto ComparadorPorNivel = [](const Player&a, const Player &b){
        return a.level > b.level;
    };

    std::sort(players_levels.begin(), players_levels.end(), ComparadorPorNivel);

    std::cout << "What level are you looking for? \n";
    std::cin >> level;
    search_by_level.level = level;

    bool result = std::binary_search(players_levels.begin(), players_levels.end(), search_by_level, ComparadorPorNivel); //Utilizamos la funcion comparador por nivel,para que no utilice la del set y pueda buscar correctamente el nivel

    if (result)
    {
        std::cout << " This level exists! \n";
    }
    else {std::cout << "This level doesn't exists \n";}

    return;
}

int ShowMenu(){

    int choice;
    std::cout << "1. Create player \n 2. Search players by character \n 3. Search by ID \n 4. Organize by power \n 5. Look if level exists (Binary) \n 6. Show top three \n 7.Exit \n Write your chooice: ";
    std::cin >> choice;
    return choice;
}

void ShowTopThree(std::set<Player> &players){

    std::cout << "Top 3 players with the most power \n";

    

}

void OrganizeByPower80(std::set<Player> &players){

    int player_counter = 0;

    std::cout << "Players organize by power more than eighty \n";

    std::map<int, std::set<Player>> search_by_power;

    for (const auto i : players)
    {
        search_by_power[i.power].insert(i); //Llenamosel set
    }
    
    auto iterador = search_by_power.upper_bound(80); //Find es para encontrar uno exacto, upper bound para encontrar mayor y lower bound menor

    if (iterador != search_by_power.end())
    {
        for (const auto i : iterador->second)
        {
            player_counter++;
            std::cout << "Player " << player_counter << std::endl;
            std::cout << "level: " << i.Id << std::endl;
            std::cout << "Name: " << i.name << std::endl;
            std::cout << "Character: " << i.character << std::endl;
            std::cout << "Power: " << i.power << std::endl;
            std::cout << std::endl;
        }
    } 
    else {std::cout << "No player with more than 80 power was found \n";}

    return;
}

void ChooseCharacter(int& chooice){
    std::cout << "What character do you want to use? \n 1. Fighter \n 2. Support \n 3. Tank \n 4. ADcarry \n";
    std::cin >> chooice;
    return;
}

void AddPlayer(std::set<Player>& players){

    Player new_player;
    int chooice = 0;

    std::cout << "What is your name? \n"; 
    std::cin.ignore();
    std::getline(std::cin, new_player.name);

    std::cout << "What is your level? (Only numbers) \n";
    std::cin >> new_player.Id;

    ChooseCharacter(chooice);

    switch (chooice)
    {
    case 1:
        new_player.character = "Fighter";
        new_player.power = 90;
        break;
    case 2:
        new_player.character = "Support";
        new_player.power = 25;
        break;
    case 3:
        new_player.character = "Tank";
        new_player.power = 20;
        break;
    case 4: 
        new_player.character = "ADcarry";
        new_player.power = 76;
        break;
    default:
        std::cout << "That character doesn't exist \n";
        break;
    }
    new_player.level = 0;
    
    players.insert(new_player);

    return;
}

void SearchByID(std::set<Player>& players){

    int id_to_be_found;
    std::unordered_map<int, Player> search_by_level;

    for (const auto i : players)
    {
        search_by_level[i.Id] = i;
    }
    
    std::cout << "What is the id are you looking for? \n";

    std::cin >> id_to_be_found;

    auto iterador = search_by_level.find(id_to_be_found);

    if (iterador != search_by_level.end())
    {
        std::cout << " The player has been found sucesfully! \n";
    
        Player player_found = iterador->second;

        std::cout << "level " << player_found.Id << std::endl;
        std::cout << "Name " << player_found.name << std::endl;
        std::cout << "Character: " << player_found.character << std::endl;
        std::cout << "Level: " << player_found.level << std::endl;
        std::cout << "Power: " << player_found.power << std::endl;
    }
    else { std::cout << "The player wasn't found \n";}

}

void OrganizeByCharacter(std::set<Player> &players){

    std::string character_to_be_found;

    std::map<std::string, std::set<int>> organize_by_character;

    for (const auto i : players)
    {
        organize_by_character[i.character].insert(i.Id); // Fill the map with the set data first character, second id
    }
    

    std::cout << "What character is the player are you looking for? \n";
    std::cin.ignore();
    std::getline(std::cin, character_to_be_found);

    auto iterador = organize_by_character.find(character_to_be_found);

    if (iterador != organize_by_character.end())
    {
        
        std::cout << "The players were found succesfully! \n";

        for (int id : iterador->second)
        {
            std::cout << "Id: " << id << std::endl;
        }
        

    }
    else {std::cout << "The players were not found \n";}

}