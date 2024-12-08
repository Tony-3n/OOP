#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

// ===== Class Character =====
class Character {
protected:
    int Health, MaxHealth;
    int Strength;
    int Magic;
    int Potions;
    int Exp;  // Thêm EXP vào lớp Character
    int Level; // Thêm Level vào lớp Character
    int SkillPoints, MaxSkillPoints; // Giới hạn lược sử dụng skill
public:
    virtual ~Character() {}
    //Character() : Exp(0), Level(1) {}  // Khởi tạo EXP và Level
    Character(int maxHP, int maxSP) : Health(maxHP), MaxHealth(maxHP), Strength(10), Magic(10), Potions(3), Exp(0), Level(1), SkillPoints(maxSP), MaxSkillPoints(maxSP) {}
    // ---------------- Character's getters -----------------------
    int getHealth() const {
        return Health;
    }
    int getStrength() const {
        return Strength;
    }
    int getMagic() const {
        return Magic;
    }
    int getPotions() const {
        return Potions;
    }
    int getExp() const {
        return Exp;
    }
    int getLevel() const {
        return Level;
    }
    int getSkillPoints() const {
        return SkillPoints;
    }
    // ---------------- Character's methods -----------------------
    void takeDamage(int D) {
        Health -= D;
    }
    void usePotion() {
        if (Potions > 0) {
            Potions--;
            int healthRestored = MaxHealth * 0.3;
            int skillPointsRestored = ceil(MaxSkillPoints * 0.3);

            Health += healthRestored;
            if (Health > MaxHealth) { Health = MaxHealth; }

            SkillPoints += skillPointsRestored;
            if (SkillPoints > MaxSkillPoints) { SkillPoints = MaxSkillPoints; }

            cout << "You used a potion! Health and Skill Points slightly restored.\n";
            cout << "Remaining potions: " << Potions << ".\n";
        }
        else {
            cout << "No potions left! Turn lost.\n";
        }
    }
    virtual void replenishHealth() { // Hồi đầy máu
        Health = MaxHealth;
        cout << "Health replenished to " << Health << "!\n";
    }
    virtual void replenishSkillPoints() { // Hồi đầy skill point
        SkillPoints = MaxSkillPoints;
        cout << "Skill Points replenished to " << SkillPoints << "!\n";
    }
    //gain exp, level up to heal 100%
    virtual void gainExp(int value) {
        Exp += value;
        while (Exp >= 100) {  // Level up khi EXP đạt 100 hoặc hơn
            Exp -= 100;
            Level++;
            cout << "Level Up! You are now level " << Level << "!" << endl;
            replenishHealth(); // Refill health after leveling up
            replenishSkillPoints(); // Refill Skill Points after leveling up
            // Heal player stats and increase them after leveling up
            Strength += Strength * 0.2;  // Increase Strength by 20%
            Magic += Magic * 0.2;  // Increase Magic by 20%
            // Potions increase by 1 for every level-up
            Potions++;
            cout << "Stats increased by 20%! Strength: " << Strength << ", Magic: " << Magic << ", Health: " << Health << endl;
        }
    }
    virtual void showStats() const {
        cout << "Health: " << Health << " | Strength: " << Strength << " | Magic: " << Magic << " | Level: " << Level << " | Skill Points: " << SkillPoints << endl;
    }
    virtual int action() = 0;  // Phương thức hành động ảo cho các lớp kế thừa
    virtual int useSkill(int skillChoice) = 0;
};

// ===== Class Knight =====
class Knight : public Character {
public:
    Knight() : Character(120, 5) {
        Health = 120;
        Strength = 15;
        Magic = 0;
        Potions = 3;
    }
    void replenishHealth() override {
        Health = MaxHealth; // Restore Health
    }
    void replenishSkillPoints() override {
        SkillPoints = MaxSkillPoints; // Restore Skill points
    }

