package ucsc.wildfirestudios.BattleForWesteros;

//-------------------------------------------------------------------------------------
// Items.java
// Wildfire Studios
// Created by: Khang Tran
// Modified by: 
// Notes: 
//-------------------------------------------------------------------------------------

import java.util.ArrayList;

public class Items {

    /* DATA --------------------------------------------------------------------------- */
    public static String inputType, inputName;
    public static int inputMinLvl, inputDmg, inputDef, inputDur;

    // ArrayLists weaponBag, armorBag, and potionBag are used as the game's storage for items
    public static ArrayList<Weapon> weaponBag = new ArrayList<Weapon>();
    public static ArrayList<Armor> armorBag = new ArrayList<Armor>();
    public static ArrayList<Potion> potionBag = new ArrayList<Potion>();

    /* CONSTRUCTOR -------------------------------------------------------------------- */

    public Items() {
        // Adds 4 different weapons to game storage
        weaponBag.add(new Weapon("weapon", "RustySword",
                0, 5, 0, 10 ));
        weaponBag.add(new Weapon("weapon", "SteelSword",
                1, 7, 0, 10 ));
        weaponBag.add(new Weapon("weapon", "BattleAxe",
                2, 10, 0, 12 ));
        weaponBag.add(new Weapon("weapon", "GodKiller",
                0, 1000, 0, 1000));

        // Adds 4 different armor sets to game storage
        armorBag.add(new Armor("armor", "LeatherArmor",
                0, 0, 20, 0 ));
        armorBag.add(new Armor("armor", "HardenedLeatherArmor",
                1, 0, 30, 0 ));
        armorBag.add(new Armor("armor", "SteelArmor",
                2, 0, 50, 0 ));
        armorBag.add(new Armor("armor", "GodArmor",
                0, 0, 1000, 0));

        // Adds potions to be later placed around the map
        potionBag.add(new Potion("potion", "LesserHealingPotion", 10));
        potionBag.add(new Potion("potion", "LesserHealingPotion", 10));
        potionBag.add(new Potion("potion", "LesserHealingPotion", 10));
        potionBag.add(new Potion("potion", "HealingPotion", 20));
        potionBag.add(new Potion("potion", "HealingPotion", 20));
        potionBag.add(new Potion("potion", "GreaterHealingPotion", 40));


    }
    /* ACCESS FUNCTIONS --------------------------------------------------------------- */
    public ArrayList<Weapon> getWeapons() {
        return weaponBag;
    }
    public ArrayList<Armor> getArmors() {
        return armorBag;
    }

    /* MODIFIERS ---------------------------------------------------------------------- */
    // Creates the item as a weapon object so it can be equipped or stored by the player
    // TO BE MODIFIED

    // Weapon addWeapon()
    // Creates the item as an armor object so it can be equipped or stored by the player
    // TO BE MODIFIED
    public static Weapon addWeapon(String inputType, String inputName,
                                   int inputMinLvl, int inputDmg, int inputDef, int inputDur) {

        Weapon weapon = new Weapon(inputType, inputName, inputMinLvl, inputDmg, inputDef, inputDur);
        return weapon;
    }

    // Armor addArmor()
    // Creates the item as an armor object so it can be equipped or stored by the player
    // TO BE MODIFIED
    public static Armor addArmor(String inputType, String inputName,
                                 int inputMinLvl, int inputDmg, int inputDef, int inputDur) {

        Armor armor = new Armor(inputType, inputName, inputMinLvl, inputDmg, inputDef, inputDur);
        return armor;
    }
}