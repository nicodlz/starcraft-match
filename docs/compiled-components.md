# Compiled dependencies and bounded differential execution

The next reconstruction target is larger routines and their real dependencies.
The pinned specimen remains SHA-256
`ad6b58b27b8948845ccfa69bcfcc1b10d6aa7a27a371ee3e61453925288c6a46`.

| Reviewed region | Original / compiled bytes | Literal result | Emulated fixtures |
| --- | ---: | --- | ---: |
| [sub_00414290](functions/00414290.md), unsigned eight-neighbor WORD count | 431 / 431 | Exact external-only link | 976 passed |
| [sub_00404410](functions/00404410.md), typed 1,000-record pool restorer | 92 / 92 | Exact with both C dependencies | 80 + 80 chained |
| [sub_00432810](functions/00432810.md), typed record decoder with complete switch table | 196 / 196 | Exact with actual C path decoder | 80 passed |
| [sub_00404350](functions/00404350.md), typed 1,000-record pool encoder | 187 / 187 | Exact with actual C callee | 80 passed |
| [sub_004328E0](functions/004328E0.md), five-type record encoder | 263 / 263 | Exact, counted once | 80 passed |
| [sub_00403DB0](functions/00403DB0.md), related list initialization | 155 / 155 | Exact | 80 + 80 lifecycle |
| [sub_00403E50](functions/00403E50.md), 1,000-node list encoder | 915 / 915 | Exact | 80 + 80 chained |
| [sub_004041F0](functions/004041F0.md), related list restorer | 140 / 140 | Exact | 80 + 80 chained |
| [sub_004308A0](functions/004308A0.md), rectangle query | 599 / 599 | Exact, native LTCG | 380 passed |
| [sub_00469B00](functions/00469B00.md), compiled dependency of the query | 83 / 83 | Exact, already counted | Included in query fixtures |
| [sub_004036D0](functions/004036D0.md), pool packing caller | 166 / 166 | Exact, new | 80 + 80 chained |
| [sub_00438240](functions/00438240.md), compiled unit/path encoder | 126 / 126 | Exact, new, counted once | Included in packing fixtures |
| [sub_00404550](functions/00404550.md), 100-record pool initialization | 205 / 205 | Exact | 80 + 80 initialization/encoding |
| [sub_00404620](functions/00404620.md), 100-record pool packing caller | 165 / 165 | Exact | 80 passed |
| [sub_00403AE0](functions/00403AE0.md), compiled list/unit encoder | 450 / 450 | Exact, counted once | Included in 100-record pool fixtures |
| [sub_00403CB0](functions/00403CB0.md), related list/unit restoration | 248 / 248 | Exact | 80 passed |
| [sub_00403650](functions/00403650.md), pool initialization | 127 / 127 | Exact | 80 + 80 lifecycle |
| [sub_00437290](functions/00437290.md), related path decoder | 73 / 73 | Exact | 1,240 passed |
| [sub_00404280](functions/00404280.md), typed 1,000-record pool initialization | 198 / 198 | Non-exact | 80 + 80 initialization/encoding/restoration |
| [sub_00403780](functions/00403780.md), 1,000-entry reference restoration | 864 / 788 | Non-exact | 80 passed |

The rectangle query contributes **599 exact bytes** through the separate
[native MSVC LTCG method](native-ltcg.md), with its 83-byte C callee counted once.
The 864-byte path restoration remains exploratory and contributes no exact bytes.
Fixture counts and source compilation remain distinct from byte equality.

The new packing component contributes **two exact functions / 292 bytes**. Its
caller and callee both retain their complete original regions, with an actual C
call between them. The existing restoration candidate is still non-exact.

## Actual C dependencies

The `gnu-i386pe-component-v1` profile retains whole compiler-authored function
contributions at independently reviewed addresses. The native LTCG component comprises
the rectangle query and the existing independently written C binary search, compiled
in one translation unit so MSVC can choose their observed private EDI/EDX/stack ABI.
The search C source is included directly and tracked in the candidate's hash inventory;
it is not copied from the game. Every local call targets the actual emitted search
function. No external code address is substituted for it.

The GNU adapter rejects external code bindings, defined-symbol rebinding, unsupported
relocations, incomplete helper extents, overlapping placements, unapproved code/data,
references to discarded contexts, unreachable retained functions, imports and base
relocations. It checks every DIR32/REL32 result and all nonrelocation bytes after
ordinary GNU linking. Each linked function keeps its whole virtual extent; file
alignment never counts as original code. The matcher separately requires every
retained dependency to equal its complete pinned region and match a reviewed ABI
record. A dependency is not counted again as a new function.