    int useSkill(int skillChoice) override {
        if (SkillPoints <= 0) { // Kiểm tra nhân vật còn điểm SP không
            cout << "Not enough Skill Points! Turn lost.\n";
            return 0;
        }
        SkillPoints--; // Giam 1 SP sau moi luoc dung skill
        // Ultimate Skill: The Final Sword
        switch (skillChoice) {
        case 1: // Power Slash
            cout << "You use Power Slash!" << endl;
            return Strength * 2;
        case 2: // Shield Block
            cout << "You use Shield Block! You can now take more damage." << endl;
            Health += 37;
            return 0;
        case 3: // Charge
            cout << "You use Charge! Strength increases." << endl;
            Strength += 5;
            return Strength * 0.2; // Moderate damage
        case 4: // last Resort
            cout << "You use Last Resort!" << endl;
            SkillPoints = 0;
            return Strength * 50 / Health;
        default:
            cout << "You don't know how to use that! Turn lost." << endl;
            return 0;
        }
    }

    int action() override {
        // Knight tấn công với kiếm hoặc sử dụng potion
        cout << "Choose your action:\n1. Attack\n2. Use Potion\n3. Use Skills\n";
        int choice;
        cin >> choice;
        if (choice == 1) {
            cout << "You attack with your sword!" << endl;
            // SP increases by 1 each turn.
            if (SkillPoints < MaxSkillPoints) {
                SkillPoints += 1;
            }
            else {
                SkillPoints += 0;
            }
            return Strength;
        }
        else if (choice == 2 && Potions > 0) {
            usePotion();
            return 0;
        }
        else if (choice == 3) {
            cout << "Knight skills: " << endl;
            cout << "1. Power Slash\n2. Shield Block\n3. Charge\n4. Last Resort\n";
            int skillChoice;
            cin >> skillChoice;
            return useSkill(skillChoice);
        }
        else {
            cout << "Invalid choice or out of potions!" << endl;
            return 0;
        }
    }

    void showStats() const override {
        cout << "Knight Stats - ";
        Character::showStats();
    }
};

// ===== Class Wizard =====
class Wizard : public Character {
public:
    Wizard() : Character(1000, 10) {
        Health = 1000;
        Strength = 5;
        Magic = 20;
        Potions = 3;
    }

    void replenishHealth() override {
        Health = MaxHealth; // Restore Health
    }
    void replenishSkillPoints() override {
        SkillPoints = MaxSkillPoints; // Restore Skill points
    }

    int useSkill(int skillChoice) override {
        if (SkillPoints <= 0) { // Kiểm tra nhân vật còn điểm SP không
            cout << "Not enough Skill Points! Turn lost.\n";
            return 0;
        }
        SkillPoints--; // Giam 1 SP sau moi luoc dung skill
        // Ultimate skill: The Light Of Justice
        switch (skillChoice) {
        case 1: // Fire ball
            cout << "You cast Fireball!" << endl;
            return Magic * 2;
        case 2: // Magic Shield
            cout << "You cast Magic Shield! You can now take more damage." << endl;
            Health += 10;
            return 0;
        case 3: // Arcane Surge
            cout << "You use Arcane Surge! Magic increases." << endl;
            Magic += 14;
            return 0;
        case 4: // The Light of Justice
            cout << "You use The Light of Justice!" << endl;
            if (SkillPoints == 1) {
                SkillPoints = 0;
                return Magic * MaxSkillPoints;
            }
            else {
                cout << "Fail to use! (Your SP must precisely be at 1 point to use)" << endl;
                return 0;
            }
            return 0;
        default:
            cout << "You don't know how to use that! Turn lost." << endl;
            return 0;
        }
    }

