enum enchanting {ENCHANTMENT_EMPTY, ENCHANTMENT_IGNITE, ENCHANTMENT_POISON};
enum damage_type {DMG_TYPE_NORMAL, DMG_TYPE_FIRE, DMG_TYPE_WATER, DMG_TYPE_GRASS};
enum item_type {ITEM_TYPE_THROWING_WEAPON, ITEM_TYPE_ARMOR, ITEM_TYPE_HELMET, ITEM_TYPE_LEGS, ITEM_TYPE_BOOTS};
enum item_id {ITEM_ID_EMPTY, ITEM_ID_SHURIKEN, ITEM_ID_THROWING_KNIFE, ITEM_ID_ARMOR, ITEM_ID_HEAVYARMOR, ITEM_ID_LIGHTARMOR, ITEM_ID_HELMET, ITEM_ID_LEGS, ITEM_ID_BOOTS};

class Item{
public:
    int returnItemType();
    int returnItemId();
    int returnStack();
    int returnDamage();
    float returnDamageReduction();
    int returnDamageType();
    int returnProtectionType();
    int returnEnchantingSlot(int slot_);
    int returnEnchantingSlotUsed();
    int returnEnchantmentsAvailable();

    bool isItemEquiped();

    void setItemType(int itemType_);
    void setItemId(int itemId_);
    void setStack(int stack_);
    void increaseStack();
    void decreaseStack();
    void setDamage(int damage_);
    void setDamageReduction(float damageReduction_);
    void setDamageType(int type);
    void setProtectionType(int protectionType);
    void setEnchantingSlot(int enchantment_, int slot_);
    void setEnchantingSlotUsed(int enchSlotUsed_);
    void increaseEnchantingSlotUsed();
    void decreaseEnchantingSlotUsed();
    void setEnchantingSlotAvailable(int enchSlotAvailable_);
    void increaseEnchantingSlotAvailable();
    void decreaseEnchantingSlotAvailable();
    void setEquipedStatus(bool equiped_);


private:
    int itemType;
    int itemId;
    int stack;
    int damage;
    float damageReduction;
    int damageType;
    int protectionType;
    int enchantingSlot[3];
    int enchantingSlotUsed;
    int enchantingSlotAvailable;
    bool equiped;
};