# Historical compiler — eighth game-function lot

**261 complete C functions / 12,007 original bytes match exactly**, up from
253 / 10,659. This lot adds **eight functions / 1,348 bytes**, with whole bodies
from 155 to 180 bytes. There are 268 source candidates: 261 exact, four reviewed
mismatches and three uncorroborated regions. The total includes 76 static
initializers / 836 bytes and 185 other reviewed functions / 11,171 bytes.

Every observation concerns Windows i386 1.16.1 SHA-256
`ad6b58b27b8948845ccfa69bcfcc1b10d6aa7a27a371ee3e61453925288c6a46`.
The coordinator independently inspected complete regions, neighboring boundaries,
entry references and actual ABI, then freshly rebuilt each final public source.
Literal equality covers entire isolated sections with no unresolved relocations,
original-byte arrays, assembly copies, patches, trimming or normalization.

| Address | Community annotation | Original / compiled bytes | Profile |
| --- | --- | ---: | --- |
| [0x0041A1B0](functions/0041A1B0.md) | isEventInDlgField | 180 / 180 | `msvc71-o2-frame` |
| [0x0042F790](functions/0042F790.md) | assignPathCreateFromUnitPath | 155 / 155 | `msvc71-o2` |
| [0x00440520](functions/00440520.md) | GetStaticMinRange | 178 / 178 | `msvc71-o2` |
| [0x0044F4E0](functions/0044F4E0.md) | getHumansOnTeam | 171 / 171 | `msvc71-o2` |
| [0x00483160](functions/00483160.md) | SAI_PathCreate_Sub5 | 160 / 160 | `msvc71-o2-frame` |
| [0x004916E0](functions/004916E0.md) | Unannotated | 161 / 161 | `msvc71-o2` |
| [0x004977C0](functions/004977C0.md) | getSpriteRect | 179 / 179 | `msvc71-o2-frame` |
| [0x00497C30](functions/00497C30.md) | UpdateVisibilityHash | 164 / 164 | `msvc71-o2-frame` |

Community annotations remain separate from observed behavior. Twenty bounded
groups examined forty reserved leads. Failed variants stay private; this selected
sample is not a representative whole-game matching rate.

## Observed behavior and limits

The UI hit test retains signed WORD coordinates, wrapped subtraction, auxiliary
bounds and inclusive comparisons. The path copy converts signed BYTE counts to
unsigned copy lengths; negative counts can produce huge invalid copies. General
portable C equivalence is not claimed for those extents. The weapon selector
updates an unsigned minimum with original sentinels, type checks and table widths.
The team counter compares a full DWORD argument against BYTE records in the
original short-circuit order.

The neighbor classifier reloads the global array on each iteration, counts unique
WORD identifiers and returns before storing a fifth identifier. Unit unlinking
keeps alias-sensitive rereads, guards and ordered global updates. Image bounds
use signed WORD offsets and BYTE dimensions, strict minimum/maximum comparisons,
and leave output untouched when no image qualifies. The hash routine retains
ordered BYTE table writes, wrapping start-plus-13 arithmetic, rotations and final
BYTE and DWORD stores.

Ordinary C contexts induce private register contracts. Helpers are separate,
unmatched compilation devices; their relocations lie outside the selected leaf.
The whole translation unit is hashed. Source/context/compiler/profile changes
invalidate evidence.

## Validation

`make proof` freshly verifies **261 exact functions / 12,007 bytes**. `make`
compiles all 268 candidates and passes 20 tests. A checkout without game or
historical compiler binaries compiles all candidates with marked source-only
fallback and passes 19 tests with one original-input skip. The staged publication
guard passes. The coordinator separately extracts all eight portable Clang
symbols with no unresolved relocations; portable ABI/equality are not claimed.

Compiler provenance is documented in the [first historical lot](historical-2026-10-02.md).
No original-process execution, differential execution, whole-program link, playable
game or complete compiler reconstruction is claimed. Unmeasured semantic, CFG and
instruction metrics remain null.
