# Original compiler and matching toolchain

Initial conclusion: **Microsoft Visual C++ .NET 2003 (MSVC 7.1)** is the strongest
compiler hypothesis for this 1.16.1 specimen. It was initially absent; a private
Toolkit 2003 compiler now runs locally for synthetic experiments (see below).
Modern Clang is used for the feedback loop; it is not presented as a matching substitute.

This conclusion concerns the **1.16.1 patch executable built in 2009**, not the
original late-1990s retail release. A later patch can use a later compiler. The PE
timestamp is metadata rather than an authenticated build date; its 2009 value,
1.16.1 version resource and CodeView build path agree. Linked legacy objects and
third-party libraries may have different compiler histories.

| Conclusion | Evidence | Confidence |
| --- | --- | --- |
| VS 2003 / compiler family 7.1 | [Blizzard engineer Elias Bachaalany's presentation](https://files.bnetdocs.org/StarCraft_EUD_Emulator.pdf), “Identify – Reversing the game /2”, describes finding VS 2003 for a close 1.16.1 rebuild; local linker version 7.10 corroborates | High for family; not direct verification of every original object |
| Exact compiler build, service pack and hotfixes | Not established by current inspection | Unknown |
| Microsoft linker 7.10 | Local PE optional header major/minor linker version 7/10 | High for header observation; metadata alone can be altered |
| Original optimization switches | Presentation reports approximate switches but does not disclose them; tiny region uses compact loads/tests and shared return paths | Unknown; do not infer `/O2` globally from one leaf |
| 32-bit x86 Windows | PE32 optional header and machine 0x014C | Verified |
| Custom register argument ABI at `0x004020B0` | Original first dereference uses EAX, both returns set EAX to 0/1, plain `ret`; no stack argument read | High for this region; incoming caller audit pending |
| Runtime selection | Imports are KERNEL32, USER32, GDI32, ADVAPI32, IMM32, VERSION, SHELL32 and storm; no MSVCRT/MSVCP import | Verified absence in import table; static CRT possible, exact CRT and `/MT` vs alternatives unverified |
| Preferred image / relocations | Image base 0x00400000, relocations stripped and relocation directory absent | Verified in this specimen |
| Debug linkage | CodeView RSDS record refers to a 1.16.1 build and `BroodWar.pdb`; no PDB supplied | Verified metadata; not usable debugging symbols |
| Rich header | Marker present | Verified marker only; product IDs/checksum not decoded |

The presentation was downloaded locally and read via `pdftotext`; the web reader
could not render it. No private Blizzard source snapshot or leaked code was obtained.
The account's source snapshot is historical testimony, not an input to this project.
The compiler used for BWAPI or GPTP is not evidence of the compiler used for StarCraft.
Diablo's matching toolchain must not be generalized to StarCraft.

Working profile: Clang 18.1.3, `--target=i686-pc-windows-msvc -std=c11 -O2
-ffreestanding -fno-stack-protector -fno-ident -ffunction-sections`. The isolated
function requires no Windows SDK/CRT. An i386 `regparm(1)` attribute expresses the
observed EAX input; this is not an assertion that the original source used this
attribute. ABI observations should eventually include preserved registers and callers.

Initial candidate is 48 bytes vs 50 original bytes. Clang moves the pointer from
EAX to ECX, tests a byte of status directly, compares timers in memory, and uses
`setne` for the last condition. Original code loads DWORD status into ECX, tests CH,
loads each timer into CL, and shares a true return block. Those are actual measured
code-generation differences. Matching memory access width matters too; truth-table
tests alone do not prove equivalent fault behavior or ABI.

Next toolchain experiment: use a legally obtained VS 2003 compiler in an isolated
Windows environment (or Wine, once validated), record compiler/linker hashes and
versions, and test narrowly scoped optimization/source-shape variations. Some
register ABIs may require a compiler-specific adapter or a separate assembly ABI
shim; do not count a handwritten copy of original instructions as C decompilation.
Compare relocated final machine code, not unresolved object placeholders. The phase-1
extractor rejects candidate sections with relocations until this is supported.


## Exact matches obtained with the modern scaffold

Four short game-state leaves (0x00488780, 0x00496FF0, 0x004CE6B0, 0x004DC540)
compile to literally identical bytes using the recorded Clang 18.1.3 profile.
They consist of one or two fixed-address loads/stores followed by ret, totaling
37 original bytes. The last takes ECX and returns the prior DWORD in EAX;
one-argument i386 fastcall reproduces that contract without an assembly shim.
These results are measured exceptions to the general difficulty of reproducing
historical code with a different compiler, not evidence that Clang can match the
original program broadly. The compiler-family hypothesis remains MSVC 7.1.

The initial unsigned-byte getter attempt at 0x004CE6C0 did not match with-O2: original uses an AL-only load, whereas Clang emits a full EAX
zero-extension. Even equally simple adjacent routines need ABI/source-shape care.


## Second research batch

The reviewed proof set expanded to eleven exact functions / 158 original bytes.
`clang-i686-size` differs by using `-Oz`: it produces AL-only byte loads for
0x004CE6C0 and the narrow AL/CL copy at0x0047CCB0. Those candidates failed with-O2.
The indexed property predicate0x00473490 matches with i386 fastcall; the two-branch
image-state update0x00498150 matches using Clang regcall to express EAX and CL inputs.
All complete candidate sections are re-extracted and byte-compared by the coordinator;
no encoding substitutions or post-build patches are applied.
The earlier unsigned-byte getter mismatch is now resolved by the-Oz profile.
Exact results here remain narrow code-generation observations, not proof of the
historic compiler's exact switches or a viable full-game Clang replacement.


## Narrow-register profile for the 100-function milestone

`clang-i686-scaffold-narrow` retains the scaffold flags and adds
`-mllvm -fixup-byte-word-insts=false`. In the reviewed
[0x004E1220](functions/004E1220.md) candidate, this prevents widening two partial
WORD loads into MOVZX. The complete 50-byte function then matches exactly, including
its access widths, caller contract and preservation of EAX/EDX. Both the ordinary
scaffold and narrow profile produce 50 bytes, but the ordinary profile differs at
those two loads. The option changes compiler instruction selection before emission;
no assembly copy, encoding substitution or post-build patch is involved.

This profile is pinned through the build manifests to the local Clang 18.1.3
executable and recorded flags. It does not establish the original compiler's options
or solve the broader XOR/MOV encoding and CMP-direction mismatches. The compiler
researcher's private synthetic matrix measured 50 Clang and 16 GCC configurations;
no general XOR `33` / `31` or MOV `8B` / `89` solution was established. Shared profile
changes require a fresh rebuild of the full proof set, including previous matches.

## Machine block-placement experiment

`clang-i686-scaffold-narrow-fixed-layout` adds `-mllvm -disable-block-placement`
to the narrow profile. In [0x00402C40](functions/00402C40.md), the existing C source
then retains one shared return instead of a duplicated return and matches all
20 original bytes. The global BYTE test remains before the object WORD load;
EAX input/result and other register preservation match. Disabling this pass does
not freeze the entire compiler layout or establish historical compiler equivalence.
The full proof set must be freshly rebuilt after adding this shared profile.

## Historical compiler smoke test

A privately extracted Visual C++ Toolkit 2003 compiler, **13.10.3077**, compiled an
independent synthetic C function under [wibo 1.2.0](https://github.com/decompals/wibo/releases/tag/1.2.0).
The isolated COFF function is nine bytes and has no relocations. This establishes a
working compile-only experiment, not a game-function match or the identity of the
original compiler build. [Research notes](continuous-2026-10-02.md) distinguish
container integrity, historical signing evidence and current certificate trust.
CL SHA-256: `2ecf86a3edfd3deae498e08298e210e984537ce9e11759930561e43f40bd2515`.
Compiler, DLLs and runner remain private; no proprietary compiler binaries are bundled.
