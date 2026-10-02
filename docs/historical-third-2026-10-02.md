# Historical compiler — third game-function lot

**197 complete C functions / 5,768 original bytes match exactly**, up from
154 / 2,805. This lot adds **43 game functions / 2,963 bytes**. The static
initializer category remains 76 functions / 836 bytes; the other 121 reviewed
functions total 4,932 bytes. New bodies range from 55 to 84 bytes and include
linked-list maintenance, searches, button and trigger callbacks, resource refunds,
option updates and parser callbacks.

All observations concern the pinned Windows i386 specimen SHA-256
`ad6b58b27b8948845ccfa69bcfcc1b10d6aa7a27a371ee3e61453925288c6a46`.
The coordinator independently rebuilt every final public candidate and reviewed
its whole region, entry references, memory widths/order and emitted ABI.
The strict extractor rejects unresolved candidate relocations; the comparisons
use complete sections without trimming, normalization, copied assembly,
original instruction arrays or post-build patches.

| Address | Community annotation | Original / compiled bytes | Profile |
| --- | --- | ---: | --- |
| [0x0041BDA0](functions/0041BDA0.md) | isDialogInRect | 76 / 76 | `msvc71-o2` |
| [0x0041BF60](functions/0041BF60.md) | isRectBoundsInside_Assign_16 | 84 / 84 | `msvc71-o2` |
| [0x0041D7D0](functions/0041D7D0.md) | drawVertLine | 64 / 64 | `msvc71-o2-frame` |
| [0x0041D810](functions/0041D810.md) | MinimapFill | 76 / 76 | `msvc71-o2-frame` |
| [0x00420640](functions/00420640.md) | ApplyDefaultOptions | 81 / 81 | `msvc71-o2` |
| [0x00423190](functions/00423190.md) | getLarvaeUnitsFromList | 62 / 62 | `msvc71-o2-frame` |
| [0x00428360](functions/00428360.md) | BTNSCOND_LurkerStop | 84 / 84 | `msvc71-o2` |
| [0x00428810](functions/00428810.md) | BTNSCOND_HasNuke | 71 / 71 | `msvc71-o2-frame` |
| [0x0042B850](functions/0042B850.md) | PtFuncCompare | 65 / 65 | `msvc71-o2-frame` |
| [0x0042C6E0](functions/0042C6E0.md) | TRGCND_ElapsedTime | 57 / 57 | `msvc71-o2` |
| [0x0042CE70](functions/0042CE70.md) | refundBuildingCost | 80 / 80 | `msvc71-o2` |
| [0x00432320](functions/00432320.md) | AI_getNumOwnedMineralClusters | 64 / 64 | `msvc71-o2` |
| [0x00436B90](functions/00436B90.md) | AI_WaitTurrets | 55 / 55 | `msvc71-o2` |
| [0x00436BD0](functions/00436BD0.md) | AI_WaitBunkers | 55 / 55 | `msvc71-o2` |
| [0x00437180](functions/00437180.md) | IsRegionANeighborOfRegionB | 71 / 71 | `msvc71-o2-frame` |
| [0x004402B0](functions/004402B0.md) | GetBestSCVForRepairProc | 60 / 60 | `msvc71-o2` |
| [0x00440790](functions/00440790.md) | AI_RecallRequirementsProc | 67 / 67 | `msvc71-o2` |
| [0x00440930](functions/00440930.md) | powerupCanBePickedUpProc | 70 / 70 | `msvc71-o2` |
| [0x00447090](functions/00447090.md) | AI_AttackTimerDecrement | 64 / 64 | `msvc71-o2` |
| [0x00458800](functions/00458800.md) | setDefaultTooltipInfo | 80 / 80 | `msvc71-o2-frame` |
| [0x0045AEA0](functions/0045AEA0.md) | isAIScriptNameValid | 69 / 69 | `msvc71-o2` |
| [0x0045B210](functions/0045B210.md) | AI_FindSuitableUnit | 68 / 68 | `msvc71-o2` |
| [0x00463360](functions/00463360.md) | AI_NukeReady | 76 / 76 | `msvc71-o2` |
| [0x00468930](functions/00468930.md) | unit_isGeyserUnitEx | 60 / 60 | `msvc71-o2-frame` |
| [0x00469B00](functions/00469B00.md) | finderIdxFromValue_binary_search | 83 / 83 | `msvc71-o2-frame` |
| [0x00479FA0](functions/00479FA0.md) | unitOrderMoveToTargetUnitResetOrderState | 64 / 64 | `msvc71-o2` |
| [0x0047B850](functions/0047B850.md) | getModifiedUnitTurnRadius | 78 / 78 | `msvc71-o2` |
| [0x00489350](functions/00489350.md) | isPlayerIDValidForScoreChange | 58 / 58 | `msvc71-o2` |
| [0x004893C0](functions/004893C0.md) | resetTriggerProperties | 70 / 70 | `msvc71-o2` |
| [0x0048AAC0](functions/0048AAC0.md) | clearBulletTargets | 63 / 63 | `msvc71-o2` |
| [0x00493100](functions/00493100.md) | removeFromPsiProviderList | 81 / 81 | `msvc71-o2` |
| [0x00494F90](functions/00494F90.md) | getFlingyHaltDistance | 68 / 68 | `msvc71-o2` |
| [0x0049A2C0](functions/0049A2C0.md) | isSelectedUnitGroupEnabled | 81 / 81 | `msvc71-o2` |
| [0x0049C9A0](functions/0049C9A0.md) | SAI_GetRegionIdFromPx | 68 / 68 | `msvc71-o2-frame` |
| [0x0049DCA0](functions/0049DCA0.md) | CListPushBackUsedUnitEntry | 55 / 55 | `msvc71-o2` |
| [0x0049DE00](functions/0049DE00.md) | CListRemoveEmptyUnitEntry | 66 / 66 | `msvc71-o2` |
| [0x0049DE50](functions/0049DE50.md) | CListRemoveHiddenUnitEntry | 66 / 66 | `msvc71-o2` |
| [0x0049DEA0](functions/0049DEA0.md) | CListRemoveUsedUnitEntry | 66 / 66 | `msvc71-o2` |
| [0x0049E4E0](functions/0049E4E0.md) | GiveSprite | 70 / 70 | `msvc71-o2` |
| [0x004BB9B0](functions/004BB9B0.md) | parseSection | 69 / 69 | `msvc71-o2-frame` |
| [0x004C3090](functions/004C3090.md) | read_buf | 64 / 64 | `msvc71-o2-frame` |
| [0x004C5250](functions/004C5250.md) | TRGACT_Wait_fn | 75 / 75 | `msvc71-o2` |
| [0x004E6BA0](functions/004E6BA0.md) | unitIsActiveTransport | 59 / 59 | `msvc71-o2` |

