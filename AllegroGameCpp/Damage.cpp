#include "mainHeader.hpp"

bool DmgAndColision::projectileHitPlayer(Projectile *projectile, Player *player){

    if (isProjectileIn(player->showHitBox(), *projectile) && player->showHealth() > 0){
        projectile->setThrowingStatus(false);
        player->decrementHealth(projectile->showDamage());
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
        enemy->decrementHealth(player->returnWeaponEquiped().returnDamage());
        if (enemy->showHealth() <= 0)
            enemy->setAliveStatus(false);
        player->projectile.setThrowingStatus(false);
        return true;
    }
    return false;
}

bool DmgAndColision::isNextPositionPlayerValidEach(Player player, Obstacles obst){
    player.movePlayer();
    if (isHitboxIn(player.showHitBox(), obst.showHitBox()))
        return false;
    else
        return true;
}

bool DmgAndColision::isNextPositionEnemyValidEach(Enemies enemy, Obstacles obst){
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
bool DmgAndColision::isNextPositionProjValid(Projectile proj, Obstacles obs[]){
    for (int j = 0; j < NUM_WALLS; j ++){
        //if (abs(obs[j].showCoord().x - proj.projectileCoord().x) < 100 && abs(obs[j].showCoord().y - proj.projectileCoord().y) < 100){
            if (!isNextPositionProjectileValid(proj, obs[j])){
                return false;
                
            }
        //}
    }
    return true;
}

bool DmgAndColision::isNextPositionPlayerValid(Player player, Obstacles obs[]){
    for (int i = 0; i < NUM_WALLS; i ++)
        //if (abs(obs[i].showCoord().x - player.showCoord().x) < 100 && abs(obs[i].showCoord().y - player.showCoord().y) < 100)
            if (!isNextPositionPlayerValidEach(player, obs[i]))
                return false;
    return true;
}

bool DmgAndColision::isNextPositionEnemyValid(Enemies enemy, Obstacles obs[]){
    for (int j = 0; j < NUM_WALLS; j ++)
        //if (abs(obs[j].showCoord().x - enemy.showCoord().x) < 100 && abs(obs[j].showCoord().y - enemy.showCoord().y) < 100)
            if (!isNextPositionEnemyValidEach(enemy, obs[j]))
                return false;
    return true;

}