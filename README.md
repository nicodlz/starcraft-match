# StarCraft: Brood War 1.16.1 matching decompilation

Research foundation for reconstructing compilable C/C++ whose generated x86 machine
code matches the original Windows executable, one function at a time. Behaviorally
compatible implementations are useful references, but machine code from the pinned
original is the authority. This is not a playable engine or an OpenBW replacement.
No modernization is underway; bugs, limits and original behavior must be preserved.

The first milestone is a working original-region → candidate C → x86 compile →
automatic comparison loop. **Four real game-state functions now match exactly,
byte for byte, from independently compiled C.** A fifth candidate compiles but
still differs. Next milestones are 10, then 100 well-evidenced functions before
large-scale automation is evaluated.

## Target and proprietary data policy

Target: StarCraft: Brood War **1.16.1**, Windows **32-bit x86**, PE32.
Place a legally obtained executable at `original/StarCraft.exe`. Supported initial
specimen: 1,220,608 bytes, file version 1.16.1.1, SHA-256:

```text
ad6b58b27b8948845ccfa69bcfcc1b10d6aa7a27a371ee3e61453925288c6a46
```

`config/target.json` records its identity and provenance. This is an observed hash,
not a publisher authenticity certificate or a claim covering every regional release.
The user's requested download succeeded from the competition's public distribution;
see [provenance](docs/binary-provenance.md) and [competition resources](https://davechurchill.ca/starcraft/resources/).
The local executable is already present in this workspace, but will not be in a clone.

**Never commit or publish Blizzard binaries/assets.** `original/`, `downloads/`,
`analysis/`, `build/`, `.local/`, binary containers and object outputs are ignored.
Strings, disassembly, decompiler text and task exports generated from the binary
stay local. Tool output directories are restricted to ignored locations. Do not
bundle these directories in release artifacts or force-add them to Git.
No third-party source code was copied into the repository.

`tools/check-publication --staged` rejects staged private paths and recognized binary
containers. A local pre-commit hook is installed here. In a fresh clone install it:

```sh
printf '#!/bin/sh\nexec ./tools/check-publication --staged\n' > .git/hooks/pre-commit
chmod +x .git/hooks/pre-commit
```

This guard supplements review; Git ignores and hooks are not a legal/provenance audit.

## Setup and working commands

Required: Python 3.10+, Clang with i686 Windows code generation, GNU objdump. GCC is
used for optional native semantic tests. No Python packages, Windows SDK, game assets,
Wine or historic compiler are needed for these isolated candidates. The initial host
has Python 3.12, Clang 18, GCC 13 and objdump 2.42; see [environment](docs/environment.md).

```sh
# Works without StarCraft.exe: isolated Windows-x86 candidate and synthetic tests
make
# Equivalently:
./tools/decomp build 0x004020B0
python3 -m unittest discover -s tests -v

# Requires the supported original/StarCraft.exe
./tools/decomp analyze
./tools/match function 0x004020B0
make proof                 # Recompile and require all four exact matches
./tools/decomp task 0x004020B0 --out analysis/tasks/004020B0.json

./tools/decomp status
./tools/decomp next
./tools/decomp show 0x004020B0
./tools/check-publication
```

An unknown hash is rejected by default. Read-only metadata exploration can use
`./tools/decomp analyze --binary original/other.exe --allow-unverified --out analysis/other`.
It does not authorize matching or silently change the immutable target.

Analysis outputs: `binary.json`, `imports.json`, `sections.json`, `strings.json`,
`functions.json`, `symbols.json`. Metadata includes identity, PE version/debug records,
linker fields and import ordinals. String scanning finds printable ASCII/UTF-16LE
runs, including possible false positives; references are not inferred by this scanner.
Without Ghidra, function discovery seeds only entry/export addresses plus the reviewed
catalog. Sizes and boundaries are left unknown for unreviewed seeds. **Six function
records are not a census of the executable.** Stripped symbols stay unknown.

Optional Ghidra integration:

```sh
GHIDRA_HOME=/path/to/ghidra ./tools/ghidra/run-headless
```

The headless exporter covers discovery, disassembly, decompiler text, direct calls,
references, strings and symbols. Ghidra and Java were absent here, so that integration
is supplied but unvalidated. See [Ghidra instructions](tools/ghidra/README.md).

## Current result and limitations

The proof of concept now contains four exact matches:

| Address | Community annotation | Original / candidate size | Exact bytes |
| --- | --- | --- | --- |
| [0x00488780](docs/functions/00488780.md) | isGamePaused | 6 / 6 | true |
| [0x00496FF0](docs/functions/00496FF0.md) | EnableVisibilityHashUpdate | 11 / 11 | true |
| [0x004CE6B0](docs/functions/004CE6B0.md) | SetMapStartStatus (clears a byte) | 8 / 8 | true |
| [0x004DC540](docs/functions/004DC540.md) | SetInGameLoop (returns old DWORD) | 12 / 12 | true |

These are deliberately tiny non-library state routines: **37 original bytes total**.
Each boundary and relevant direct caller was checked against the pinned executable,
and BWAPI's public map agrees on entries and sizes. `make proof` recompiles them,
requires literal equality and compatible ABI, and writes a private aggregate report
at `analysis/proof-of-concept.json`. It fails if any expected exact match regresses.
The sources contain no inline assembly, embedded original bytes or post-processing.
Their absolute global addresses rely on the original preferred image layout.

The initial [`sub_004020B0`](docs/functions/004020B0.md) unit-state predicate remains
**50 original bytes / 48 compiled bytes, not exact**. It is retained as an exploratory
candidate rather than counted as matched. Nine tests pass with the local executable,
including a deliberate source regression that the proof command rejects. Without
the executable, eight portable tests pass and the real-binary regression is skipped.
No original execution/differential testing has been performed.

The match command writes `analysis/matches/0x004020B0.json`, including original and
candidate disassembly, literal differences and compile provenance. Instruction
similarity and CFG similarity are **null**: no reliable scoring engine exists yet.
Unresolved relocations are rejected. Whole-program linking is not implemented.

The strongest original-toolchain hypothesis is **MSVC 7.1 / Visual Studio .NET 2003**,
supported by linker 7.10 and a Blizzard engineer's public account. Exact compiler
build and optimization switches remain unknown. Clang supplies a useful scaffold;
its different instruction selection/register allocation prevents the frozen-state
match. Simple exact matches with Clang do not establish historical compiler equivalence.
See [toolchain evidence](docs/toolchain.md) and [public references](docs/prior-art.md).

## Repository and function workflow

```text
config/                  target hashes, compiler profiles, function catalog/schema
include/reverse/         minimal observed layout with compile-time offset checks
src/units/               exploratory unit-state candidate
src/game/                three exact game-state routines
src/map/                 one exact map-state routine
tools/                  decomp CLI, matching wrapper, publication check
tools/analysis/          bounds-checked PE metadata reader
tools/matching/          isolated COFF extraction and literal/disassembly diff
tools/ghidra/            optional headless import/export scripts
tests/                  synthetic PE/COFF and candidate semantics checks
docs/functions/         reviewed per-address reasoning and matching status
```

Gameplay/AI/rendering/network folders will be created when actual reconstructed
functions need them.

[`config/functions.json`](config/functions.json) is the small machine-readable
reviewed database. Binary-derived discoveries and match reports are separate private
artifacts. [`docs/agent-pipeline.md`](docs/agent-pipeline.md) explains task exports,
iteration, provenance, progress counters and eventual SQLite migration.
[`docs/validation.md`](docs/validation.md) distinguishes code matching, differential
execution, deterministic simulation and replay synchronization.

Each reviewed function gets `docs/functions/<address>.md` with observed assembly,
region boundaries, inferred ABI, source reasoning, references, uncertainty and
current result. Proposed community names remain separate from neutral symbols.
The later `starcraft-modern` fork is out of scope until faithful reconstruction exists.

## Next three milestones

1. Validate headless Ghidra exports with a pinned official release; audit incoming
   callers for `0x004020B0` and rank small non-library function candidates.
2. Obtain a lawful VS 2003 toolchain, pin compiler provenance, explore source/flags
   and ABI adapters for less trivial C-derived matches; add relocation support as needed.
3. Reach 10 documented, compiling and automatically compared real functions, then
   100, measuring agent iteration success before adding a scheduler or simulation tests.
