void __cdecl CNWSCreature::ResolveSneakAttack(CNWSCreature *this, CNWSCreature *a2)
{
  int v2; // ebx@2
  int v3; // eax@2
  char *v4; // eax@2
  long double v5; // fst5@37
  long double v6; // tt@37
  long double v7; // fst5@37
  long double v8; // t2@37
  long double v9; // fst5@37
  int v10; // eax@38
  __int16 v11; // fps@41
  bool v12; // c0@41
  char v13; // c2@41
  bool v14; // c3@41
  __int16 v15; // fps@47
  bool v16; // c0@47
  char v17; // c2@47
  bool v18; // c3@47
  signed int v19; // edi@51
  signed int v20; // edi@55
  __int16 v21; // fps@66
  bool v22; // c0@66
  char v23; // c2@66
  bool v24; // c3@66
  CNWCCMessageData *v25; // ebx@74
  char *v26; // eax@74
  signed int v27; // [sp+4h] [bp-64h]@1
  signed int v28; // [sp+8h] [bp-60h]@1
  signed int v29; // [sp+Ch] [bp-5Ch]@55
  int v30; // [sp+10h] [bp-58h]@51
  float v31; // [sp+14h] [bp-54h]@1
  int v32; // [sp+18h] [bp-50h]@2
  int v33; // [sp+1Ch] [bp-4Ch]@2
  float v34; // [sp+20h] [bp-48h]@37
  float v35; // [sp+24h] [bp-44h]@37
  float v36; // [sp+28h] [bp-40h]@37
  float v37; // [sp+30h] [bp-38h]@37
  float v38; // [sp+34h] [bp-34h]@37
  float v39; // [sp+38h] [bp-30h]@37
  float v40; // [sp+40h] [bp-28h]@37
  float v41; // [sp+44h] [bp-24h]@37
  float v42; // [sp+48h] [bp-20h]@37

  v31 = 0.0;
  v28 = 0;
  v27 = 0;
  if ( a2 )
  {
    v2 = *((_DWORD *)this + 794);
    v3 = *((_DWORD *)this + 691);
    v33 = *(_BYTE *)(v3 + 8468);
    v4 = CNWSCombatRound::GetAttack((CNWSCombatRound *)v3, v33);
    v32 = *((_DWORD *)v4 + 13);
    if ( (unsigned __int16)(*((_WORD *)v4 + 41) - 867) > 1u
      && (CNWSCreatureStats::HasFeat((CNWSCreatureStats *)v2, 0xDDu)
       || CNWSCreatureStats::HasFeat((CNWSCreatureStats *)v2, 0x159u)
       || CNWSCreatureStats::HasFeat((CNWSCreatureStats *)v2, 0x15Au)
       || CNWSCreatureStats::HasFeat((CNWSCreatureStats *)v2, 0x15Bu)
       || CNWSCreatureStats::HasFeat((CNWSCreatureStats *)v2, 0x15Cu)
       || CNWSCreatureStats::HasFeat((CNWSCreatureStats *)v2, 0x15Du)
       || CNWSCreatureStats::HasFeat((CNWSCreatureStats *)v2, 0x15Eu)
       || CNWSCreatureStats::HasFeat((CNWSCreatureStats *)v2, 0x15Fu)
       || CNWSCreatureStats::HasFeat((CNWSCreatureStats *)v2, 0x160u)
       || CNWSCreatureStats::HasFeat((CNWSCreatureStats *)v2, 0x161u)
       || CNWSCreatureStats::HasFeat((CNWSCreatureStats *)v2, 0x408u)
       || CNWSCreatureStats::HasFeat((CNWSCreatureStats *)v2, 0x409u)
       || CNWSCreatureStats::HasFeat((CNWSCreatureStats *)v2, 0x40Au)
       || CNWSCreatureStats::HasFeat((CNWSCreatureStats *)v2, 0x40Bu)
       || CNWSCreatureStats::HasFeat((CNWSCreatureStats *)v2, 0x40Cu)
       || CNWSCreatureStats::HasFeat((CNWSCreatureStats *)v2, 0x40Du)
       || CNWSCreatureStats::HasFeat((CNWSCreatureStats *)v2, 0x40Eu)
       || CNWSCreatureStats::HasFeat((CNWSCreatureStats *)v2, 0x40Fu)
       || CNWSCreatureStats::HasFeat((CNWSCreatureStats *)v2, 0x410u)
       || CNWSCreatureStats::HasFeat((CNWSCreatureStats *)v2, 0x411u)
       || CNWSCreatureStats::HasFeat((CNWSCreatureStats *)v2, 0x1CCu)
       || CNWSCreatureStats::HasFeat((CNWSCreatureStats *)v2, 0x1CDu)
       || CNWSCreatureStats::HasFeat((CNWSCreatureStats *)v2, 0x1CEu)
       || CNWSCreatureStats::HasFeat((CNWSCreatureStats *)v2, 0x3F0u)
       || CNWSCreatureStats::HasFeat((CNWSCreatureStats *)v2, 0x3F1u)
       || CNWSCreatureStats::HasFeat((CNWSCreatureStats *)v2, 0x3F2u)
       || CNWSCreatureStats::HasFeat((CNWSCreatureStats *)v2, 0x3F3u)
       || CNWSCreatureStats::HasFeat((CNWSCreatureStats *)v2, 0x3F4u)
       || CNWSCreatureStats::HasFeat((CNWSCreatureStats *)v2, 0x3F5u)
       || CNWSCreatureStats::HasFeat((CNWSCreatureStats *)v2, 0x3F6u)
       || CNWSCreatureStats::HasFeat((CNWSCreatureStats *)v2, 0x3F7u)
       || CNWSCreatureStats::HasFeat((CNWSCreatureStats *)v2, 0x3F8u)
       || CNWSCreatureStats::HasFeat((CNWSCreatureStats *)v2, 0x3FAu)) )
    {
      if ( v32 )
      {
        qmemcpy(&v37, (char *)this + 124, 0xCu);
        qmemcpy(&v34, (char *)a2 + 124, 0xCu);
        v5 = v37 - v34;
        v40 = v5;
        v6 = v5;
        v7 = v38 - v35;
        v41 = v7;
        v8 = v7 * v7;
        v9 = v39 - v36;
        v42 = v9;
        v31 = v6 * v6 + v8 + v9 * v9;
      }
      v10 = CNWSCreature::GetVisibleListElement(a2, *((_DWORD *)this + 1));
      if ( !v10 || !(*(_BYTE *)(v10 + 4) & 1) )
      {
        if ( v32 == 1
          && (v12 = v31 < 100.0, v13 = 0, v14 = v31 == 100.0, (unsigned __int8)((HIBYTE(v11) & 0x45) - 1) < 0x40u)
          || !v32 )
        {
          v27 = 1;
        }
      }
      if ( !v27 && CNWSCreature::GetFlatFooted(a2) == 1 )
      {
        if ( v32 == 1
          && (v16 = v31 < 100.0, v17 = 0, v18 = v31 == 100.0, (unsigned __int8)((HIBYTE(v15) & 0x45) - 1) < 0x40u)
          || !v32 )
        {
          v27 = 1;
        }
      }
      if ( !CNWSCreatureStats::HasFeat(*((CNWSCreatureStats **)a2 + 794), 0xFBu) )
        goto LABEL_77;
      v30 = 0;
      v19 = 0;
      if ( *(_BYTE *)(v2 + 161) )
      {
        do
        {
          if ( CNWSCreatureStats::GetClass((CNWSCreatureStats *)v2, v19) == (_BYTE)CNWClass::CCLASS_ROGUE )
            v30 = (unsigned __int8)CNWSCreatureStats::GetClassLevel((CNWSCreatureStats *)v2, v19, 0);
          ++v19;
        }
        while ( v19 < *(_BYTE *)(v2 + 161) );
      }
      v29 = 0;
      v20 = 0;
      if ( *(_BYTE *)(*((_DWORD *)a2 + 794) + 161) )
      {
        do
        {
          if ( (CNWSCreatureStats::GetClass((CNWSCreatureStats *)v2, v20) == (_BYTE)CNWClass::CCLASS_ROGUE
             || CNWSCreatureStats::GetClass((CNWSCreatureStats *)v2, v20) == (_BYTE)CNWClass::CCLASS_BARBARIAN)
            && (unsigned __int8)CNWSCreatureStats::GetClass((CNWSCreatureStats *)v2, v20) > v29 )
          {
            v29 = (unsigned __int8)CNWSCreatureStats::GetClass((CNWSCreatureStats *)v2, v20);
          }
          ++v20;
        }
        while ( v20 < *(_BYTE *)(*((_DWORD *)a2 + 794) + 161) );
      }
      if ( v30 >= v29 - 4 )
LABEL_77:
        v28 = 1;
      if ( v28 == 1 && CNWSCreature::GetFlanked(this, a2) == 1 )
      {
        if ( v32 == 1
          && (v22 = v31 < 100.0, v23 = 0, v24 = v31 == 100.0, (unsigned __int8)((HIBYTE(v21) & 0x45) - 1) < 0x40u)
          || !v32 )
        {
          v27 = 1;
        }
      }
      if ( v27 == 1 )
      {
        if ( CNWSCreatureStats::GetEffectImmunity(
               *((CNWSCreatureStats **)a2 + 794),
               CNWSEffectListHandler::IMMUNITY_TYPE_BACKSTAB,
               this)
          || CNWSCreatureStats::GetEffectImmunity(
               *((CNWSCreatureStats **)a2 + 794),
               CNWSEffectListHandler::IMMUNITY_TYPE_CRITICAL_HITS,
               this)
          || CNWSCreatureStats::HasFeat(*((CNWSCreatureStats **)a2 + 794), 0x380u) == 1 )
        {
          v25 = (CNWCCMessageData *)_builtin_new(0x34u);
          CNWCCMessageData::CNWCCMessageData(v25);
          CNWCCMessageData::SetObjectID(v25, 0, *((_DWORD *)a2 + 1));
          CNWCCMessageData::SetInteger(v25, 0, 134);
          v26 = CNWSCombatRound::GetAttack(*((CNWSCombatRound **)this + 691), v33);
          CExoArrayList<CNWCCMessageData *>::Add((int)(v26 + 156), (int)v25);
        }
        else
        {
          *((_DWORD *)CNWSCombatRound::GetAttack(*((CNWSCombatRound **)this + 691), v33) + 14) = 1;
        }
      }
    }
  }
}
