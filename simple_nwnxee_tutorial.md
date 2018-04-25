# Objective 

The objective of this tutorial is to learn how to add basic functionality to NWNXEE. In order to do that I'll show you how to implement the very simple SetCorpseDecayTime function. After that, the best way to progress is to learn from the code of other plugins. 

# API

The API (the definition of the clases, structures, fucntions... that the game uses internally) is located in the directory NWNXLib/API/Linux/API (I'll focus on the Linux API only)

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
    string sFunc = "SetCorpseDecayTime";                     // This will be the name of the NWNXEE function we want to call
    NWNX_PushArgumentInt(NWNX_Creature, sFunc, nDecayTime);  // Push into the stack the decay time
    NWNX_PushArgumentObject(NWNX_Creature, sFunc, creature); // Push the creature object ID (no, this is not the object)

    NWNX_CallFunction(NWNX_Creature, sFunc); // Call the NWNXEE function
}
```
Note 1: The order of the "pushes" are important!! we'll have to do the "pops" in inverse order in the NWNXEE code.

Note 2: The objects in NWN scripts are not the structures or classes we have seen before, they are identifiers (ObjectIDs) that can be used to get the full memory structure in NWNXEE.

# NWNXEE code

Now we have to add the function to the NWNXEE creature plugin.

## Creature.hpp
Firstly, we'll add the "SetCorpseDecayTime" declaration to the Creature.hpp header, for example at the end of all the other declarations. As I said earlier, you can see that the input and output arguments are stacks:

```C
    .....
    ArgumentStack GetMovementType               (ArgumentStack&& args);
    ArgumentStack SetWalkRateCap                (ArgumentStack&& args);
    ArgumentStack SetGold                       (ArgumentStack&& args);
    ArgumentStack SetCorpseDecayTime            (ArgumentStack&& args); //<---- Here
```

At the begining of the header file you can see that ArgumentStack is in fact NWNXLib::Services::Events::ArgumentStack:

```C
using ArgumentStack = NWNXLib::Services::Events::ArgumentStack;
```
If you look at the code of other plungins you will surely find (Depending on the author, the time of the coding...) declarations like:

```C
NWNXLib::Services::Events::ArgumentStack SetCorpseDecayTime( NWNXLib::Services::Events::ArgumentStack&& args); 
```
Which is equivalent.

## Creature.cpp

In the CPP file we have to: 

1. Add the definition of the function, 
2. but also we have to "register" the funcion in the NWNXEE Core so it'll know this function exists.

Let's starts with easy part, the registration, which is done in the constructor of the plugin:

```C
reature::Creature(const Plugin::CreateParams& params)
    : Plugin(params)
{
#define REGISTER(func) \
//...
//We have to register our function here, adding the following line:
//If we do not register the function, the NWNXEE core will throw an error if we try to use it
REGISTER(SetCorpseDecayTime); 
//..
#undef REGISTER
}
```
And finally, let see the definition of our function:

```C
ArgumentStack Creature::SetCorpseDecayTime(ArgumentStack&& args)
{
    ArgumentStack stack;                  // The returned stack (output arguments) recquired even if we return nothing
    if (auto *pCreature = creature(args)) // "Pop" the creature from the stack using function creature (see note below)
    {
        // Pop from the stack the second argument: the time (note the order of the two "pops")
        const auto nDecayTime = Services::Events::ExtractArgument<int32_t>(args); 
        ASSERT(nDecayTime >= 0); // Just for security: time can't be negative
        pCreature->m_nDecayTime = nDecayTime; // Change our creature structure
    }
    return stack; //Always return a stack, even if empty
}
``` 
The "creature()" function is already defined in the plugin (line 121 when writting this tutorial, the comments are mine)

```C
CNWSCreature *Creature::creature(ArgumentStack& args)
{
    const auto creatureId = Services::Events::ExtractArgument<Types::ObjectID>(args); //Pop the creature ID 

    //Check if OBJECT is valid. 
    //All the NWN script constants like OBJECT_INVALID are defined in the NWNXLib/API/Constants.hpp file
    if (creatureId == Constants::OBJECT_INVALID) 
    {
        // If it is not valid, send an error to the LOG
        LOG_NOTICE("NWNX_Creature function called on OBJECT_INVALID"); 
        return nullptr;
    }
    
    // return the Creature object from the object ID
    return Globals::AppManager()->m_pServerExoApp->GetCreatureByGameObjectID(creatureId);
}
```

Now compile the plugin with the command Scripts/buildnwnx.sh, and that's all! :)


