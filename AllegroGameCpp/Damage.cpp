#include "mainHeader.hpp"

bool DmgAndColision::projectileHitPlayer(Projectile *projectile, Player *player){

    if (isProjectileIn(player->showHitBox(), *projectile) && player->showHealth() > 0){
        projectile->setThrowingStatus(false);
        player->decrementHealth(projectile->showDamage());
        player->setSpeed(3);
        return true;
    }
    return false;
}

bool DmgAndColision::enemyHitPlayer(Enemies *enemy, Player *player){
    if (isEnemyIn(*player, *enemy) && player->showHealth() > 0){
        player->decrementHealth(100);
        return true;
    }
    return false;
}

bool DmgAndColision::playerProjectileHit(Enemies *enemy, Player *player){
    if (isProjectileIn(enemy->showHitBox(), player->projectile)){
        enemy->decrementHealth(200);
        if (enemy->showHealth() <= 0)
            enemy->setAliveStatus(false);
        player->projectile.setThrowingStatus(false);
        return true;
    }
    return false;
}

bool DmgAndColision::isNextPositionPlayerValid(Player player, Obstacles obst){
    HitBoxRange newHBPlayer = player.showHitBox();
    if (player.showKeyDown()[UP]){
        newHBPlayer.inf.y -= 10;

        newHBPlayer.sup.y -= 10;

    }
    if (player.showKeyDown()[DOWN]){
        newHBPlayer.inf.y += 10;
        newHBPlayer.sup.y += 10;
    }
    if (player.showKeyDown()[LEFT]){
        newHBPlayer.inf.x -= 10;
        newHBPlayer.sup.x -= 10;
    }
    if (player.showKeyDown()[RIGHT]){
        newHBPlayer.inf.x += 10;
        newHBPlayer.sup.x += 10;
    }

    if (isHitboxIn(obst.showHitBox(), newHBPlayer))
        return false;
    return true;
}
