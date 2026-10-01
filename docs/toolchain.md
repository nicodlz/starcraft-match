# Original compiler and matching toolchain

Initial conclusion: **Microsoft Visual C++ .NET 2003 (MSVC 7.1)** is the strongest
compiler hypothesis for this 1.16.1 specimen. It is not available on this host.
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
