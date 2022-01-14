#include "mainHeader.hpp"

void Player::movePlayer(){

    coord.y -= keyDown[UP] * moveSpeed;
    coord.y += keyDown[DOWN] * moveSpeed;
    coord.x -= keyDown[LEFT] * moveSpeed;
    coord.x += keyDown[RIGHT] * moveSpeed;

    setNewDirectionAfterMove();
    setHitBox();
}

void Player::setKeyDown(int key_, bool value_){
    keyDown[key_] = value_;
}

bool* Player::showKeyDown(){
    return keyDown;
}

void Player::setNewDirectionAfterMove(){
    if(keyDown[UP] + keyDown[DOWN] != 1){
        switch(keyDown[RIGHT] - keyDown[LEFT]){
        case -1:
            setDirection(LEFT);
            break;
        case 1:
            setDirection(RIGHT);
            break;
        }
    }
    else {
        if (keyDown[RIGHT] + keyDown[LEFT] == 0){
            switch(keyDown[DOWN] - keyDown[UP]){
            case -1:
                setDirection(UP);
                break;
            case 1:
                setDirection(DOWN);
                break;
            }
        }
    }
}

void Player::setDirection(int dir_){
    directionView = dir_;
}

void Player::loadBitmap(char nameFile[], int dir_){
    switch (dir_){
    case UP:
        bitmapUp = al_load_bitmap(nameFile);
        break;
    case DOWN:
        bitmapDown = al_load_bitmap(nameFile);
        break;
    case LEFT:
        bitmapLeft = al_load_bitmap(nameFile);
        break;
    case RIGHT:
        bitmapRight = al_load_bitmap(nameFile);
        break;
    }
}

void Player::drawPlayer(){
    switch(directionView){
    case UP:
        al_draw_scaled_bitmap(bitmapUp, 0, 0, 40, 40, coord.x, coord.y, 60, 60, 0);
        break;
    case DOWN:
        al_draw_scaled_bitmap(bitmapDown, 0, 0, 40, 40, coord.x, coord.y, 60, 60, 0);
        break;
    case LEFT:
        al_draw_scaled_bitmap(bitmapLeft, 0, 0, 40, 40, coord.x, coord.y, 60, 60, 0);
        break;
    case RIGHT:
        al_draw_scaled_bitmap(bitmapRight, 0, 0, 40, 40, coord.x, coord.y, 60, 60, 0);
        break;
    }
}

void Player::loadAllBitmaps(){
    loadBitmap("assets/narutoback.png", UP);
    loadBitmap("assets/naruto.png", DOWN);
    loadBitmap("assets/narutoleft.png", LEFT);
    loadBitmap("assets/narutoright.png", RIGHT);
    initInventory();
    projectile.loadBitmap("assets/shuriken.png", "assets/throwingknife.png");
}

void Player::setPosition(int x_, int y_){
    coord.x = x_;
    coord.y = y_;
}

void Player::setHitBox(){
    hitBox.inf.x = coord.x;
    hitBox.inf.y = coord.y;
    hitBox.sup.x = coord.x + 60;
    hitBox.sup.y = coord.y + 60;
}

void Player::initPlayer(){
    health = 600;
    fullHp = 600;
    moveSpeed = 3;
    stdSpeed = 3;
    keyDownInit();
    initEquips();
    maxStorage = 10;
}

void Player::initEquips(){
    weaponEquiped = createEmptyItem();
    helmetEquiped = createEmptyItem();
    armorEquiped = createEmptyItem();
    legsEquiped = createEmptyItem();
    bootsEquiped = createEmptyItem();
    shieldEquiped = createEmptyItem();

    //helmetEquiped = createHelmet();
    //armorEquiped = createArmor();
    //legsEquiped = createLegs();
    //bootsEquiped = createBoots();
}

void Player::keyDownInit(){
    for (int i = 0; i < 4; i ++)
        keyDown[i] = false;
}

Coordinates Player::showCoord(){
    return coord;
}

HitBoxRange Player::showHitBox(){
    return hitBox;
}

void Player::drawHitbox(){
    Colors colors;
    al_draw_rectangle(hitBox.inf.x, hitBox.inf.y, hitBox.sup.x, hitBox.sup.y, colors.pastelBlue(), 1);
}

void Player::drawHealthBar(){
    al_draw_filled_rectangle(coord.x, coord.y - 5, coord.x + ((60*health)/fullHp), coord.y , al_map_rgb(0, 255, 0));
    al_draw_filled_rectangle(coord.x + ((60*health)/fullHp), coord.y -5, coord.x+60, coord.y, al_map_rgb(80, 80, 80));
}

