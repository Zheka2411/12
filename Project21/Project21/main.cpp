#include <iostream>
#include <string>
using namespace std;

// Enum for Weapon Grade
enum class Grade {
    Common, Rare, Epic, Legendary, Mythic
};

// Base class for Weapon
class Weapon {
protected:
    Grade grade;
    string name;
    int damage;

public:
    Weapon(Grade grade, string name, int damage) : grade(grade), name(name), damage(damage) {}
    Weapon(string name) : grade(Grade::Common), name(name), damage(10) {}

    virtual Grade GetDamage() const { return grade; }
    virtual void UpGrade() {
        if (grade != Grade::Mythic) {
            grade = static_cast<Grade>(static_cast<int>(grade) + 1);
            damage += 10; // Increase damage with upgrade
        }
    }

    virtual ~Weapon() {}
};

// Stick Class
class Stick : public Weapon {
    int charges;

public:
    Stick(string name, int charges) : Weapon(name), charges(charges) {}

    Grade GetDamage() const override { return grade; }
    void UpGrade() override {
        Weapon::UpGrade();
        charges += 5; // Increase charges with upgrade
    }
};

// Sword Class
class Sword : public Weapon {
public:
    Sword(string name, int damage) : Weapon(Grade::Common, name, damage) {}

    Grade GetDamage() const override { return grade; }
    void UpGrade() override {
        Weapon::UpGrade();
        damage += 5; // Additional bonus for swords
    }
};

// Bow Class
class Bow : public Weapon {
    int maxDamage;

public:
    Bow(string name, int maxDamage) : Weapon(name), maxDamage(maxDamage) {}

    Grade GetDamage() const override { return grade; }
    void UpGrade() override {
        Weapon::UpGrade();
        maxDamage += 10; // Increase max damage with upgrade
    }
};

// Base class for Unit
class Unit {
protected:
    int HP;
    Weapon* weapon;
    int speed;
    string name;
    bool IsDefense;

public:
    Unit(string name, int HP, Weapon* weapon = nullptr) : name(name), HP(HP), weapon(weapon), IsDefense(false) {}

    virtual void TakeDamage(int value) {
        if (IsDefense) {
            value /= 2; // Reduce damage if in defense mode
        }
        HP -= value;
        if (HP < 0) HP = 0;
    }

    virtual void Attack(Unit& target) {
        if (weapon) {
            target.TakeDamage(weapon->GetDamage());
        }
        else {
            target.TakeDamage(10); // Default attack damage
        }
    }

    virtual void Defense() { IsDefense = true; }
    virtual ~Unit() {}
};

// Swordman Class
class Swordman : public Unit {
    unsigned int power;

public:
    Swordman(string name, int HP, unsigned int power, Weapon* weapon) : Unit(name, HP, weapon), power(power) {}

    void Attack(Unit& target) override {
        cout << name << " attacks with power!\n";
        Unit::Attack(target);
    }

    void Defense() override {
        cout << name << " is defending!\n";
        IsDefense = true;
    }
};

// Mage Class
class Mage : public Unit {
    unsigned int mana;

public:
    Mage(string name, int HP, unsigned int mana, Weapon* weapon) : Unit(name, HP, weapon), mana(mana) {}

    void Attack(Unit& target) override {
        if (mana >= 20) {
            cout << name << " casts a spell!\n";
            mana -= 20;
            Unit::Attack(target);
        }
        else {
            cout << name << " is out of mana!\n";
        }
    }

    void Defense() override {
        cout << name << " creates a magic barrier!\n";
        IsDefense = true;
    }
};

// Archer Class
class Archer : public Unit {
    unsigned int arrows;

public:
    Archer(string name, int HP, unsigned int arrows, Weapon* weapon) : Unit(name, HP, weapon), arrows(arrows) {}

    void Attack(Unit& target) override {
        if (arrows > 0) {
            cout << name << " shoots an arrow!\n";
            arrows--;
            Unit::Attack(target);
        }
        else {
            cout << name << " is out of arrows!\n";
        }
    }

    void Defense() override {
        cout << name << " hides in cover!\n";
        IsDefense = true;
    }
};

int main() {
    Sword sword("Excalibur", 50);
    Bow bow("Longbow", 100);

    Swordman swordman("Arthur", 150, 50, &sword);
    Archer archer("Robin", 100, 10, &bow);

    swordman.Attack(archer);
    archer.Defense();
    archer.Attack(swordman);

    return 0;
}