Community annotations remain separate from neutral source names. Twenty bounded
worker groups reserved eighty leads; unsuccessful candidates remain private.
This selected lot does not measure a representative whole-game match rate.

## C compilation contexts and observed behavior

The [previous lot](historical-second-2026-10-02.md) validated a static pure C leaf
with an ordinary C caller as a means of exposing MSVC's private register allocation.
This lot measures further EAX, AL, AX, CL, ESI, EDI and EBX argument contracts.
Each function note records the actual emitted inputs, result width, preserved
registers and stack cleanup. A nominal decorated C symbol alone does not establish
that contract. The auxiliary callers are compilation devices, not recovered
original functions: they are neither matched nor counted. Their ordinary call
relocations reside in separate sections. Changing the whole translation unit,
profile or compiler components invalidates evidence and requires rebuilding.

Access order and unusual original behavior remain explicit. Examples include
WORD loads before resource stores, pointer reloads between coordinate stores,
a signed pointer test while traversing trigger lists, a callback returning -1,
and a parser accepting a matching tag without checking its declared payload size.
These observations are preserved rather than repaired. Semantic field meanings
remain hypotheses where the original bytes do not establish them.

Compiler-generated `memset` and `memcpy` intrinsics are ordinary C inputs; no
assembly implementation is supplied by this repository. The portable branches
compile independently with the same recorded candidate symbols, without claiming
the historical register contract or byte equality. In particular, the portable
copy loop avoids an unresolved external `memcpy` relocation.

## Validation and limits

`make proof` freshly rebuilds and requires all **197 exact functions / 5,768 bytes**.
`make` compiles all **219 candidates** and passes the **20 tests**, including the
original-input proof regression and intentional source mutation. A private checkout
without game or historical compiler binaries compiles all candidates using marked
source-only fallback where required and passes 19 tests, with the original-input
test skipped. The staged publication guard passes.

Compiler provenance and component identity remain those recorded in the
[first historical lot](historical-2026-10-02.md). Game, compiler and research binaries
remain private. There is no original-process execution, differential execution,
whole-program link, playable game or complete compiler reconstruction claimed.
Unmeasured instruction, CFG and semantic metrics remain null.