void Player::setSpeed(int value_){
    moveSpeed = value_;
}

void Player::throwProjectile(){
    if (weaponEquiped.returnItemId() != ITEM_ID_EMPTY){
        projectile.setThrowingStatus(true);
        for (int i = 0; i < 4; i ++)
            projectile.setProjDir(i, 0);
        projectile.setProjDir(directionView, 1);
        projectile.setCoord(coord.x + 10, coord.y + 10);
        projectile.setHitBox();
    }
}

void Player::decrementHealth(int value_){
    
    health -= (float)value_ * (1.0 - (
        armorEquiped.returnDamageReduction() +
        helmetEquiped.returnDamageReduction() +
        legsEquiped.returnDamageReduction() +
        bootsEquiped.returnDamageReduction()));
    
}   

int Player::showHealth(){
    return health;
}


void Player::initTimer(int timer_, double value_){
    switch (timer_){
    case TIMER_SLOW:
        timerSlow = al_create_timer(value_);
        break;
    case TIMER_INCREASE_SPEED:
        timerIncreaseSpeed = al_create_timer(value_);
        break;
    }
}

void Player::startTimer(int timer_){
    switch (timer_){
    case TIMER_SLOW:
        al_start_timer(timerSlow);
        break;
    case TIMER_INCREASE_SPEED:
        al_start_timer(timerIncreaseSpeed);
        break;
    }
}

void Player::stopTimer(int timer_){
    switch (timer_){
    case TIMER_SLOW:
        al_stop_timer(timerSlow);
        break;
    case TIMER_INCREASE_SPEED:
        al_stop_timer(timerIncreaseSpeed);
        break;
    }
}

ALLEGRO_TIMER* Player::showTimer(int timer_){
    switch(timer_){
    case TIMER_SLOW:
        return timerSlow;
    case TIMER_INCREASE_SPEED:
        return timerIncreaseSpeed;
    }
}

void Player::setSlow(double value_){
    slowned = true;
    moveSpeed = moveSpeed * value_;
}

void Player::resetSpeed(){
    slowned = false;
    moveSpeed = stdSpeed;
}

void Player::initInventory(){
    numItems = 0;
    for (int i = 0; i < 5; i ++){
        inventory[i] = createEmptyItem();
    }
}

int Player::returnSlotOfItem(int itemId){
    for(int i = 0; i < maxStorage; i ++)
        if (inventory[i].returnItemId() == itemId)
            return i;
    return -1;
}

void Player::insertItemInventory(Item item_){
    if(numItems < maxStorage){
        if(isItemInInventory(item_.returnItemId())){
            inventory[returnSlotOfItem(item_.returnItemId())].increaseStack();
        }
        else{
            inventory[numItems] = item_;
            numItems ++;
        }
    }
}

void Player::deleteItemInventory(int itemId){
    for (int i = 0; i <= numItems; i ++)
        if (inventory[i].returnItemId() == itemId){
            int j;
            inventory[j] = createEmptyItem();
            numItems --;
            break;
        }

}

bool Player::isItemInInventory(int itemId){
    for (int i = 0; i < numItems; i ++)
        if (inventory[i].returnItemId() == itemId)
            return true;
    return false;
}

int Player::showMaxStorage(){
    return maxStorage;
}

Item Player::showItemInSlot(int slot_){
    return inventory[slot_];
}

void Player::removeItemStack(int slot_){
    inventory[slot_].decreaseStack();
    if (inventory[slot_].returnStack() <= 0){
        deleteItemInventory(inventory[slot_].returnItemId());
    }
}

void Player::equipHelmet(int slot_){
    if (inventory[slot_].returnItemId() != weaponEquiped.returnItemId()){
        if (inventory[slot_].returnStack() == 1){
            Item buffer;
            buffer = helmetEquiped;
            helmetEquiped = inventory[slot_];
            if (isItemInInventory(buffer.returnItemId()) && buffer.returnItemId() != ITEM_ID_EMPTY)
                inventory[returnSlotOfItem(buffer.returnItemId())].increaseStack();
            else    
                inventory[slot_] = buffer;
        }
        else if (numItems < maxStorage - 1){
            Item buffer;
            buffer = helmetEquiped;
            helmetEquiped = inventory[slot_];
            inventory[slot_].decreaseStack();
            if (isItemInInventory(buffer.returnItemId()))
                inventory[returnSlotOfItem(buffer.returnItemId())].increaseStack();
            else    
                insertItemInventory(buffer);
        }
    }
}

