#include "mainHeader.hpp"

bool Damage::projectileHitPlayer(Projectile projectile, Player *player){
    if (isProjectileIn(*player, projectile)){
        player->decrementHealth(projectile.showDamage());
        return true;
    }
    return false;
}
