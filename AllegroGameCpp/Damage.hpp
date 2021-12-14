#pragma once

class Damage{
public:
    bool projectileHitPlayer(Projectile *projectile, Player *player);
    bool enemyHitPlayer(Enemies* enemy, Player* player);
};
