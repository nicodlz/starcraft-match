# Third-session third reviewed linked C lot — 2026-10-02

Eleven independently authored whole C functions add **828 exact original bytes**. The integration reconciles third-session tip `6a8d58b` with concurrent principal-branch tip `7af5441`, retaining both of the latter's whole-function records, sources and notes. Those two functions add 86 bytes; their boundaries, callers and actual dependency contracts were independently reviewed again before the coordinator's fresh combined build. No concurrent research source or worktree is edited.

Pinned executable SHA-256: `ad6b58b27b8948845ccfa69bcfcc1b10d6aa7a27a371ee3e61453925288c6a46`.

| Function | Original / linked bytes | Compiler profile |
| --- | ---: | --- |
| [0x00436A80](functions/00436A80.md) | 72 / 72 | msvc71-o2 |
| [0x004CBEF0](functions/004CBEF0.md) | 72 / 72 | msvc71-o2-frame |
| [0x00472D60](functions/00472D60.md) | 73 / 73 | msvc71-o2 |
| [0x004BD3A0](functions/004BD3A0.md) | 74 / 74 | msvc71-o2-frame |
| [0x004D6640](functions/004D6640.md) | 74 / 74 | msvc71-o2 |
| [0x00452370](functions/00452370.md) | 75 / 75 | msvc71-o2-frame |
| [0x004ED3F0](functions/004ED3F0.md) | 75 / 75 | msvc71-o2 |
| [0x004384A0](functions/004384A0.md) | 76 / 76 | msvc71-o2 |
| [0x0041E050](functions/0041E050.md) | 78 / 78 | msvc71-o2 |
| [0x004439B0](functions/004439B0.md) | 79 / 79 | msvc71-o2 |
| [0x0045E4C0](functions/0045E4C0.md) | 80 / 80 | msvc71-o2-frame |

This lot includes list allocation, native compiler zeroing, timer cancellation, descriptor bounds, table access and import wrappers. External DLL and runtime implementations are reviewed only for ABI and remain uncounted. The allocator and callback contracts do not imply reconstructed semantics or a functioning game. Ordinary C contexts select observed private register inputs and are separately inventoried and excluded.

The reviewed variant of sub_004384A0 performs unsigned32 address arithmetic before pointer conversion, retaining original depth-underflow wrapping without C array-index arithmetic outside the table. Per-function notes retain unchecked allocation, missing pointer/table guards, unsigned range edges and original return behavior. The fatal error dependency imports ExitProcess, not ExitThread. The complete fastcall dependency of sub_004439B0 occupies 64 code bytes; metadata distinguishes physical extents from discovery chunk totals. Semantic, CFG and original differential metrics remain null where unmeasured.

The combined milestone is **418 exact functions / 24,638 bytes**: **367 isolated zero-relocation COFF functions / 21,719 bytes** and **51 external-only standard-linked C functions / 2,919 bytes**. There are 425 source candidates including the four reviewed mismatches and three uncorroborated regions. No helper rebinding, original-byte insertion, inline assembly, object edits, selected-subsequence matching, trimming, normalization or post-build patch is used.

Validation: all eleven new records satisfy the function schema. The coordinator freshly recompiles each final public path, runs `make` with all 64 tests and `make proof` for every combined exact expectation, then checks staged publication. Private binary inputs and reports remain untracked. Historical branch reports retain their original snapshot totals. This is not a full-program link, original-process execution or playable game.
