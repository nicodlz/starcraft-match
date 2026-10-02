# Historical compiler — reviewed-mismatch promotions

**212 complete C functions / 6,145 original bytes match exactly**, up from
197 / 5,768. This lot promotes **15 existing reviewed candidates / 377 bytes**;
it introduces no new function entries. There remain **4 reviewed mismatches**
and **3 uncorroborated regions** among 219 source candidates. The exact total
comprises 76 static initializers / 836 bytes and 136 other functions / 5,309 bytes.

All observations concern the pinned Windows i386 1.16.1 specimen SHA-256
`ad6b58b27b8948845ccfa69bcfcc1b10d6aa7a27a371ee3e61453925288c6a46`.
The coordinator independently compiled each final source at its public path and
reviewed full boundaries, entry references, memory widths/order and actual ABI.
The strict extractor uses each complete isolated section and rejects relocations;
no copied assembly, original-byte arrays, trimming, normalization or patches are used.

| Address | Original / compiled bytes | Observed inputs | Profile |
| --- | ---: | --- | --- |
| [0x004011F0](functions/004011F0.md) | 25 / 25 | EAX pointer | `msvc71-o2` |
| [0x00401430](functions/00401430.md) | 25 / 25 | EAX pointer | `msvc71-o2` |
| [0x00401450](functions/00401450.md) | 25 / 25 | EAX pointer | `msvc71-o2` |
| [0x00401470](functions/00401470.md) | 25 / 25 | EAX pointer | `msvc71-o2` |
| [0x00401490](functions/00401490.md) | 25 / 25 | EAX pointer | `msvc71-o2` |
| [0x004014E0](functions/004014E0.md) | 24 / 24 | EAX pointer | `msvc71-o2` |
| [0x00401D40](functions/00401D40.md) | 27 / 27 | EAX pointer | `msvc71-o2` |
| [0x004020B0](functions/004020B0.md) | 50 / 50 | EAX pointer | `msvc71-o2` |
| [0x00402310](functions/00402310.md) | 20 / 20 | EAX pointer | `msvc71-o2` |
| [0x00402A70](functions/00402A70.md) | 24 / 24 | EAX pointer | `msvc71-o2` |
| [0x00432430](functions/00432430.md) | 27 / 27 | EAX pointer / ECX index | `msvc71-o2` |
| [0x00494BD0](functions/00494BD0.md) | 24 / 24 | EAX / ECX unsigned values | `msvc71-o2` |
| [0x004A8B90](functions/004A8B90.md) | 18 / 18 | AL byte | `msvc71-o2` |
| [0x004C50D0](functions/004C50D0.md) | 11 / 11 | No consumed arguments | `msvc71-o2` |
| [0x004DBBE0](functions/004DBBE0.md) | 27 / 27 | No arguments | `msvc71-o2` |

## What changed

Thirteen promotions use the ordinary C compilation-context technique validated
in the [previous historical lots](historical-third-2026-10-02.md). A static
non-inlined C leaf and an independent ordinary C caller allow MSVC to infer private
register arguments. Each emitted leaf matches the original complete function,
including preserved registers and result width. The contexts remain experimental
compilation devices: their separate sections and relocations are not matched,
counted or presented as recovered original callers. The whole source is hashed;
changes to these contexts invalidate the evidence.

`004C50D0` and `004DBBE0` need no context helpers. Historical code generation emits
the former's DWORD store using EAX=1; an unsigned address variable emits the latter's
observed SUB and descending BYTE accesses. The remaining mismatches illustrate
instruction-selection limits: MOVZX versus XOR/MOV AX, ADD versus SUB or LEA,
and a register argument that cannot yet be expressed while preserving the original
ECX. Same-sized output is still rejected when even one byte differs.

`004020B0`, the initial four-field unit predicate, now matches all 50 bytes with
its actual EAX input. Its native GCC branch remains exported for the existing
16-case truth-table test. That test concerns candidate behavior only; it is not
execution of the original function. The Clang fallback compiles the same recorded
symbol and makes no historical ABI or byte-equality claim.

Nineteen existing mismatches were reserved in disjoint worker paths. Fifteen were
promoted; four remained private research results. A separate larger-leaf retry
also remained non-exact and was not introduced into the catalog. This selected
batch is not a representative whole-program reconstruction rate.

## Validation

`make proof` freshly requires **212 exact functions / 6,145 bytes**. `make` compiles
all 219 candidates and passes the 20 tests, including original-input proof and
intentional source mutation. The checkout without game or historical compiler
binaries compiles all candidates using marked source-only fallback and passes
19 tests; the original-input test is skipped. The staged publication guard passes.

Compiler provenance and identities remain those of the
[first historical lot](historical-2026-10-02.md). No binaries leave the private
research directories. There is no original-process or differential execution,
whole-program link, playable game or complete compiler reconstruction claimed.
Unmeasured instruction, CFG and semantic metrics remain null.
