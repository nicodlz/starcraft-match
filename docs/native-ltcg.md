# Native MSVC 7.1 link-time compilation

The rectangle query [sub_004308A0](functions/004308A0.md) now matches its complete
**599-byte** region, including its four calls to the actual **83-byte** C search
dependency. Native Microsoft LINK **7.10.3077** generates both functions from
independently written C intermediate input produced by CL **13.10.3077** `/GL`.
The C algorithm is unchanged from the earlier ordinary-COFF candidate; link-time
compilation resolves its remaining instruction-ordering difference.

This is a separate measured method, `native-msvc71-ltcg-c-component`, rather than
an extension of the ordinary COFF relocation proof. `/GL` input is opaque compiler
intermediate material. The adapter does not pretend to parse native instructions
or relocation records from that format.

## Whole contributions and placement

The source selects `.text$b` for the whole query and `.text$d` for the whole search
function. A separately generated layout COFF contains two zero-only placement
sections and ten reviewed absolute **data** symbols. It contains no game function,
instruction implementation, original-byte input or ABI shim. The placement sections
put both actual generated C functions at their reviewed original addresses. Their
zero bytes are not compared with the game and contribute no exact functions or bytes.

The native linker receives the unchanged intermediate object and the independent
layout object, with `/DLL /NOENTRY /NODEFAULTLIB /LTCG /FIXED /MACHINE:X86`, an image
base of `0x00400000` and 16-byte section/file alignment. `/INCLUDE` retains the root
and layout symbols; no exports, imports or base relocations are present. The native
linker emits its normal image timestamp, recorded through the output hash. Whole
function comparisons do not depend on that timestamp. The resulting low-alignment
image is an analysis artifact, not a Windows game executable.

The adapter checks the native map's **complete 599- and 83-byte contributions**,
their symbols, ownership, offsets and placements. It rejects any omitted, shortened,
overlapping or additional contribution, unexpected symbol, incorrect data binding,
import, base relocation or nonzero placement byte. Complete instruction decoding
checks direct calls to retained C function entries, internal branch destinations
and reachability of every dependency. Indirect control flow is currently unsupported.
The ordinary pinned-binary matcher then compares every byte of both contributions.
It performs no trimming, instruction normalization or post-build object/image patch.

Build manifests pin source/includes, compiler flags, CL and its DLLs, wibo, native
LINK, its driver, Wine runner, the supplied immutable Wine runtime tree, intermediate
object, auxiliary layout, native map and complete output image. Any replacement
invalidates freshness. The mutable private Wine prefix is kept outside the runtime
identity tree; ambient compiler/linker options and Wine DLL overrides are cleared.

## Local tooling and reproduction

The native profile remains optional. It requires a legally supplied Toolkit 2003
toolchain and a working private **32-bit Wine** runtime. No Microsoft or Wine binaries
are distributed by this repository. Supply the ordinary `SC_MSVC71_BIN` and `SC_WIBO`
settings, plus absolute local paths:

```sh
export SC_WINE32=/absolute/path/to/private/wine-runner
export SC_WINE32_RUNTIME_ROOT=/absolute/path/to/immutable/wine-runtime
export SC_WINE32_PREFIX=/absolute/project/.local/wine-prefix
# When a relocated runtime needs explicit search paths:
export SC_WINE32_DLLPATH=/absolute/path/to/runtime/i386-windows
export SC_WINE32_LIBRARY_PATH=/absolute/path/to/runtime/i386-linux-gnu

./tools/compilers/mslink71 --identity-json
./tools/decomp match 0x004308A0 --require-exact
make
make proof
```

The runtime identity root must include the runner's runtime files and must exclude
the mutable prefix. File symlinks must resolve inside that immutable tree. Wine must
already initialize and load its libraries correctly; the driver does not install it.
The local experiment used publisher-index-verified Ubuntu Wine **9.0** packages,
extracted privately, with loader paths relocated for local execution. Native linker
operation required no Wine API source changes. Compilation still uses the existing
wibo 1.2.0 runner. A missing native runtime permits only the explicit portable
source-compilation fallback in `build-all`; it cannot produce exact evidence.

The optional Unicorn runner passes **380 bounded comparisons** of the exact native
query/search pair, including outputs, ABI and ordered memory accesses. A separately
compiled C mutation changing the first-axis strict filter from `>` to `>=` is
rejected in fixture 164 through its ordered memory accesses. The mutant retains
the complete 599-byte contribution and the exact C callee. These
fixtures do not establish original-process execution or universal equivalence.

## Compiler-mode evidence

An independent one-function synthetic experiment compared classic C, classic C++,
`/GL` C and `/GL` C++ using the same compiler/linker build. Classic compiler records
identify product/build pairs **95/3077** and **96/3077** respectively. Native `/LTCG`
images identify **99/3077** for C and **100/3077** for C++ in their decoded Rich headers.
The pinned game header contains **100/3077 with count 289**, alongside **95/3077 with
count 152** and **96/3077 with count 3**. This supports investigating mixed ordinary
and C++ link-time compiler inputs; those counts are linker metadata, not a verified
function census or proof of the original source or every original optimization flag.
The new exact C query establishes this candidate's measured code generation only.
