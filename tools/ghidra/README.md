# Headless analysis

Install an official Ghidra release and the JDK it requires. Set `GHIDRA_HOME`.
Run `./tools/ghidra/run-headless`. This imports the pinned executable, performs default
auto-analysis, runs `ExportResearch.java`, and deletes the transient project.
The local export under `analysis/ghidra/<sha256>/` contains function bodies,
disassembly, decompiler text, direct calls, incoming references, strings, and symbols.
A manifest records Ghidra version, language, compiler spec, and binary identity.
For reproducible results use the same Ghidra/JDK release; defaults can change.

## Validated local setup

On 2026-10-02, official **Ghidra 12.1.4** and Eclipse Temurin
**JDK 21.0.12.1+1-LTS** were installed locally. The pinned executable was imported
and auto-analyzed successfully; `ExportResearch.java` compiled and completed with
exit status zero. The manifest records `x86:LE:32:default` and compiler spec `windows`.
The export contains 4,644 function hypotheses, all with decompiler output,
50,643 symbols and 1,277 strings. There are 373 multi-range function bodies.
Successful decompilation does not establish correctness; Ghidra also reported an
unreadable-address warning while decompiling `0x004F2A70`.

On this host, activate the ignored local configuration from the repository root:

```sh
source .local/tools/activate.sh
./tools/ghidra/run-headless
```

Fresh clones must install Ghidra and its JDK separately and set `GHIDRA_HOME`.
See [environment](../../docs/environment.md) for versions and archive checksums.
The transient project lives under ignored `analysis/ghidra/projects/` because
Ghidra rejects project paths with dot-prefixed components such as `.local/`.
Ghidra remains optional for the working PE/COFF/diff pipeline.

Exported function boundaries, conventions, prototypes and names remain hypotheses.
Multi-range bodies must not be flattened into a contiguous region using their size.
Review start/end and provenance before adding a function to `config/functions.json`.
The CLI does not automatically import Ghidra guesses into the reviewed catalog.
All exports are private, ignored by Git, and unsuitable as publication bundles.
