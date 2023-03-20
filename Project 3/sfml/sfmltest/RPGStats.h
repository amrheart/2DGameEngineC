#ifndef RPGSTATS_H
#define RPGSTATS_H
class RPGStats
{
private:
    // Sprites will contain stats about characters
    int strength;
    int dexterity;
    int intelligence;

    int base_health;
    int max_health;
    int health;
    int health_per_level;

    int attack;
    int base_attack;
    int attack_per_level;

    int exp;
    int level;

    int gold;
    int exp_reward;
    int gold_reward;
public:

    // getters and setters for stats
    void SetAttack(int attack);
    int GetAttack();

    void SetHealth(int health);
    int GetHealth();

    void SetMaxHealth(int max_health);
    int GetMaxHealth();

    void SetStrength(int strength);
    int GetStrength();

    void SetDexterity(int dexterity);
    int GetDexterity();

    void SetIntelligence(int intelligence);
    int GetIntelligence();

    // will return true if player levels up, false otherwise
    bool SetExp(int exp);
    int GetExp();

    // defines behavior when a sprite levels up
    void LevelUp();

    void SetLevel(int level);
    int GetLevel();

    void SetGold(int some_gold);
    int GetGold();

    int GetExpReward();
    int GetGoldReward();
};

#endif