# Whole-function linking for reviewed C candidates

Raw COFF extraction still rejects relocations. A function may instead declare an
explicit `linkage` record using `coff-ld-i386-v1`, with the complete list of
external symbol/address bindings reviewed against the pinned executable. A
binding does not establish its target's ABI, its original entry, or a data object's
extent; the function note must document those observations and uncertainties.

The native backend accepts autonomous C under the recorded `msvc71-o2` and
`msvc71-o2-frame` profiles. Headers, preprocessor directives, assembly, pragma
operators and extra nonempty code/data sections are outside this initial subset.
It compiles the source freshly, preserves the whole function and supported MSVC
metadata, and invokes real GNU ld 2.42 at the reviewed function address. It audits
every resolved DIR32/REL32/RVA32 word and every other retained byte. No original
bytes are inserted, patched, trimmed or normalized. Function boundaries and ABI
compatibility require independent review and a fresh original-byte comparison.

Each link uses a new ignored build directory. Its manifest records the source,
profile, compiler components, linker and dependencies, Python, parser, PE reader,
object, placement script, image and complete candidate. Match freshness also
checks the orchestration and schema identities. Failed match rebuilds remove the
previous per-function report. Unresolved bindings, ambiguous COFF, unsupported
sections, warnings and identity changes fail instead of yielding a partial body.

Only an initially absent default historical compiler permits the existing
explicit `build-all` portable fallback. Invalid explicit configuration and a
compiler disappearing after acquisition are hard failures. Individual native
matching and proof remain strict.

The portable backend resolves the same reviewed bindings with the registered
`clang-i686-scaffold` profile for source-only validation. It preserves every
admitted nonempty section; Clang's empty input sections may be excluded only after
checking zero size, relocations, line records and user symbols. Nonempty LLVM
auxiliary sections are rejected. Portable linked builds cannot qualify as exact
matches or original differential execution.

The supported host uses the genuine dynamically linked ELF GNU ld 2.42. The
inventories do not make Python/Bash dependencies recursively hermetic and do not
protect against hostile concurrent file replacement. Retained opaque MSVC debug
metadata depends on the build path. No full-program linkage or original-process
execution is established.
