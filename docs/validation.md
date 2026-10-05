# Validation ladder

**A — machine-code match.** Literal comparison includes every byte in a complete
reviewed function, including internal compiler alignment; only reviewed padding
outside that function is excluded. The default isolated extractor rejects relocations.
Explicit external-only and compiled-component profiles use ordinary linking, audit
all relocations and retain complete compiler contributions. Instruction normalization
never establishes exact equality. Similarity and CFG metrics remain null.

The current proof set has **483 functions / 32,313 bytes**. `make proof` freshly
recompiles all exact expectations. A local real-binary regression test deliberately
changes a candidate in a private source-only checkout to confirm rejection. The
proprietary input is read locally and never bundled with that checkout. Two new
larger candidates remain non-exact and add no bytes to this proof set.

**B — differential function testing.** A bounded emulator experiment now compares
the original rectangle query and its search callee with a linked C component across
380 synthetic fixtures, and original pool restoration with its C candidate across
80 complete 1,000-entry fixtures. Result checks cover the reviewed ABI, mutable
memory and ordered data-access addresses, widths and values. A deliberate C query
regression is rejected. See [scope and reproduction](compiled-components.md).

These tests execute reviewed original regions in Unicorn x86-32, with synthetic
mapped state. They do not launch or call an original Windows process, initialize the
game, or prove universal semantic equivalence. Private stack temporaries, volatile
registers/flags and unestablished return values are excluded from equivalence. Native
candidate-only truth tables remain source-side tests, distinct from this experiment.

**C — deterministic simulation.** Later, identical maps, seeds and player commands
should produce identical serialized state at specified frame boundaries. This needs
sufficient reconstructed dependencies and carefully defined observable state.

**D — replay synchronization.** Later, original Brood War replays should remain in
sync against the reconstructed simulation. Individual function byte equality or
bounded synthetic fixtures do not establish replay compatibility.

No simulation, replay runner, whole-program emulation or modern port is established.
Tests protect the pipeline against wrong targets, malformed input, incomplete
contributions, unresolved relocations and stale or misleading reports. Public
fixtures are independently written C and synthetic state; original code and generated
binary evidence stay in the ignored local research directories.
