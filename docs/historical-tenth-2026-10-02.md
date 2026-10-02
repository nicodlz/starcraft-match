# Historical compiler — tenth game-function lot

**263 complete C functions / 12,713 original bytes match exactly**, up from
262 / 12,537. This lot adds one **176-byte** initializer. There are 270 source
candidates: 263 exact, four reviewed mismatches and three uncorroborated regions.
Static data initializers remain 76 / 836 bytes; the other 187 reviewed functions
account for 11,877 bytes.

[0x004D5A50](functions/004D5A50.md), community-annotated InitializeImageData,
has a custom compiler-induced ABI: EAX object, full ESI index, EDI parent,
and two DWORD stack slots consumed as BYTE inputs; RET 8. The nominal `@20`
symbol decoration does not describe the observed register/stack allocation.
Three direct callers corroborate the entry. The coordinator inspected the full
region and adjacent boundaries and independently rebuilt the final public C
source with `msvc71-o2-frame`. The whole isolated 176-byte section matches with
zero unresolved relocations. No assembly copies, original-byte arrays, patches,
trimming or normalization are used.

The target is Windows i386 1.16.1 SHA-256
`ad6b58b27b8948845ccfa69bcfcc1b10d6aa7a27a371ee3e61453925288c6a46`.
The C candidate came from an independently authored parallel research handoff;
its cached equality was not used as coordinator proof. The complete source,
compiler identity and final public object were freshly measured.

## Behavior and validation

The routine stores the low WORD index but uses the full DWORD input for initial
table reads and its second type check. The first type check reloads the stored
WORD. Ordered BYTE/WORD/DWORD fields, bit masks, constant zero ranges and
conditional parent/table-derived values are preserved. No index normalization
or bounds checks were introduced. Compiler-inlined constant memset operations
emit no unresolved calls. The independent context helper remains unmatched and
uncounted in its separate section; the whole translation unit is hashed.

`make proof` freshly verifies **263 exact functions / 12,713 bytes**. `make`
compiles all 270 candidates and passes 20 tests. A checkout without game or
historical compiler binaries compiles every candidate with marked portable
fallback and passes 19 tests with one original-input skip. The staged publication
guard passes. Portable Clang extracts the same symbol as a whole 239-byte
zero-relocation section; original ABI and equality are not claimed for it.

The coordinator caught an unresolved portable memset call and replaced only
the portable branch with an independently authored volatile BYTE loop. The
historical branch remains unchanged and its final source was freshly recompiled.

No original-process or differential execution, full-program linking, playable
game or complete compiler reconstruction is claimed. Unmeasured metrics stay null.
Compiler provenance is documented in the [first historical lot](historical-2026-10-02.md).
