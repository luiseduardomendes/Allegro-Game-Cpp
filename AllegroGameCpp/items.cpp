#include "items.hpp"

int Item::returnItemType(){
    return itemType;
}
int Item::returnItemId(){
    return itemId;
}
int Item::returnStack(){
    return stack;
}
int Item::returnDamage(){
    return damage;
}
float Item::returnDamageReduction(){
    return damageReduction;
}
int Item::returnDamageType(){
    return damageType;
}
int Item::returnProtectionType(){
    return protectionType;
}
int Item::returnEnchantingSlot(int slot_){
    return enchantingSlot[slot_];
}
int Item::returnEnchantingSlotUsed(){
    return enchantingSlotUsed;
}
int Item::returnEnchantmentsAvailable(){
    return enchantingSlotAvailable;
}

void Item::setItemType(int itemType_){
    itemType = itemType_;
}
void Item::setItemId(int itemId_){
    itemId = itemId_;
}
void Item::setStack(int stack_){
    stack = stack_;
}
void Item::increaseStack(){
    stack ++;
}
void Item::decreaseStack(){
    stack --;
}
void Item::setDamage(int damage_){
    damage = damage_;
}
void Item::setDamageReduction(float damageReduction_){
    damageReduction = damageReduction_;
}
void Item::setDamageType(int type){
    damageType = type;
}
void Item::setProtectionType(int protectionType_){
    protectionType = protectionType_;
}
void Item::setEnchantingSlot(int enchantment_, int slot_){
    enchantingSlot[slot_] = enchantment_;
}
void Item::setEnchantingSlotUsed(int enchSlotUsed_){
    enchantingSlotUsed = enchSlotUsed_;
}
void Item::increaseEnchantingSlotUsed(){
    enchantingSlotUsed ++;
}
void Item::decreaseEnchantingSlotUsed(){
    enchantingSlotUsed --;
}
void Item::setEnchantingSlotAvailable(int enchSlotAvailable_){
    enchantingSlotAvailable = enchSlotAvailable_;
}
void Item::increaseEnchantingSlotAvailable(){
    enchantingSlotAvailable ++;
}
void Item::decreaseEnchantingSlotAvailable(){
    enchantingSlotAvailable --;
}

void Item::setEquipedStatus(bool status_){
    equiped = status_;
}
