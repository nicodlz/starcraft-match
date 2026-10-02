# Third-session second reviewed linked C lot — 2026-10-02

Fifteen independently authored whole C functions add **979 exact original bytes** after the validated main-branch merge `f0f1806`. Each boundary, entry, incoming/outgoing ABI and undefined external binding was reviewed by a different worker and then by the coordinator. The coordinator freshly compiles and links every accepted source from its final public path, using existing compiler profiles and the unchanged [external-only linker](standard-linking.md).

Pinned executable SHA-256: `ad6b58b27b8948845ccfa69bcfcc1b10d6aa7a27a371ee3e61453925288c6a46`.

| Function | Original / linked bytes | Compiler profile |
| --- | ---: | --- |
| [0x004213E0](functions/004213E0.md) | 61 / 61 | msvc71-o2-frame |
| [0x004617C0](functions/004617C0.md) | 61 / 61 | msvc71-o2 |
| [0x0041E4B0](functions/0041E4B0.md) | 62 / 62 | msvc71-o2 |
| [0x00459360](functions/00459360.md) | 62 / 62 | msvc71-o2-frame |
| [0x004DA510](functions/004DA510.md) | 62 / 62 | msvc71-o2 |
| [0x004A6A30](functions/004A6A30.md) | 64 / 64 | msvc71-o2-frame |
| [0x004BA1A0](functions/004BA1A0.md) | 66 / 66 | msvc71-o2 |
| [0x0042F600](functions/0042F600.md) | 67 / 67 | msvc71-o2-frame |
| [0x0044A3C0](functions/0044A3C0.md) | 67 / 67 | msvc71-o2-frame |
| [0x0044A450](functions/0044A450.md) | 67 / 67 | msvc71-o2-frame |
| [0x0048EBC0](functions/0048EBC0.md) | 67 / 67 | msvc71-o2 |
| [0x004CB140](functions/004CB140.md) | 67 / 67 | msvc71-o2-frame |
| [0x0046E170](functions/0046E170.md) | 68 / 68 | msvc71-o2-frame |
| [0x004CB0A0](functions/004CB0A0.md) | 69 / 69 | msvc71-o2-frame |
| [0x004CDF50](functions/004CDF50.md) | 69 / 69 | msvc71-o2-frame |

The lot includes dialog and import wrappers, list allocation/removal/search, fixed-width state writes, a table lookup and a stack-local visitation routine. The latter naturally generates a compiler `__chkstk` reference; the runtime probe is bound externally and not reconstructed or counted. An unsigned-address variant of sub_004A6A30 preserves the complete match while avoiding signed overflow in address additions. Callers corroborate private register contracts selected naturally by ordinary C contexts; the contexts are separately inventoried, discarded and uncounted.

Per-function notes explicitly retain missing-child reads at address 0x14, uninitialized message buffers, unchecked allocation and table paths, and target-specific pointer mappings. For sub_0046E170, upper EAX is zero on all observed exits; source-level ordering reasoning excludes invalid or aliasing table extents. No portable semantics, differential original execution, library ownership or complete runtime reconstruction is inferred from byte equality.

The combined milestone is **405 exact functions / 23,724 bytes**: 367 isolated COFF functions / 21,719 bytes and 38 externally standard-linked C functions / 2,005 bytes. All compiler contributions are whole and every relocation is explicitly approved; no original-byte payload, inline assembly, helper rebinding, object edits, trimming, normalization or post-build patch. Semantic and CFG metrics remain null where unmeasured.

Validation: all new records satisfy the function schema; `make` passes all 64 tests and `make proof` freshly verifies every combined exact expectation. Staged publication guard passes before committing. Other sessions' uncommitted work remains outside this snapshot.
