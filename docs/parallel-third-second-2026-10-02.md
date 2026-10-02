# Second third-session reviewed matching lot — 2026-10-02

The coordinator independently reviewed and recompiled 25 independently authored C candidates from their final public paths. All 2,784 reviewed original bytes match complete zero-relocation function sections under the recorded MSVC 13.10.3077 profiles.

Pinned executable SHA-256: `ad6b58b27b8948845ccfa69bcfcc1b10d6aa7a27a371ee3e61453925288c6a46`.

| Address | Original / compiled bytes | Profile |
| --- | ---: | --- |
| [0x00413D10](functions/00413D10.md) | 146 / 146 | msvc71-o2-frame |
| [0x004195E0](functions/004195E0.md) | 91 / 91 | msvc71-o2-frame |
| [0x004489F0](functions/004489F0.md) | 219 / 219 | msvc71-o2-frame |
| [0x00448B20](functions/00448B20.md) | 142 / 142 | msvc71-o2-frame |
| [0x0044D0C0](functions/0044D0C0.md) | 59 / 59 | msvc71-o2-frame |
| [0x00459DC0](functions/00459DC0.md) | 55 / 55 | msvc71-o2-frame |
| [0x00459E00](functions/00459E00.md) | 187 / 187 | msvc71-o2-frame |
| [0x00465200](functions/00465200.md) | 107 / 107 | msvc71-o2-frame |
| [0x004652A0](functions/004652A0.md) | 130 / 130 | msvc71-o2 |
| [0x004686D0](functions/004686D0.md) | 90 / 90 | msvc71-o2-frame |
| [0x0047A670](functions/0047A670.md) | 106 / 106 | msvc71-o2-frame |
| [0x0047A6E0](functions/0047A6E0.md) | 106 / 106 | msvc71-o2-frame |
| [0x0047A750](functions/0047A750.md) | 107 / 107 | msvc71-o2-frame |
| [0x0047E440](functions/0047E440.md) | 50 / 50 | msvc71-o2-frame |
| [0x00487470](functions/00487470.md) | 199 / 199 | msvc71-o2-frame |
| [0x00494FE0](functions/00494FE0.md) | 155 / 155 | msvc71-o2-frame |
| [0x004AACC0](functions/004AACC0.md) | 61 / 61 | msvc71-o2-frame |
| [0x004AADA0](functions/004AADA0.md) | 72 / 72 | msvc71-o2 |
| [0x004AADF0](functions/004AADF0.md) | 48 / 48 | msvc71-o2-frame |
| [0x004ABF50](functions/004ABF50.md) | 143 / 143 | msvc71-o2-frame |
| [0x004BB890](functions/004BB890.md) | 70 / 70 | msvc71-o2-frame |
| [0x004BBA90](functions/004BBA90.md) | 81 / 81 | msvc71-o2-frame |
| [0x004BBCF0](functions/004BBCF0.md) | 130 / 130 | msvc71-o2-frame |
| [0x004DEED0](functions/004DEED0.md) | 173 / 173 | msvc71-o2 |
| [0x004E18C0](functions/004E18C0.md) | 57 / 57 | msvc71-o2 |

Independent audits cover the whole region, incoming register and stack contract, and indirect calls. The coordinator corrected an omitted EBX preservation note, a return-address typo, a neutral function name and a structure-description field. Unsigned products in sub_0047A670 explicitly preserve 32-bit wrapping; this source change was freshly rebuilt and still matches all 106 bytes.

For sub_004BBA90, stack restoration alone does not establish the indirect method cleanup convention. The [function note](functions/004BBA90.md) separates the observed DirectSound object-creation chain from public API annotations supporting its COM stdcall contract. Caller stack data whose role is unresolved remains documented as such.

Hypothetical compiler contexts remain separate and uncounted. Historical access widths, callback behavior, unchecked API failures and partial local initialization are retained. This measures literal code equality, not original-process execution, differential semantic proof or complete program linking. Missing metrics remain null.

Validation: `make` passes 20 tests; `make proof` freshly verifies 273 exact expectations / 12,204 bytes. The staged publication guard passes. These totals describe this isolated branch snapshot and exclude changes from other concurrent sessions.