    int action() override {
        // Wizard tấn công bằng phép thuật hoặc sử dụng potion
        cout << "Choose your action:\n1. Attack\n2. Use Potion\n3. Use Skills\n";
        int choice;
        cin >> choice;
        if (choice == 1) {
            cout << "You hit your opponent with your wand!" << endl;
            // SP increases by 1 each turn.
            if (SkillPoints < MaxSkillPoints) {
                SkillPoints += 1;
            }
            else {
                SkillPoints += 0;
            }
            return Strength;
        }
        else if (choice == 2 && Potions > 0) {
            usePotion();
            return 0;
        }
        else if (choice == 3) {
            cout << "Wizard skills: " << endl;
            cout << "1. Fire ball\n2. Magic Shield\n3. Arcane Surge\n4. The Light of Justice\n";
            int skillChoice;
            cin >> skillChoice;
            return useSkill(skillChoice);
        }
        else {
            cout << "Invalid choice or out of potions!" << endl;
            return 0;
        }
    }
    void showStats() const override {
        cout << "Wizard Stats - ";
        Character::showStats();
    }
};

// ===== Class Assassin =====
class Assassin : public Character {
public:
    Assassin() : Character(80, 7) {
        Health = 80;
        Strength = 20;
        Magic = 0;
        Potions = 3;
    }

    void replenishHealth() override {
        Health = MaxHealth; // Restore Health
    }
    void replenishSkillPoints() override {
        SkillPoints = MaxSkillPoints; // Restore Skill points
    }

    int useSkill(int skillChoice) override {
        if (SkillPoints <= 0) { // Kiểm tra nhân vật còn điểm SP không
            cout << "Not enough Skill Points! Turn lost.\n";
            return 0;
        }
        SkillPoints--; // Giam 1 SP sau moi luoc dung skill
        int ConsumedSkillPoints;
        switch (skillChoice) {
        case 1: // Deep Cut
            cout << "You use Deep Cut!" << endl;
            return Strength * 2;
        case 2: // Dodge
            cout << "You use Dodge!" << endl;
            if (Health < MaxHealth * 0.2) {
                Health *= Strength;
            }
            else {
                Health += Strength;
            }
            return 0;
        case 3: // Hide and Prepare
            cout << "You hide in some corners to prepare your trick." << endl;
            SkillPoints += 3;
            return 0;
        case 4: // Stealth
            cout << "You use Stealth." << endl;
            ConsumedSkillPoints = SkillPoints + 1;
            SkillPoints = 0;
            return Strength * 0.3 * ConsumedSkillPoints;
        default:
            cout << "You don't know how to use that! Turn lost." << endl;
            return 0;
        }
    }

    int action() override {
        // Knight tấn công với kiếm hoặc sử dụng potion
        cout << "Choose your action:\n1. Attack\n2. Use Potion\n3. Use Skills\n";
        int choice;
        cin >> choice;
        if (choice == 1) {
            cout << "You attack with your hidden blade!" << endl;
            // SP increases by 1 each turn.
            if (SkillPoints < MaxSkillPoints) {
                SkillPoints += 1;
            }
            else {
                SkillPoints += 0;
            }
            return Strength;
        }
        else if (choice == 2 && Potions > 0) {
            usePotion();
            return 0;
        }
        else if (choice == 3) {
            cout << "Assassin skills: " << endl;
            cout << "1. Deep Cut\n2. Dodge\n3. Hide and Prepare\n4. Stealth\n";
            int skillChoice;
            cin >> skillChoice;
            return useSkill(skillChoice);
        }
        else {
            cout << "Invalid choice or out of potions!" << endl;
            return 0;
        }
    }

    void showStats() const override {
        cout << "Assassin Stats - ";
        Character::showStats();
    }
};

// ===== Class Enemy =====
class Enemy {
public:
    string Name;
    int Health;
    int Damage;
    Enemy(string name, int health, int damage)
        : Name(name), Health(health), Damage(damage) {}

    virtual ~Enemy() {}

    string getName() const {
        return Name;
    }

    int getHealth() const {
        return Health;
    }

    void takeDamage(int D) {
        Health -= D;
    }

    int attack() const {
        cout << Name << " attacks for " << Damage << " damage!" << endl;
        return Damage;
    }

    void increaseHealth(int amount) {
        Health += amount;
    }

    void showStats() const {
        cout << Name << " Stats - Health: " << Health << " | Damage: " << Damage << endl;
    }
};

