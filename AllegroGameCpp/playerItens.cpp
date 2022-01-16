#include "mainHeader.hpp"

void Player::initInventory(){
    numItems = 0;
    for (int i = 0; i < maxStorage; i ++){
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
        if(isItemInInventory(item_.returnItemId()))
            inventory[returnSlotOfItem(item_.returnItemId())].increaseStack();
        
        else
            for(int i = 0; i < maxStorage; i++)
                if (inventory[i].returnItemId() == ITEM_ID_EMPTY){
                    inventory[i] = item_;
                    break;
                }
            
        setNumItems();
    }
}

void Player::deleteItemInventory(int itemId){
    for (int i = 0; i <= maxStorage; i ++)
        if (inventory[i].returnItemId() == itemId){
            int j;
            inventory[j] = createEmptyItem();
            break;
        }

}

bool Player::isItemInInventory(int itemId){
    for (int i = 0; i < maxStorage; i ++)
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
            else  if(inventory[slot_].returnItemId() != ITEM_ID_EMPTY) 
                inventory[slot_] = buffer;
        }
        else if (numItems < maxStorage - 1){
            Item buffer;
            buffer = helmetEquiped;
            helmetEquiped = inventory[slot_];
            inventory[slot_].decreaseStack();
            if (isItemInInventory(buffer.returnItemId()))
                inventory[returnSlotOfItem(buffer.returnItemId())].increaseStack();
            else  if(inventory[slot_].returnItemId() != ITEM_ID_EMPTY) 
                insertItemInventory(buffer);
        }
    }
    setNumItems();
}

void Player::equipArmor(int slot_){
    if (inventory[slot_].returnItemId() != weaponEquiped.returnItemId()){
        if (inventory[slot_].returnStack() == 1){
            Item buffer;
            buffer = armorEquiped;
            armorEquiped = inventory[slot_];
            if (isItemInInventory(buffer.returnItemId()) && buffer.returnItemId() != ITEM_ID_EMPTY)
                inventory[returnSlotOfItem(buffer.returnItemId())].increaseStack();
            else if(inventory[slot_].returnItemId() != ITEM_ID_EMPTY) 
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
    setNumItems();
}

void Player::equipLegs(int slot_){
    if (inventory[slot_].returnItemId() != legsEquiped.returnItemId()){
        if (inventory[slot_].returnStack() == 1){
            Item buffer;
            buffer = legsEquiped;
            legsEquiped = inventory[slot_];
            if (isItemInInventory(buffer.returnItemId()) && buffer.returnItemId() != ITEM_ID_EMPTY)
                inventory[returnSlotOfItem(buffer.returnItemId())].increaseStack();
            else  if(inventory[slot_].returnItemId() != ITEM_ID_EMPTY) 
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
    setNumItems();
}

void Player::equipBoots(int slot_){
    if (inventory[slot_].returnItemId() != bootsEquiped.returnItemId()){
        if (inventory[slot_].returnStack() == 1){
            Item buffer;
            buffer = bootsEquiped;
            bootsEquiped = inventory[slot_];
            if (isItemInInventory(buffer.returnItemId()) && buffer.returnItemId() != ITEM_ID_EMPTY)
                inventory[returnSlotOfItem(buffer.returnItemId())].increaseStack();
            else if(inventory[slot_].returnItemId() != ITEM_ID_EMPTY)   
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
    setNumItems();
}

void Player::equipWeapon(int slot_){
    if (inventory[slot_].returnItemId() != weaponEquiped.returnItemId()){
        Item buffer;
        buffer = weaponEquiped;
        weaponEquiped = inventory[slot_];
        inventory[slot_] = buffer;
    }
    else{
        weaponEquiped.setStack(weaponEquiped.returnStack() + inventory[slot_].returnStack());
        inventory[slot_] = createEmptyItem();
    }
    setNumItems();
}

void Player::equipShield(int slot_){
    Item buffer;
    buffer = shieldEquiped;
    shieldEquiped = inventory[slot_];
    inventory[slot_] = buffer;
    numItems --;
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

void Player::setNumItems(){
    numItems = 0;
    for(int i = 0; i < maxStorage; i ++)
        if (inventory[i].returnItemId() != ITEM_ID_EMPTY)
            numItems++;
}

void Player::increaseCoins(int coins_){
    coins += coins_;
}

void Player::decreaseCoins(int coins_){
    coins -= coins_;
}

int Player::returnCoins(){
    return coins;
}