The second serialization component retains the complete 450-byte list/unit encoder
and its 165-byte caller. A paired Header C view reproduces the observed ordering
without volatile qualifiers. It has one external data symbol and no code binding.

A further **450-byte serialization component** retains the 187-byte caller and
263-byte typed record encoder. Its five external data bindings preserve unchecked
BYTE owner selectors and signed WORD limits. Both functions pass 80 comparisons;
1699-unit-limit and 999-record mutations are detected. Its paired
initializer is not included in the exact chain. The restoration chain adds a
92-byte root and a 196-byte record decoder retaining its actual 73-byte C path
decoder. It passes 80 full-pool comparisons and 80 encoding/restoration chains.

The query binds nine external **data** declarations to observed addresses. The
packing component has one external data binding and no external code binding.
These components do not reconstruct a complete program or initialized game data.
Uncounted compiler contexts remain outside each image. Compiler-emitted static
labels and tables inside the same complete function contribution support DIR32
references only when symbol offsets plus signed addends remain within that
contribution. Cross-contribution interior references and label REL32 relocations
remain rejected. Every linked relocation and unchanged nonrelocation byte is
checked. Synthetic independently compiled C label fixtures test successful linking
and rejection of escaping offsets, relative labels and references across sections.
Separately emitted tables/data contributions and arbitrary runtime dependencies
remain unsupported.

```sh
source .local/tools/activate.sh  # Host-local paths, when installed
./tools/decomp match 0x004308A0
./tools/decomp match 0x00403780
./tools/decomp match 0x004036D0 --require-exact
./tools/decomp match 0x00438240 --require-exact
```

The query/restoration commands report `exact_byte_match: false`; the query also
records its freshly checked compiled dependency. Packing and its encoder report
`exact_byte_match: true`. Existing isolated and external-only
matches retain their distinct methods and strict extraction gates.

## Local emulator comparison

The optional runner executes only the reviewed original function regions and the
candidate machine code in fresh Unicorn x86-32 instances. Original code is read from
the supported local executable. Candidate code comes from a fresh recorded-compiler
build; the linked query calls its compiled C dependency. Globals, tables, object
records and stack arguments are independently generated synthetic fixture state.
No original game process, imports, assets or whole-game initialization are executed.

The full integration regression passes **3,140 bounded comparisons across 21
execution modes**, including individual records, complete pools and chained
initialization/encoding/restoration. Overlapping function coverage is counted as
separate execution comparisons, not additional exact functions.

Unicorn 2.1.4 was used locally. It is optional and is not a dependency of portable
`make` or `make proof`. Install it in a private environment if reproducing these tests:

```sh
python3 -m venv .local/components-venv
.local/components-venv/bin/pip install unicorn==2.1.4
source .local/tools/activate.sh
.local/components-venv/bin/python tools/validation/function-differential 0x00404410
.local/components-venv/bin/python tools/validation/function-differential 0x00432810
.local/components-venv/bin/python tools/validation/function-differential 0x00404350 --roundtrip
.local/components-venv/bin/python tools/validation/function-differential 0x00404350
.local/components-venv/bin/python tools/validation/function-differential 0x004328E0
.local/components-venv/bin/python tools/validation/function-differential 0x004308A0
.local/components-venv/bin/python tools/validation/function-differential 0x00403780
.local/components-venv/bin/python tools/validation/function-differential 0x004036D0
.local/components-venv/bin/python tools/validation/function-differential 0x004036D0 --roundtrip
.local/components-venv/bin/python tools/validation/function-differential 0x00437290
.local/components-venv/bin/python tools/validation/function-differential 0x00403650
.local/components-venv/bin/python tools/validation/function-differential 0x004036D0 --initialize --roundtrip
.local/components-venv/bin/python tools/validation/function-differential 0x00404620
.local/components-venv/bin/python tools/validation/function-differential 0x00404550
.local/components-venv/bin/python tools/validation/function-differential 0x00404620 --initialize
.local/components-venv/bin/python tools/validation/function-differential 0x00403CB0
.local/components-venv/bin/python tools/validation/function-differential 0x00403E50
.local/components-venv/bin/python tools/validation/function-differential 0x004041F0
.local/components-venv/bin/python tools/validation/function-differential 0x00403E50 --roundtrip
.local/components-venv/bin/python tools/validation/function-differential 0x00403DB0
.local/components-venv/bin/python tools/validation/function-differential 0x00403E50 --initialize --roundtrip
```