Enemy generateRandomEnemy() {
    // Randomly choose an enemy type
    int enemyType = rand() % 6; // 0: Slime, 1: Skeleton, 2: Dragon
    switch (enemyType) {
    case 0:
        return Enemy("Slime", 50, 10);
    case 1:
        return Enemy("Skeleton", 80, 15);
    case 2:
        return Enemy("Dragon", 120, 30);
        //dracula, goblin, God, 
    case 3: 
        return Enemy("Dracula", 200, 100);
    case 4:
        return Enemy("Goblin", 60, 10);
    case 5:
        return Enemy("Leviathan", 350, 50);
    case 6:
        return Enemy("GOD", 999999, 999999);
    default:
        // Handle invalid enemy type
        return Enemy("Unknown Enemy", 50, 50);
    }
}

//void clearscreen() {
//#ifdef _WIN32
//    system("cls"); // Windows system command to clear the screen
//#else
//    system("clear"); // Unix-based systems (Linux, macOS) command to clear the screen
//#endif
//}

// ===== Function: battle PVE) =====
void pveStatus(Character& player, Enemy& enemy) {
    // Show health status
    //system("cls");
    cout << "\n------ Status Update -------\n";
    player.showStats();
    enemy.showStats();
    cout << "----------------------------\n";
}

void pvpStatus(Character& player1, Character& player2) {
    //system("cls");
    cout << "----------------------------\n";
    cout << "Player 1 HP: " << player1.getHealth() << " | Skill Points: " << player1.getSkillPoints() << endl;
    cout << "Player 2 HP: " << player2.getHealth() << " | Skill Points: " << player2.getSkillPoints() << endl;
    cout << "----------------------------\n";
}

void battlePVE(Character& player, Enemy& enemy) {
    cout << "Battle Started!" << endl;
    while (player.getHealth() > 0) {
        pveStatus(player, enemy);
        // Player's turn
        cout << "Player's turn:\n";
        int damage = 0;
        if (auto knight = dynamic_cast<Knight*>(&player)) {
            damage = knight->action();
        }
        else if (auto wizard = dynamic_cast<Wizard*>(&player)) {
            damage = wizard->action();
        }
        else if (auto assassin = dynamic_cast<Assassin*>(&player)) {
            damage = assassin->action();
        }
        enemy.takeDamage(damage);
        cout << "After attack, " << enemy.Name << " has " << enemy.Health << " health left.\n";
        cout << "----------------------------\n";
        // Enemy's turn
        pveStatus(player, enemy);
        if (enemy.Health > 0) {
            cout << enemy.Name << "'s turn:\n";
            cout << enemy.Name << " attacks!\n";
            player.takeDamage(enemy.Damage);
            cout << "After enemy attack, Player has " << player.getHealth() << " health left.\n";
        }
        else {
            enemy = generateRandomEnemy();
            cout << "A new enemy, " << enemy.Name << ", appears!\n";
        }
        cout << "----------------------------\n";
        // Wait for user input
        std::string input;
        cout << "Press Enter to continue...";
        std::getline(cin, input);
    }
    cout << "You lost!" << endl;
    // Wait for user input before exiting
    std::string input;
    cout << "Press Enter to continue...";
    std::getline(cin, input);
    //clearscreen();
}

