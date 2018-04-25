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

# NWN Script and interface with NWNXEE

Form the NWNScript point of view we'll have a function like this one:

```C
void NWNX_Creature_SetCorpseDecayTime(object creature, int nDecayTime);
```
"creature" is the creature we want to change its decay time, and nDecayTime is the new time we wan to set: it's an int because in the structure of the game it is stored as an int. But time in what? seconds? minutes? In the Toolset you can see that the Decay Time of a creature is defined in seconds, so maybe it is stored in seconds... but it seems odd to use an int32 to store a time in seconds. We'll have to test it, and if you do you'll see this int represent the time in milliseconds.

This NWN Script function will call the NWNXEE function using "NWNX_CallFunction" defined in the nwnx.h header. The input and ouput arguments between nwnscript and nwnxee are passed using "stacks", we just have to push things on the stack and they will be available to the NWNXEE function:

```C
const string NWNX_Creature = "NWNX_Creature"; //The plugin where the function is

void NWNX_Creature_SetCorpseDecayTime(object creature, int nDecayTime)
{
    string sFunc = "SetCorpseDecayTime";                     // This will be the name of the NWNXEE function we want to call
    NWNX_PushArgumentInt(NWNX_Creature, sFunc, nDecayTime);  // Push into the stack the decay time
    NWNX_PushArgumentObject(NWNX_Creature, sFunc, creature); // PUsh the creature object

    NWNX_CallFunction(NWNX_Creature, sFunc); // Call the function
}
```
The order of the "pushes" are important: we'll have to do the "pops" in inverse order in the NWNXEE code.

# NWNXEE code

## Creature.hpp
Now we have to add the function the NWNXEE creature plugin. Firstly, we'll add the "SetCorpseDecayTime" declaration to the Creature.hpp header, we will add it at the end of all the declarations. As I said earlier, you can see that the input and output arguments are stacks:

```C
    ArgumentStack SetGold                       (ArgumentStack&& args);
    ArgumentStack SetCorpseDecayTime            (ArgumentStack&& args); <---- Here
    
    NWNXLib::API::CNWSCreature *creature(ArgumentStack& args);
```

At the begining of the file you can see that ArgumentStack is in fact NWNXLib::Services::Events::ArgumentStack:

```C
using ArgumentStack = NWNXLib::Services::Events::ArgumentStack;
```

## Creature.cpp

In the CPP file we'll have to add the definition of the function, but also we'll have to register the funcion in the NWNXEE Core so it'll know this function exists.

Let's starts with the registration which is done in the constructor of the plugin:

```C
reature::Creature(const Plugin::CreateParams& params)
    : Plugin(params)
{
#define REGISTER(func) \
//...
//We have to register our function here adding the following line:
REGISTER(SetCorpseDecayTime); 
//..
#undef REGISTER
}
```



