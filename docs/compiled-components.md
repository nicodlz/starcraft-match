# Compiled dependencies and bounded differential execution

The next reconstruction target is larger routines and their real dependencies.
The pinned specimen remains SHA-256
`ad6b58b27b8948845ccfa69bcfcc1b10d6aa7a27a371ee3e61453925288c6a46`.

| Reviewed region | Original / compiled bytes | Literal result | Emulated fixtures |
| --- | ---: | --- | ---: |
| [sub_004308A0](functions/004308A0.md), rectangle query | 599 / 598 | Non-exact | 380 passed |
| [sub_00469B00](functions/00469B00.md), compiled dependency of the query | 83 / 83 | Exact, already counted | Included in query fixtures |
| [sub_00403780](functions/00403780.md), 1,000-entry reference restoration | 864 / 788 | Non-exact | 80 passed |

The two new candidates cover **1,463 reviewed original bytes** but contribute
**zero new exact functions or bytes**. Their catalog expectations remain exploratory.
The query's length difference is not a measure of byte similarity. Neither fixture
counts nor a source compilation result are exact-function evidence.

## Actual C dependencies

The `gnu-i386pe-component-v1` profile retains whole compiler-authored function
contributions at independently reviewed addresses. The first component comprises
the rectangle query and the existing independently written C binary search, compiled
in one translation unit so MSVC can choose their observed private EDI/EDX/stack ABI.
The search C source is included directly and tracked in the candidate's hash inventory;
it is not copied from the game. Every local call targets the actual emitted search
function. No external code address is substituted for it.

The adapter rejects external code bindings, defined-symbol rebinding, unsupported
relocations, incomplete helper extents, overlapping placements, unapproved code/data,
references to discarded contexts, unreachable retained functions, imports and base
relocations. It checks every DIR32/REL32 result and all nonrelocation bytes after
ordinary GNU linking. Each linked function keeps its whole virtual extent; file
alignment never counts as original code. The matcher separately requires every
retained dependency to equal its complete pinned region and match a reviewed ABI
record. A dependency is not counted again as a new function.

Nine external **data** declarations still bind original observed addresses. The
component is not a complete program and does not reconstruct initialized game data.
Two uncounted compiler contexts remain outside the image. Jump tables, retained
data contributions and arbitrary runtime dependencies are still unsupported.

```sh
source .local/tools/activate.sh  # Host-local paths, when installed
./tools/decomp match 0x004308A0
./tools/decomp match 0x00403780
```

Both commands currently report `exact_byte_match: false`; the first additionally
records its freshly checked compiled dependency. Existing isolated and external-only
matches retain their distinct methods and strict extraction gates.

## Local emulator comparison

The optional runner executes only the reviewed original function regions and the
candidate machine code in fresh Unicorn x86-32 instances. Original code is read from
the supported local executable. Candidate code comes from a fresh recorded-compiler
build; the linked query calls its compiled C dependency. Globals, tables, object
records and stack arguments are independently generated synthetic fixture state.
No original game process, imports, assets or whole-game initialization are executed.

Unicorn 2.1.4 was used locally. It is optional and is not a dependency of portable
`make` or `make proof`. Install it in a private environment if reproducing these tests:

```sh
python3 -m venv .local/components-venv
.local/components-venv/bin/pip install unicorn==2.1.4
source .local/tools/activate.sh
.local/components-venv/bin/python tools/validation/function-differential 0x004308A0
.local/components-venv/bin/python tools/validation/function-differential 0x00403780
```

The deterministic seed is 1161. Query fixtures include empty tables, tied coordinates,
single entries, 1,700 entries, reversed/degenerate/signed rectangles, extent expansion
and nonzero upper global bits. Restoration fixtures include 80 complete pools with
1,000 entries each, signed limits, absent bases and encoded-width/wrapping cases.
The runner compares return values when established, nonvolatile registers, stack
cleanup, mutable memory snapshots and ordered data-access addresses, widths and
values. Private stack temporaries, volatile registers and flags are outside equivalence.
An instruction bound rejects nontermination instead of treating it as a return.

A separately compiled query mutation changing `mark == 3` to `mark == 2` fails fixture
31 with different output memory, cursor and access trace. This checks that the runner
actually detects changes in the C candidate. The explicit private `--candidate-image`
override supports such regression experiments and records that no fresh build was
requested for the override. Reports and all generated artifacts stay ignored.

These finite mapped states provide a bounded differential result. They do not prove
universal semantic equivalence, arbitrary invalid-pointer behavior, native Windows ABI
execution, deterministic simulation or replay synchronization. General semantic and
CFG metrics remain null.

## Remaining byte work

The query still differs in register selection and instruction scheduling despite
identical data-access traces in the tested states. Restoration still differs in loop
induction and compiler allocation despite identical restored pools. The next byte
experiments should resolve these specific compiler/source layouts, preserve the
compiled search ABI, and add reviewed caller/callee dependencies. Enlarging these
connected components takes priority over collecting unrelated trivial leaves.
