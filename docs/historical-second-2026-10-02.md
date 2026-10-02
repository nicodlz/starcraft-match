# Historical compiler — larger game-function lot

**154 complete C functions / 2,805 original bytes match exactly**, up from
134 / 1,924. This lot adds **20 game functions / 881 bytes**, including selection
scans, signed resource updates, linked-target writes, a queue-slot search and
indexed score calculations. The unchanged static-initializer category is
76 functions / 836 bytes; the other 78 reviewed functions total 1,969 bytes.

All observations concern the pinned Windows i386 specimen SHA-256
`ad6b58b27b8948845ccfa69bcfcc1b10d6aa7a27a371ee3e61453925288c6a46`.
The coordinator independently recompiled every final public candidate and reviewed
its complete region, entry references, memory widths/order and register contract.
Unresolved candidate relocations, region trimming, normalization, copied assembly,
original instruction arrays and post-build patches are excluded.

| Address | Community annotation | Original / compiled bytes | Profile |
| --- | --- | ---: | --- |
| [0x00413A70](functions/00413A70.md) | getCreepValue | 43 / 43 | `msvc71-o2-frame` |
| [0x00428310](functions/00428310.md) | BTNSCOND_SCVisBuilding | 42 / 42 | `msvc71-o2` |
| [0x004283C0](functions/004283C0.md) | BTNSCOND_Movement | 45 / 45 | `msvc71-o2` |
| [0x00428530](functions/00428530.md) | BTNSCOND_IsTraining | 44 / 44 | `msvc71-o2-frame` |
| [0x004285E0](functions/004285E0.md) | BTNSCOND_CanRepair | 42 / 42 | `msvc71-o2` |
| [0x00428610](functions/00428610.md) | BTNSCOND_SCVCanAttack | 42 / 42 | `msvc71-o2` |
| [0x00428640](functions/00428640.md) | BTNSCOND_SCVCanStop | 42 / 42 | `msvc71-o2` |
| [0x00428670](functions/00428670.md) | BTNSCOND_SCVCanMove | 42 / 42 | `msvc71-o2` |
| [0x00428860](functions/00428860.md) | BTNSCOND_TankMove | 51 / 51 | `msvc71-o2` |
| [0x00436B60](functions/00436B60.md) | AI_getTerranInfantryScore | 42 / 42 | `msvc71-o2-frame` |
| [0x004381D0](functions/004381D0.md) | isAIControllerNotABuilding | 44 / 44 | `msvc71-o2` |
| [0x00446B40](functions/00446B40.md) | AI_GiveMoney | 52 / 52 | `msvc71-o2` |
| [0x00465450](functions/00465450.md) | unitIsCarrierReaverSecondaryOrderState2 | 46 / 46 | `msvc71-o2` |
| [0x004669B0](functions/004669B0.md) | getQueuedUnitCount | 47 / 47 | `msvc71-o2` |
| [0x004759C0](functions/004759C0.md) | incrementUnitKillCount | 40 / 40 | `msvc71-o2` |
| [0x00479FE0](functions/00479FE0.md) | unitOrderMoveToTargetUnit | 41 / 41 | `msvc71-o2` |
| [0x004A8DE0](functions/004A8DE0.md) | setAllValidPlayerOwnersToOpen | 44 / 44 | `msvc71-o2` |
| [0x004BD0C0](functions/004BD0C0.md) | get_chk_String | 43 / 43 | `msvc71-o2` |
| [0x004C3C90](functions/004C3C90.md) | eventSetPlayerFlag | 49 / 49 | `msvc71-o2-frame` |
| [0x004D4410](functions/004D4410.md) | endVideoProc | 40 / 40 | `msvc71-o2` |

The table's names are community annotations, separate from neutral source names.
Several distinct button predicates share an observed scan pattern; their separate
entry references and complete function regions were reviewed. Those repetitions
are not evidence of distinct reconstructed gameplay systems.

Ten bounded groups investigated forty reserved leads. Failed variants and
unrepresentable contracts remain private rather than entering the exact milestone.
Other historical profiles and source shapes were tried only where measured
instruction selection or layout justified them.

## C-generated custom register contract

[0x00479FE0](functions/00479FE0.md) receives the object in EAX and target in ECX.
A static, non-inlined pure C definition and an independently authored C caller give
MSVC a local optimization context. The compiler selects these registers itself;
no assembly binds them. Fresh compiled caller inspection confirms their setup.
The complete 41-byte callee matches the original, including its pointer reload
between two WORD stores and its preserved EAX.

The auxiliary caller is a compilation device. It is not a reconstructed original
function, is not counted and is not part of a claimed linked program. Its relocation
belongs to a separate section. The strict extractor accepts only the entire isolated
callee section, which has no relocations. Changes to this context invalidate its
source evidence. The portable Clang branch merely compiles the source with the same
symbol; it claims neither the custom ABI nor exact byte equality.

This demonstrates a narrowly measured compiler optimization technique, not a general
custom-ABI solution or recovery of the original translation unit. Further tests
are reserved in bounded worker groups.

## Caller limits and validation

[0x004C3C90](functions/004C3C90.md) has independently observed callback registration
through a Storm import and a complete one-stack-argument callee contract. Its C
matches all 49 bytes, including RET4 and preserved registers. The external Storm
dispatcher is unavailable and was not inspected; its argument preparation, result
consumption and actual execution remain unknown. Callee ABI evidence and external
caller uncertainty are distinguished in the record and function note.

`make proof` freshly rebuilds and compares all **154 exact functions / 2,805 bytes**.
`make` compiles all **176 candidates** and runs the **20 tests**, including the
original-input proof regression and intentional source mutation. The source-only
checkout also compiles every candidate with marked fallback where required;
its original-input test is skipped. Compiler and game binaries remain private.
There is no original-process execution, differential execution, whole-program link
or complete compiler reconstruction. Unmeasured similarity metrics remain null.
