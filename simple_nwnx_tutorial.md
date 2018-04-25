# Objective: 

The objective of this tutorial is to learn how to add basic functionality to NWNXEE. In order to do that I'll show you how to implement the very simple SetCoprseDecayTime function. After that, the best way to progress is to learn form the code of other plugins. 

# API

The API (the definition of the clases, structures, fucntions... that the game uses internally) is located in the directory NWNXLib/API/Linux/API (I'll focus on the Linux API only)

The first thing we need to implement the SetCorpseDecayTime function is to find where this time is stored in the API. At the beginning it can be hard to search something in this bunch of files... but after a while you'll see their names are more than enough to know where to look. 

Since we are interested in a creature property we should start looking at files with "creature" in its name, most of the basic creature properties are defined in the file "CNWSCreature.hpp". This header defines the CNWSCreature structure, based on the more general CNWSObject.

If you look at the beggining of this structure definition you'll see:

```C
struct CNWSCreature
    : CNWSObject
{
    int32_t m_bPonyRide;
    uint16_t m_nEquipArrayIndex;
    uint32_t m_poidCntrSpellObjects[10];
    int32_t m_nNumCntrSpellObjects;
    CExoString m_sScripts[13];
    CExoString m_sOriginalScripts[13];
    CNWSQuickbarButton* m_pQuickbarButton;
    int32_t m_bLootable;
    uint32_t m_nDecayTime; <--- This one
 ```
How do we know this is the correct place? well, we really don't know for sure because we don't have access to the full code of the game, we'll need to test it, but the name of the variable seems promising.

# Inerface between NWSCRIPT and NWNXEE

Form the NWNScript point of view we'll have a function like this one:

```C
void NWNX_Creature_SetCorpseDecayTime(object creature, int nDecayTime);
```
"creature" is the creature we want to change its decay time, and nDecayTime is the new time we wan to set: it's an int because in the structure of the game it is stored as an int. But time in what? seconds? minutes? In the Toolset you can see that the Decay Time of a creature is defined in seconds, so maybe it is stored in seconds... but it seems odd to use an int32 to store a time in seconds. We'll have to test it, and if you do you'll see this int represent the time in milliseconds.

This NWN Script function will call the NWNXEE function using "NWNX_CallFunction" defined in the nwnx.h header. The input and ouput arguments are passed between nwnscript and nwnxee using "stacks":

```C
void NWNX_Creature_SetCorpseDecayTime(object creature, int nDecayTime)
{
    string sFunc = "SetCorpseDecayTime";
    NWNX_PushArgumentInt(NWNX_Creature, sFunc, nDecayTime);
    NWNX_PushArgumentObject(NWNX_Creature, sFunc, creature);

    NWNX_CallFunction(NWNX_Creature, sFunc);
}
```






