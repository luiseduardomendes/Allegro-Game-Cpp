#pragma once

class DmgAndColision{
public:
    /*damage*/
    bool projectileHitPlayer(Projectile *projectile, Player *player);
    bool enemyHitPlayer(Enemies* enemy, Player* player);
    bool playerProjectileHit(Enemies* enemy, Player *player);

    /*colision*/
    bool isNextPositionProjValid(Projectile proj, Obstacles obs[]);
    bool isNextPositionPlayerValid(Player player, Obstacles obs[]);
    bool isNextPositionEnemyValid(Enemies enemy, Obstacles obs[]);

private:
    bool isNextPositionPlayerValidEach(Player player, Obstacles obst);
    bool isNextPositionEnemyValidEach(Enemies enemy, Obstacles obst);
    bool isNextPositionProjectileValid(Projectile projectile, Obstacles obst);
};
