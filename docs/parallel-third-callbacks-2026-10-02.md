# Third-session callback and pool lot — 2026-10-02

Fifteen independently authored whole C functions match 1,400 reviewed original bytes after coordinator source review, independent boundary/ABI audits and fresh final-public-path builds. Pinned executable SHA-256: `ad6b58b27b8948845ccfa69bcfcc1b10d6aa7a27a371ee3e61453925288c6a46`. Existing MSVC 13.10.3077 profiles are unchanged.

| Address | Original / compiled bytes | Profile |
| --- | ---: | --- |
| [0x00402B10](functions/00402B10.md) | 143 / 143 | msvc71-o2-frame |
| [0x004049A0](functions/004049A0.md) | 48 / 48 | msvc71-o2 |
| [0x00404BC0](functions/00404BC0.md) | 24 / 24 | msvc71-o2-frame |
| [0x00404810](functions/00404810.md) | 148 / 148 | msvc71-o2 |
| [0x00413AA0](functions/00413AA0.md) | 49 / 49 | msvc71-o2-frame |
| [0x00403130](functions/00403130.md) | 241 / 241 | msvc71-o2 |
| [0x00402180](functions/00402180.md) | 129 / 129 | msvc71-o2 |
| [0x00401FA0](functions/00401FA0.md) | 124 / 124 | msvc71-o2 |
| [0x00414230](functions/00414230.md) | 84 / 84 | msvc71-o2-frame |
| [0x004D1120](functions/004D1120.md) | 23 / 23 | msvc71-o2 |
| [0x00404920](functions/00404920.md) | 124 / 124 | msvc71-o2-frame |
| [0x004DC6D0](functions/004DC6D0.md) | 68 / 68 | msvc71-o2-frame |
| [0x0044A5D0](functions/0044A5D0.md) | 28 / 28 | msvc71-o2-frame |
| [0x00487A90](functions/00487A90.md) | 110 / 110 | msvc71-o2-frame |
| [0x00453680](functions/00453680.md) | 57 / 57 | msvc71-o2-frame |

Callback entries are corroborated by code-address registrations and reviewed dispatch paths; Ghidra DATA labels alone are insufficient. Discovery also mislabeled tail JMPs as CALLs, and a comparator dispatch helper omitted three epilogue bytes. Reviewed native boundaries and argument/result contracts govern acceptance.

The final [pool reset](functions/00403130.md) uses explicit i386 integer addresses and DWORD links, removing field-subobject pointer arithmetic and final out-of-object pointer formation without changing its 241 compiled bytes. [sub_00414230](functions/00414230.md) has a reviewed direction domain 0..8; unmasked C shifts outside that domain are not equivalence evidence. [sub_004D1120](functions/004D1120.md) is process exception-filter infrastructure, distinct from gameplay and from data initializers; application versus embedded-library provenance remains unresolved.

Hypothetical compiler contexts remain separate and uncounted. Literal equality measures whole zero-relocation sections, not original-process execution, differential semantics or whole-program linking. Missing semantic/CFG metrics stay null.

`make` passes 20 tests; `make proof` freshly verifies all 288 exact expectations / 13,604 bytes. The staged publication guard passes. Counts describe this isolated branch and exclude additions by concurrent sessions.
