#include "mainHeader.hpp"

bool Damage::projectileHitPlayer(Projectile *projectile, Player *player){

    if (isProjectileIn(*player, *projectile) && player->showHealth() > 0){
        projectile->setThrowingStatus(false);
        player->decrementHealth(projectile->showDamage());
        return true;
    }
    return false;
}
