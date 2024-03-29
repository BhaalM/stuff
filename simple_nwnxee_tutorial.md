# Objective 

The objective of this tutorial is to learn how to add basic functionality to NWNXEE. In order to do that I'll show you how to implement the very simple SetCorpseDecayTime function. After that, the best way to progress is to learn from the code of other plugins. 

# API

The API (the definition of the clases, structures, functions... that the game uses internally) is located in the directory NWNXLib/API/Linux/API.

In order to implement the SetCorpseDecayTime function the first thing we need to know is how this time is stored in the API. At the beginning it can be hard to search something in this big bunch of files... but after a while you'll see their names are more than enough to know where to look. 

Since we are interested in a creature property we should start looking at files with "creature" in its name: the basic creature properties are defined in the file "CNWSCreature.hpp", their stats are defined in "CNWSCreatureStats.hpp", its appearance in CNWSCreatureAppearanceInfo.hpp... 

In our case, the CNWSCreature.hpp header defines the CNWSCreature structure, based on the more general CNWSObject. Basically all the creatures we encounter in the game are defined with this structure. If you look at the begining of its definition you'll see a field named "m_nDecayTime":

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
    uint32_t m_nDecayTime; //<--- This one
 ```
So if we could access to the struct of the creature and change this value, we should be able to change the corpse decay time. And this is exactly what you can do with NWNXEE.

How do we know this is the correct field? well, we really don't know for sure because we don't have access to the whole code of the game, we'll need to test it, but the name of the variable seems promising.

# NWN Script and interface with NWNXEE

Form the NWNScript point of view we'll have a function like this one:

```C
void NWNX_Creature_SetCorpseDecayTime(object creature, int nDecayTime);
```
"creature" is the creature we want to change its decay time, and nDecayTime is the new time we want to set: it's an int because in the structure of the game it is stored as an int. But time in what? seconds? minutes? In the Toolset you can see that the Decay Time of a creature is defined in seconds, so maybe it is stored in seconds... but it seems odd to use an int32 to store a time in seconds. We'll have to test it, and if you do you'll see this int is not in second but in milliseconds.

This NWN Script function will call the NWNXEE function using "NWNX_CallFunction" defined in the nwnx.h header. The input and ouput arguments between nwnscript and nwnxee are passed using "stacks", we just have to push things onto the stack and they will be available to the NWNXEE function:

```C
const string NWNX_Creature = "NWNX_Creature"; //The plugin the function belongs to

void NWNX_Creature_SetCorpseDecayTime(object creature, int nDecayTime)
{
    string sFunc = "SetCorpseDecayTime"; // This is the name of the NWNXEE function we want to call (we'll create it later)
    NWNX_PushArgumentInt(nDecayTime);    // Push into the stack the decay time
    NWNX_PushArgumentObject(creature);   // Push the creature object ID (no, this is not the object)

    NWNX_CallFunction(NWNX_Creature, sFunc); // Call the NWNXEE function
}
```
Note 1: The order of the "pushes" are important!! we'll have to do the "pops" in inverse order in the NWNXEE code. The convention in NWNXEE plugins is that we push the arguments in inverse order in the nwnscript file, so the pop in the C++ code are done in the correct order.

Note 2: The objects in NWN scripts are not the structures or classes we have seen before, they are identifiers (ObjectIDs) that can be used to get the full memory structure in NWNXEE.

# NWNXEE code

Now we have to add the function to the NWNXEE creature plugin. For our very simple function we only have to change one file in the creature plugin: Plugins/Creature/Creature.cpp.

If you open this file you'll see a lot of function declarations like for example:

```C
NWNX_EXPORT ArgumentStack AddFeat(ArgumentStack&& args)
```

These are the functions that can be accessed from nwnscript code through the `NWNX_CallFunction` we've seen before and, in this case, it corresponds to the `AddFeat` function of the creature plugin. The `ArgumentStack` is just the stack with all the pushed variables of the corresponding nwnscript function. 

So, in order to add our `SetCorpseDecayTime` the code we can add:

```C
NWNX_EXPORT ArgumentStack SetCorpseDecayTime(ArgumentStack&& args)
{
    // "Pop" the creature from the stack, if null do not enter the if (See note below)
    if (auto *pCreature = Utils::PopCreature(args))    
    {
        // Pop from the stack the second argument: the time (note the order of the two "pops")
        const auto nDecayTime = args.extract<int32_t>();  
          ASSERT_OR_THROW(nDecayTime >= 0); // Just for security: time can't be negative
        pCreature->m_nDecayTime = nDecayTime; // Change our creature structure
    }
    return {}; // The returned stack (output arguments) recquired even if we return nothing
}
```
The `PopCreature` function is already defined int the file `Utils.cpp`. if you open that file you'll see it "pops" the object ID we pushed in the nwnscript function and returns a pointer to the CNWSCreature structure of our creature we want to modify.

Now compile the plugin with the command Scripts/buildnwnx.sh, and that's all! :)
