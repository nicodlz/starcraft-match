<div align="center">

# StarCraft Match

**A function-by-function matching decompilation of StarCraft: Brood War 1.16.1.**

[![Portable checks](https://github.com/nicodlz/starcraft-match/actions/workflows/portable.yml/badge.svg)](https://github.com/nicodlz/starcraft-match/actions/workflows/portable.yml)
![Target: Windows x86](https://img.shields.io/badge/target-1.16.1%20%7C%20Windows%20x86-315b82)
![490 exact functions](https://img.shields.io/badge/verified-490%20exact%20functions-287d67)
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

**490 whole functions match exactly, totaling 33,668 original bytes.** The independent
candidates are pure C; no original-byte arrays, copied assembly or post-build patches
are used to obtain these results. They include global accessors, trigger callbacks,
list operations, AI state updates and image-state callbacks.

The aggregate separates **387 isolated COFF matches / 23,872 bytes** from
**101 matches / 9,465 bytes** using the reviewed
[external-only standard linker](docs/standard-linking.md), plus
**two compiled-component matches / 331 bytes** with their actual C dependencies
(counted once among the 101 external-only matches).
Of the 490 functions, 76 are static data initializers totaling 836 bytes;
their destination semantics remain unknown. The count does not establish a
representative whole-game match rate. See the [function census](docs/function-census.md)
for the full breakdown and [per-function notes](docs/functions/) for reviewed evidence.
Detailed research reports remain under [docs/](docs/).

A complete **292-byte packing component** now matches exactly: the 1,000-entry
pool serializer and its compiled unit/path encoder. It passes 80 whole-pool emulator
comparisons and 80 chained packing/restoration comparisons. Its related 73-byte
path-reference decoder also matches exactly and passes 1,240 emulator comparisons.
The 127-byte initializer is exact too, extending the reconstructed pool lifecycle;
80 comparisons cover initialization followed by packing and restoration.
A second **615-byte component** serializes a 100-record pool and retains its exact
450-byte list/unit encoder; 80 comparisons cover its complete 46,004-byte state.
Its related 248-byte record restoration is exact and passes 80 record comparisons.

Work toward larger components also includes a 599-byte rectangle query linked with its
actual compiled C search dependency and an 864-byte pathfinding reference-restoration
routine. Both candidates remain non-exact; together they pass 460 bounded
original/C emulator fixtures. See [compiled components](docs/compiled-components.md).

Selected reviewed regions:

| Address | Reviewed operation | Original / compiled | Result |
| --- | --- | ---: | --- |
| [0x004BDB30](docs/functions/004BDB30.md) | Masked palette distance scan | 519 / 519 | Exact |
| [0x00483960](docs/functions/00483960.md) | Grid and coordinate scanning | 492 / 492 | Exact |
| [0x00403AE0](docs/functions/00403AE0.md) | List/unit reference encoding | 450 / 450 | Exact |
| [0x00403CB0](docs/functions/00403CB0.md) | List/unit reference restoration | 248 / 248 | Exact |
| [0x00404620](docs/functions/00404620.md) | 100-record serialization with actual C encoder | 165 / 165 | Exact |
| [0x004036D0](docs/functions/004036D0.md) | 1,000-entry serialization with actual C encoder | 166 / 166 | Exact |
| [0x004308A0](docs/functions/004308A0.md) | Rectangle query with actual C search dependency | 599 / 598 | Non-exact |
| [0x00403780](docs/functions/00403780.md) | 1,000-entry reference restoration | 864 / 788 | Non-exact |

Names are community annotations, not authenticated original symbols. Exact means
literal equality across the entire reviewed function, excluding inspected padding,
with the observed ABI represented in the candidate.

Six reviewed functions remain unmatched: [`0x00401120`](docs/functions/00401120.md),
[`0x00432180`](docs/functions/00432180.md), [`0x00446D40`](docs/functions/00446D40.md),
[`0x0047B210`](docs/functions/0047B210.md), [`0x00403780`](docs/functions/00403780.md)
and [`0x004308A0`](docs/functions/004308A0.md). Their complete regions and measured
compiler/ABI differences remain documented separately from exact expectations.
Three further regions compile
but lack independent entry corroboration; they remain exploratory and are excluded
from the exact-function count. The total number of game functions is **not measured**.
The public BWAPI map lists **4,201 distinct function entries**; our 490 matches are
about **11.66% of that community list by function count**, not by code size or effort.
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
make proof                    # Recompile and require all 490 exact matches
./tools/decomp match 0x00498150 --require-exact
./tools/decomp task 0x00498150 --out analysis/tasks/00498150.json
```

`make proof` fails on a regression and writes a private aggregate report to
`analysis/proof-of-concept.json`. A real-binary test deliberately changes a candidate
in a private source-only checkout to confirm that the failure gate works.
The 80-test suite includes an original-input proof and deliberate source-regression
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
