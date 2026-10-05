# Historical compiler — seventh game-function lot

**253 complete C functions / 10,659 original bytes match exactly**, up from
239 / 8,850. This lot adds **14 functions / 1,809 bytes**, with complete bodies
from 120 to 146 bytes. The total comprises 76 static initializers / 836 bytes and
177 other reviewed functions / 9,823 bytes. The catalog has 260 source candidates:
253 exact, four reviewed mismatches and three uncorroborated regions.

Every observation concerns Windows i386 1.16.1 SHA-256
`ad6b58b27b8948845ccfa69bcfcc1b10d6aa7a27a371ee3e61453925288c6a46`.
The coordinator inspected complete bodies, neighboring boundaries, independent
entry references and actual ABI, then rebuilt every final public source. Entire
isolated sections match literally with zero unresolved relocations, without
copied assembly, original-byte arrays, patches, trimming or normalization.

| Address | Community annotation | Original / compiled bytes | Profile |
| --- | --- | ---: | --- |
| [0x00436CF0](functions/00436CF0.md) | PopulateRgnsWithSecondaryEnemyNeighbors | 132 / 132 | `msvc71-o2-frame` |
| [0x00436D80](functions/00436D80.md) | PopulateRgnsWithNeighbors | 136 / 136 | `msvc71-o2-frame` |
| [0x00436F70](functions/00436F70.md) | AssignCaptainToSlowestUnit | 142 / 142 | `msvc71-o2-frame` |
| [0x004626E0](functions/004626E0.md) | RemoveAllGuards | 126 / 126 | `msvc71-o2` |
| [0x00475DC0](functions/00475DC0.md) | getUpgradedWpnCooldown | 123 / 123 | `msvc71-o2` |
| [0x0047B3C0](functions/0047B3C0.md) | researchTech | 129 / 129 | `msvc71-o2-frame` |
| [0x0047B770](functions/0047B770.md) | Unit_IsMultiSelectable | 146 / 146 | `msvc71-o2` |
| [0x0047EAB0](functions/0047EAB0.md) | GetScrollSpeed | 126 / 126 | `msvc71-o2` |
| [0x00481B00](functions/00481B00.md) | speedOptnsScreenScrollSliders | 122 / 122 | `msvc71-o2` |
| [0x0048C510](functions/0048C510.md) | createOrder | 121 / 121 | `msvc71-o2-frame` |
| [0x004AAEA0](functions/004AAEA0.md) | eventSetGameType | 130 / 130 | `msvc71-o2-frame` |
| [0x004BFA80](functions/004BFA80.md) | templarMergePartner | 136 / 136 | `msvc71-o2-frame` |
| [0x004CB3A0](functions/004CB3A0.md) | CHK_ERA | 120 / 120 | `msvc71-o2-frame` |
| [0x004DC5B0](functions/004DC5B0.md) | network_SetReturnMenu | 120 / 120 | `msvc71-o2` |

Community annotations are separate from binary observations. Twenty bounded
worker groups examined forty reserved leads. Failed variants stay private;
this selected sample is not a representative whole-game match rate.

## Behavior and limits

Two AI propagation routines snapshot 2,500 BYTE states with compiler-generated
REP copies and walk WORD neighbor indexes. Counts retain unsigned BYTE minus
signed BYTE behavior, including wrapping negative counts. The group selector
retains signed speed minima, strict comparisons and preference between two categories.
A cooldown routine uses BYTE fields, DWORD flags and unsigned arithmetic, then
clamps the result to 5 through 250. An upgrade callback and a type/field predicate
retain their original table offsets, widths and missing guards.

The list-transfer routine reloads its global head at loop continuation, rather
than using the saved next pointer alone. The table-index adjustment retains
unsigned underflow without a lower clamp. Two UI lookups retain the missing-node
null dereference. The order allocator reads the global counter before clearing
links, then stores the incremented DWORD afterward. The candidate selector wraps
squared distances modulo 32 bits, skips zero pointers, preserves strict unsigned
minimum comparison, and replaces improved array entries with the preceding best.

The map callback checks its length argument against 2, but copies view.size bytes
into a local WORD. It preserves the wrapping source-end comparison and stores the
WORD before rejecting unsupported values. Copy extents above 2 overflow and
extents below 2 leave uninitialized bytes. The pinned compiler places this local
in the upper half of a stack argument slot, exactly matching the original body;
general portable C equivalence is not claimed for invalid copy extents.

The event callback is corroborated by its registration through the Storm ordinal
123 import. The callee's one-stack-argument/RET4 ABI is observed, while argument
preparation and result use inside the unavailable external dispatcher remain
unobserved. No external invocation or runtime reachability is claimed.

Independent ordinary C contexts shape private register ABI. Helpers are
compilation devices, not recovered or counted functions. Their separate sections
and relocations are outside the selected leaf. The whole translation unit is
hashed; source/context/compiler/profile changes invalidate its evidence.

## Validation

`make proof` freshly verifies **253 exact functions / 10,659 bytes**. `make` compiles
all 260 candidates and passes 20 tests, including original-input proof and an
intentional source regression. A checkout without game or historical compiler
binaries compiles every candidate with marked source-only fallback and passes
19 tests, with the original-input test skipped. The staged publication guard
passes. Portable extraction uses the recorded symbols with zero unresolved
relocations; original register ABI and equality are not claimed for those builds.

Two portable memcpy relocations were caught by coordinator extraction and fixed
using independent volatile BYTE loops; the matching compiler branches were
unchanged and public sources independently recompiled afterward. No ignored
compiler intrinsic or unresolved call is accepted as a portable build.

Compiler identities and provenance remain documented in the
[first historical lot](historical-2026-10-02.md). Game, compiler and research
binaries stay private. No original-process or differential execution,
whole-program link, playable game or complete compiler reconstruction is claimed.
Unmeasured semantic, CFG and instruction metrics remain null.
