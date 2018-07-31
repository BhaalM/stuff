// Recquired includes: mali_string_fns.nss from Malishara DM Stage Wand and nwnx_object.nss
// Read placeables information from item description and create them in the area: this script is the ON ACTIVATE event script
// g_invis_obj is the resref of a non static object you have to create on the module (the base building block)


#include "mali_string_fns"
#include "x2_inc_switches"
#include "nwnx_object"


const int DEBUG_ESCENARIO=0;

void Unpack(object oWidget, location lReference);

void main()
{
    int nEvent =GetUserDefinedItemEventNumber();
    // SendMessageToPC(GetFirstPC(),IntToString(nEvent));

    if (nEvent ==  X2_ITEM_EVENT_ACTIVATE)
    {
      object oPC   = GetItemActivator();
      object oItem = GetItemActivated();

      Unpack(oItem, GetLocation(oPC));
    }
}

void Unpack(object oWidget, location lReference)
{  

    int nCount=0;
    int bFlag=TRUE;
    int iAppearance;
    float fFacing, fX, fY, fZ;
    int iPlot, iUseable;
    string sTag;
    string sResRef;
    location lLoc;
    vector vVect;
    object oProp;
    string sAux;
    
    string sDesc = GetDescription(oWidget, FALSE);
    if(DEBUG_ESCENARIO) SendMessageToAllDMs("sDesc: " + sDesc);

    while(bFlag)
    {
        while(GetStringLeft(sDesc, 1)=="\n")
        {
            sDesc = GetStringRight(sDesc,GetStringLength(sDesc)-1);
        }
        sAux = FirstWord(sDesc, "\n");
        if(DEBUG_ESCENARIO) SendMessageToAllDMs("sAux: " + sAux);
        sDesc = RestWords(sDesc, "\n");
        if(DEBUG_ESCENARIO) SendMessageToAllDMs("sDesc: " + sDesc);


        iAppearance = StringToInt(FirstWord(sAux, ","));            
        if(iAppearance<=0) return;
        if(DEBUG_ESCENARIO) SendMessageToAllDMs("Appearance: " + IntToString(iAppearance));
        sAux = RestWords(sAux, ",");

        fFacing=StringToFloat(FirstWord(sAux, ","));
        if(fFacing<-1.0 || fFacing>361.0) return;
        if(DEBUG_ESCENARIO) SendMessageToAllDMs("Facing: " + FloatToString(fFacing));
        sAux = RestWords(sAux, ",");

        iPlot=StringToInt(FirstWord(sAux, ","));
        if(iPlot!=0 && iPlot!=1) return;
        if(DEBUG_ESCENARIO) SendMessageToAllDMs("iPlot: " + IntToString(iPlot));
        sAux = RestWords(sAux, ",");

        sTag = FirstWord(sAux, ",");
        if(sTag=="") return;
        if(DEBUG_ESCENARIO) SendMessageToAllDMs("sTag: " + sTag);
        sAux = RestWords(sAux, ",");

        sResRef = FirstWord(sAux, ",");
        if(sResRef=="") return;
        if(DEBUG_ESCENARIO) SendMessageToAllDMs("sResRef: " + sResRef);
        sAux = RestWords(sAux, ",");

        iUseable=StringToInt(FirstWord(sAux, ","));
        if(iUseable!=0 && iUseable!=1) return;
        if(DEBUG_ESCENARIO) SendMessageToAllDMs("iUseable: " + IntToString(iUseable));
        sAux = RestWords(sAux, ",");

        fX=StringToFloat(FirstWord(sAux, ","));
        if(DEBUG_ESCENARIO) SendMessageToAllDMs("fX: " + FloatToString(fX));
        sAux = RestWords(sAux, ",");

        fY=StringToFloat(FirstWord(sAux, ","));
        if(DEBUG_ESCENARIO) SendMessageToAllDMs("fY: " + FloatToString(fY));
        sAux = RestWords(sAux, ",");

        fZ=StringToFloat(FirstWord(sAux, ","));
        if(DEBUG_ESCENARIO) SendMessageToAllDMs("fZ: " + FloatToString(fZ));
        sAux = RestWords(sAux, ",");

        vVect = Vector(fX, fY, fZ);
        lLoc = Location(GetAreaFromLocation(lReference), vVect, fFacing);

        oProp = CreateObject(OBJECT_TYPE_PLACEABLE, "g_invis_obj", lLoc, FALSE, sTag);
        if(!GetIsObjectValid(oProp)) return;

        NWNX_Object_SetAppearance(oProp, iAppearance);
        SetPlotFlag(oProp, iPlot);
        SetUseableFlag(oProp, iUseable);
    }
}
