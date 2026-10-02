# Historical compiler — sixth game-function lot

**239 complete C functions / 8,850 original bytes match exactly**, up from
226 / 7,422. This lot adds **13 functions / 1,428 bytes**, with bodies from
103 to 115 bytes. The total comprises 76 static initializers / 836 bytes and
163 other reviewed functions / 8,014 bytes. The catalog has 246 source candidates:
239 exact, four reviewed mismatches and three uncorroborated regions.

Every observation concerns Windows i386 1.16.1 SHA-256
`ad6b58b27b8948845ccfa69bcfcc1b10d6aa7a27a371ee3e61453925288c6a46`.
The coordinator inspected complete bodies, neighboring boundaries, independent
entry references and actual ABI, then rebuilt every final public source. Entire
isolated sections match literally with zero unresolved relocations, without
copied assembly, original-byte arrays, patches, trimming or normalization.

| Address | Community annotation | Original / compiled bytes | Profile |
| --- | --- | ---: | --- |
| [0x00432760](functions/00432760.md) | AI_Unassign | 105 / 105 | `msvc71-o2` |
| [0x00436C10](functions/00436C10.md) | AISomethingHasOwnershipOfRegion | 115 / 115 | `msvc71-o2-frame` |
| [0x00437E00](functions/00437E00.md) | isCaptainTrackingNonCritter | 103 / 103 | `msvc71-o2` |
| [0x004401B0](functions/004401B0.md) | Unassigned | 106 / 106 | `msvc71-o2` |
| [0x0045CC90](functions/0045CC90.md) | isRectOutOfScreen_fixup | 108 / 108 | `msvc71-o2` |
| [0x0047B340](functions/0047B340.md) | increaseUpgradeLevel | 113 / 113 | `msvc71-o2-frame` |
| [0x0048E850](functions/0048E850.md) | getSfxPanFromXDistance | 112 / 112 | `msvc71-o2` |
| [0x00491790](functions/00491790.md) | secondaryOrd_Cloak | 113 / 113 | `msvc71-o2` |
| [0x004C5520](functions/004C5520.md) | TRGACT_LeaderBoard_fn | 111 / 111 | `msvc71-o2` |
| [0x004E1D20](functions/004E1D20.md) | DrawBox | 103 / 103 | `msvc71-o2-frame` |
| [0x004E2DA0](functions/004E2DA0.md) | CreateUnitHash | 114 / 114 | `msvc71-o2` |
| [0x004E5DB0](functions/004E5DB0.md) | CanSeeTarget | 114 / 114 | `msvc71-o2` |
| [0x004E5E30](functions/004E5E30.md) | isTargetVisible | 111 / 111 | `msvc71-o2` |

Community annotations are separate from binary observations. Twenty bounded
worker groups examined forty reserved leads. Failed variants stay private;
this selected sample is not a representative whole-game match rate.

## Observed behavior and limits

The lot includes AI-slot cleanup, region and target predicates, a random selector,
signed rectangle clipping, an upgrade callback, distance scoring, list insertion,
trigger state writes, pixel filling, hashing and visibility masks. Per-function
notes describe observed widths, ordering, original bugs and omitted guards.

The pixel fill compares its DWORD loop counter's signed low WORD against an
unsigned WORD height: heights at least 32768 never reach the observed loop exit.
Width zero still loads row state. Its historical memset is compiler-generated;
a volatile BYTE loop avoids the library relocation only in the portable branch.
The trigger callback retains a redundant BYTE comparison against 255. List
insertion increments a BYTE counter before checking its old value and reloads
the global head after storing links. The hash preserves six rotates, signed
WORD coordinates, wrapping DWORD addition and arithmetic right shift. Its
predecessor's indirect jump and four-pointer table were independently inspected;
the table is data outside the selected function.

Visibility routines return DWORD masks rather than canonical Booleans. Their C
shifts are defined only for player values below 32, a bound not established by
inspected callers. The exact emitted x86 SHL masks all BYTE counts modulo 32.
The random selector retains faulting DIV for count zero even when randomization
is disabled; C remainder by zero has no general semantic guarantee. These are
pinned-compiler byte matches, without general portable C equivalence for those
inputs. Notes and catalog retain these limits; no guards were added.

Independent ordinary C contexts shape private register ABI. Their separate
sections and relocations are outside the selected leaf; helpers are compilation
devices, not recovered or counted functions. The whole translation unit is hashed.
Changing source/context/compiler/profile invalidates its evidence.

## Validation

`make proof` freshly verifies **239 exact functions / 8,850 bytes**. `make` compiles
all 246 candidates and passes 20 tests, including original-input proof and an
intentional source regression. A checkout without game or historical compiler
binaries compiles every candidate with marked source-only fallback and passes
19 tests, with the original-input test skipped. The staged publication guard
passes. Portable extraction uses the recorded symbols with zero unresolved
relocations; original register ABI and equality are not claimed for those builds.

Compiler identities and provenance remain documented in the
[first historical lot](historical-2026-10-02.md). Game, compiler and research
binaries stay private. No original-process or differential execution,
whole-program link, playable game or complete compiler reconstruction is claimed.
Unmeasured semantic, CFG and instruction metrics remain null.
