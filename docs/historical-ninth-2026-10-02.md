# Historical compiler — ninth game-function lot

**262 complete C functions / 12,537 original bytes match exactly**, up from
261 / 12,007. This lot adds one **530-byte** region-merging function. The catalog
has 269 source candidates: 262 exact, four reviewed mismatches and three
uncorroborated regions. Static initializers remain 76 / 836 bytes; the other
186 reviewed functions account for 11,701 bytes.

[0x00482E10](functions/00482E10.md) has a genuine one-argument stdcall ABI,
RET 4, and a reviewed direct caller. Its entire isolated 530-byte section
matches under `msvc71-o2-frame`, without unresolved relocations, assembly copies,
original-byte arrays, patches, trimming or normalization. The target is Windows
i386 1.16.1 SHA-256
`ad6b58b27b8948845ccfa69bcfcc1b10d6aa7a27a371ee3e61453925288c6a46`.

## Behavior and limits

The routine repeatedly walks regions backward, increases a signed threshold by
two, selects the first eligible neighbor with strictly minimal WORD weight,
updates a WORD tile grid using signed coordinates divided by 32 with truncation
toward zero, wraps the merged weight and expands signed rectangle bounds.
It repeats while at least 2,500 regions have nonzero weight. Missing validation,
self-neighbor behavior, threshold overflow and possible nonconvergence remain.

The one-element declared region tail and the decrement before its beginning
do not supply a general standard-C guarantee, even for a larger allocation and
positive count. The pinned compiler's complete machine output is measured;
portable language equivalence is not claimed for this representation or invalid
accesses. No bounds guards, pass caps or self-edge exclusions were added.

## Validation

The coordinator reviewed the whole original region, neighbors, ABI, direct
caller and independent entry evidence, then freshly compiled the final public
source. `make proof` verifies all **262 exact functions / 12,537 bytes**.
`make` compiles all 269 candidates and passes 20 tests. A checkout without game
or historical compiler binaries compiles every candidate with marked portable
fallback and passes 19 tests with one original-input skip. The staged publication
guard passes. The same function symbol extracts as a complete 846-byte portable
Clang section without relocations; this is source-only evidence.

No original-process or differential execution, full-program linking, playable
game or complete compiler reconstruction is claimed. Unmeasured metrics stay null.
Compiler provenance is documented in the [first historical lot](historical-2026-10-02.md).
