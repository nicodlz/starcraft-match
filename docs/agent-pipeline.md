# Minimal agent iteration primitive

The unit of work is a function **region tied to an executable SHA-256**, not a
semantic name. `config/functions.json` is the reviewed JSON database; each record
follows `config/function.schema.json`. It is intentionally small and can later be
migrated to SQLite without changing address/hash identity. Analysis discoveries
live separately in ignored `analysis/functions.json` and optional Ghidra exports.
Never promote an analyzer guess to a verified boundary automatically.

Working commands:

```sh
./tools/decomp next
./tools/decomp show 0x004020B0
./tools/decomp task 0x004020B0 --out analysis/tasks/004020B0.json
./tools/decomp build 0x004020B0
./tools/decomp match 0x004020B0
./tools/decomp status
./tools/decomp verify-matches  # Rebuild and enforce the exact proof set
```

A task export adds original assembly, candidate text, structures, calls, prototype,
ABI, provenance and the latest match report to the reviewed record. Decompiler
output is null until a real Ghidra result is supplied. `match_report` is a snapshot:
rerun after any edit; do not treat an old report as current evidence.
Original/decompiler text and machine bytes must remain local and must not be sent
to an external agent service or published without the user's explicit scope.

An agent working locally should:

1. Check hash, exact region and all evidence classifications. Request human boundary
   review if function start/end or noncontiguous body membership is ambiguous.
2. Read only the task's dependencies and minimal known layouts. Preserve behavior,
   bugs, limits and memory side effects; keep uncertain names as `sub_XXXXXXXX`.
3. Change one candidate and, when necessary, its compiler profile. Each build has
   one function in an isolated executable section. Calls/globals with relocations
   require a later linker/relocation adapter; current extraction refuses them.
4. Build and match; inspect literal differences and manifest. Unavailable scores
   stay null. Never replace the candidate with copied assembly merely to claim a
   successful C reconstruction.
5. Record a small reviewable change and rationale. Update confidence only from
   evidence. Retain the known-good catalog if discovery outputs change.

The compile manifest records command, target flags, compiler version/binary hash, function-record and source/header
hashes and extracted candidate hash. Original machine code is extracted directly
from the pinned PE at every match; there is no cache of unchecked original bytes.
Output paths are restricted to ignored analysis/build/.local directories. The COFF
extractor rejects unresolved relocations, nonzero symbol offsets and shared function
sections. It does not guess symbol length from padding. For this isolated Clang
function the section extent was inspected against its return instruction.

Progress reports count observed catalog/discovery records, not an estimated total
number of game functions. Identified, neutral names, prototype, source, compiling,
semantic evidence, partial assembly scores and exact match are separate concepts.
Unavailable total/partial-match metrics are null. The current named count is zero
because no original name is known. `compiling` currently means a successful, fresh
build recorded by a match report; a build-only invocation is not counted. Exact
match requires literal bytes and a compatible ABI. Semantic truth-table tests of
the candidate alone do not increment original differential equivalence.

A future scheduler can add immutable task revisions, function ownership, queue
priorities, compiler artifact hashes, reviewer decisions and SQLite storage once
10–100 real functions demonstrate useful iteration. No autonomous scheduler,
external agent upload, modernization branch or full-game build exists yet.


The four proof functions have `match_expectation: "exact"`. This is a regression
expectation, not a cached result: `verify-matches` compiles and compares every one
against the pinned PE each time, and fails on byte inequality or incompatible ABI.
It removes an earlier aggregate success before starting, so a failed run cannot
leave an old successful proof file behind. `match ADDRESS --require-exact` provides
the same gate for a single task. Ordinary exploratory `match` still returns a useful
diff without treating expected non-equality as a command error. Exact status counters
use fresh local reports, not merely the catalog's recorded historical status.
