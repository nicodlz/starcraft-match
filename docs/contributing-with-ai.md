# Contributing with AI agents

AI agents can investigate independent functions and try source/compiler variations
in parallel. Their output is a proposal until the evidence and compilation result
are reviewed. The pinned executable and fresh machine-code comparison remain the
authority. More agents do not justify weaker boundaries, guessed names presented
as facts, or inflated progress counts.

This guide describes a coordination workflow using existing scripts. There is no
implemented autonomous scheduler or repository-wide reservation service. See
[the task format and iteration primitive](agent-pipeline.md) and
[the contribution checklist](../CONTRIBUTING.md).

## Keep task inputs local

A generated task can contain original assembly, decompiler text, candidate source,
structure information and private matching reports. Export it to an ignored location:

```sh
./tools/decomp task 0x004020B0 --out analysis/tasks/004020B0.json
```

Keep original executables, assets, extracted bytes, full analysis exports and task
bundles out of Git and published artifacts. Do not send proprietary binary-derived
inputs to an external model service without the user's explicit authorization for
that scope. Permission to create public repository documentation or a pull request
does not authorize uploading private analysis. Share minimal task context with
agents operating in the authorized environment; do not expose unrelated local files,
credentials or personal data.

Reference projects may inform semantics and layouts, but must not become copied
candidate implementations. Agents should cite consulted sources and distinguish
community claims, binary observations and hypotheses.

## Reserve addresses and file ownership

Before starting parallel work, the coordinator records each agent's address set and
permitted paths in the team conversation or another agreed task record. Include:

- Executable SHA-256 and function addresses, with reviewed sizes or explicit unknowns.
- Evidence available, ABI assumptions and unresolved questions.
- Candidate source/doc paths owned by the agent.
- Shared files the agent must leave to the coordinator.
- Acceptance checks and where private proposed records/reports should be written.

Give each agent a small set of non-overlapping functions. Use separate worktrees when
available. If agents share a workspace, address reservations and path ownership must
be explicit. Reserve newly discovered addresses before editing their candidates;
an agent should report overlaps and hand back ownership rather than overwrite work.

Keep shared catalog/profile/tool changes with one integrator. An agent can propose
records in `.local/<task>-records.json` and a compiler profile in its task report;
the integrator reviews and merges those changes. Do not have every agent append to
`config/functions.json`, edit the README, or commit shared work concurrently.

## Run a bounded reconstruction experiment

An agent should inspect the task, verify hash/boundaries and audit relevant callers
before claiming an ABI. It should then independently write a minimal C/C++ candidate,
compile it, compare the complete region and inspect the differences. Compiler-profile
changes are legitimate experiments when recorded and reproducible. Narrow loads,
calling conventions and register allocation often matter even for simple functions.

Each iteration should retain the source and build provenance required to reproduce
its result. Use existing build/match commands after integration into the catalog:

```sh
./tools/decomp build 0x004020B0
./tools/decomp match 0x004020B0
```

Do not replace reconstruction with inline assembly, embedded original bytes or
post-processing the compiled function. Do not manually mark a mismatch as exact,
change the supported hash to evade validation, or accept a matching subsequence as
a complete function. Leave unavailable similarity metrics null. A changed source
invalidates an old report until compilation and comparison are repeated.

Return a concise handoff: owned files, proposed catalog/profile changes, observed
region and ABI evidence, fresh result, commands used, references and blockers.
If a function does not match, report the concrete difference and preserve useful
candidate work. A well-explained failed experiment is preferable to an invented score.

## Integrate independently

The integrator reviews each handoff before promoting it to the proof set:

1. Recheck the original specimen's hash and review the entry, complete body, returns
   and excluded padding. Confirm that community or analyzer boundaries were actually
   inspected. Ambiguous or noncontiguous bodies need further analysis.
2. Review caller evidence, argument/return width, stack cleanup, register contract,
   global access widths and source behavior. Byte equality alone cannot rescue an
   incorrectly described ABI or a region that omits part of the function.
3. Merge only the intended source, minimal declarations, function notes and reviewed
   catalog/compiler records. Verify independent authorship and source provenance.
4. Rebuild from the checked-in candidate with the pinned compiler profile and extract
   the original region directly from the accepted PE. Use a fresh report; do not
   trust the agent's success text or cached JSON as independent verification.
5. Run `make proof` after adding exact expectations, then run the ordinary tests and
   publication checks. Investigate failures before updating aggregate progress.

```sh
./tools/decomp match 0x004CE6C0 --require-exact
make proof
make
./tools/check-publication
./tools/check-publication --staged
```

The example getter is suitable for demonstrating the exact-match gate. Larger
functions may require additional analysis or matcher support; do not bypass a
relocation rejection or guess the function extent to make the command succeed.
Independent verification retains strict extraction by default. The explicit
external-only standard-linker method instead resolves approved references, checks
the entire compiler contribution and records its separate method; see
[standard linking](standard-linking.md).

## Measure useful progress

Report the reviewed functions and byte regions actually matched, with their compiler
profiles and limitations. Keep compiling candidates, exact matches, semantic tests
and original differential testing separate. A collection of tiny getters is a valid
proof of the loop, but not evidence that complex gameplay systems are reconstructed
or that a fixed percentage of the whole program is complete.

For experiments across a representative batch, record iteration time, compiler
variants tried, exact-match rate, review effort and recurring blockers. This supports
an evidence-based decision about further automation. Do not bulk-promote analyzer
seeds, runtime thunks or speculative implementations merely to increase counts.

Public updates should link reviewed source and notes. Private generated reports stay
ignored; summarize their measured results without uploading the original bytes or
full decompiler dumps. Modernization, new game behavior and a playable reimplementation
remain outside the matching project's current scope.
