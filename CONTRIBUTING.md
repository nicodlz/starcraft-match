# Contributing

This project reconstructs the Windows x86 StarCraft: Brood War 1.16.1 executable
function by function. A useful contribution supplies reviewable evidence and a
reproducible experiment. An exact match is welcome; an honestly documented mismatch
can also improve the project. Gameplay compatibility alone does not establish a
matching decompilation.

Read the [README](README.md), [toolchain evidence](docs/toolchain.md),
[validation levels](docs/validation.md) and [public references](docs/prior-art.md)
before choosing a function. For parallel or AI-assisted work, also read
[contributing with AI](docs/contributing-with-ai.md).

## Local setup and proprietary inputs

Use only an executable and assets that you legally possess. Place the supported
executable at `original/StarCraft.exe`; `config/target.json` records the accepted
SHA-256. A clone does not include the game. An observed supported hash identifies
our specimen, rather than certifying publisher authenticity or every regional build.
Do not change the target hash to make a different executable pass validation.

Do not commit, publish, attach to issues, or bundle Blizzard executable files,
libraries or assets. Keep extracted bytes, strings, full disassembly, decompiler
exports and agent task bundles under ignored `analysis/`, `build/` or `.local/`.
Keep downloads and originals under their ignored directories. Never force-add
private files. Public function notes should contain concise, manually reviewed
evidence and reasoning; they should not become dumps of generated analysis.

Public reverse-engineering projects are references for hypotheses, layouts and
semantics. Cite them, preferably at a pinned revision. Independently write candidate
source; do not copy implementations from BWAPI, OpenBW or another project.

Required tooling and versions are documented in the README. These checks work
without an original executable:

```sh
make
./tools/check-publication
```

Exact comparison requires the supported executable:

```sh
./tools/decomp analyze
make proof
```

The optional Ghidra workflow is documented in [tools/ghidra](tools/ghidra/README.md).
Missing optional tools should be reported explicitly, rather than represented as
successful analysis.

## Choose and reserve a small unit of work

Start with a short non-library function whose entry, complete body and ABI can be
reviewed. Avoid large gameplay systems until smaller experiments establish the
needed structures and toolchain behavior. Check the catalog and existing function
notes before starting. Coordinate an address reservation in the issue, pull request
or active team conversation; a reservation is a coordination convention, not an
implemented scheduler or lock.

Use the neutral symbol `sub_XXXXXXXX` when the original name is unknown. Keep
community or inferred names in `proposed_names`, with their sources and confidence.
Do not describe a community label as an authenticated original symbol.

## Reconstruct and compare one function

1. Verify the executable SHA-256. Record the function address and complete region
   size against that hash. Inspect the entry, returns, branches and surrounding
   bytes. Community maps and analyzer output are supporting evidence, not automatic
   boundary verification. Leave ambiguous boundaries unverified.
2. Inspect relevant callers to establish argument locations, stack cleanup, return
   width and register behavior. Distinguish an EAX result from an AL result whose
   upper bits are unspecified. Verify offsets, widths and access order before
   assigning semantic structure names.
3. Write a small independent C/C++ candidate in the appropriate `src/` directory.
   Add only layouts needed by observed accesses; check important offsets at compile
   time. Preserve bugs, limits, state effects and the observed calling convention.
   Current C-derived proof candidates must not use inline assembly, embedded
   original machine bytes or post-compilation patching.
4. Add or update the reviewed record in `config/functions.json`, following
   `config/function.schema.json`. Record the binary hash, boundary evidence, ABI,
   candidate source/symbol, compiler profile, dependencies and uncertainty. Compiler
   flags may be explored, but do not characterize modern Clang as the historical
   toolchain merely because it matches a small routine.
5. Compile and compare the candidate. Inspect the entire extracted region and fresh
   report, including relocation checks and the build manifest. The present matcher
   rejects unsupported relocation cases; do not bypass the restriction to claim a
   match. Keep unsupported similarity metrics null.
6. Write `docs/functions/XXXXXXXX.md`: address, size, evidence, inferred prototype,
   relevant references, source reasoning, compiler profile, result and limitations.
   Explain why a remaining difference matters instead of hiding it.

After registering the address, replace the example below with your function:

```sh
./tools/decomp show 0x004020B0
./tools/decomp build 0x004020B0
./tools/decomp match 0x004020B0
```

For a new exact match, set `match_expectation` to `"exact"`, then verify it and the
existing proof set:

```sh
./tools/decomp match 0x004CE6C0 --require-exact
make proof
```

Use `--require-exact` only when equality is the expected result; the getter above
is an existing exact-match example. A failed comparison is useful evidence, not permission
to set a success field manually. `match.exact` in a catalog records a reviewed result;
a fresh build and comparison are required to establish current equality.

## Describe evidence precisely

Separate these categories in notes and pull requests:

| Category | Example | What it establishes |
| --- | --- | --- |
| Pinned-binary observation | A byte read at a reviewed address; caller consumes AL | Behavior of this exact specimen and region |
| Community reverse-engineering knowledge | A BWAPI map label or documented structure offset | A sourced annotation requiring specimen verification |
| Compatible reimplementation | An OpenBW analogue | Helpful semantics; no original-byte equality |
| Hypothesis | An inferred prototype, compiler switch or guessed field meaning | A proposed explanation with stated uncertainty |

Literal equality of a complete reviewed function, with a compatible ABI, is the
current strongest local milestone. It does not establish a full-game linked build,
original differential execution, deterministic simulation or replay synchronization.
Candidate-only tests do not demonstrate equivalence with the original executable.

## Submit a reviewable pull request

Keep changes focused: one function or a small related group, plus necessary evidence
and infrastructure. The pull request should explain the behavior reconstructed,
binary/hash and boundary evidence, ABI, compiler profile, measured result, checks
run and remaining uncertainty. Link function notes and public references. Report
checks requiring unavailable tools as unrun.

Run the existing synthetic checks and, when the original is available, the proof set.
Add meaningful tests for matcher or analysis changes; a trivial getter usually does
not need a test that simply repeats its implementation.

```sh
make
make proof
./tools/check-publication
./tools/check-publication --staged
```

Review `git diff` and `git diff --cached` before committing. Stage specific public
files. Publication checks supplement manual review; they do not determine ownership,
provenance or whether every text excerpt is appropriate to publish. Do not upload
private match reports as CI artifacts or pull-request attachments.

A reviewer should rebuild the candidate and extract the original region independently,
check the recorded boundaries and ABI, and verify equality using the repository's
matcher. Source reconstruction, compilation, partial comparison and exact equality
remain separate progress states. No percentage or total-function census should be
claimed unless the relevant measurement actually exists.
