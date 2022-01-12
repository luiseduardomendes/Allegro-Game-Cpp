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
        enemy->decrementHealth(player->projectile.showDamage());
        if (enemy->showHealth() <= 0)
            enemy->setAliveStatus(false);
        player->projectile.setThrowingStatus(false);
        return true;
    }
    return false;
}

bool DmgAndColision::isNextPositionPlayerValid(Player player, Obstacles obst){
    player.movePlayer();
    if (isHitboxIn(player.showHitBox(), obst.showHitBox()))
        return false;
    else
        return true;
}

bool DmgAndColision::isNextPositionEnemyValid(Enemies enemy, Obstacles obst){
    enemy.moveEnemy();
    if (isHitboxIn(enemy.showHitBox(), obst.showHitBox()))
        return false;
    else
        return true;
}

bool DmgAndColision::isNextPositionProjectileValid(Projectile projectile, Obstacles obst){
    projectile.moveProj();
    if (isHitboxIn(projectile.showHitBox(), obst.showHitBox()))
        return false;
    else
        return true;

}