// PVP battle (Updated with status updates)
void battlePVP(Character& player1, Character& player2) {
    while (player1.getHealth() > 0 && player2.getHealth() > 0) {
        pvpStatus(player1, player2); // Show status
        // Player 1's turn
        cout << "Player 1's turn:\n";
        int damage1 = 0;
        if (auto knight1 = dynamic_cast<Knight*>(&player1)) {
            damage1 = knight1->action();
        }
        else if (auto wizard1 = dynamic_cast<Wizard*>(&player1)) {
            damage1 = wizard1->action();
        }
        else if (auto assassin1 = dynamic_cast<Assassin*>(&player1)) {
            damage1 = assassin1->action();
        }
        player2.takeDamage(damage1);
        // Show status update
        cout << "Player 1 attacks with " << damage1 << " damage!" << endl;
        cout << "----------------------------\n";
        // Wait for user input before Player 2's turn
        cout << "Press Enter to continue...\n";
        cin.ignore(); // Clear the newline character from previous input
        cin.get();    // Wait for the user to press Enter
        if (player2.getHealth() <= 0) break; // Check if player2's health is below zero.
        pvpStatus(player1, player2); // Show status
        // Player 2's turn
        cout << "Player 2's turn:\n";
        int damage2 = 0;
        if (auto knight2 = dynamic_cast<Knight*>(&player2)) {
            damage2 = knight2->action();
        }
        else if (auto wizard2 = dynamic_cast<Wizard*>(&player2)) {
            damage2 = wizard2->action();
        }
        else if (auto assassin2 = dynamic_cast<Assassin*>(&player2)) {
            damage2 = assassin2->action();
        }
        player1.takeDamage(damage2);
        // Show status update
        cout << "Player 2 attacks with " << damage2 << " damage!" << endl;
        cout << "----------------------------\n";
        // Wait for user input before the next round
        cout << "Press Enter to continue...\n";
        cin.ignore(); // Clear the newline character from previous input
        cin.get();    // Wait for the user to press Enter
    }
    pvpStatus(player1, player2); // Show status
    if (player1.getHealth() <= 0) {
        cout << "Player 2 wins!" << endl;
    }
    else {
        cout << "Player 1 wins!" << endl;
    }
    cout << "Press Enter to return to the main menu...\n";
    cin.ignore(); // Clear any leftover newline character
    cin.get();    // Wait for the user to press Enter
    //clearscreen();
}

// ===== Function: Main Menu =====
void mainMenu() {
    cout << "Welcome to the game!" << endl;
    cout << "1. PVP (Player vs Player)" << endl;
    cout << "2. PVE (Player vs Environment)" << endl;
    cout << "3. Exit game" << endl;
    cout << "Choose your mode: ";
}

/// ===== Main Function =====
int main() {
    srand(static_cast<unsigned int>(time(0)));
    int modeChoice;
    do {
        mainMenu(); // Display the main menu
        cin >> modeChoice;
        if (modeChoice == 1) {
            // PVP Mode
            //system("cls");
            cout << "PVP Mode selected." << endl;
            cout << "Player 1, Choose your character:\n1. Knight\n2. Wizard\n3. Assassin\n";
            int choice1;
            cin >> choice1;
            Character* player1;
            if (choice1 == 1) {
                player1 = new Knight();
            }
            else if (choice1 == 2) {
                player1 = new Wizard();
            }
            else {
                player1 = new Assassin();
            }
            cout << "Player 2, Choose your character:\n1. Knight\n2. Wizard\n3. Assassin\n";
            int choice2;
            cin >> choice2;
            Character* player2;
            if (choice2 == 1) {
                player2 = new Knight();
            }
            else if (choice2 == 2) {
                player2 = new Wizard();
            }
            else {
                player2 = new Assassin();
            }
            battlePVP(*player1, *player2);
            delete player1;
            delete player2;
        }
        else if (modeChoice == 2) {
            // PVE Mode
            //system("cls");
            cout << "PVE Mode selected." << endl;
            cout << "Choose your character:\n1. Knight\n2. Wizard\n3. Assassin\n";
            int choice;
            cin >> choice;
            Character* player;
            if (choice == 1) {
                player = new Knight();
            }
            else if (choice == 2) {
                player = new Wizard();
            }
            else {
                player = new Assassin();
            }
            do {
                Enemy enemy = generateRandomEnemy();
                cout << "A " << enemy.getName() << "appears" << endl;
                battlePVE(*player, enemy);
            } while(player->getHealth() > 0);
            delete player;
        }
        else if(modeChoice == 3) {
            cout << "Exiting the game..." << endl;
            break;  // Exit the loop
        }
        else {
            cout << "Invalid choice. Please select a valid option." << endl;
        }
    } while(modeChoice !=3);
    return 0;
}