# Function counts and progress denominators

As of 2026-10-02, the [public BWAPI Broodwar.map at the inspected revision](https://github.com/bwapi/bwapi/blob/d727fed68558c506163048ea889131d8cbb33915/Release_Binary/Starcraft/bwapi-data/data/Broodwar.map)
contains **4,201 name/address/size entries and 4,201 distinct addresses**. All listed
starts fall inside an executable section of our pinned PE. None of these entries
has a zero declared size. Counting and section membership are measured observations;
we have not independently validated all 4,201 boundaries, prototypes or identities.

The map includes runtime/library routines and is not exhaustive: for example,
three routine-like regions at 0x004DC510/520/530 do not appear in it. Those regions
also lack independent entry references, so we do not promote them to exact functions.
The map count must not be labeled a verified total number of functions in the game.
A Ghidra census with reviewed split/merged boundaries and library classification
remains outstanding.

**504 verified exact functions / 4,201 community entries ≈ 12.00% by listed-function
count.** This is not a code-size, effort or completion percentage. The matches total
37,943 original bytes and were deliberately selected for low complexity. More complex
routines, dependencies and linking will have very different costs.

Reproduce the community count without storing the map in the public repository:

```sh
./tools/analysis/count-map /path/to/public/Broodwar.map --binary original/StarCraft.exe
```

The command emits aggregate metadata only and leaves `verified_total_program_functions`
null. The map's SHA-256 is included so a later upstream change cannot silently change
the denominator. Obtain the public text from the pinned reference above and keep
local research inputs under `.local/`. No community map or game binary is bundled.

`decomp status` counts the local catalog/discovery records, not the 4,201 external
map entries. There are currently 515 source candidates: 504 confirmed exact, 8 reviewed
mismatches and 3 uncorroborated regions, plus a PE-entry seed without a source candidate.

The exact count includes **76 static data initializers / 836 bytes** and **428 other
reviewed functions / 37,107 bytes**. The initializer destinations have unknown semantics;
identical copy patterns at distinct referenced entries do not demonstrate 76 distinct
gameplay systems. The [numeric milestone report](hundred-functions-2026-10-02.md)
separates the categories and explains the bounded selection.

By measured method, the exact aggregate consists of **389 isolated zero-relocation COFF functions / 24,232 bytes** and **108 standard-linked external-only C functions / 11,954 bytes**, plus **six compiled-component functions / 1,158 bytes**. The actual 126-byte, 450-byte and 263-byte dependencies are counted once among the external-only functions; the shared 73-byte path decoder is counted once among isolated functions. The restoration root also retains the 196-byte component decoder, counted once among component functions. The 196-byte decoder includes its reviewed 36-byte compiler switch table and one-byte alignment. A fourth method, [native MSVC LTCG](native-ltcg.md), adds one complete 599-byte query with its existing 83-byte C search dependency counted once among isolated functions. All four methods retain complete compiler contributions; no compiler context or auxiliary zero placement space is counted.

The 2026-10-05 integration adds 18 isolated functions / 1,953 bytes from the
[seventh historical lot](historical-seventh-2026-10-02.md) and
[REA trial](rea-trial-2026-10-04.md), preserving the concurrent linked batches.

The 864-byte path reference restorer remains non-exact and is excluded from the
exact total. Its 80 bounded emulator fixtures are separate evidence. The now-exact
599-byte rectangle query passes 380 comparisons with its actual C search callee;
see [compiled components](compiled-components.md).

The exact packing component adds two related functions / 292 bytes. It serializes
the same 1,000-entry pool used by the non-exact restoration candidate and passes
80 packing comparisons plus 80 chained packing/restoration comparisons.

Two further related functions add **200 exact bytes**: the pool initializer and
path-reference decoder. They pass 80 and 1,240 emulator comparisons respectively;
80 further cases cover initialization followed by packing and restoration.

The 100-record serialization component contributes two exact functions / 615 bytes
and passes 80 emulator comparisons of its complete 46,004-byte pool.

The related record restoration adds **248 exact bytes** and passes 80 comparisons
of its complete 460-byte record. Its pool caller remains outside the exact total.

The related 1,000-node list encoder/restorer add **two functions / 1,055 exact bytes**.
Each passes 80 complete-pool comparisons; another 80 run encoding then restoration.
They are independent external-only C contributions, counted once each.

Its initializer contributes **155 further exact bytes**, passing 80 standalone
comparisons and 80 initialization/encoding/restoration comparisons with all three
complete C functions exact. These are independent sequential contributions.

The 100-record pool initializer adds **205 exact bytes**, passing 80 standalone
comparisons and 80 initialization/encoding comparisons retaining the actual C
record encoder. Its pool restoration remains outside the exact total.
