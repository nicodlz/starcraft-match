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

**483 verified exact functions / 4,201 community entries ≈ 11.50% by listed-function
count.** This is not a code-size, effort or completion percentage. The matches total
32,313 original bytes and were deliberately selected for low complexity. More complex
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
map entries. There are currently 492 source candidates: 483 confirmed exact, 6 reviewed
mismatches and 3 uncorroborated regions, plus a PE-entry seed without a source candidate.

The exact count includes **76 static data initializers / 836 bytes** and **407 other
reviewed functions / 31,477 bytes**. The initializer destinations have unknown semantics;
identical copy patterns at distinct referenced entries do not demonstrate 76 distinct
gameplay systems. The [numeric milestone report](hundred-functions-2026-10-02.md)
separates the categories and explains the bounded selection.

By measured method, the exact aggregate consists of **385 isolated zero-relocation COFF functions / 23,672 bytes** and **98 standard-linked external-only C functions / 8,641 bytes**. Whole compiler contributions are retained for both methods; linking resolves only reviewed external symbols and counts no dependency implementations or compiler contexts.

The 2026-10-05 integration adds 18 isolated functions / 1,953 bytes from the
[seventh historical lot](historical-seventh-2026-10-02.md) and
[REA trial](rea-trial-2026-10-04.md), preserving the concurrent linked batches.

Two larger non-exact candidates cover 1,463 additional reviewed original bytes;
these bytes are excluded from the exact total. One candidate retains the real
compiled 83-byte search dependency, already counted above. Their 460 bounded
emulated differential fixtures are a separate result; see
[compiled components](compiled-components.md).
