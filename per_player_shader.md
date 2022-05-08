
# Objective

The objective of this short tutorial is to show how to activate shaders for a particular player, allowing to change how they see the world without affecting the rest of players.

# Requirements

The latest version of [NWNX](https://github.com/nwnxee/unified). We'll use the following functions: `NWNX_Player_UpdateWind()` and `NWNX_Area_GetWindPower()`

# Limitations

This tutorial supposes you are not using the `SetAreaWind` function of the base game:

```C
// Sets the detailed wind data for oArea
// The predefined values in the toolset are:
//   NONE:  vDirection=(1.0, 1.0, 0.0), fMagnitude=0.0, fYaw=0.0,   fPitch=0.0
//   LIGHT: vDirection=(1.0, 1.0, 0.0), fMagnitude=1.0, fYaw=100.0, fPitch=3.0
//   HEAVY: vDirection=(1.0, 1.0, 0.0), fMagnitude=2.0, fYaw=150.0, fPitch=5.0
void SetAreaWind(object oArea, vector vDirection, float fMagnitude, float fYaw, float fPitch);
```

That is, the wind is set by the toolset and not by any script in your module. If this is not your case you'll have to change the code of this tutorial.

# How it works

The shaders have access to some _uniforms_ (see this [tutorial](https://nwn.wiki/display/NWN1/Shaders) for more info on shaders and uniforms) that are set by the game: the area flags, the world time, etc. And the one we will use in this tutorial _areaGlobalWind_ which contains the global wind vector for the area.

¿Why this _uniform_? because I found this _uniform_ can be changed in a per player basis, so we can change the value of _areaGlobalWind_ for **only one player**. There are sureley other _uniforms_ that can be used but, as we will see, this one allows an easy way for the shader to detect we want to apply a specific effect without affecting, at least noticeably, the wind effects in the area.  
