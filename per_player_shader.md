
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

The shaders have access to some _uniforms_ (see this [tutorial](https://nwn.wiki/display/NWN1/Shaders) for more info on shaders and uniforms) that are set by the game: the area flags, the world time, ... and the one we will use in this tutorial _areaGlobalWind_ which contains the global wind vector for the area.

¿Why this _uniform_? because I found this _uniform_ can be changed in a per player basis, so we can change the value of _areaGlobalWind_ for **only one player**. There are sureley other _uniforms_ that can be used but, as we will see, this one allows an easy way for the shader to detect we want to apply a specific effect without affecting, at least noticeably, the wind effects in the area.

If you haven't changed the wind in any area of your module using the `SetAreaWind` function, the wind will be configured by the toolset. From `SetAreaWind` help text, this means we'll have only three possible states for `vDirection` and `fMagnitude` (if you know math you'll see the fMagnitude is not what we think it is, because the length of vDirection is not 1):

- `vDirection=(1.0, 1.0, 0.0), fMagnitude=0.0`: the squared modulus of the _areaGlobalWind_ vector will be 0
- `vDirection=(1.0, 1.0, 0.0), fMagnitude=1.0`: the squared modulus of the _areaGlobalWind_ vector will be 2
- `vDirection=(1.0, 1.0, 0.0), fMagnitude=2.0`: the squared modulus of the _areaGlobalWind_ vector will be 8

What we are going to do is to change slightly those numbers (slightly, in order to not have any noticeable/visible effect on the wind of the area). Since the modulus of _areaGlobalWind_ is a float, an easy way to do this is to add a fractional part to the squared modulus: the shader will check the fractional part and apply an effect depending on its value. For example if the fractional part is 0.01 we can remove the colors, if it's 0.02 we can inverse the colors to get an ethereal effect, etc.

# Shader code

For the sake of brevity I'm showing the code for the `fslit.shd` shader, you'll have to also modify `fslit_nm.shd`, `fslit_sm.shd`, `fslit_sm_nm.shd`, `fswater.shd` and `fsgrass.shd`. As an alternative you can modify only `fsfbpostpr.shd` but be carefull because this will affect all the textures: traps will not be red if you change the colors.

```C
//=============================================================================
//
// fslit.shd
//
//=============================================================================

#define SHADER_TYPE 2

#define FOG 1
#define KEYHOLING 1
#define LIGHTING 1

#define NORMAL_MAP 0
#define SPECULAR_MAP 0
#define ROUGHNESS_MAP 0
#define HEIGHT_MAP 0
#define SELF_ILLUMINATION_MAP 0
#define ENVIRONMENT_MAP 0

#include "inc_standard"

// Per player shaders code begins here
//====================================
uniform vec3 areaGlobalWind; // This uniform is already defined in the water shader, don't declare it again!
#define SM_WINDMAG_ETHER 0.01
#define SM_WINDMAG_ULTRAVISION 0.02

//To avoid float round off errors
#define SM_WINDMAG_PRECISION 0.005

// Per player shaders code ends here
//====================================

void main ()
{
    FragmentColor = vec4(1.0);
    SetupStandardShaderInputs();
    ApplyStandardShader();
    
    // Per player shaders code begins here
    //====================================
    float fWindMagnitud = dot(areaGlobalWind,areaGlobalWind); // Squared modulus
    fWindMagnitud = fract(fWindMagnitud); // fractional part
    
    // Now apply the shader if needed
    if(fWindMagnitud>SM_WINDMAG_ETHER-SM_WINDMAG_PRECISION && fWindMagnitud<SM_WINDMAG_ETHER+SM_WINDMAG_PRECISION)
    {
        vec3 vColor = FragmentColor.xyz;
        vColor = 1.0 - vColor;
        FragmentColor.xyz = clamp(vColor,0.0,1.0); // Just in case, maybe not needed
    }
    else if(fWindMagnitud>SM_WINDMAG_ULTRAVISION-SM_WINDMAG_PRECISION && fWindMagnitud<SM_WINDMAG_ULTRAVISION+SM_WINDMAG_PRECISION)
    {
        vec3 vColor = FragmentColor.xyz;
        vColor = vec3((vColor.r*0.2126) + (vColor.g*0.587) + (vColor.b*0.114));
        vColor *= 2.0;
        FragmentColor.xyz = clamp(vColor,0.0,1.0); // Just in case, maybe not needed
    }
    // Per player shaders code ends here
    //====================================
    
    gl_FragColor = FragmentColor;
}
```

