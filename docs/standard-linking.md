# Reviewed external-only standard linking

This branch reuses the independently developed [external-only linking adapter from commit af83da3](https://github.com/nicodlz/starcraft-match/commit/af83da33e1f73c006f927542f7e6a2cc37a5c28f). The adapter and its tests are reused without changes. Other-session function sources and catalog records are excluded from this tooling integration.

The target remains SHA-256 `ad6b58b27b8948845ccfa69bcfcc1b10d6aa7a27a371ee3e61453925288c6a46`. Every linked candidate requires independent boundary, ABI and binding review followed by a coordinator rebuild. External symbol declarations bind addresses without inserting implementations.

## Reproduce locally

Supply the supported executable and recorded historical toolchain. GNU ld with
`i386pe` support is additionally required for linked candidates. The measured
local linker is GNU Binutils 2.42. Linker binaries are not bundled or asserted to
be the original game linker.

```sh
./tools/decomp match ADDRESS --require-exact
make proof
make
```

The aggregate proof includes `verified_by_method`: `isolated-coff` and
`standard-linked-c-external`. Portable builds without the optional historical
compiler compile fallback objects only; they do not link or compare those objects
and cannot supply exact evidence. Synthetic linker tests use Clang and GNU ld;
all generated objects/images are temporary.

## Evidence gates

`config/linkers.json` records the supported external-only linker configuration.
An explicit per-function `linking` record gives a unique compiler-authored section,
external symbol bindings with reviewed evidence, and an exact inventory of
uncounted context contributions. The linker receives the original compiler object,
an independently generated placement script and ordinary absolute external symbol
definitions. Context contributions induce private compiler-selected ABIs but are
excluded from both the linked output and the match count.

The adapter rejects malformed or overlapping COFF structures, unapproved code/data
contributions, unresolved or unsupported references, and rebinding of defined local
helpers. It accepts only external DIR32 and REL32 references. It then checks the
standard linker's PE bounds, sole executable section, fixed address, whole virtual
extent, entry, absence of imports/base relocations, every relocation result and
unchanged nonrelocation bytes. File-alignment padding is outside the section's
virtual extent; no compiler contribution is shortened or normalized.

Neither an external data symbol nor a callee binding inserts an implementation.
The candidate's ABI must independently agree with observed call sites and returns;
a nominal C symbol decoration alone does not establish the optimized contract.

Build/match records retain source/header/profile/compiler identities, full function
and linking record hashes, linker binary/version/configuration, adapter/engine
hashes, object/image/script identities and literal original comparisons. Freshness
inspection checks the current inputs and retained artifacts, rejects incomplete
header inventories and source-only fallbacks, and invalidates changed tools even
within one process. A fresh report never replaces a fresh required match build.

The default isolated COFF extractor still rejects linked candidates' relocations.
No assembly, embedded original bytes, object edits, post-link patches or ignored
relocations are used. This does not establish a full-program link, callee match,
original-process execution, differential execution or a playable game.

## Remaining research

The separate [compiled-component profile](compiled-components.md) now retains and
checks a real C search dependency for a larger non-exact query. It does not relax
this external-only adapter or count that existing dependency twice.

Retained synthetic helpers and jump-table contributions are separate private
experiments. They are not supported by this public external-only adapter and
contribute no functions or bytes to the counts above. Cross-session addresses stay
reserved; this lot remains isolated from the other coordinator's active catalog.