The deterministic seed is 1161. Query fixtures include empty tables, tied coordinates,
single entries, 1,700 entries, reversed/degenerate/signed rectangles, extent expansion
and nonzero upper global bits. Restoration fixtures include 80 complete pools with
1,000 entries each, signed limits, absent bases and encoded-width/wrapping cases.
Packing fixtures cover shuffled free lists of 0..1,000 entries, unit serial bytes,
out-of-range unit pointers, unchecked BYTE pool selectors 8/255 and signed limits.
An additional 80 comparisons execute packing then restoration in each emulator.
`all_regions_exact` remains false for that chain because restoration is non-exact;
its build and code hash are recorded separately. The roundtrip checks original/C
results, not identity of arbitrary input before and after serialization.
The 100-record component adds 80 comparisons over a separate 46,004-byte pool,
with free-list lengths 0..100, unit serial BYTE values, wrapping subtraction and
unaligned heads. Its EBX argument is checked for preservation like the other
nonvolatile registers, and the complete compiled child must match before execution.
Its 205-byte initializer adds 80 complete-pool comparisons and 80 initialization/
encoding comparisons, with the initializer and both component regions exact.
Restoration is excluded while the pool restorer remains non-exact. A compiled
97-middle-record initialization mutation is detected in fixture 0.
The related 1,000-node list contributes 915-byte encoding and 140-byte restoration
functions, each independently linked with two external data symbols. They pass 80
comparisons each and 80 sequential encoding/restoration comparisons over 24,004
bytes. Both whole C contributions are exact. This chain is not a retained callee
component or a reconstruction of the original file-writing caller. The related
155-byte initializer passes 80 full-pool cases and 80 initialization/encoding/
restoration comparisons, also with all three C regions exact. A compiled mutation
initializing 997 middle nodes is detected in fixture 0. The compiler-only
barrier in the explicit five-record encoder emits no hardware fence or external call.
Mutations omitting the final five nodes or narrowing the decode mask fail fixture 0.
The related 248-byte record restoration adds 80 complete 460-byte comparisons
with an explicitly assigned EAX input, null and wrapping heads, and masked unit
indices including zero under a nonzero serial. Its 115-byte pool caller remains
non-exact in private research and is excluded from component totals.
The initializer adds 80 complete-pool comparisons and 80 lifecycle comparisons
(initialization, packing, restoration). Its independent build is recorded for the
chain. Initialization replaces the initial free list with all 1,000 entries;
`all_regions_exact` remains false while restoration differs.
The decoder adds 1,240 comparisons covering BYTE quotient narrowing, wrapped
DWORD inputs, signed limits and absent bases. Its ECX input is assigned explicitly;
ECX remains volatile, while EBX/ESI/EDI/EBP are checked for preservation.
The runner compares return values when established, nonvolatile registers, stack
cleanup, mutable memory snapshots and ordered data-access addresses, widths and
values. Private stack temporaries, volatile registers and flags are outside equivalence.
An instruction bound rejects nontermination instead of treating it as a return.

A separately compiled query mutation changing `mark == 3` to `mark == 2` fails fixture
31 with different output memory, cursor and access trace. This checks that the runner
actually detects changes in the C candidate. A separately compiled packing mutation omitting the final entry fails fixture 0
in the complete pool and access trace. The explicit private `--candidate-image`
override supports linked-component regression experiments and records that no fresh build was
requested for the override. Reports and all generated artifacts stay ignored.

A separately compiled 100-record packing mutation processing only 99 records
fails fixture 0 in the complete pool and access trace; its unchanged compiled
450-byte dependency is still required to match before executing the mutation.

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

The typed 44-byte record pool now has 80 standalone initialization comparisons
and 80 complete initialization/encoding/restoration comparisons over 44,004 bytes.
The chain contains six reviewed regions totaling 1,009 original bytes; five
regions totaling 811 bytes match exactly, while the 198-byte initializer remains
non-exact. Its compiler-only write barrier preserves the observed memory-access
order. A compiled 997-middle-record mutation fails fixture 0 in both memory and
access order. Run the chain with `0x00404350 --initialize --roundtrip`; its
`all_regions_exact` remains false. No complete initialization or save caller is
claimed from these sequential component executions.

The eight-neighbor WORD counter passes 976 cases, including all 256 center
predicate masks, zero dimensions, grid boundaries and unsigned coordinate wrap.
Its two stack DWORD arguments and RET8 cleanup are checked explicitly. A source
mutation testing `0020` instead of `0010` fails fixture 0 on the full EAX result.
Run it with `tools/validation/function-differential 0x00414290` in the optional
emulator environment. This is a whole external-only C contribution with no
retained game callee.
