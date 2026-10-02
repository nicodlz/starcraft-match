# Exact-function growth batch

**Fourteen additional C-derived whole functions match exactly, totaling 176 bytes.**
The proof set grew from **13 functions / 185 bytes** to **27 functions / 361 bytes**.
The coordinator independently reviewed boundaries, entry corroboration, register/stack
contracts and source, then rebuilt every accepted candidate and compared its complete
isolated COFF section to a fresh extraction from the pinned PE.

All binary observations refer to Windows i386 Brood War 1.16.1 specimen SHA-256
`ad6b58b27b8948845ccfa69bcfcc1b10d6aa7a27a371ee3e61453925288c6a46`.
The public [BWAPI map at pinned revision](https://github.com/bwapi/bwapi/blob/d727fed68558c506163048ea889131d8cbb33915/Release_Binary/Starcraft/bwapi-data/data/Broodwar.map)
supplies independent entry/size annotations; original boundaries and ABI were checked
locally. Community names remain annotations, not authenticated original symbols.

Twenty workers owned disjoint candidate/doc paths in a bounded experiment across
94 mapped leads. An initial discovery filter incorrectly included empty reference
lists; those unsupported entries were rejected before promotion, and the selection
was corrected. Byte-equal regions without independent entry evidence stayed private.
Three additional callbacks were reviewed after the main batch, including the
previously present `sub_004282D0.c`, compiled unchanged rather than reauthored.

| Function | Exact original bytes | Recorded compiler profile |
| --- | ---: | --- |
| [0x004180C0](functions/004180C0.md) | 13 | clang-i686-scaffold |
| [0x00423180](functions/00423180.md) | 1 | clang-i686-scaffold |
| [0x00427E40](functions/00427E40.md) | 6 | clang-i686-scaffold |
| [0x004282D0](functions/004282D0.md) | 8 | clang-i686-scaffold |
| [0x0042C680](functions/0042C680.md) | 6 | clang-i686-scaffold |
| [0x00446BA0](functions/00446BA0.md) | 32 | clang-i686-size |
| [0x00455650](functions/00455650.md) | 8 | clang-i686-scaffold |
| [0x0047A070](functions/0047A070.md) | 25 | clang-i686-scaffold |
| [0x004C51B0](functions/004C51B0.md) | 22 | clang-i686-scaffold |
| [0x004C52A0](functions/004C52A0.md) | 18 | clang-i686-scaffold |
| [0x004C5350](functions/004C5350.md) | 6 | clang-i686-scaffold |
| [0x004CB550](functions/004CB550.md) | 8 | clang-i686-scaffold |
| [0x004D55F0](functions/004D55F0.md) | 1 | clang-i686-scaffold |
| [0x004DBC00](functions/004DBC00.md) | 22 | clang-i686-size |

The larger accepted leaves include a 32-byte conditional byte-state update and a
25-byte pointer-link insertion that preserves the repeated read and alias-sensitive
store order. Two accepted routines are one-byte empty callbacks: they add two functions
and only two bytes, and do not represent substantive gameplay reconstruction. The
callback at `0x00427E40` has a corroborated map entry and stored pointer, but the
inspected dispatcher excludes its slot; reachable invocation is not asserted.

Rejected mapped trials remain private. Recurring blockers include different encodings
of otherwise identical XOR or MOV instructions, inverted comparison operands, narrowed
memory accesses, register clobbers, branch folding and loop alignment. Equal textual
disassembly or equal size never replaced literal byte equality. No instruction/CFG
similarity or original differential-execution score was invented. The batch is biased
toward short leaves and callbacks, so it is not a representative whole-game match rate.

All accepted functions use the two existing Clang 18.1.3 profiles. No compiler/profile
or shared header changes, original byte insertion, assembly copies, post-build patches,
relocation bypass or byte trimming were used. This is isolated function evidence,
without full-program linking or original-process execution.

## Validation

The coordinator ran fresh `./tools/decomp match ADDRESS --require-exact` checks
for all fourteen additions. `make` compiled all fifty source candidates and passed
all nine tests, including the pinned-binary proof and deliberate source-regression
check. `make proof` independently rebuilt and verified all **27 exact functions /
361 bytes** against the pinned executable. Private byte-comparison reports remain
under ignored research directories; public CI can reproduce the portable checks
without the executable, but cannot reproduce the original-byte comparisons.
