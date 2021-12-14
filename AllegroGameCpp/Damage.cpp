#include "mainHeader.hpp"

bool Damage::projectileHitPlayer(Projectile *projectile, Player *player){

    if (isProjectileIn(*player, *projectile) && player->showHealth() > 0){
        projectile->setThrowingStatus(false);
        player->decrementHealth(projectile->showDamage());
        player->setSpeed(3);
        return true;
    }
    return false;
}

bool Damage::enemyHitPlayer(Enemies *enemy, Player *player){
    if (isEnemyIn(*player, *enemy) && player->showHealth() > 0){
        player->decrementHealth(100);
        return true;
    }
    return false;
}
