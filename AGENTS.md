# Agent instructions

This repository reconstructs **StarCraft: Brood War 1.16.1, Windows i386** through
matching decompilation. Read README.md, CONTRIBUTING.md and
`docs/contributing-with-ai.md` before changing a candidate.

## Scope and evidence

- Match the pinned executable, not a clean reimplementation or modern port.
- Keep original behavior, limits, bugs, access widths and observed calling conventions.
- Tie every function claim to the SHA-256 in `config/target.json` and a reviewed region.
- Separate binary observations, community names, reimplementation analogues and hypotheses.
- Use neutral `sub_XXXXXXXX` names. Put proposed semantic names in the catalog separately.
- Padding or a plausible decompilation alone does not prove a function entry. Keep
  uncorroborated regions exploratory and out of the exact-function milestone.
- Do not copy third-party implementations, private source snapshots or leaked source.
- Do not insert original bytes, inline assembly copies, or post-build patches to claim
  that a C candidate matches. If a future assembly ABI shim is needed, document its
  scope and keep its result separate from a C-derived function match.

## Local-only material

`original/`, `downloads/`, `analysis/`, `build/` and `.local/` are private, ignored
research directories. Never stage them, force-add them, upload them as CI artifacts,
attach them to issues, or include them in a source release. Read legally available
originals in place. Do not search unrelated personal directories.

The source tree, hand-reviewed small function notes, public reference links, schemas
and independent tooling are publishable project material. Run the publication guard
before committing. External service uploads and GitHub pushes require user
instructions authorizing that action; existing session authorization remains valid.

## Work and validation

1. Inspect the catalog before choosing an address; read its function note and task.
2. Change one candidate at a time with the smallest necessary layout/profile changes.
3. Build using the recorded compiler profile. Unresolved relocations must be rejected,
   not ignored. Do not trim or normalize bytes and call the result exact.
4. When the executable is available, run `./tools/decomp match ADDRESS` and inspect
   its fresh report. Use `--require-exact` only for a reviewed exact expectation.
5. Run `make` for source compilation and portable tests. Run `make proof` locally
   when the supported executable is available, and `./tools/check-publication --staged`
   before a commit. Public CI cannot reproduce game-byte comparisons without that input.
6. Update the per-function document and catalog with what was measured. Missing metrics
   stay null; a source-only test is not original differential execution.

A compiler/profile/source/header change invalidates old evidence. The coordinator
must rebuild; do not trust a sub-agent's cached success report. Optional Ghidra
integration was validated locally with Ghidra 12.1.4 and JDK 21 on 2026-10-02;
its discovery results still require independent boundary and ABI review.

## Parallel work

When the user requests parallel agents, reserve disjoint function addresses and
owned paths. Worker agents create their candidates and notes; the coordinator owns
shared catalogs, compiler profiles, progress reporting and publication. Workers may
submit provisional records under ignored `.local/`. The coordinator reviews boundary
and ABI evidence and independently recompiles the accepted functions before merging.
Do not launch an unlimited scheduler or expand the task into modernization.

## Reporting

Lead with measured outcomes: exact functions/bytes, tests run, remaining uncertainties.
Do not imply a playable game, full-program linking, original-process execution, or a
complete compiler reconstruction. Keep changes small and commits reviewable.
