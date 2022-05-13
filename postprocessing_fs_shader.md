This is the code of a fragment postprocessing shader. That is, the code replace `fsfbpostpr.shd`. 

You can see this shader in action [here](https://www.youtube.com/watch?v=sLSG2CjMuFA) IMPORTANT: Configure the youtube player to 1080p or you'll see nothing.

This shader has been adapated to nwnEE from the youtube tutorial [Underwater World Shaders](https://www.youtube.com/watch?v=v15C8SbTTac&list=PL3POsQzaCw51Cvlnery3cIabH-YqQtMpa) by Peer Play.

You'll need to use a system like the one defined [here](https://nwn.wiki/display/NWN1/Shaders+and+Area+Flags) or [here](https://nwn.wiki/display/NWN1/Per+player+shaders) to use the shader only in certain areas. 

This shader use a noise function included in the nwnEE shader files (it's in the `inc_common.shd`): `NoiseSimplex3D()`. 

See more about [Perlin noise functions](https://www.youtube.com/watch?v=Qf4dIN99e2w&list=PLRqwX-V7Uu6bgPNQAdxQZpJuJCjeOr7VD)

```C
#define SHADER_TYPE 2

#include "inc_postpr"

// Change these defines to suit your needs
#define SM_NOISE_UW_FREQUENCY 8.0
#define SM_NOISE_UW_SCALE 0.8
#define SM_NOISE_UW_SPEED 1.0
#define SM_UW_PIXEL_OFFSET 0.002

uniform int worldtimerTimeOfDay;

void main()
{
    vec4 Color = FS_PostProcess();
    
    //New shader begin here:
    float SMtick = (worldtimerTimeOfDay/1000.0);
    vec3 spos;
    spos.xy = vVertexTexCoords.xy*SM_NOISE_UW_FREQUENCY;
    spos.z = SMtick*SM_NOISE_UW_SPEED;
    float noise = SM_NOISE_UW_SCALE * ((NoiseSimplex3D(spos) +1)/2);
    vec2 noiseToDirection = vec2(cos(2*PI*noise), sin(2*PI*noise));
    vec2 coord = vVertexTexCoords+ SM_UW_PIXEL_OFFSET*noiseToDirection; 
    Color.rgb = texture2D(texFBColor, coord).rgb;
    gl_FragColor = Color;
}
```
