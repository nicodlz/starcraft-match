# Environment inspection and local tool setup

Initially inspected 2026-10-01; availability updated 2026-10-02. The starting directory was empty, without Git history,
AGENTS.md or an executable. The executable search was restricted to this workspace,
three levels deep; unrelated personal directories were not scanned.

Host: Ubuntu 24.04.4 LTS, x86_64, Linux 6.8.0-136-generic.

| Tool | Observed availability | Role |
| --- | --- | --- |
| Python | 3.12.3; standard library, no pip | PE reader, JSON catalog, CLI, tests |
| GCC / G++ | 13.3.0 | Native candidate truth-table tests |
| Clang / Clang++ | 18.1.3 | Windows i686 COFF scaffold; no SDK needed for this function |
| CMake | 3.28.3 | Available; unnecessary for isolated compiler invocations |
| GNU objdump | Binutils 2.42 | Original and candidate x86 disassembly |
| LLVM tools | Versioned `llvm-objdump-18`, `llvm-readobj-18`, `llvm-objcopy-18`, etc. | Optional PE/COFF investigation |
| Git | 2.43.0 | Source tracking and local publication guard |
| Ghidra / analyzeHeadless | 12.1.4 under `.local/tools/`; activate the local environment below | Validated headless discovery and decompilation |
| radare2 / rizin | Not found in PATH | Optional alternative analysis |
| Java / javac | Temurin JDK 21.0.12.1+1 under `.local/tools/` | Validated Ghidra runtime and script compiler |
| Wine | Not found in PATH | Historical Windows compiler execution / later differential tests |
| Ninja | Not found in PATH | Not required |
| Historic MSVC / wibo | MSVC 13.10.3077 and wibo 1.2.0 locally available | Recorded historical exact-matching profiles |

No optional tools were installed during the initial inspection. Python, Clang and objdump suffice for the working
analysis → isolated compile → byte/disassembly comparison primitive. `make` is a
convenience layer; each command can also be run directly.

Following the user's explicit download request, the competition distribution was
retrieved and only its executable extracted. See [binary provenance](binary-provenance.md).

## Local reverse-engineering setup, 2026-10-02

Following the user's installation request, the official
[Ghidra 12.1.4 release](https://github.com/NationalSecurityAgency/ghidra/releases/tag/Ghidra_12.1.4_build)
and Eclipse Temurin JDK **21.0.12.1+1-LTS** were installed under ignored
`.local/tools/`. Downloaded archives remain under ignored `downloads/tools/`.
Both archive SHA-256 values were checked against the upstream release metadata:

| Archive | SHA-256 |
| --- | --- |
| Ghidra 12.1.4 | `ddac49f903da9d5bac833e5cc79395098b9c33cfd3279be5f31bd00387d2d4db` |
| Temurin JDK 21.0.12.1+1 | `ce79869e1307ed8ee1e2baa86a412b1eb5b75d10a01006d788a6f968bcfaee94` |

The existing local MSVC **13.10.3077** and **wibo 1.2.0** were made available at
the adapter's default `.local/toolchains/` paths through local symlinks. No
compiler components or recorded compiler profiles were changed. LLVM 18 tools,
GNU objdump and GDB were already available.

Activate this host's setup from the repository root:

```sh
source .local/tools/activate.sh
./tools/ghidra/run-headless
```

The activation script sets `JAVA_HOME`, `GHIDRA_HOME`, `PATH`, `SC_MSVC71_BIN`
and `SC_WIBO`. Explicit historical toolchain paths also support the regression
test's temporary source checkout. The script and installation manifest are local
configuration, not files supplied by a fresh clone.

Headless import, auto-analysis and the Java export completed against the pinned
SHA-256 in `config/target.json`. The private export contains 4,644 function
hypotheses with decompiler output, including 373 multi-range bodies, plus 50,643
symbols and 1,277 strings. None of these discoveries has been promoted to the
reviewed catalog. `make` passes all 20 tests, and `make proof` freshly verifies
the existing 212 exact functions / 6,145 bytes.
