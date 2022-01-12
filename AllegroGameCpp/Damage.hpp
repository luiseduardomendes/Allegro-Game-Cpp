#pragma once

class DmgAndColision{
public:
    bool projectileHitPlayer(Projectile *projectile, Player *player);
    bool enemyHitPlayer(Enemies* enemy, Player* player);
    bool playerProjectileHit(Enemies* enemy, Player *player);
    bool isNextPositionPlayerValid(Player player, Obstacles obst);
    bool isNextPositionEnemyValid(Enemies enemy, Obstacles obst);
    bool isNextPositionProjectileValid(Projectile projectile, Obstacles obst);
};
