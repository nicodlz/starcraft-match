# Headless analysis

Install an official Ghidra release and the JDK it requires. Set `GHIDRA_HOME`.
Run `./tools/ghidra/run-headless`. This imports the pinned executable, performs default
auto-analysis, runs `ExportResearch.java`, and deletes the transient project.
The local export under `analysis/ghidra/<sha256>/` contains function bodies,
disassembly, decompiler text, direct calls, incoming references, strings, and symbols.
A manifest records Ghidra version, language, compiler spec, and binary identity.
For reproducible results use the same Ghidra/JDK release; defaults can change.

Ghidra and Java were absent on the initial host. The exporter is supplied but has
**not been executed or compiled here**. Validating it with a pinned official release
is a remaining milestone. It is optional for the working PE/COFF/diff pipeline.

Exported function boundaries, conventions, prototypes and names remain hypotheses.
Multi-range bodies must not be flattened into a contiguous region using their size.
Review start/end and provenance before adding a function to `config/functions.json`.
The CLI does not automatically import Ghidra guesses into the reviewed catalog.
All exports are private, ignored by Git, and unsuitable as publication bundles.