void Player::equipArmor(int slot_){
    if (inventory[slot_].returnItemId() != weaponEquiped.returnItemId()){
        if (inventory[slot_].returnStack() == 1){
            Item buffer;
            buffer = armorEquiped;
            armorEquiped = inventory[slot_];
            if (isItemInInventory(buffer.returnItemId()) && buffer.returnItemId() != ITEM_ID_EMPTY)
                inventory[returnSlotOfItem(buffer.returnItemId())].increaseStack();
            else    
                inventory[slot_] = buffer;
        }
        else if (numItems < maxStorage - 1){
            Item buffer;
            buffer = armorEquiped;
            armorEquiped = inventory[slot_];
            inventory[slot_].decreaseStack();
            if (isItemInInventory(buffer.returnItemId()))
                inventory[returnSlotOfItem(buffer.returnItemId())].increaseStack();
            else    
                insertItemInventory(buffer);
        }
    }
}

void Player::equipLegs(int slot_){
    if (inventory[slot_].returnItemId() != legsEquiped.returnItemId()){
        if (inventory[slot_].returnStack() == 1){
            Item buffer;
            buffer = legsEquiped;
            legsEquiped = inventory[slot_];
            if (isItemInInventory(buffer.returnItemId()) && buffer.returnItemId() != ITEM_ID_EMPTY)
                inventory[returnSlotOfItem(buffer.returnItemId())].increaseStack();
            else    
                inventory[slot_] = buffer;
        }
        else if (numItems < maxStorage - 1){
            Item buffer;
            buffer = legsEquiped;
            legsEquiped = inventory[slot_];
            inventory[slot_].decreaseStack();
            if (isItemInInventory(buffer.returnItemId()))
                inventory[returnSlotOfItem(buffer.returnItemId())].increaseStack();
            else    
                insertItemInventory(buffer);
        }
    }
}

void Player::equipBoots(int slot_){
    if (inventory[slot_].returnItemId() != bootsEquiped.returnItemId()){
        if (inventory[slot_].returnStack() == 1){
            Item buffer;
            buffer = bootsEquiped;
            bootsEquiped = inventory[slot_];
            if (isItemInInventory(buffer.returnItemId()) && buffer.returnItemId() != ITEM_ID_EMPTY)
                inventory[returnSlotOfItem(buffer.returnItemId())].increaseStack();
            else    
                inventory[slot_] = buffer;
        }
        else if (numItems < maxStorage - 1){
            Item buffer;
            buffer = bootsEquiped;
            bootsEquiped = inventory[slot_];
            inventory[slot_].decreaseStack();
            if (isItemInInventory(buffer.returnItemId()))
                inventory[returnSlotOfItem(buffer.returnItemId())].increaseStack();
            else    
                insertItemInventory(buffer);
        }
    }
}

void Player::equipWeapon(int slot_){
    if (inventory[slot_].returnItemId() != weaponEquiped.returnItemId()){
        if (inventory[slot_].returnStack() == 1){
            Item buffer;
            buffer = weaponEquiped;
            weaponEquiped = inventory[slot_];
            if (isItemInInventory(buffer.returnItemId()) && buffer.returnItemId() != ITEM_ID_EMPTY)
                inventory[returnSlotOfItem(buffer.returnItemId())].increaseStack();
            else    
                inventory[slot_] = buffer;
        }
        else if (numItems < maxStorage - 1){
            Item buffer;
            buffer = weaponEquiped;
            weaponEquiped = inventory[slot_];
            inventory[slot_].decreaseStack();
            if (isItemInInventory(buffer.returnItemId()))
                inventory[returnSlotOfItem(buffer.returnItemId())].increaseStack();
            else    
                insertItemInventory(buffer);
        }
    }
}

void Player::equipShield(int slot_){
    Item buffer;
    buffer = shieldEquiped;
    shieldEquiped = inventory[slot_];
    inventory[slot_] = buffer;
}

Item Player::returnHelmetEquiped(){
    return helmetEquiped;
}
Item Player::returnArmorEquiped(){
    return armorEquiped;
}
Item Player::returnLegsEquiped(){
    return legsEquiped;
}
Item Player::returnBootsEquiped(){
    return bootsEquiped;
}
Item Player::returnWeaponEquiped(){
    return weaponEquiped;
}
Item Player::returnShieldEquiped(){
    return shieldEquiped;
}