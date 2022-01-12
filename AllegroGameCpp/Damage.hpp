#pragma once

class DmgAndColision{
public:
    bool projectileHitPlayer(Projectile *projectile, Player *player);
    bool enemyHitPlayer(Enemies* enemy, Player* player);
    bool playerProjectileHit(Enemies* enemy, Player *player);
    bool isNextPositionPlayerValidEach(Player player, Obstacles obst);
    bool isNextPositionEnemyValidEach(Enemies enemy, Obstacles obst);
    bool isNextPositionProjectileValid(Projectile projectile, Obstacles obst);
    bool isNextPositionProjValid(Projectile proj, Obstacles obs[]);
    bool isNextPositionPlayerValid(Player player, Obstacles obs[]);
    bool isNextPositionEnemyValid(Enemies enemy, Obstacles obs[]);
};
