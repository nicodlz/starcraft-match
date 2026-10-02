# Third-session reviewed standard-linked C lot — 2026-10-02

The coordinator independently reviewed and freshly compiled/linked 23 whole C functions from their final public paths. All 1,026 original bytes match their complete compiler contributions. This uses the [external-only standard linker](standard-linking.md) reused from the other session’s reviewed af83da3 commit, with unchanged compiler profiles; no independent duplicate linker was implemented.

Pinned executable SHA-256: `ad6b58b27b8948845ccfa69bcfcc1b10d6aa7a27a371ee3e61453925288c6a46`. GNU Binutils 2.42 i386pe resolves explicitly reviewed undefined code/data symbols. The adapter validates every relocation, unchanged nonrelocation bytes and the whole virtual function extent. No local helper rebinding, object edits, trimming, normalization, original-byte payload or post-build patch. Contexts are separately inventoried, discarded from the linked output and uncounted. External declarations bind addresses only and insert no implementations.

| Address | Original / compiled-linked bytes | Compiler profile |
| --- | ---: | --- |
| [0x00421360](functions/00421360.md) | 61 / 61 | msvc71-o2-frame |
| [0x004213A0](functions/004213A0.md) | 61 / 61 | msvc71-o2-frame |
| [0x00457CA0](functions/00457CA0.md) | 59 / 59 | msvc71-o2 |
| [0x004BDAC0](functions/004BDAC0.md) | 55 / 55 | msvc71-o2 |
| [0x004B7DA0](functions/004B7DA0.md) | 59 / 59 | msvc71-o2-frame |
| [0x0044A210](functions/0044A210.md) | 59 / 59 | msvc71-o2-frame |
| [0x004B65D0](functions/004B65D0.md) | 56 / 56 | msvc71-o2 |
| [0x004BE1A0](functions/004BE1A0.md) | 56 / 56 | msvc71-o2-frame |
| [0x004D8620](functions/004D8620.md) | 60 / 60 | msvc71-o2-frame |
| [0x004D8660](functions/004D8660.md) | 60 / 60 | msvc71-o2-frame |
| [0x00401240](functions/00401240.md) | 40 / 40 | msvc71-o2-frame |
| [0x0048E940](functions/0048E940.md) | 56 / 56 | msvc71-o2-frame |
| [0x00470CB0](functions/00470CB0.md) | 40 / 40 | msvc71-o2-frame |
| [0x004232D0](functions/004232D0.md) | 25 / 25 | msvc71-o2-frame |
| [0x004232F0](functions/004232F0.md) | 25 / 25 | msvc71-o2-frame |
| [0x00423430](functions/00423430.md) | 25 / 25 | msvc71-o2-frame |
| [0x004C0420](functions/004C0420.md) | 34 / 34 | msvc71-o2-frame |
| [0x004C0450](functions/004C0450.md) | 34 / 34 | msvc71-o2-frame |
| [0x00452350](functions/00452350.md) | 30 / 30 | msvc71-o2 |
| [0x004CE440](functions/004CE440.md) | 29 / 29 | msvc71-o2-frame |
| [0x0041F1B0](functions/0041F1B0.md) | 28 / 28 | msvc71-o2-frame |
| [0x004C3010](functions/004C3010.md) | 34 / 34 | msvc71-o2-frame |
| [0x004DC9A0](functions/004DC9A0.md) | 40 / 40 | msvc71-o2 |

These functions include packet wrappers, callback dispatch, dialog/error handling, text conversion and copy wrappers. Dependence on runtime functions does not mean those implementations were reconstructed or counted. Incoming private registers, external callee stack cleanup and ignored arguments were independently reviewed; the linker does not repair ABI differences. Other candidates with incompatible implicit EAX/ESI/EDI/BL contracts remain private and uncounted.

A natural dllimport declaration in [sub_0044A210](functions/0044A210.md) preserves the observed import-pointer caching that the previous fixed-address expression compiled differently. [sub_0048E940](functions/0048E940.md) retains the original divide-by-zero fault in measured code; abstract C reasoning is limited to nonfaulting paths, and runtime tables do not prove that all divisors are nonzero. [sub_0041F1B0](functions/0041F1B0.md) retains the Windows i386 variadic contract and unchecked capacity behavior; not all callers have been reviewed. Semantic, CFG and differential execution metrics remain null.

Validation: all 23 new catalog records satisfy the function schema. `make` passes 64 tests; `make proof` freshly verifies 311 whole exact expectations / 14,630 bytes, separated as 288 isolated-coff functions / 13,604 bytes and 23 standard-linked-c-external functions / 1,026 bytes. Publication guard passes. This isolated branch snapshot excludes concurrent-session function additions. No original-process execution, full-program link or playable game is claimed.
