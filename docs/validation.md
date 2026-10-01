# Validation ladder

**A — machine-code match.** Current primitive compares literal byte arrays and emits
an address-based Intel disassembly diff. Exact means identical bytes for the reviewed
region, excluding inspected alignment padding. Candidate sections must be isolated
and relocation-free. Same-size functions do not imply a match. Unknown instruction
and CFG metrics remain null. Future work: linked address placement, relocation-aware
comparison, instruction normalization, block boundaries and graph comparisons. A
normalized score is supporting evidence, not an exact-byte claim.

The initial exact proof set has four functions / 37 bytes. `make proof` verifies
all four, and an optional real-binary regression test changes a candidate in a
private source-only checkout to ensure the gate rejects it. The proprietary input
is read in place and never bundled with that checkout.

**B — differential function testing.** Future controlled execution of original and
candidate in a compatible 32-bit environment, including ABI, memory reads/writes,
register preservation and edge cases. Current native truth-table tests validate only
candidate semantics and layout. We have not loaded or called the original binary.

**C — deterministic simulation.** Later, identical maps, seeds and player commands
should produce identical serialized state at specified frame boundaries. Requires
sufficient reconstructed dependencies and carefully defined observable state.

**D — replay synchronization.** Later, original Brood War replays should remain in
sync against the original simulation. Binary code equality of a tiny leaf does not
establish replay compatibility.

No simulation, replay runner, whole-program emulation or modern port is being built
in phase 1. Tests protect the real pipeline against wrong targets, truncated PE data,
unbacked RVAs, unresolved relocations and misleading match reports; fixture bytes
are original synthetic test data, not game bytes.
