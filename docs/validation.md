# Validation ladder

**A — machine-code match.** Literal comparison includes every byte in a complete
reviewed function, including internal compiler alignment; only reviewed padding
outside that function is excluded. The default isolated extractor rejects relocations.
Explicit external-only and compiled-component profiles use ordinary linking, audit
all relocations and retain complete compiler contributions. Instruction normalization
never establishes exact equality. Similarity and CFG metrics remain null.

The current proof set has **489 functions / 33,420 bytes**. `make proof` freshly
recompiles all exact expectations. A local real-binary regression test deliberately
changes a candidate in a private source-only checkout to confirm rejection. The
proprietary input is read locally and never bundled with that checkout. Two new
larger candidates remain non-exact and add no bytes to this proof set.

**B — differential function testing.** A bounded emulator experiment now compares
the original rectangle query and its search callee with a linked C component across
380 synthetic fixtures, and original pool restoration with its C candidate across
80 complete 1,000-entry fixtures. The exact packing component additionally passes
80 complete-pool fixtures and 80 packing-then-restoration comparisons. The latter
reuse packing inputs and check the resulting serialized/restored state, without
asserting that serialization preserves arbitrary input unchanged. The exact decoder
passes another 1,240 fixtures, the exact initializer passes 80, and 80 more execute
initialization, packing and restoration. A mutation rejecting equality at the path
limit changes EAX and is detected. The 615-byte 100-record serialization component
passes 80 further comparisons of all 46,004 pool bytes. Result checks cover the reviewed ABI, mutable
memory and ordered data-access addresses, widths and values. Deliberate C query
and omitted-final-entry packing regressions are rejected. See [scope and reproduction](compiled-components.md).

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
