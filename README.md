<div align="center">

# StarCraft Match

**A function-by-function matching decompilation of StarCraft: Brood War 1.16.1.**

[![Portable checks](https://github.com/nicodlz/starcraft-match/actions/workflows/portable.yml/badge.svg)](https://github.com/nicodlz/starcraft-match/actions/workflows/portable.yml)
![Target: Windows x86](https://img.shields.io/badge/target-1.16.1%20%7C%20Windows%20x86-315b82)
![541 exact functions](https://img.shields.io/badge/verified-541%20exact%20functions-287d67)
[![License: MIT](https://img.shields.io/badge/original%20contributions-MIT-6a5b91)](LICENSE)

[Getting started](#getting-started) · [Progress](#current-progress) · [Contributing](CONTRIBUTING.md) · [Contributing with AI](docs/contributing-with-ai.md) · [Evidence](docs/prior-art.md)

</div>

![Matching workflow: observe, reconstruct, compile, compare](docs/assets/pipeline.svg)

This project reconstructs independently written C/C++ and compares its compiled
machine code with a pinned original executable. Equivalent behavior is useful;
**identical machine code is the matching target**. Each claim has an address,
reviewed boundary, calling convention, compiler profile and reproducible comparison.

This is an early research repository, not a playable engine. It contains no Blizzard
executables or game assets, performs no original-process execution, and does not yet
link a complete program. Faithful 1.16.1 reconstruction comes before any modern port.

## Current progress

**541 whole functions match exactly, totaling 46,522 original bytes.** The independent
candidates are pure C; no original-byte arrays, copied assembly or post-build patches
are used to obtain these results. They include global accessors, trigger callbacks,
list operations, AI state updates and image-state callbacks.

The aggregate separates **392 isolated COFF matches / 24,658 bytes** from
**136 matches / 18,394 bytes** using the reviewed
[external-only standard linker](docs/standard-linking.md), plus
**eight compiled-component matches / 1,581 bytes** with their actual C dependencies
(each dependency counted once under its measured method). A separate
[native MSVC LTCG component](docs/native-ltcg.md) contributes **599 exact bytes**
for the rectangle query and retains its already-counted 83-byte C search callee.
**Four whole C leaf contributions / 1,290 bytes** use the strict
[local-table linker](docs/standard-linking.md#whole-leaf-contributions), retaining
all compiler-owned switch tables and alignment (913 instruction bytes / 377 table
and alignment bytes).
Of the 541 functions, 76 are static data initializers totaling 836 bytes;
their destination semantics remain unknown. The count does not establish a
representative whole-game match rate. See the [function census](docs/function-census.md)
for the full breakdown and [per-function notes](docs/functions/) for reviewed evidence.
Detailed research reports remain under [docs/](docs/).

Three serialization components retain their actual C dependencies: **292 bytes**
for a 1,000-entry path pool, **615 bytes** for a 100-record state pool, and
**450 bytes** for a 1,000-record pool with five typed references per record.
The typed pool also has **288 exact restoration bytes** and passes 80 complete
encoding/restoration chains, retaining its 73-byte C path decoder.
A related 24-byte-node pool has **1,210 exact bytes** across initialization,
encoding and restoration. Bounded emulator comparisons check complete pools,
ordered memory accesses and observed calling conventions; see
[compiled components](docs/compiled-components.md) for fixture counts and limits.

The **599-byte rectangle query** now matches with native link-time compilation
and passes 380 bounded emulator comparisons. The **864-byte path reference
restorer** also matches exactly. Its initialization/encoding/restoration chain
retains **1,283 exact C bytes** and passes 80 complete-pool comparisons.

Selected reviewed regions:

| Address | Reviewed operation | Original / compiled | Result |
| --- | --- | ---: | --- |
| [0x004AA620](docs/functions/004AA620.md) | Two-pass record compaction and backup rebuild | 602 / 602 | Exact; 144 conditional-service oracle comparisons pass |
| [0x00408AE0](docs/functions/00408AE0.md) | 43 live-field calls with cdecl service ABI | 400 / 400 | Exact; 512 conditional-service comparisons pass |
| [0x00495240](docs/functions/00495240.md) | Signed-coordinate update with packed snapshots | 74 / 74 | Exact; 800 comparisons pass |
| [0x0047EA60](docs/functions/0047EA60.md) | Masked BYTE copy with source/destination overlap | 74 / 74 | Exact; 756 comparisons pass |
| [0x004DC550](docs/functions/004DC550.md) | Bounded modular DWORD draw with counter aliases | 92 / 92 | Exact; 256 comparisons pass |
| [0x0041CF60](docs/functions/0041CF60.md) | Signed WORD rectangle adjustment | 302 / 302 | Exact; 1,024 oracle comparisons pass |
| [0x0041F610](docs/functions/0041F610.md) | BYTE dispatch, complete jump table | 400 / 400 | Exact; 1,024 comparisons pass |
| [0x00491870](docs/functions/00491870.md) | Type/player selection, both dispatch tables | 439 / 439 | Exact; 82,464 comparisons pass |
| [0x00476000](docs/functions/00476000.md) | BYTE result with conditional bonuses, complete tables | 371 / 371 | Exact; 1,584 comparisons pass |
| [0x00497A10](docs/functions/00497A10.md) | Coordinate update and row-list migration | 268 / 268 | Exact; 640 comparisons pass |
| [0x00413870](docs/functions/00413870.md) | WORD selector with raw DWORD mode | 80 / 80 | Exact; local tables retained |
| [0x00482AE0](docs/functions/00482AE0.md) | Two forward neighborhood passes | 378 / 378 | Exact; 500 comparisons pass |
| [0x004888C0](docs/functions/004888C0.md) | BYTE category table query | 50 / 50 | Exact; 1,024 comparisons pass |
| [0x00488900](docs/functions/00488900.md) | Unsigned table minimum | 82 / 82 | Exact; 1,024 comparisons pass |
| [0x00473300](docs/functions/00473300.md) | List spatial query with private ABI | 257 / 257 | Exact; 850 comparisons pass |
| [0x00482090](docs/functions/00482090.md) | Eight WORD neighbors and mutable dimensions | 270 / 270 | Exact; 5,924 comparisons pass |
| [0x0049C9F0](docs/functions/0049C9F0.md) | Two-level WORD index query | 121 / 121 | Exact; 67,152 comparisons pass |
| [0x00403480](docs/functions/00403480.md) | Four unit references and list-header encoding | 289 / 289 | Exact; 400 comparisons pass |
| [0x00424540](docs/functions/00424540.md) | Twelve position/type snapshots | 287 / 287 | Exact; 130 comparisons pass |
| [0x0047EF80](docs/functions/0047EF80.md) | Prioritized flags and unsigned comparisons | 345 / 345 | Exact; 67,149 comparisons pass |
| [0x00402FB0](docs/functions/00402FB0.md) | Complete 1,000-record detail-pool restoration | 117 / 117 | Exact; 80 standalone and 80 exact-chain comparisons pass |
| [0x00402D10](docs/functions/00402D10.md) | Complete 1,000-record detail-pool serialization | 660 / 660 | Exact; 80 whole-pool comparisons and independent oracle pass |
| [0x00404410](docs/functions/00404410.md) | Typed 1,000-record pool restoration | 92 / 92 | Exact with both C callees |
| [0x00432810](docs/functions/00432810.md) | Typed record decoder, complete switch table | 196 / 196 | Exact with C callee |
| [0x00404350](docs/functions/00404350.md) | Typed 1,000-record pool serialization | 187 / 187 | Exact with C callee |
| [0x004328E0](docs/functions/004328E0.md) | Five-type record encoder | 263 / 263 | Exact |
| [0x00403DB0](docs/functions/00403DB0.md) | Related 1,000-node initialization | 155 / 155 | Exact |
| [0x00403E50](docs/functions/00403E50.md) | 1,000-node serialization | 915 / 915 | Exact |
| [0x004041F0](docs/functions/004041F0.md) | Related 1,000-node restoration | 140 / 140 | Exact |
| [0x004BDB30](docs/functions/004BDB30.md) | Masked palette distance scan | 519 / 519 | Exact |
| [0x00483960](docs/functions/00483960.md) | Grid and coordinate scanning | 492 / 492 | Exact |
| [0x00414290](docs/functions/00414290.md) | Unsigned eight-neighbor WORD count | 431 / 431 | Exact |
| [0x00403AE0](docs/functions/00403AE0.md) | List/unit reference encoding | 450 / 450 | Exact |
| [0x00403CB0](docs/functions/00403CB0.md) | List/unit reference restoration | 248 / 248 | Exact |
| [0x00404550](docs/functions/00404550.md) | 100-record pool initialization | 205 / 205 | Exact |
| [0x00404620](docs/functions/00404620.md) | 100-record serialization with actual C encoder | 165 / 165 | Exact |
| [0x004036D0](docs/functions/004036D0.md) | 1,000-entry serialization with actual C encoder | 166 / 166 | Exact |
| [0x004308A0](docs/functions/004308A0.md) | Rectangle query with actual C search dependency | 599 / 599 | Exact with native LTCG |
| [0x004C3ED0](docs/functions/004C3ED0.md) | Player relations initialization with both actual C callees | 532 / 532 | Non-exact; 4,096 complete-chain comparisons and independent oracle pass |
| [0x0045A9B0](docs/functions/0045A9B0.md) | Group-selected DWORD peer masks | 366 / 366 | Exact; 11,232 comparisons and independent oracle pass |
| [0x0048FDB0](docs/functions/0048FDB0.md) | Selector-driven player mask with actual C callee | 352 / 352 | Exact; 5,120 comparisons pass |
| [0x0048FC70](docs/functions/0048FC70.md) | Eight-record WORD mask accumulation | 319 / 319 | Exact; 1,280 comparisons pass |
| [0x0042FF80](docs/functions/0042FF80.md) | Generation-marked rectangle query with actual C search | 339 / 338 | Non-exact; 400 comparisons pass |
| [0x00479E60](docs/functions/00479E60.md) | Shared sprite/unit reference restoration | 85 / 85 | Exact; 160 comparisons pass |
| [0x00479EC0](docs/functions/00479EC0.md) | Shared sprite/unit reference encoding | 162 / 162 | Exact; 160 comparisons pass |
| [0x0048A9A0](docs/functions/0048A9A0.md) | 112-byte record encoding with actual C callee | 224 / 224 | Exact; 480 comparisons pass |
| [0x0048A8D0](docs/functions/0048A8D0.md) | 112-byte record restoration with actual C callee | 199 / 199 | Exact; 480 complete encoding/restoration chains pass |
| [0x0048C770](docs/functions/0048C770.md) | Complete 2,000-record reference restoration | 86 / 86 | Exact; 80 whole-pool comparisons pass |
| [0x0048C7D0](docs/functions/0048C7D0.md) | Complete 2,000-record reference encoding | 158 / 158 | Exact; 80 initialization/encoding/restoration chains pass |
| [0x0048A720](docs/functions/0048A720.md) | Complete 100-record list reconstruction | 420 / 420 | Non-exact; 260 pool comparisons and 80 full chains pass |
| [0x0048A560](docs/functions/0048A560.md) | Active-to-free record transfer | 147 / 147 | Exact; 1,600 whole-pool comparisons pass |
| [0x0048A690](docs/functions/0048A690.md) | Complete 100-record pool initialization | 113 / 113 | Exact; 80 whole-pool comparisons pass |
| [0x0048C590](docs/functions/0048C590.md) | Complete 2,000-record pool initialization | 394 / 394 | Exact; 80 whole-pool comparisons pass |
| [0x0047DC10](docs/functions/0047DC10.md) | Existing-neighbor node reclassification with both C callees | 321 / 332 | Non-exact; 1,550 comparisons pass |
| [0x0047DD60](docs/functions/0047DD60.md) | Node reclassification with both actual C callees | 216 / 208 | Non-exact; 1,848 comparisons pass |
| [0x00404280](docs/functions/00404280.md) | Typed 1,000-record pool initialization | 198 / 198 | Non-exact |
| [0x00403780](docs/functions/00403780.md) | 1,000-entry reference restoration | 864 / 864 | Exact; 80 standalone and 80 initialized-chain comparisons pass |

Operation descriptions summarize reviewed instructions. Community names in the
catalog are annotations, not authenticated original symbols. Exact means
literal equality across the entire reviewed function, excluding inspected padding,
with the observed ABI represented in the candidate.

Nine reviewed functions remain unmatched: [`0x00401120`](docs/functions/00401120.md),
[`0x00446D40`](docs/functions/00446D40.md),
[`0x0047B210`](docs/functions/0047B210.md),
[`0x00404280`](docs/functions/00404280.md),
[`0x0047DD60`](docs/functions/0047DD60.md),
[`0x0042FF80`](docs/functions/0042FF80.md),
[`0x0047DC10`](docs/functions/0047DC10.md),
[`0x0048A720`](docs/functions/0048A720.md) and
[`0x004C3ED0`](docs/functions/004C3ED0.md).
Their complete regions and measured compiler/ABI differences remain documented separately from exact expectations.
Three further regions compile
but lack independent entry corroboration; they remain exploratory and are excluded
from the exact-function count. The total number of game functions is **not measured**.
The public BWAPI map lists **4,201 distinct function entries**; our 541 matches are
about **12.88% of that community list by function count**, not by code size or effort.
The map is not a verified exhaustive census. See [function counts](docs/function-census.md).
This small sample demonstrates the workflow, not large-scale reconstruction success.

## Getting started

On Linux, the portable workflow needs **Python 3.10+**, **Clang**, **GNU objdump** and
**Make**. GCC runs the native candidate truth-table test. There are no Python package
dependencies, and these isolated candidates require no Windows SDK or CRT.
The measured profiles use **Clang 18.1.3**, generating i686 Windows COFF with `-O2`
or `-Oz`; a separate narrow-register profile disables one LLVM widening pass.
Historical profiles additionally require locally supplied Microsoft C 13.10.3077
and wibo 1.2.0. Their binaries are not bundled. `make` can compile these sources
with an explicit Clang fallback when the default historical toolchain is absent;
exact matching and `make proof` require the recorded compiler.
See [environment](docs/environment.md) and [toolchain evidence](docs/toolchain.md).

```sh
git clone https://github.com/nicodlz/starcraft-match.git
cd starcraft-match
make                          # Build every candidate and run the test suite
./tools/decomp status
```

A clean clone builds without the original executable. The real-binary regression
test is skipped until the supported local input is supplied. Public CI checks
source compilation, portable tests and tracked-file policy; its green badge does
**not** assert that the original game was available in CI.

### Supply the immutable target locally

Place a legally obtained **StarCraft: Brood War 1.16.1 Windows executable** at:

```text
original/StarCraft.exe
```

The supported initial specimen is PE32 i386, 1,220,608 bytes, file version 1.16.1.1,
with SHA-256:

```text
ad6b58b27b8948845ccfa69bcfcc1b10d6aa7a27a371ee3e61453925288c6a46
```

The hash pins a reviewed specimen; it is not a publisher authenticity certificate
or a claim about every regional distribution. See [provenance](docs/binary-provenance.md)
and [`config/target.json`](config/target.json). A clone does not contain the executable.

```sh
./tools/decomp analyze
make proof                    # Recompile and require all 541 exact matches
./tools/decomp match 0x00498150 --require-exact
./tools/decomp task 0x00498150 --out analysis/tasks/00498150.json
```

`make proof` fails on a regression and writes a private aggregate report to
`analysis/proof-of-concept.json`. A real-binary test deliberately changes a candidate
in a private source-only checkout to confirm that the failure gate works.
The 100-test suite includes an original-input proof and deliberate source-regression
test. A source-only checkout skips the real-binary test. With the executable
present, activate the host-local compiler paths before the full suite:

```sh
source .local/tools/activate.sh
make
```

Install the local commit guard in a fresh clone:

```sh
printf '#!/bin/sh\nexec ./tools/check-publication --staged\n' > .git/hooks/pre-commit
chmod +x .git/hooks/pre-commit
```

## Analysis and matching tools

| Command | Purpose |
| --- | --- |
| `./tools/decomp analyze` | Export deterministic PE identity, imports, sections, strings, function seeds and symbols |
| `./tools/decomp build-all` | Compile every reviewed candidate without needing the game |
| `./tools/decomp match ADDRESS` | Rebuild one candidate and emit a literal byte/disassembly diff |
| `./tools/match function ADDRESS` | Short wrapper for the same comparison |
| `./tools/decomp verify-matches` | Require every reviewed exact-match expectation to pass |
| `./tools/decomp next` / `show ADDRESS` | Inspect the catalog and its exploratory work |
| `./tools/decomp task ADDRESS` | Export one local function task with fresh match evidence |
| `./tools/decomp status` | Count candidates and fresh local results |

Analysis writes `binary.json`, `imports.json`, `sections.json`, `strings.json`,
`functions.json` and `symbols.json` under ignored `analysis/`. The basic reader seeds
entry/export addresses and incorporates reviewed functions; it does not perform a
complete function census. Printable-string scanning can produce false positives.
Stripped names, undiscovered references and unknown boundaries stay unknown.

Unknown hashes are rejected for matching. Read-only exploration can explicitly use
`analyze --binary original/other.exe --allow-unverified --out analysis/other`; this
never changes the supported target or promotes guesses into reviewed functions.

Matching compares the pinned PE region with the isolated compiled COFF function.
Reports retain compiler/source/header/record hashes and literal differences.
Instruction similarity and CFG scores are **null**, because reliable scoring for
those metrics has not been implemented. Unresolved relocations are rejected. An explicit reviewed catalog record can use
the [external-only standard linker](docs/standard-linking.md), which checks every
relocation and the complete compiler contribution and reports a separate method.

A [compiled-component profile](docs/compiled-components.md) can instead retain
reviewed C dependencies and verify their complete original regions. Optional local
emulator tests compare larger candidates with original function execution on synthetic
state; they are separate from exact-byte proofs and original-process execution.

Optional headless Ghidra integration is supplied for discovery, disassembly,
decompiler output, calls, references, strings and symbols:

```sh
GHIDRA_HOME=/path/to/ghidra ./tools/ghidra/run-headless
```

The local integration was validated on 2026-10-02 with Ghidra 12.1.4 and Temurin
JDK 21.0.12.1+1. Import, auto-analysis and the Java exporter completed against the
pinned executable, producing 4,644 function hypotheses with decompiler output.
These are discovery results, not reviewed boundaries or additional exact matches.
See [Ghidra instructions](tools/ghidra/README.md). The strongest original-compiler
hypothesis is **MSVC 7.1 / VS .NET 2003**; simple matches with modern Clang do not
establish broad compiler equivalence.

## Contributing

Start with [CONTRIBUTING.md](CONTRIBUTING.md). Reserve one function, inspect its
binary evidence, reconstruct a minimal candidate, compile it, compare it, and open
a small PR with the result and remaining uncertainty. Contributions to tooling,
boundary review, documentation and compiler experiments are also useful.

For agent-assisted work, read [Contributing with AI](docs/contributing-with-ai.md)
and [AGENTS.md](AGENTS.md). Parallel workers own distinct addresses and paths; a
coordinator independently rebuilds and verifies results before integration.
Automated success reports never replace original-byte evidence.

**Keep proprietary material local.** `original/`, `downloads/`, `analysis/`, `build/`
and `.local/` are ignored and are not release artifacts. Never force-add binaries,
assets, code extracts or complete decompiler/export dumps, attach them to public
issues, or upload them as CI artifacts. No third-party implementation is copied into
this tree. Source contributions use the [MIT license](LICENSE); it grants no rights
to Blizzard's binaries/assets or other third-party works. This project is independent
and is not affiliated with or endorsed by Blizzard Entertainment.

## Repository map

```text
config/               target identity, compiler profiles, function catalog/schema
include/reverse/      minimal observed layouts and fixed-address views
src/{game,map,units}/ independently compilable candidates
tools/analysis/      bounds-checked PE reader
tools/matching/      isolated COFF extraction and literal/disassembly comparison
tools/ghidra/        optional headless analysis/export
tests/               synthetic tests and optional local-binary regression
docs/functions/      per-address evidence, ABI, source reasoning and results
.github/             portable CI and contribution templates
```

Documentation: [Prior art](docs/prior-art.md) · [Toolchain](docs/toolchain.md) ·
[Agent pipeline](docs/agent-pipeline.md) · [Validation ladder](docs/validation.md).

## Next milestones

1. Resolve the remaining byte differences in the larger query and pathfinding
   candidates, retaining their reviewed ABI and measured data-access behavior.
2. Expand connected C components with real compiled dependencies, required layouts
   and reviewed linkage. Measure matched bytes, dependency coverage, iteration time
   and review effort alongside function counts.
3. Extend bounded differential tests as components grow. Original-process execution,
   deterministic simulation, replay synchronization and a complete linked program
   remain unestablished; modernization remains out of scope.
