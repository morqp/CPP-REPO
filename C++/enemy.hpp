#pragma once

#include "gameObject.hpp"
#include <SFML/Graphics.hpp>
#include "spriteObject.hpp"

class Enemy : public GameObject {
    private:
        int maxHealth;
        int health;
        int attackDamage;
        int healAmount;
        float attackChance;
        float healChance;
        float doNothingChance;

    public:
        Enemy(std::string identifier);
        ~Enemy();
    public:
        SpriteObject* sprite;

        void update() override;
        void render(sf::RenderWindow& window) override;

        void setMaxHealth(int maxHealth);
        void setHealth(int health);
        int getHealth() const;
        int getMaxHealth() const;

        void setAttackDamage(int attackDamage);
        int getAttackDamage() const;

        void setHealAmount(int healAmount);
        int getHealAmount() const;

        void setSpriteFile(std::string spriteFile);
        void attackAction();
        void healAction();
        void doNothingAction();
        int chooseAction();
        void takeDamage(int damage);
        void reset();
};