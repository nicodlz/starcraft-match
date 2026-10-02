# Continuous research — first game-function lot

**110 whole C functions / 1,444 original bytes match exactly**, up from 109 / 1,424.
This lot promotes one previously unmatched, reviewed **20-byte game leaf** without
changing its independently written C source. The existing 76 static initializers
remain a separate category; there are now 34 other exact functions / 608 bytes.

All original observations concern the pinned Windows i386 Brood War 1.16.1 specimen
SHA-256 `ad6b58b27b8948845ccfa69bcfcc1b10d6aa7a27a371ee3e61453925288c6a46`.

## Accepted result

[0x00402C40](functions/00402C40.md) tests one global BYTE, reads an object WORD and
conditionally shifts the zero-extended value left by four. Its EAX pointer input,
full EAX result, other register preservation, complete return boundary and two
callers were independently reviewed. The callers consume AX. Field/global semantic
names remain unknown; the map label is a community annotation.

`clang-i686-scaffold-narrow-fixed-layout` adds `-mllvm -disable-block-placement`
to the narrow Clang 18.1.3 profile. The unchanged C now emits one shared return
instead of a duplicated return and matches all 20 original bytes. No bytes were
trimmed, normalized or patched; isolated COFF extraction rejects relocations.
The coordinator independently rebuilt, compared the complete region, integrated
the record and ran a fresh `./tools/decomp match 0x00402C40 --require-exact`.

## Bounded parallel experiment

Twenty workers participated: nineteen examined disjoint groups from a pool of
65 mapped no-call leaves up to 200 bytes; one revisited the twenty cataloged
mismatches with the available profiles. Static initializers and runtime-only helpers
were excluded. The new game leaves did not yield accepted exact functions in this
lot; all failed trials remain private rather than entering the exact count.

Reviewed blockers include compiler elimination of redundant branches, loop
rotation/alignment, CMP operand order, pointer/register allocation, extra register
clobbers and original inputs in EBX/ESI/EDI that available isolated C conventions
cannot express. Equal sizes and textual disassembly did not replace literal equality.
Some leads were excluded as runtime helpers or because their caller ABI was not
representable; the candidate pool is not a measured success-rate denominator.

## Historical toolchain preparation

A private copy of Microsoft's publicly released Visual C++ Toolkit 2003 was
obtained, extracted without running its installer and reviewed for container
integrity/signature provenance. Its compiler is **13.10.3077**. The official
[wibo 1.2.0 release](https://github.com/decompals/wibo/releases/tag/1.2.0) runs the
compiler locally without installing Wine. An independently written synthetic C
function compiled successfully to a strict isolated nine-byte COFF function,
without relocations. This is a compiler smoke test, not an original game match.

Microsoft documented the toolkit as a free release in its
[release announcement](https://devblogs.microsoft.com/buckh/download-the-vc-toolkit/).
The installer, compiler, DLLs, runner, extraction logs and certificate analysis
remain private. Historical signer mathematics and the published root identity were
checked separately; current certificate-chain trust is not claimed. This does not
identify the exact original compiler build or optimization switches. Adapter and
ABI experiments are a separate bounded next step; no assembly shim is counted.

## Validation

`make proof` freshly rebuilt and verified all **110 exact C-derived functions /
1,444 bytes** after the shared profile addition. `make` compiled all **132 source
candidates** and passed all **nine tests**, including the pinned-binary regression
and intentional source mutation. Publication checks cover only reviewed public
source/configuration/notes; original material and research reports are excluded.
There is no full-program linking, original-process execution or original differential
execution. Unavailable similarity and semantic metrics remain null.
