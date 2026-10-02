# Third-session reviewed matching lot — 2026-10-02

Twenty workers investigated 100 disjoint regions in the first two bounded lots.
The coordinator reviewed the independent source and boundary/ABI audits and
recompiled the 22 accepted candidates from their final public paths. All 1,998
reviewed original bytes match complete, isolated, zero-relocation COFF sections.
The unchanged recorded profiles use locally supplied MSVC 13.10.3077.

The pinned executable SHA-256 is
`ad6b58b27b8948845ccfa69bcfcc1b10d6aa7a27a371ee3e61453925288c6a46`.

| Address | Original / compiled bytes | Profile |
| --- | ---: | --- |
| [0x004161C0](functions/004161C0.md) | 126 / 126 | msvc71-o2-frame |
| [0x00417E50](functions/00417E50.md) | 32 / 32 | msvc71-o2-frame |
| [0x00417F00](functions/00417F00.md) | 31 / 31 | msvc71-o2 |
| [0x00418270](functions/00418270.md) | 123 / 123 | msvc71-o2-frame |
| [0x004196A0](functions/004196A0.md) | 75 / 75 | msvc71-o2-frame |
| [0x00420860](functions/00420860.md) | 126 / 126 | msvc71-o2-frame |
| [0x00421670](functions/00421670.md) | 27 / 27 | msvc71-o2 |
| [0x00427DA0](functions/00427DA0.md) | 136 / 136 | msvc71-o2 |
| [0x0044A000](functions/0044A000.md) | 111 / 111 | msvc71-o2-frame |
| [0x00461720](functions/00461720.md) | 40 / 40 | msvc71-o2 |
| [0x00489200](functions/00489200.md) | 67 / 67 | msvc71-o2 |
| [0x004BB5A0](functions/004BB5A0.md) | 87 / 87 | msvc71-o2-frame |
| [0x004BB600](functions/004BB600.md) | 56 / 56 | msvc71-o2 |
| [0x004BB640](functions/004BB640.md) | 158 / 158 | msvc71-o2 |
| [0x004D1650](functions/004D1650.md) | 154 / 154 | msvc71-o2-frame |
| [0x004D1750](functions/004D1750.md) | 96 / 96 | msvc71-o2-frame |
| [0x004D1810](functions/004D1810.md) | 106 / 106 | msvc71-o2 |
| [0x004D1880](functions/004D1880.md) | 127 / 127 | msvc71-o2-frame |
| [0x004D3510](functions/004D3510.md) | 37 / 37 | msvc71-o2 |
| [0x004D9FE0](functions/004D9FE0.md) | 126 / 126 | msvc71-o2-frame |
| [0x004DCC50](functions/004DCC50.md) | 59 / 59 | msvc71-o2-frame |
| [0x004E88B0](functions/004E88B0.md) | 98 / 98 | msvc71-o2-frame |

These candidates include UI event callbacks, trigger iteration, input state,
window/cursor helpers and indirect interface calls. Community names remain
annotations. Fixed IAT/vtable calls can compile without candidate relocations;
relative calls and jump tables rejected by the extractor remain private research.
Hypothetical ordinary C contexts select several private register contracts; their
helpers are separate, nonmatching and excluded from the counts.

Unchecked API failures, partially uninitialized local records and historical signed
arithmetic remain limitations of source-level reasoning. Literal code equality
is measured; no original-process execution, differential semantic proof or linked
whole-program build is claimed. Unsupported metrics remain null.

`make` passes all 20 tests, including a real-executable proof and deliberate
source-regression failure test. `make proof` independently verifies all 248 exact expectations / 9,420 bytes
in this branch snapshot. The staged publication guard passes for the 48 public
files in this lot. This isolated branch snapshot excludes additions
being integrated by other concurrent sessions.
