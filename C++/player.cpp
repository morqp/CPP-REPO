#include "player.hpp"

Player::Player(std::string identifier) : GameObject(identifier), sprite(nullptr) {
    this->maxHealth = 100;
    this->health = 100;
    this->attackDamage = 10;
    this->healAmount = 10;
}

Player::~Player() {
}

void Player::update() {
}

void Player::render(sf::RenderWindow& window) {
    sprite->render(window);
}

void Player::setMaxHealth(int maxHealth) {
    this->maxHealth = maxHealth;
}

void Player::setHealth(int health) {
    this->health = health;
}

int Player::getHealth() const {
    return this->health;
}

void Player::setAttackDamage(int attackDamage) {
    this->attackDamage = attackDamage;
}

int Player::getAttackDamage() const {
    return this->attackDamage;
}

void Player::setHealAmount(int healAmount) {
    this->healAmount = healAmount;
}

int Player::getHealAmount() const {
    return this->healAmount;
}

void Player::setSpriteFile(std::string spriteFile) {
    this->sprite = new SpriteObject(this->getIdentifier(), spriteFile);
}

void Player::attackAction() {
    printf("Player attacks for %d damage\n", this->attackDamage);
}

void Player::healAction() {
    if (this->health < this->maxHealth) {
        int heal = std::min(this->healAmount, this->maxHealth - this->health);
        this->health += heal;
        printf("Player heals for %d\n", heal);
    }
    else {
        printf("Player is already at full health\n");
    }
}

void Player::doNothingAction() {
    printf("Player does nothing\n");
}

void Player::takeDamage(int damage) {
    this->health -= damage;
    if (this->health <= 0) {
        this->health = 0;
    }
}

void Player::reset() {
    this->health = maxHealth;
}