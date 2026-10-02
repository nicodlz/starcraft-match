# 100 exact-function numeric milestone

**109 reviewed whole C functions / 1,424 original bytes match the pinned executable.**
This bounded batch adds **82 functions / 1,063 bytes** to the preceding 27 / 361.
The additional functions comprise **76 static data initializers / 836 bytes**, **four
game routines / 225 bytes**, and **two empty callbacks / two bytes**. The total proof
set therefore contains 76 initializers and 33 other reviewed functions / 588 bytes.
This reaches the requested numeric threshold, not 100 representative gameplay routines.

All binary observations refer to Windows i386 Brood War 1.16.1 specimen SHA-256
`ad6b58b27b8948845ccfa69bcfcc1b10d6aa7a27a371ee3e61453925288c6a46`.
The [public BWAPI map at pinned revision](https://github.com/bwapi/bwapi/blob/d727fed68558c506163048ea889131d8cbb33915/Release_Binary/Starcraft/bwapi-data/data/Broodwar.map)
is independent entry/size corroboration. Its names remain community annotations.
The original PE, map copy, full disassembly and comparison reports remain private.

## Selection and independent review

Twenty workers participated: nineteen owned disjoint address/source/note sets and
one researched compiler options. Discovery produced 736 new mapped no-call leads of
at most 120 bytes; this is a candidate pool, not a count of attempted or verified
functions. Workers tried candidates sequentially and retained nonmatching experiments
privately. Runtime forwarding thunks and uncorroborated regions were excluded.

A repeated family of startup DWORD copies was identified. The accepted lot is limited
to four individually reviewed initializers from each of the nineteen address groups.
Additional provisional initializer results were preserved privately, without entering
the public catalog or milestone count. This keeps selection bounded and leaves the
bias visible rather than claiming broad gameplay reconstruction.

The coordinator freshly extracted each complete original body and adjacent boundaries,
reviewed map entries, references, stack/register contracts and source, independently
rebuilt every selected C candidate, and compared the entire isolated COFF function.
Unresolved relocations are rejected. No compiler-emitted byte was normalized, trimmed
or patched, and no original instruction arrays or assembly copies were used.

## Other additions

| Function | Bytes | Community annotation | Profile |
| --- | ---: | --- | --- |
| [0x0047D160](functions/0047D160.md) | 1 | nullsub_gameloop | clang-i686-scaffold |
| [0x00484350](functions/00484350.md) | 1 | NullInput | clang-i686-scaffold |
| [0x0049DCE0](functions/0049DCE0.md) | 55 | CListPushBackHiddenUnitEntry | clang-i686-scaffold |
| [0x004B2AF0](functions/004B2AF0.md) | 60 | structureScoreCalc | clang-i686-scaffold |
| [0x004B2B30](functions/004B2B30.md) | 60 | unitScoreCalc | clang-i686-scaffold |
| [0x004E1220](functions/004E1220.md) | 50 | MenuGenericBtnInitChildren | clang-i686-scaffold-narrow |

The two 60-byte score callbacks preserve five ordered indexed DWORD reads and four
record writes, including wrapped addition. The 55-byte pointer-link routine preserves
a second link read after an intervening store, including alias-sensitive cases.
The 50-byte object update preserves WORD arithmetic, an unaligned DWORD store and
an observed BYTE store. Their community semantics are not original execution evidence.
The two one-byte no-op callbacks account for two functions and only two bytes.

`clang-i686-scaffold-narrow` adds `-mllvm -fixup-byte-word-insts=false` to the existing
Clang 18.1.3 scaffold profile. It resolves two widened WORD register loads in
`0x004E1220` during compilation, with no object rewriting. The broader XOR/MOV
encoding, CMP operand order, register allocation and branch-folding problems remain.
See [toolchain evidence](toolchain.md). The compiler-family hypothesis remains MSVC 7.1.

## Static data initializers

Each entry below is an independently corroborated **11-byte** whole function. It reads
one DWORD from `0x004FF8F8`, stores the same representation to the listed destination,
and returns. EAX contains the copied value; other registers and flags are preserved.
There are no consumed arguments or stack cleanup. No floating arithmetic is inferred
from the community `_initFloat` names, and destination semantics remain unknown.

The coordinator inspected the startup dispatcher at `0x00404E95`–`0x00404EB9`.
It traverses `[0x0050C000, 0x0050C4BC)` in DWORD steps, skips null entries and calls
through EAX at `0x00404EAC` without arguments. The copied EAX result is ignored.
Every listed slot lies in this traversed range and freshly resolves to its corresponding
entry. Each complete body and excluded adjacent padding was reviewed separately.
All use `clang-i686-scaffold`; every comparison includes all 11 original/candidate bytes.

| Function | DWORD destination | Referenced startup slot |
| --- | --- | --- |
| [0x004FC1A0](functions/004FC1A0.md) | `0x006D5ED4` | `0x0050C010` |
| [0x004FC1B0](functions/004FC1B0.md) | `0x006D5ED8` | `0x0050C014` |
| [0x004FC1E0](functions/004FC1E0.md) | `0x006D5EF4` | `0x0050C01C` |
| [0x004FC1F0](functions/004FC1F0.md) | `0x006D5EF8` | `0x0050C020` |
| [0x004FC200](functions/004FC200.md) | `0x006D5EFC` | `0x0050C024` |
| [0x004FC230](functions/004FC230.md) | `0x006D5F04` | `0x0050C02C` |
| [0x004FC260](functions/004FC260.md) | `0x006D5F08` | `0x0050C034` |
| [0x004FC270](functions/004FC270.md) | `0x006D5F0C` | `0x0050C038` |
| [0x004FC280](functions/004FC280.md) | `0x006D5F10` | `0x0050C03C` |
| [0x004FC290](functions/004FC290.md) | `0x006D5F14` | `0x0050C040` |
| [0x004FC2A0](functions/004FC2A0.md) | `0x006D5F18` | `0x0050C044` |
| [0x004FC2B0](functions/004FC2B0.md) | `0x006D5F1C` | `0x0050C048` |
| [0x004FC2C0](functions/004FC2C0.md) | `0x006D5F20` | `0x0050C04C` |
| [0x004FC2D0](functions/004FC2D0.md) | `0x006D5F24` | `0x0050C050` |
| [0x004FC2E0](functions/004FC2E0.md) | `0x006D5F28` | `0x0050C054` |
| [0x004FC2F0](functions/004FC2F0.md) | `0x006D5F2C` | `0x0050C058` |
| [0x004FC300](functions/004FC300.md) | `0x006D5F30` | `0x0050C05C` |
| [0x004FC310](functions/004FC310.md) | `0x006D5F34` | `0x0050C060` |
| [0x004FC320](functions/004FC320.md) | `0x006D5F38` | `0x0050C064` |
| [0x004FC330](functions/004FC330.md) | `0x006D5F3C` | `0x0050C068` |
| [0x004FC340](functions/004FC340.md) | `0x006D5F40` | `0x0050C06C` |
| [0x004FC350](functions/004FC350.md) | `0x006D5F44` | `0x0050C070` |
| [0x004FC360](functions/004FC360.md) | `0x006D5F48` | `0x0050C074` |
| [0x004FC3B0](functions/004FC3B0.md) | `0x006D5F64` | `0x0050C080` |
| [0x004FC3C0](functions/004FC3C0.md) | `0x006D5F68` | `0x0050C084` |
| [0x004FC3F0](functions/004FC3F0.md) | `0x006D5F6C` | `0x0050C08C` |
| [0x004FC420](functions/004FC420.md) | `0x006D5F70` | `0x0050C094` |
| [0x004FC430](functions/004FC430.md) | `0x006D5F74` | `0x0050C098` |
| [0x004FC440](functions/004FC440.md) | `0x006D5F78` | `0x0050C09C` |
| [0x004FC450](functions/004FC450.md) | `0x006D5F7C` | `0x0050C0A0` |
| [0x004FC480](functions/004FC480.md) | `0x006D5F80` | `0x0050C0A8` |
| [0x004FC490](functions/004FC490.md) | `0x006D5F84` | `0x0050C0AC` |
| [0x004FC4C0](functions/004FC4C0.md) | `0x006D5F88` | `0x0050C0B4` |
| [0x004FC4D0](functions/004FC4D0.md) | `0x006D5F8C` | `0x0050C0B8` |
| [0x004FC4E0](functions/004FC4E0.md) | `0x006D5F90` | `0x0050C0BC` |
| [0x004FC4F0](functions/004FC4F0.md) | `0x006D5F94` | `0x0050C0C0` |
| [0x004FC500](functions/004FC500.md) | `0x006D5F98` | `0x0050C0C4` |
| [0x004FC510](functions/004FC510.md) | `0x006D5F9C` | `0x0050C0C8` |
| [0x004FC520](functions/004FC520.md) | `0x006D5FA0` | `0x0050C0CC` |
| [0x004FC530](functions/004FC530.md) | `0x006D5FA4` | `0x0050C0D0` |
| [0x004FC580](functions/004FC580.md) | `0x006D5FA8` | `0x0050C0DC` |
| [0x004FC590](functions/004FC590.md) | `0x006D5FAC` | `0x0050C0E0` |
| [0x004FC5C0](functions/004FC5C0.md) | `0x006D5FB0` | `0x0050C0E8` |
| [0x004FC5F0](functions/004FC5F0.md) | `0x006D5FB4` | `0x0050C0F0` |
| [0x004FC600](functions/004FC600.md) | `0x006D5FB8` | `0x0050C0F4` |
| [0x004FC610](functions/004FC610.md) | `0x006D5FBC` | `0x0050C0F8` |
| [0x004FC640](functions/004FC640.md) | `0x006D5FC0` | `0x0050C100` |
| [0x004FC650](functions/004FC650.md) | `0x006D5FC4` | `0x0050C104` |
| [0x004FC660](functions/004FC660.md) | `0x006D5FC8` | `0x0050C108` |
| [0x004FC670](functions/004FC670.md) | `0x006D5FCC` | `0x0050C10C` |
| [0x004FC680](functions/004FC680.md) | `0x006D5FD0` | `0x0050C110` |
| [0x004FC690](functions/004FC690.md) | `0x006D5FD4` | `0x0050C114` |
| [0x004FC6A0](functions/004FC6A0.md) | `0x006D5FD8` | `0x0050C118` |
| [0x004FC6B0](functions/004FC6B0.md) | `0x006D5FDC` | `0x0050C11C` |
| [0x004FC6C0](functions/004FC6C0.md) | `0x006D5FE0` | `0x0050C120` |
| [0x004FC6D0](functions/004FC6D0.md) | `0x006D5FE4` | `0x0050C124` |
| [0x004FC6E0](functions/004FC6E0.md) | `0x006D5FE8` | `0x0050C128` |
| [0x004FC6F0](functions/004FC6F0.md) | `0x006D5FEC` | `0x0050C12C` |
| [0x004FC700](functions/004FC700.md) | `0x006D5FF0` | `0x0050C130` |
| [0x004FC710](functions/004FC710.md) | `0x006D5FF4` | `0x0050C134` |
| [0x004FC720](functions/004FC720.md) | `0x006D5FF8` | `0x0050C138` |
| [0x004FC730](functions/004FC730.md) | `0x006D5FFC` | `0x0050C13C` |
| [0x004FC740](functions/004FC740.md) | `0x006D6000` | `0x0050C140` |
| [0x004FC750](functions/004FC750.md) | `0x006D6004` | `0x0050C144` |
| [0x004FC760](functions/004FC760.md) | `0x006D6008` | `0x0050C148` |
| [0x004FC770](functions/004FC770.md) | `0x006D600C` | `0x0050C14C` |
| [0x004FC780](functions/004FC780.md) | `0x006D6010` | `0x0050C150` |
| [0x004FC790](functions/004FC790.md) | `0x006D6014` | `0x0050C154` |
| [0x004FC7A0](functions/004FC7A0.md) | `0x006D6018` | `0x0050C158` |
| [0x004FC7B0](functions/004FC7B0.md) | `0x006D601C` | `0x0050C15C` |
| [0x004FC7C0](functions/004FC7C0.md) | `0x006D6020` | `0x0050C160` |
| [0x004FC7D0](functions/004FC7D0.md) | `0x006D6024` | `0x0050C164` |
| [0x004FC7E0](functions/004FC7E0.md) | `0x006D6028` | `0x0050C168` |
| [0x004FC870](functions/004FC870.md) | `0x006D602C` | `0x0050C170` |
| [0x004FC880](functions/004FC880.md) | `0x006D6030` | `0x0050C174` |
| [0x004FC890](functions/004FC890.md) | `0x006D6034` | `0x0050C178` |

## Validation and limits

`make` compiled all **132 source candidates** and passed all **nine tests**, including
the pinned-binary proof and deliberate source-regression check. `make proof` freshly
rebuilt and verified all **109 exact functions / 1,424 bytes** after the shared
compiler-profile addition. All **82** additions also passed fresh individual
`./tools/decomp match ADDRESS --require-exact` checks after catalog integration.
The publication guard checks staged paths before committing; research inputs and
comparison reports remain ignored and are excluded from publication.

There is no full-program linking, original-process execution or original differential
test. Unimplemented instruction/CFG/semantic metrics stay null. The listed-function
ratio is 109 / 4,201 community map entries, approximately 2.59%; it is not a completion
percentage, effort estimate or verified exhaustive program census. Public CI can
compile the sources and run portable checks, but cannot reproduce game-byte comparisons
without the private pinned executable. Repeated static initializers dominate this
numeric milestone; a representative 100-function gameplay sample remains future work.
