# Historical compiler — fifth game-function lot

**226 complete C functions / 7,422 original bytes match exactly**, up from
212 / 6,145. This lot adds **14 functions / 1,277 bytes**, with bodies ranging
from 85 to 100 bytes. The exact total comprises 76 static initializers / 836 bytes
and 150 other reviewed functions / 6,586 bytes. There are 233 source candidates:
226 exact, 4 reviewed mismatches and 3 uncorroborated regions.

All observations concern the pinned Windows i386 1.16.1 SHA-256
`ad6b58b27b8948845ccfa69bcfcc1b10d6aa7a27a371ee3e61453925288c6a46`.
The coordinator independently rebuilt every final public source, inspected entry
references and whole boundaries, and reviewed access widths/order and actual ABI.
Strict extraction selects the complete isolated function section, rejecting
relocations. No copied assembly, original-byte arrays, patches, trimming or
normalization are used.

| Address | Community annotation | Original / compiled bytes | Profile |
| --- | --- | ---: | --- |
| [0x00419640](functions/00419640.md) | removeDlgFromTimerTracking | 86 / 86 | `msvc71-o2` |
| [0x00431F90](functions/00431F90.md) | AI_BuildAndTechAndUpgrade | 94 / 94 | `msvc71-o2-frame` |
| [0x00432480](functions/00432480.md) | isUnitTypeRaceUnitRace | 87 / 87 | `msvc71-o2` |
| [0x0045B100](functions/0045B100.md) | getStandardUnitCount | 100 / 100 | `msvc71-o2-frame` |
| [0x0045B170](functions/0045B170.md) | parseAIScriptName | 95 / 95 | `msvc71-o2` |
| [0x0047B2E0](functions/0047B2E0.md) | unitIsFactoryUnit | 85 / 85 | `msvc71-o2` |
| [0x00482C60](functions/00482C60.md) | SAI_PathCreate_Sub3_0_1 | 92 / 92 | `msvc71-o2-frame` |
| [0x00491810](functions/00491810.md) | unitHasStatusEffect | 89 / 89 | `msvc71-o2` |
| [0x004981B0](functions/004981B0.md) | updateCarryableSpriteFlag | 99 / 99 | `msvc71-o2` |
| [0x0049DF10](functions/0049DF10.md) | isUnitTypeAtPositionInBounds | 87 / 87 | `msvc71-o2` |
| [0x004A6660](functions/004A6660.md) | mapEntry_Append | 87 / 87 | `msvc71-o2` |
| [0x004B2A90](functions/004B2A90.md) | Unassigned | 88 / 88 | `msvc71-o2` |
| [0x004CAEE0](functions/004CAEE0.md) | CHK_FORC | 95 / 95 | `msvc71-o2-frame` |
| [0x004D17B0](functions/004D17B0.md) | Game_NumLockInit | 93 / 93 | `msvc71-o2` |

Community annotations remain separate from neutral source names. Twenty bounded
worker groups examined forty reserved larger leads; unsuccessful sources remain
private. This selected sample is not a representative whole-game match rate.

## Observed behavior and compilation

The matched routines include a fixed-slot pointer clear, a twelve-type predicate,
a signed rectangle fill on a 256-column grid, two table searches with different
strides, encoded link maintenance, two image-list scans, a field predicate,
a score-count calculation and a map chunk callback. The key-state reset writes
18 BYTE locations in their observed order; it is invoked from a conditional
runtime caller, not from a startup initializer table.

Unusual original behavior remains explicit. The slot search can write entry 100
when that slot is empty. Rectangle coordinates and table bounds retain signed
versus unsigned widths. The score-count function narrows the main index to WORD
while comparing special cases against the full DWORD argument. The map callback
zeros output first, takes its copy length from context rather than the checked
size argument, and preserves unsigned overflow in the source-end check. No
additional null, index, overflow or alias guards are introduced.

MSVC selects several private register inputs from static pure C leaves and
independent ordinary C compilation contexts. Emitted contexts, complete callees
and original callers were independently inspected. The contexts are neither
recovered original functions nor counted matches. Their separate section
relocations are excluded from the strictly isolated, relocation-free callee.
Decorated argument counts alone do not establish the actual stack/register ABI.

C intrinsics generate the historical memory operations and a compiler-only
ordering barrier; no assembly implementation is provided. Portable branches use
independent C loops where necessary to avoid unresolved library calls. They
compile at the same recorded candidate symbols, with no original ABI or exactness
claim. The whole translation unit is hashed and any source/context/profile or
compiler component change invalidates its evidence.

## Validation and limits

`make proof` freshly requires **226 exact functions / 7,422 bytes**. `make` compiles
all 233 candidates and passes the 20 tests, including original-input proof and
intentional source mutation. A checkout without game or historical compiler
binaries compiles all candidates with marked source-only fallback and passes
19 tests; the original-input test is skipped. The staged publication guard passes.

Compiler provenance and identities remain those recorded in the
[first historical lot](historical-2026-10-02.md). Compiler, game and research
binaries stay private. There is no original-process or differential execution,
whole-program link, playable game or complete compiler reconstruction claimed.
Unmeasured instruction, CFG and semantic metrics remain null.
