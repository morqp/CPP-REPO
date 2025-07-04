#include "enemy.hpp"

Enemy::Enemy(std::string identifier) : GameObject(identifier), sprite(nullptr) {
    this->maxHealth = 100;
    this->health = 100;
    this->attackDamage = 10;
    this->healAmount = 5;
    this->attackChance = 0.45f;
    this->healChance = 0.3f;
    this->doNothingChance = 0.25f;
}   

Enemy::~Enemy() {
}

void Enemy::update() {
}

void Enemy::render(sf::RenderWindow& window) {
    sprite->render(window);
}

void Enemy::setSpriteFile(std::string spriteFile) {
    this->sprite = new SpriteObject(this->getIdentifier(), spriteFile);
}

void Enemy::setMaxHealth(int maxHealth)
{
    this->maxHealth = maxHealth;
}

void Enemy::setHealth(int health) {
    this->health = health;
}

int Enemy::getHealth() const {
    return this->health;
}

int Enemy::getMaxHealth() const {
    return this->maxHealth;
}

void Enemy::setAttackDamage(int attackDamage) {
    this->attackDamage = attackDamage;
}

int Enemy::getAttackDamage() const {
    return this->attackDamage;
}

void Enemy::setHealAmount(int healAmount) {
    this->healAmount = healAmount;
}

int Enemy::getHealAmount() const {
    return this->healAmount;
}

void Enemy::attackAction() {
}

void Enemy::takeDamage(int damage) {
    this->health -= damage;
    if (this->health <= 0) {
        this->health = 0;
    }
}

void Enemy::healAction() {
    static int healActionCounter = 0;
    healActionCounter++;
    printf("Entering healAction(), healActionCounter: %d\n", healActionCounter);

    if (this->health < this->maxHealth) {
        int heal = (this->health + this->healAmount <= this->maxHealth) ? this->healAmount : (this->maxHealth - this->health);
        this->health += heal;
        printf("Heal amount is %d\n", heal);
    }
    else {
        printf("Enemy is already at full health\n");
    }

    printf("Exiting healAction()\n");
}

void Enemy::doNothingAction() {
}

int Enemy::chooseAction() {
    if (this->health <= 0) {
        reset();
        printf("Enemy died, resetting\n");
        return 4;
    }
    float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    printf("Random number: %f\n", random);

    if (random <= this->attackChance) {
        printf("Picked attack action.\n");
        return 0; // attack
    }
    else if (random > this->attackChance && random <= (this->attackChance + this->healChance)) {
        printf("Picked heal action.\n");
        return 1; // heal
    }
    else {
        printf("Picked do nothing action.\n");
        return 2; // do nothing
    }
}

void Enemy::reset() {
    this->health = maxHealth;
    this->attackDamage = 10;
    this->healAmount = 10;
}