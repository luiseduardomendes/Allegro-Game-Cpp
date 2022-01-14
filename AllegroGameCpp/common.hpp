#pragma once

void checkChests(Chests chests[], Player *player);
double distanceBetween(Coordinates a, Coordinates b);
void createObstacles(Obstacles obstacles[], Screen screen);
bool isEnemyIn(Player player, Enemies enemy);
bool pointInsideBox(Coordinates, HitBoxRange);
bool isProjectileIn(HitBoxRange HB, Projectile projectile);
bool isHitboxIn(HitBoxRange HB1, HitBoxRange HB2);
Item createEmptyItem();
Item createShuriken();
Item createThrowingKnife();
Item createArmor();
Item createHelmet();
Item createLegs();
Item createBoots();